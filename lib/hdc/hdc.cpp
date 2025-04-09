#include "hdc.h"
#include <QDebug>
#include "ptyqt.h"
#include "quuid.h"
#include <QProcess>
#include <QImage>
#include <QDir>
#include <QCoreApplication>
#include <QtConcurrent>
class HdcPrivate : public QObject
{
public:
    HdcPrivate(Hdc* q)
    :m_q(q)
    {
        ptyProcess = PtyQt::createPtyProcess(IPtyProcess::PtyType::AutoPty);
        workDirInit();
        createTempPath();
    }
    ~HdcPrivate()
    {
        qDebug() << "HdcPrivate delete";
        quit = true;
        // if(ptyProcess)
        //     delete ptyProcess;
    }
    void workDirInit()
    {
        workDir = defaultWorkDir;
    }
    bool setDefaultTarget()
    {
        if(!target.isEmpty())
        {
            return true;
        }
        QStringList listTargets = m_q->listTargets();
        if(listTargets.isEmpty())
        {
            qWarning() << "No target";
            return false;
        }
        if (quit || !isVaild)
        {
            return false;
        }
        m_q->setTarget(listTargets.first());
        return true;
    }
    QProcess *shellProcess(const QStringList &arguments = {}, int wait = 30000)
    {
        if (quit || !isVaild || !setDefaultTarget())
        {
            return nullptr;
        }
        QProcess *process = new QProcess;
        process->setWorkingDirectory(workDir);
        process->start(path, QStringList{"-t", target} << arguments);
        if (!process->waitForFinished(wait))
        {
            qWarning() << "Hdc process timeout!" << arguments;
            process->kill();
        }
        return process;
    }
    void runHdc(const QStringList &arguments = {}, int wait = 5000)
    {
        QProcess * process = shellProcess(arguments, wait);
        if (process)
        {
            process->deleteLater();
        }
    }
    QString runHdc(const QStringList &arguments, QString &error)
    {
        QProcess * process = shellProcess(arguments);
        QString output;
        if (process)
        {
            error = process->readAllStandardError();
            output = process->readAllStandardOutput();
            process->deleteLater();
        }
        return output;
    }
    QString runHdcWithoutTarget(const QStringList &arguments, QString &error)
    {
        if (quit || !isVaild)
        {
            return "";
        }
        QProcess process;
        process.setWorkingDirectory(workDir);
        process.start(path, arguments, QProcess::ReadOnly);
        if (!process.waitForFinished()) // 限制等待时间，避免死锁
        {
            qWarning() << "Hdc process timeout!" << arguments;
            process.kill(); // 终止进程
        }
        error = process.readAllStandardError();
        return process.readAllStandardOutput();
    }
    void runShell(const QStringList &arguments = {}, int wait = 5000, QProcess::OpenMode mode = QProcess::ReadOnly)
    {
        runHdc(QStringList{"shell"} << arguments, wait);
    }

    void createTempPath()
    {
        QString applicationName = QCoreApplication::applicationName();
        if (localTempPath.isEmpty())
        {
            localTempPath = QDir::tempPath() + QDir::separator() + applicationName;
            if (!QDir(localTempPath).exists())
            {
                QDir().mkpath(localTempPath);
            }
        }
        remoteTempPath = "/data/local/tmp/" + applicationName;
        // m_q->mkdir(remoteTempPath);
    }

    IPtyProcess *ptyProcess = nullptr;
    friend class Hdc;
private:
    Hdc* m_q = nullptr;
    QString path;
    QString workDir;
    const QString defaultWorkDir = QCoreApplication::applicationDirPath();
    QString remoteTempPath;
    QString localTempPath;
    bool isVaild = false;
    bool quit = false;
    QString target;
};

Hdc::Hdc(QString hdcPath, QObject *parent)
    : QObject(parent),
    m_p(new HdcPrivate(this))
{
    if (!hdcPath.isEmpty())
    {
        setPath(hdcPath);
    }
    mkdir(m_p->remoteTempPath);
}

Hdc::~Hdc()
{
    quit();
    delete m_p;
    m_p = nullptr;
}

QString Hdc::path() const
{
    return m_p->path;
}

void Hdc::setPath(const QString &path)
{
    if (m_p->path == path)
        return;
#ifdef Q_OS_WIN
    QString exeName = "/hdc.exe";
#else
    QString exeName = "/hdc";
#endif
    //判断是否是目录
    if (QFileInfo(path).isDir())
    {
        m_p->path = path.endsWith("/") ? path + exeName : path + exeName;
    }
    else if (QFileInfo(path).isFile())
    {
        m_p->path = path;
    }
    else {
        qWarning() << "Path is not exist";
    }
    m_p->isVaild = QFileInfo(m_p->path).isExecutable();
    if (!m_p->isVaild)
    {
        qWarning() << "Hdc path is not exist";
    }
    emit pathChanged(m_p->path);
}

QString Hdc::version()
{
    QString error;
    QString version = m_p->runHdcWithoutTarget({"version"}, error).trimmed();
    version = version.split(" ").last();
    return !error.isEmpty() ? error : version;
}

QStringList Hdc::help()
{
    QString error;
    QString help = m_p->runHdcWithoutTarget({"help"}, error).trimmed();

    return !error.isEmpty() ? QStringList{error} : help.split("\r\n");
}

QStringList Hdc::listTargets()
{
    QString error;
    QString targets = m_p->runHdcWithoutTarget({"list", "targets"}, error).trimmed();;
    return !error.isEmpty() ? QStringList{error} : targets.split("\r\n");
}

void Hdc::snapshotDisplay(const QString &savePath)
{
    qDebug() << "Snapshot display";
    QFileInfo fileInfo(savePath);
    if (fileInfo.suffix().isEmpty())
    {
        return;
    }
    QString snapshotPath = QString("%1/%2.jpeg").arg(m_p->remoteTempPath, fileInfo.baseName());
    m_p->runShell(QStringList{"snapshot_display", "-f", snapshotPath});
    recvFile(snapshotPath, savePath);
}

QImage Hdc::snapshotDisplay()
{
    QImage image;
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString savePath = QString(m_p->localTempPath + QDir::separator() + uuid + ".jpeg");
    snapshotDisplay(savePath);
    image.load(savePath);
    return image;
}

void Hdc::recvFile(const QString &remotePath, const QString &localPath)
{
    QFileInfo fileInfo(localPath);
    m_p->workDir = !fileInfo.suffix().isEmpty() ? fileInfo.absoluteDir().absolutePath() : localPath;

    m_p->runHdc({"file", "recv", remotePath});
    auto removeFile = [this](const QString &remotePath){
        this->removeFile(remotePath);
    };
    QFuture<void> future = QtConcurrent::run(removeFile, remotePath);
    m_p->workDirInit();
}

void Hdc::removeFile(const QString &remotePath)
{
    m_p->runShell({"rm", remotePath}, 5000);
}

void Hdc::mkdir(const QString &remotePath)
{
    m_p->runShell({"mkdir", remotePath}, 5000);
}

void Hdc::quit()
{
    if(m_p->quit)
    {
        return;
    }
    m_p->quit = true;
}



QString Hdc::target() const
{
    return m_p->target;
}

void Hdc::setTarget(const QString &newTarget)
{
    if (m_p->target == newTarget)
        return;
    m_p->target = newTarget;
    emit targetChanged();
}
