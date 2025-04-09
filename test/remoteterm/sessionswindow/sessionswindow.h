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
#ifndef SESSIONSWINDOW_H
#define SESSIONSWINDOW_H

#include <QObject>
#include <QWidget>

#include <QMutex>
#include <QMutexLocker>

class QTextStream;
class IPtyProcess;
class QTermWidget;
class SessionsWindow : public QObject
{
    Q_OBJECT
public:
    enum SessionType {
        LocalShell,
        SessionTypeMax,
    };
    enum ShellType {
        UnixShell = 0,
        PowerShell,
        WSL,
        Unknown,

        ShellTypeMax,
    };
    enum SessionsState {
        Connected = 0,
        Disconnected,
        Locked,
        BroadCasted,
        Error,
    };
    enum EndOfLineSeq {
        AUTO = 0,
        LF,
        CR,
        LFLF,
        CRCR,

        EndOfLineSeqMax,
    };
    enum ShowTitleType {
        LongTitle = 0,
        ShortTitle,
        NameTitle,

        TitleTypeMax,
    };
    SessionsWindow(SessionType tp, QWidget *parent = nullptr);
    ~SessionsWindow();

    void cloneSession(SessionsWindow *src, QString profile = QString());
#if defined(Q_OS_WIN)
    int startLocalShellSession(const QString &command, QString profile = QString(), ShellType sTp = PowerShell);
#else
    int startLocalShellSession(const QString &command, QString profile = QString(), ShellType sTp = UnixShell);
#endif

    void disconnect(void);

    void setWorkingDirectory(const QString &dir);
    const QString getWorkingDirectory(void) { return workingDirectory; }
    void setInBroadCastList(bool enable);
    bool isInBroadCastList() { return enableBroadCast; }
    void setTagColor(bool enable, QColor color = QColor());
    bool isTagColor() { return tagColor; }
    QColor getTagColorValue() { return tagColorValue; }

    int installWaitString(const QStringList &strList, int timeout, bool bcaseInsensitive, int mode);

    QWidget *getMainWidget() const;
    SessionType getSessionType() const { return type; }
    ShellType getShellType() const { return shellType; }
    QString getWSLUserName() const { return m_wslUserName; }
    void setShowTitleType(ShowTitleType type) { showTitleType = type; }
    ShowTitleType getShowTitleType() const { return showTitleType; }
    QString getTitle() const;
    QString getLongTitle() const { return longTitle; }
    QString getShortTitle() const { return shortTitle; }
    void setLongTitle(const QString &title) { longTitle = title; }
    void setShortTitle(const QString &title) { shortTitle = title; }
    void setName(const QString &name) { this->name = name; }
    QString getName() const { return name; }
    void lockSession(QString password);
    void unlockSession(QString password);
    bool isLocked() const { return locked; }
    SessionsState getState() const { return state; }
    void refeshTermSize(void);

    QString getCommand() const { return m_command; }

    void setScrollBarPosition(int position);
    void reTranslateUi(void);
    void setKeyBindings(const QString & kb);
    void setColorScheme(const QString & name);
    void setANSIColor(int index, const QColor & color);
    void setTerminalFont(const QFont & font);
    void setFixQuardCRTIssue33(bool fix);
    void setTerminalBackgroundMode(int mode);
    void setTerminalOpacity(qreal level);
    void setHistorySize(int lines);
    void setKeyboardCursorShape(uint32_t shape);
    void setBlinkingCursor(bool blink);
    void setWordCharacters(const QString &wordCharacters);
    void setPreeditColorIndex(int index);
    void setSelectedTextAccentColorTransparency(int transparency);
    void setTerminalBackgroundImage(const QString& backgroundImage);
    void setTerminalBackgroundMovie(const QString& backgroundMovie);
    void setTerminalBackgroundVideo(const QString& backgroundVideo);
    QString selectedText(bool preserveLineBreaks = true);
    void setShowResizeNotificationEnabled(bool enabled);
    void copyClipboard();
    void pasteClipboard();
    void selectAll();
    void toggleShowSearchBar();
    void saveHistory(QTextStream *stream, int format = 0, int start = -1, int end = -1);
    void saveHistory(QIODevice *device, int format = 0, int start = -1, int end = -1);
    void screenShot(const QString &fileName);
    void screenShot(QPixmap *pixmap);
    void clearScrollback();
    void clearScreen();
    QString screenGet(int row1, int col1, int row2, int col2, int mode);
    void clear();
    void zoomIn();
    void zoomOut();
    void proxySendData(QByteArray data);
    void proxyRecvData(QByteArray data);
    void reverseProxySendData(QByteArray data);
    QList<QAction*> filterActions(const QPoint& position);
    void addHighLightText(const QString &text, const QColor &color);
    bool isContainHighLightText(const QString &text);
    void removeHighLightText(const QString &text);
    void clearHighLightTexts(void);
    QMap<QString, QColor> getHighLightTexts(void);
    void repaintDisplay(void);
    int getLineCount(void);
    int getColumnCount(void);
    int getCursorLineCount(void);
    int getCursorColumnCount(void);
    void setConfirmMultilinePaste(bool enable);
    void setTrimPastedTrailingNewlines(bool enable);
    void setEcho(bool enable);
    void setCursorColor(const QColor &color);
    void setEnableHandleCtrlC(bool enable);
    int getEndOfLineSeq(void);
    void setEndOfLineSeq(EndOfLineSeq mode);

signals:
    void hexDataDup(const char *data, int size);
    void stateChanged(SessionsState state);
    void titleChanged(int title,const QString& newTitle);
    void modemProxySendData(QByteArray data);
    void modemProxyRecvData(const QByteArray &data);
    void waitForStringFinished(const QString &str, int matchIndex);
    void broadCastSendData(const QByteArray &data);
    void requestReconnect(void);
    void termGetFocus();
    void termLostFocus();
    
private:
    void matchString(QByteArray data);
    bool doSendData(QByteArray &data, bool isConnected);
    bool doRecvData(QByteArray &data);

private:
    SessionType type;
    ShellType shellType;
    QString workingDirectory;
    QString longTitle;
    QString shortTitle;
    QString name;
    ShowTitleType showTitleType;
    QWidget *messageParentWidget;
    QTermWidget *term;
    IPtyProcess *localShell;

    bool enableBroadCast;
    QMutex log_file_mutex;
    QByteArray password_hash;
    bool locked = false;
    SessionsState state = Disconnected;

    uint64_t tx_realtime = 0;
    uint64_t rx_realtime = 0;
    qreal tx_speed = 0;
    qreal rx_speed = 0;
    QTimer *realtimespeed_timer = nullptr;
    bool tagColor = false;
    QColor tagColorValue;
    EndOfLineSeq endOfLineSeq = AUTO;
    bool m_requestReconnect = false;
    
    QMutex modemProxyChannelMutex;
    bool modemProxyChannel = false;

    QStringList m_waitStringList;
    int m_waitStringTimeout;
    bool m_waitStringCaseInsensitive;
    int m_waitStringMode;
    QByteArray m_waitStringDate;

    QString m_command;
    QString m_wslUserName;
};

#endif // SESSIONSWINDOW_H
