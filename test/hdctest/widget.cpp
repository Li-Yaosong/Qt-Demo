#include "widget.h"
#include "ohscreenmirror.h"
#include "qthread.h"
#include <QLabel>
#include <QPainter>
#include <QTimer>
Widget::Widget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mirror = new OhScreenMirror(this);
    timer.start();  // 记录起始时间
    connect(mirror, &OhScreenMirror::screenFlush, this, &Widget::updateImage);
    qDebug() << "QWidget"<< QThread::currentThreadId();
}

Widget::~Widget() {
    if (mirror)
    {
        delete mirror;
        mirror = nullptr;
    }
}

void Widget::updateImage(const QImage &image)
{

    timer.restart();  // 重置计时器
    if (image.isNull()) return;

    currentImage = image.convertToFormat(QImage::Format_RGBA8888); // 转换格式（OpenGL 需要）
    resize(currentImage.size()/2);
    makeCurrent(); // 绑定 OpenGL 上下文
    // qDebug() << "间隔:" << timer.nsecsElapsed() / 1000000.0 << "ms";  // 转换为毫秒
    if (!texture) {
        texture = new QOpenGLTexture(currentImage);

    } else {
        texture->destroy();
        texture->create();
        texture->setData(currentImage);
    }

    doneCurrent(); // 释放 OpenGL 上下文
    update(); // 触发重绘
}

void Widget::startScreenCasting()
{
    if (mirror)
    {
        mirror->start();
    }
}

void Widget::stopScreenCasting()
{
    if (mirror)
    {
        mirror->stop();
    }
}

// void Widget::paintEvent(QPaintEvent *event)
// {
//     QPainter painter(this);
//     painter.drawImage(rect(), snapshot);
//     qDebug() << "函数执行耗时:" << timer.nsecsElapsed() / 1000000.0 << "ms";  // 转换为毫秒
// }

void Widget::initializeGL()
{
    initializeOpenGLFunctions();  // 初始化 OpenGL 函数

    glEnable(GL_TEXTURE_2D);  // 启用 2D 纹理
    glClearColor(0, 0, 0, 1); // 设置背景颜色

    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // 清空缓冲区

    if (!texture || !texture->isCreated()) return;
    texture->bind(); // 绑定纹理


    glBegin(GL_QUADS); // 画一个 2D 矩形
    glTexCoord2f(0, 1); glVertex2f(-1, -1); // 左下
    glTexCoord2f(1, 1); glVertex2f( 1, -1); // 右下
    glTexCoord2f(1, 0); glVertex2f( 1,  1); // 右上
    glTexCoord2f(0, 0); glVertex2f(-1,  1); // 左上
    glEnd();
    texture->release();  // 释放纹理

    // qDebug() << "渲染耗时:" << timer.nsecsElapsed() / 1000000.0 << "ms";  // 转换为毫秒
    timer.restart();  // 重置计时器
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
