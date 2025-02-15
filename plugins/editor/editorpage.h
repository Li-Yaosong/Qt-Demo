#ifndef EDITORPAGE_H
#define EDITORPAGE_H

#include <iwidget.h>
#include <QFile>
class EditorPagePrivate;
class EditorPage : public IWidget
{
public:
    EditorPage(IWidget *parent = nullptr);
    QIcon icon() const;
    int index() const;
    static void setUpEditorPage();
public Q_SLOTS:
    void onReceiveFile(QFile &file);
    void onSaveFile(QFile &file);
private:
    EditorPagePrivate * const m_p;
};
#endif // EDITORPAGE_H
