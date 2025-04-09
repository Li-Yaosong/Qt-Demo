#ifndef WIDGET_H
#define WIDGET_H

#include "qelapsedtimer.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QImage>
class OhScreenMirror;
class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updateImage(const QImage &image);  // 更新图片数据
    void startScreenCasting();
    void stopScreenCasting();
    // QWidget interface
protected:
    // void paintEvent(QPaintEvent *event) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
private:
    QOpenGLTexture *texture;  // 纹理对象
    QImage currentImage;  // 当前 QImage
    QSize size;  // 窗口大小
    OhScreenMirror *mirror = nullptr;
    QElapsedTimer timer;
};
#endif // WIDGET_H
