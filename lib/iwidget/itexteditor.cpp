#include "itexteditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QFile>
#include <QSyntaxStyle>
// class LineNumberArea : public QWidget {
// public:
//     LineNumberArea(ITextEditor *editor)
//     : QWidget(editor), codeEditor(editor)
//     {

//     }

//     QSize sizeHint() const override
//     {
//         return QSize(codeEditor->lineNumberAreaWidth(), 0);
//     }

// protected:
//     void paintEvent(QPaintEvent *event) override
//     {
//         QPainter painter(this);

//         painter.fillRect(event->rect(), QColor(240, 240, 240)); // 背景颜色
//         if (!isVisible()) {
//             return;
//         }
//         QTextBlock block = codeEditor->firstVisibleBlock();
//         int blockNumber = block.blockNumber();
//         int top = static_cast<int>(codeEditor->blockBoundingGeometry(block).translated(codeEditor->contentOffset()).top());
//         int bottom = top + static_cast<int>(codeEditor->blockBoundingRect(block).height());

//         while (block.isValid() && top <= event->rect().bottom()) {
//             if (block.isVisible() && bottom >= event->rect().top()) {
//                 QString number = QString::number(blockNumber + 1);
//                 painter.setPen(Qt::black);
//                 painter.drawText(0, top, width(), codeEditor->fontMetrics().height(),
//                                  Qt::AlignCenter, number);
//             }

//             block = block.next();
//             top = bottom;
//             bottom = top + static_cast<int>(codeEditor->blockBoundingRect(block).height());
//             ++blockNumber;
//         }
//     }

// private:
//     ITextEditor *codeEditor;
// };

class ITextEditorPrivate
{
public:
    ITextEditorPrivate(ITextEditor *q)
        :q_ptr(q)

    {
        Q_UNUSED(q_ptr)
    }
    ~ITextEditorPrivate() = default;
    // unique_ptr<LineNumberArea> lineNumberArea;
private:
    ITextEditor *q_ptr = nullptr;
};

ITextEditor::ITextEditor(QWidget *parent)
    :QCodeEditor{parent},
    m_p(new ITextEditorPrivate(this))
{
    // connect(this, &ITextEditor::blockCountChanged, this, &ITextEditor::updateLineNumberAreaWidth);
    // connect(this, &ITextEditor::updateRequest, this, &ITextEditor::updateLineNumberArea);
    // connect(this, &ITextEditor::cursorPositionChanged, this, &ITextEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    // highlightCurrentLine();
    QFile fl(":/resources/styles/drakula.xml");

    if (!fl.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file :/styles/drakula.xml";
        return;
    }

    auto style = new QSyntaxStyle(this);

    if (!style->load(fl.readAll()))
    {
        delete style;
        return;
    }
    setSyntaxStyle(style);
    setFontFamily("Consolas");
}

// int ITextEditor::lineNumberAreaWidth()
// {
//     int digits = 1;
//     int max = qMax(1, blockCount());
//     while (max >= 10) {
//         max /= 10;
//         ++digits;
//     }
//     int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
//     return space;
// }

void ITextEditor::setEnabled(bool e)
{
    QCodeEditor::setEnabled(e);
    setExtraSelections(QList<QTextEdit::ExtraSelection>() << QTextEdit::ExtraSelection());
    // m_p->lineNumberArea->setVisible(e);
}

void ITextEditor::resizeEvent(QResizeEvent *event)
{
    QCodeEditor::resizeEvent(event);
    // QRect cr = contentsRect();
    // m_p->lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

// void ITextEditor::updateLineNumberAreaWidth(int)
// {
//     setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
// }

// void ITextEditor::updateLineNumberArea(const QRect &rect, int dy)
// {
//     if (dy) {
//         m_p->lineNumberArea->scroll(0, dy);
//     } else {
//         m_p->lineNumberArea->update(0, rect.y(), m_p->lineNumberArea->width(), rect.height());
//     }

//     if (rect.contains(viewport()->rect())) {
//         updateLineNumberAreaWidth(0);
//     }
// }

// void ITextEditor::highlightCurrentLine()
// {
//     QList<QTextEdit::ExtraSelection> extraSelections;

//     if (!isReadOnly()) {
//         QTextEdit::ExtraSelection selection;
//         QColor lineColor = QColor(220, 240, 255);
//         selection.format.setBackground(lineColor);
//         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//         selection.cursor = textCursor();
//         selection.cursor.clearSelection();
//         extraSelections.append(selection);
//     }

//     setExtraSelections(extraSelections);
// }
