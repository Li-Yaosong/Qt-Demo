#ifndef HDC_H
#define HDC_H

#include "hdc_global.h"
#include <QObject>
class IPtyProcess;
class HdcPrivate;
class HDC_EXPORT Hdc : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(QStringList help READ help CONSTANT)
public:
    explicit Hdc(QString hdcPath = QString{}, QObject *parent = nullptr);
    ~Hdc();

    /**
     * @brief path 获取HDC路径
     * @return
     */
    QString path() const;
    /**
     * @brief setPath 设置HDC路径
     * @param path
     */
    void setPath(const QString &path);
    /**
     * @brief version 获取版本号
     * @return 版本号
     */
    QString version();
    QStringList help();
    QStringList listTargets();
    /**
     * @brief snapshotDisplay 截图
     * @param savePath 保存路径
     */
    void snapshotDisplay(const QString &savePath);
    QImage snapshotDisplay();

    /**
     * @brief recvFile 接收文件
     * @param remotePath 远程路径
     * @param localPath 本地路径
     */
    void recvFile(const QString &remotePath, const QString &localPath);
    /**
     * @brief removeFile 删除文件
     * @param remotePath 远程路径
     */
    void removeFile(const QString &remotePath);
    void mkdir(const QString &remotePath);


    IPtyProcess *shellProcess();

    void quit();
    QString target() const;
    void setTarget(const QString &newTarget);

signals:
    void pathChanged(const QString &path);

    void targetChanged();

private:
    HdcPrivate *m_p = nullptr;
};

#endif // HDC_H
