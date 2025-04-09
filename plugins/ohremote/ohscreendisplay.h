#ifndef OHSCREENDISPLAY_H
#define OHSCREENDISPLAY_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>
class OhScreenDisplayPrivate;
class OhScreenDisplay : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit OhScreenDisplay(QWidget *parent = nullptr);
    ~OhScreenDisplay();
    void startScreenCast();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
private:
    OhScreenDisplayPrivate * const m_p = nullptr;
};

#endif // OHSCREENDISPLAY_H
