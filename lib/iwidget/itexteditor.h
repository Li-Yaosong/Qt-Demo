#ifndef ITEXTEDITOR_H
#define ITEXTEDITOR_H
#include "iwidget_global.h"
#include <QCodeEditor>
using namespace std;
class ITextEditorPrivate;
class IWIDGET_EXPORT ITextEditor : public QCodeEditor
{
    Q_OBJECT
public:
    explicit ITextEditor(QWidget *parent = nullptr);
    ~ITextEditor() = default;
    // int lineNumberAreaWidth();
public:
    void setEnabled(bool e);
protected:
    void resizeEvent(QResizeEvent *event) override;
// private Q_SLOTS:
//     void updateLineNumberAreaWidth(int);
//     void updateLineNumberArea(const QRect &rect, int dy);
//     void highlightCurrentLine();
private:
    // friend class LineNumberArea;
    QSharedPointer<ITextEditorPrivate> m_p;
};

#endif // ITEXTEDITOR_H
