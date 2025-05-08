#include "ohscreendisplay.h"
#include "ohscreenmirror.h"
#include <QElapsedTimer>

class OhScreenDisplayPrivate : public QObject
{
public:
    explicit OhScreenDisplayPrivate(OhScreenDisplay *q)
        :m_q(q)
    {
        mirror = new OhScreenMirror(m_q);
        timer.start();  // 记录起始时间
        connect(mirror, &OhScreenMirror::screenFlush, this, &OhScreenDisplayPrivate::updateImage);
    }
    ~OhScreenDisplayPrivate()
    {
        if (mirror)
        {
            delete mirror;
            mirror = nullptr;
        }
    }
    void updateImage(const QImage &image)
    {
        timer.restart();
        if (image.isNull()) return;

        currentImage = image.convertToFormat(QImage::Format_RGBA8888); // 转换格式（OpenGL 需要）

        m_q->makeCurrent(); // 绑定 OpenGL 上下文

        if (!texture) {
            texture = new QOpenGLTexture(currentImage);
        } else {
            texture->destroy();
            texture->create();
            texture->setData(currentImage);
        }

        m_q->doneCurrent(); // 释放 OpenGL 上下文
        m_q->update(); // 触发重绘
    }
private:
    friend class OhScreenDisplay;
    QOpenGLTexture *texture;  // 纹理对象
    QImage currentImage;  // 当前 QImage
    QElapsedTimer timer;
    OhScreenMirror *mirror = nullptr;
    OhScreenDisplay *m_q = nullptr;
};

OhScreenDisplay::OhScreenDisplay(QWidget *parent)
    : QOpenGLWidget(parent),
    m_p(new OhScreenDisplayPrivate(this))
{

}

OhScreenDisplay::~OhScreenDisplay()
{
    if (m_p)
    {
        delete m_p;
    }
}

void OhScreenDisplay::startScreenCast()
{
    m_p->mirror->start();
}

void OhScreenDisplay::initializeGL()
{
    initializeOpenGLFunctions();  // 初始化 OpenGL 函数

    glEnable(GL_TEXTURE_2D);  // 启用 2D 纹理
    glClearColor(0, 0, 0, 1); // 设置背景颜色

    m_p->texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_p->texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_p->texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void OhScreenDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // 清空缓冲区

    if (m_p->texture && m_p->texture->isCreated()) {
        m_p->texture->bind(); // 绑定纹理
    }

    glBegin(GL_QUADS); // 画一个 2D 矩形
    glTexCoord2f(0, 1); glVertex2f(-1, -1); // 左下
    glTexCoord2f(1, 1); glVertex2f( 1, -1); // 右下
    glTexCoord2f(1, 0); glVertex2f( 1,  1); // 右上
    glTexCoord2f(0, 0); glVertex2f(-1,  1); // 左上
    glEnd();

    m_p->texture->release();
    qDebug() << "渲染耗时:" << m_p->timer.nsecsElapsed() / 1000000.0 << "ms";  // 转换为毫秒
    m_p->timer.restart();  // 重置计时器
}

void OhScreenDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  // 适配窗口大小
}
