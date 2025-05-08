/*
 * This file is part of the https://github.com/QQxiaoming/quardCRT.git
 * project.
 *
 * Copyright (C) 2023 Quard <2014500726@smail.xtu.edu.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include "ptyqt.h"
#include "iptyprocess.h"
#include <QFont>
#include <QFontDatabase>
#include <QStringList>
#include <QProcessEnvironment>
#include <QMessageBox>
#include <QDir>
#include <QCryptographicHash>
#include "qtermwidget.h"
#include "sessionswindow.h"

SessionsWindow::SessionsWindow(SessionType tp, QWidget *parent)
    : QObject(parent)
    , type(tp)
    , workingDirectory(QDir::homePath())
    , showTitleType(LongTitle)
    , messageParentWidget(parent)
    , term(nullptr)
    , localShell(nullptr)
    , enableBroadCast(false) {
    shellType = Unknown;
    if(type == LocalShell) {
        term = new QTermWidget(parent);

        // term->setProperty("session", QVariant::fromValue(this));

        term->setScrollBarPosition(QTermWidget::ScrollBarRight);
        term->setBlinkingCursor(true);
        term->setMargin(0, 2);
        term->setDrawLineChars(false);
        term->setSelectionOpacity(0.5);
        term->setShowResizeNotificationEnabled(false);
        // term->setBackgroundColor(Qt::black);
        term->setForegroundColor(Qt::white);
        QStringList availableColorSchemes = term->availableColorSchemes();
        availableColorSchemes.sort();
        qDebug() << availableColorSchemes.count();
        QString currentColorScheme = availableColorSchemes.first();
        term->setColorScheme(currentColorScheme);
        term->repaint();

        // QStringList availableKeyBindings = term->availableKeyBindings();
        // availableKeyBindings.sort();
        // QString currentAvailableKeyBindings = availableKeyBindings.first();
        // foreach(QString keyBinding, availableKeyBindings) {
        //     if(keyBinding == "linux") {
        //         term->setKeyBindings("linux");
        //         currentAvailableKeyBindings = "linux";
        //     }
        // }
    }

    switch (type) {
        case LocalShell: {
            showTitleType = ShortTitle;
            localShell = PtyQt::createPtyProcess(IPtyProcess::PtyType::ConPty);
            connect(term, &QTermWidget::termSizeChange, this, [=](int lines, int columns){
                localShell->resize(columns,lines);
            });
            break;
        }
        default:
            break;
    }

    // if(realtimespeed_timer) {
    //     connect(realtimespeed_timer, &QTimer::timeout, this, [=](){
    //         tx_speed = tx_realtime/3.0;
    //         rx_speed = rx_realtime/3.0;
    //         rx_realtime = 0;
    //         tx_realtime = 0;
    //     });
    //     realtimespeed_timer->start(3000);
    // }
}

SessionsWindow::~SessionsWindow() {
    if(localShell) {
        localShell->kill();
        delete localShell;
    }
    if(realtimespeed_timer) {
        delete realtimespeed_timer;
    }
    if(term) {
        delete term;
    }
}

void SessionsWindow::matchString(QByteArray data) {
    if(!m_waitStringList.isEmpty()) {
        if(m_waitStringCaseInsensitive) {
            foreach(const QString &waitString, m_waitStringList) {
                QString dataStr = QString::fromUtf8(data).toLower();
                if(dataStr.contains(waitString.toLower())) {
                    if(m_waitStringMode == 0) {
                        int matchIndex = m_waitStringList.indexOf(waitString);
                        QString matchStr = waitString;
                        m_waitStringList.clear();
                        emit waitForStringFinished(matchStr, matchIndex);
                        break;
                    } else {
                        int index = dataStr.indexOf(waitString.toLower());
                        m_waitStringDate.append(data.left(index + waitString.length()));
                        int matchIndex = m_waitStringList.indexOf(waitString);
                        QString matchStr(m_waitStringDate);
                        m_waitStringList.clear();
                        m_waitStringDate.clear();
                        emit waitForStringFinished(matchStr, matchIndex);
                        break;
                    }
                }
            }
            if(m_waitStringMode == 1) {
                m_waitStringDate.append(data);
            }
        } else {
            foreach(const QString &waitString, m_waitStringList) {
                if(data.contains(waitString.toUtf8())) {
                    if(m_waitStringMode == 0) {
                        int matchIndex = m_waitStringList.indexOf(waitString);
                        QString matchStr = waitString;
                        m_waitStringList.clear();
                        emit waitForStringFinished(matchStr, matchIndex);
                        break;
                    } else {
                        int index = data.indexOf(waitString.toUtf8());
                        m_waitStringDate.append(data.left(index + waitString.length()));
                        int matchIndex = m_waitStringList.indexOf(waitString);
                        QString matchStr(m_waitStringDate);
                        m_waitStringList.clear();
                        m_waitStringDate.clear();
                        emit waitForStringFinished(matchStr, matchIndex);
                        break;
                    }
                }
            }
            if(m_waitStringMode == 1) {
                m_waitStringDate.append(data);
            }
        }
    }
}

bool SessionsWindow::doSendData(QByteArray &data, bool isConnected) {
    if(modemProxyChannel) {
        return false;
    }
    if(enableBroadCast) {
        emit broadCastSendData(data);
    }
    if(!isConnected) {
        if(data.contains("\r") || data.contains("\n")) {
            if(!m_requestReconnect) {
                m_requestReconnect = true;
                emit requestReconnect();
            }
        }
        return false;
    }
    return true;
}

bool SessionsWindow::doRecvData(QByteArray &data) {
    if(modemProxyChannel) {
        emit modemProxyRecvData(data);
        return false;
    }
    matchString(data);
    emit hexDataDup(data.data(), data.size());
    switch(endOfLineSeq) {
        case LF:
            data.replace("\r","\r\n");
            break;
        case CR:
            data.replace("\n","\r\n");
            break;
        case LFLF:
            data.replace("\r\r","\r\n");
            break;
        case CRCR:
            data.replace("\n\n","\r\n");
            break;
        default:
            break;
    }
    return true;
}

void SessionsWindow::cloneSession(SessionsWindow *src, QString profile) {
    switch(src->getSessionType()) {
        case LocalShell: {
            setWorkingDirectory(src->getWorkingDirectory());
            startLocalShellSession(src->m_command, profile, src->getShellType());
            break;
        default:
            break;
        }
    }  
}

int SessionsWindow::startLocalShellSession(const QString &command,QString profile, ShellType sTp) {
    QString shellPath;
    QStringList args;
    shellType = sTp;
    if(command.isEmpty()) {
    #if defined(Q_OS_LINUX) || defined(Q_OS_MACOS)
        Q_UNUSED(profile);
        GlobalSetting settings;
        QString defaultLocalShell = settings.value("Global/Options/DefaultLocalShell", "ENV:SHELL").toString();
        if(defaultLocalShell != "ENV:SHELL") {
            QFileInfo shellInfo(defaultLocalShell);
            if(shellInfo.isExecutable()) {
                shellPath = defaultLocalShell;
            }
        }
        if(shellPath.isEmpty()) shellPath = qEnvironmentVariable("SHELL");
        if(shellPath.isEmpty()) shellPath = "/bin/sh";
    #elif defined(Q_OS_WIN)
        // GlobalSetting setting;
        QString wslUserName = "root";
        QString wslDistro = "Ubuntu";
        m_wslUserName = wslUserName;
        switch (shellType) {
            case PowerShell:
            default: {
                QString defaultLocalShell = "c:\\Windows\\system32\\WindowsPowerShell\\v1.0\\powershell.exe";
                QFileInfo shellInfo(defaultLocalShell);
                if(shellInfo.isExecutable()) {
                    shellPath = defaultLocalShell;
                } 
                if(shellPath.isEmpty()) shellPath = "c:\\Windows\\system32\\WindowsPowerShell\\v1.0\\powershell.exe";
                args = QStringList{
                    "-ExecutionPolicy",
                    "Bypass",
                    "-NoLogo",
                    "-NoProfile",
                    "-NoExit",
                    "-File",
                };
                if(profile.isEmpty()) {
                    profile = QString("\"") + "c:/Windows/System32/WindowsPowerShell/v1.0/Examples/Profile.ps1\"";
                } else {
                    profile = QString("\"") + profile + "\"";
                }
                args.append(profile);
                break;
            }
            case WSL:
                shellPath = "c:\\Windows\\System32\\wsl.exe";
                args = QStringList{
                    "-u",
                    wslUserName,
                    "-d",
                    wslDistro,
                };
                break;
        }
    #endif
    }
    // else {
    //     argv_split parser;
    //     parser.parse(command.toStdString());
    //     for(auto &it : parser.getArguments()) {
    //         args.append(QString::fromStdString(it));
    //     }
    //     shellPath = args.first();
    //     args.removeFirst();
    // }
    QStringList envs = QProcessEnvironment::systemEnvironment().toStringList();
    #if defined(Q_OS_WIN)
    // if(envs.contains("quardcrt_computername")) {
    //     envs.replaceInStrings("quardcrt_computername", MiscWin32::getComputerName());
    // } else {
    //     envs.append("quardcrt_computername=" + MiscWin32::getComputerName());
    // }
    // if(envs.contains("quardcrt_username")) {
    //     envs.replaceInStrings("quardcrt_username", MiscWin32::getUserName());
    // } else {
    //     envs.append("quardcrt_username=" + MiscWin32::getUserName());
    // }
    #endif
    // GlobalSetting setting;
#if defined(Q_OS_MACOS)
    bool defaultForceUTF8 = true;
#else
    bool defaultForceUTF8 = false;
#endif
    bool forceUTF8 = defaultForceUTF8;
    if(forceUTF8) {
        envs.append("LC_CTYPE=UTF-8");
    }
    QFileInfo fileInfo(workingDirectory);
    if(!fileInfo.exists() || !fileInfo.isDir()) {
        workingDirectory = QDir::homePath();
    }
    bool ret = localShell->startProcess(shellPath, args, workingDirectory, envs, term->screenColumnsCount(), term->screenLinesCount());
    if(!ret) {
        state = Error;
        emit stateChanged(state);
        QMessageBox::warning(messageParentWidget, tr("Start Local Shell"), getName() + "\n" + tr("Cannot start local shell:\n%1.").arg(localShell->lastError()));
        return -1;
    }
    connect(localShell->notifier(), &QIODevice::readyRead, this, [=](){
        QByteArray data = localShell->readAll();
        if(doRecvData(data)) {
            term->recvData(data.data(), data.size());
        }
    });
    connect(this,&SessionsWindow::modemProxySendData,this,[=](QByteArray data){
        if(modemProxyChannel) {
            localShell->write(data);
        }
    });
    connect(term, &QTermWidget::sendData, this, [=](const char *data, int size){
        QByteArray sendData(data, size);
        if(doSendData(sendData,true)){
            localShell->write(QByteArray(data, size));
        }
    });
    m_command = command;
    state = Connected;
    emit stateChanged(state);
    return 0;
}


void SessionsWindow::disconnect(void) {
    switch (type) {
        case LocalShell:
            localShell->kill();
            state = Disconnected;
            emit stateChanged(state);
            break;
        default:
            break;
    }
}

void SessionsWindow::setWorkingDirectory(const QString &dir)
{
    workingDirectory = dir;
}

void SessionsWindow::lockSession(QString password) {
    password_hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    locked = true;
    term->setLocked(locked);
    emit stateChanged(Locked);
}

void SessionsWindow::unlockSession(QString password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    if(hash == password_hash) {
        password_hash = QByteArray();
        locked = false;
        term->setLocked(locked);
        emit stateChanged(Locked);
    } else {
        QMessageBox::warning(messageParentWidget, tr("Unlock Session"), tr("Wrong password!"));
    }
}

void SessionsWindow::setInBroadCastList(bool enable) {
    enableBroadCast = enable; 
    emit stateChanged(BroadCasted);
}

void SessionsWindow::setTagColor(bool enable, QColor color) {
    tagColor = enable;
    tagColorValue = color;
}

int SessionsWindow::installWaitString(const QStringList &strList, int timeout, bool bcaseInsensitive, int mode) {
    m_waitStringList = strList;
    m_waitStringTimeout = timeout;
    m_waitStringCaseInsensitive = bcaseInsensitive;
    m_waitStringMode = mode;
    return 0;
}

QWidget *SessionsWindow::getMainWidget() const {
    return static_cast<QWidget *>(term);
}

QString SessionsWindow::getTitle() const {
    switch(showTitleType) {
    default:
    case LongTitle:
        return longTitle;
    case ShortTitle:
        return shortTitle;
    case NameTitle:
        return name;
    }
}

void SessionsWindow::reverseProxySendData(QByteArray data) {
    if(term) {
        QMutexLocker locker(&modemProxyChannelMutex);
        if(!modemProxyChannel) {
            modemProxyChannel = true;
            emit modemProxySendData(data);
            modemProxyChannel = false;
        }
    }
}

QList<QAction *> SessionsWindow::filterActions(const QPoint &position) {
    if(term) {
        QPoint maptermWidgetPos = term->mapFromGlobal(position);
        return term->filterActions(maptermWidgetPos);
    }
    return QList<QAction*>();
}

void SessionsWindow::addHighLightText(const QString &text, const QColor &color) {
    if(term) term->addHighLightText(text,color);
}

bool SessionsWindow::isContainHighLightText(const QString &text) {
    if(term) return term->isContainHighLightText(text);
    return false;
}

void SessionsWindow::removeHighLightText(const QString &text) {
    if(term) term->removeHighLightText(text);
}

void SessionsWindow::clearHighLightTexts() {
    if(term) term->clearHighLightTexts();
}

QMap<QString, QColor> SessionsWindow::getHighLightTexts() {
    if(term) return term->getHighLightTexts();
    return QMap<QString, QColor>();
}

void SessionsWindow::repaintDisplay() {
    if(term) term->repaintDisplay();
}

int SessionsWindow::getLineCount() {
    if(term) return term->lines();
    return -1;
}

int SessionsWindow::getColumnCount() {
    if(term) return term->columns();
    return -1;
}

int SessionsWindow::getCursorLineCount() {
    if(term) return term->getCursorY();
    return -1;
}

int SessionsWindow::getCursorColumnCount(){
    if(term) return term->getCursorX();
    return -1;
}

void SessionsWindow::setConfirmMultilinePaste(bool enable) {
    if(term) term->setConfirmMultilinePaste(enable);
}

void SessionsWindow::setTrimPastedTrailingNewlines(bool enable) {
    if(term) term->setTrimPastedTrailingNewlines(enable);
}

void SessionsWindow::setEcho(bool enable) {
    if(term) term->setEcho(enable);
}

void SessionsWindow::setCursorColor(const QColor &color) {
    if(term) term->setKeyboardCursorColor(false,color);
}

void SessionsWindow::setEnableHandleCtrlC(bool enable) {
    if(term) term->setEnableHandleCtrlC(enable);
}

int SessionsWindow::getEndOfLineSeq() {
    return endOfLineSeq;
}

void SessionsWindow::setEndOfLineSeq(EndOfLineSeq mode) {
    endOfLineSeq = mode;
}

void SessionsWindow::refeshTermSize(void) {
    if(type == LocalShell) {
        localShell->resize(term->columns(),term->lines());
    }
}

void SessionsWindow::setScrollBarPosition(int position) {
    if(term) term->setScrollBarPosition(QTermWidget::ScrollBarPosition(position));
}

void SessionsWindow::reTranslateUi() {
    if(term) term->reTranslateUi();
}

void SessionsWindow::setKeyBindings(const QString &kb) {
    if(term) term->setKeyBindings(kb);
}

void SessionsWindow::setColorScheme(const QString &name) {
    if(term) term->setColorScheme(name);
}

void SessionsWindow::setANSIColor(int index, const QColor &color) {
    if(term) term->setANSIColor(index,color);
}

void SessionsWindow::setTerminalFont(const QFont &font) {
    if(term) term->setTerminalFont(font);
}

void SessionsWindow::setFixQuardCRTIssue33(bool fix) {
    if(term) term->set_fix_quardCRT_issue33(fix);
}

void SessionsWindow::setTerminalBackgroundMode(int mode) {
    if(term) term->setTerminalBackgroundMode(mode);
}

void SessionsWindow::setTerminalOpacity(qreal level) {
    if(term) term->setTerminalOpacity(level);
}

void SessionsWindow::setHistorySize(int lines) {
    if(term) term->setHistorySize(lines);
}

void SessionsWindow::setKeyboardCursorShape(uint32_t shape) {
    if(term) term->setKeyboardCursorShape(shape);
}

void SessionsWindow::setBlinkingCursor(bool blink) {
    if(term) term->setBlinkingCursor(blink);
}

void SessionsWindow::setWordCharacters(const QString &wordCharacters) {
    if(term) term->setWordCharacters(wordCharacters);
}

void SessionsWindow::setPreeditColorIndex(int index) {
    if(term) term->setPreeditColorIndex(index);
}

void SessionsWindow::setSelectedTextAccentColorTransparency(int transparency) {
    if(term) {
        if(transparency >= 100)
            term->setSelectionOpacity(1.0);
        else if(transparency <= 10)
            term->setSelectionOpacity(0.1);
        else
            term->setSelectionOpacity(transparency / 100.0);
    }
}

void SessionsWindow::setTerminalBackgroundImage(const QString &backgroundImage) {
    if(term) term->setTerminalBackgroundImage(backgroundImage);
}

void SessionsWindow::setTerminalBackgroundMovie(const QString &backgroundMovie) {
    if(term) term->setTerminalBackgroundMovie(backgroundMovie);
}

void SessionsWindow::setTerminalBackgroundVideo(const QString &backgroundVideo) {
    if(term) term->setTerminalBackgroundVideo(backgroundVideo);
}

QString SessionsWindow::selectedText(bool preserveLineBreaks) {
    if(term) return term->selectedText(preserveLineBreaks);
    return QString();
}

void SessionsWindow::setShowResizeNotificationEnabled(bool enabled) {
    if(term) term->setShowResizeNotificationEnabled(enabled);
}

void SessionsWindow::copyClipboard() {
    if(term) term->copyClipboard();
}

void SessionsWindow::pasteClipboard() {
    if(term) term->pasteClipboard();
}

void SessionsWindow::selectAll() {
    if(term) term->selectAll();
}

void SessionsWindow::toggleShowSearchBar() {
    if(term) term->toggleShowSearchBar();
}

void SessionsWindow::saveHistory(QTextStream *stream, int format, int start, int end) {
    if(term) term->saveHistory(stream,format,start,end);
}

void SessionsWindow::saveHistory(QIODevice *device, int format, int start, int end) {
    if(term) term->saveHistory(device,format,start,end);
}

void SessionsWindow::screenShot(const QString &fileName) {
    if(term) term->screenShot(fileName);
}

void SessionsWindow::screenShot(QPixmap *pixmap) {
    if(term) term->screenShot(pixmap);
}

void SessionsWindow::clearScrollback() {
    if(term) term->clearScrollback();
}

void SessionsWindow::clearScreen() {
    if(term) term->clearScreen();
}

QString SessionsWindow::screenGet(int row1, int col1, int row2, int col2, int mode) {
    if(term) return term->screenGet(row1, col1, row2, col2, mode);
    return QString();
}

void SessionsWindow::clear() {
    if(term) term->clear();
}

void SessionsWindow::zoomIn() {
    if(term) term->zoomIn();
}

void SessionsWindow::zoomOut() {
    if(term) term->zoomOut();
}

void SessionsWindow::proxySendData(QByteArray data) {
    if(term) term->proxySendData(data);
}

void SessionsWindow::proxyRecvData(QByteArray data) {
    if(term) term->recvData(data.data(),data.size());
}
