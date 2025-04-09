#ifndef TERMINALTABWIDGET_H
#define TERMINALTABWIDGET_H

#include <QTabWidget>

class TerminalTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TerminalTabWidget(QWidget *parent = nullptr);



    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // TERMINALTABWIDGET_H
