#include "editorpage.h"
// #include "qscilexercpp.h"
#include "toolbarmanager.h"
#include <QStyle>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include "itexteditor.h"
#include "menubarmanager.h"
#include "filemenu.h"
class EditorPagePrivate
{
public:
    EditorPagePrivate(EditorPage *q)
        : editor(new ITextEditor(q)),
        q_ptr(q)
    {
        Q_UNUSED(q_ptr)
        // editor = new QsciScintilla;
        editor->setEnabled(false);
        // editor->setTabWidth(4);
        // editor->setAutoIndent(true);
        // editor->setCaretLineVisible(true);
        // // editor->zoomIn(8);
        // QsciLexerCPP *textLexer=new QsciLexerCPP;
        // editor->setLexer(textLexer);
        // textLexer->setPaper(QColor(200,250,200));
        // textLexer->setColor(QColor(0,170,0),QsciLexerCPP::Comment);
        // textLexer->setColor(QColor(Qt::yellow),QsciLexerCPP::CommentDocKeyword);
        // textLexer->setColor(QColor(Qt::yellow),QsciLexerCPP::);
    }
    ITextEditor *editor = nullptr;
private:
    EditorPage *q_ptr = nullptr;
};

EditorPage::EditorPage(IWidget *parent)
    :IWidget{parent},
    m_p(new EditorPagePrivate(this))
{
    setWindowTitle("Editor");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_p->editor);

    setLayout(layout);
    connect(MenuBarManager::menu<FileMenu>(), &FileMenu::sendFile, this, &EditorPage::onReceiveFile);
    connect(MenuBarManager::menu<FileMenu>(), &FileMenu::saveFile, this, &EditorPage::onSaveFile);

}

QIcon EditorPage::icon() const
{
    return QApplication::style()->standardIcon((QStyle::SP_FileDialogDetailedView));
}

int EditorPage::index() const
{
    return 1;
}

void EditorPage::setUpEditorPage()
{
    qDebug() << "EditorPage::setUpEditorPage()";
    ToolBarManager::registerWidget<EditorPage>();
}

void EditorPage::onReceiveFile(QFile &file)
{

    if(!file.open(QIODevice::ReadOnly))
        return;
    m_p->editor->setEnabled(true);
    m_p->editor->setPlainText(file.readAll());
    // m_p->editor->setMarginType(0, QsciScintilla::NumberMargin);
    // m_p->editor->setMarginLineNumbers(0, true);
    // m_p->editor->setMarginWidth(0,40);
    file.close();
}

void EditorPage::onSaveFile(QFile &file)
{
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(m_p->editor->toPlainText().toUtf8());
    file.close();
    qDebug() << "Save file" << file.fileName();
}
