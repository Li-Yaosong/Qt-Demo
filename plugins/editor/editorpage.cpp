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
#include "qsourcehighliter.h"
#include <QCXXHighlighter>
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
    if(file.fileName().endsWith(".cpp"))
    {
        m_p->editor->setHighlighter(new QCXXHighlighter);
        // (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
        //     ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeCpp);
    }
    else if(file.fileName().endsWith(".h"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeCpp);
    }
    else if(file.fileName().endsWith(".py"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodePython);
    }
    else if(file.fileName().endsWith(".java"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeJava);
    }
    else if(file.fileName().endsWith(".css"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeCSS);
    }
    else if(file.fileName().endsWith(".js"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeTypeScript);
    }
    else if(file.fileName().endsWith(".xml"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeXML);
    }
    else if(file.fileName().endsWith(".json"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeJSON);
    }
    else if(file.fileName().endsWith(".sql"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeSQL);
    }
    else if(file.fileName().endsWith(".sh"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeBash);
    }
    else if(file.fileName().endsWith(".bat"))
    {
        (new QSourceHighlite::QSourceHighliter(m_p->editor->document()))
            ->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeBash);
    }
    ToolBarManager::setActiveWidget(index());
}

void EditorPage::onSaveFile(QFile &file)
{
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(m_p->editor->toPlainText().toUtf8());
    file.close();
    qDebug() << "Save file" << file.fileName();
}
