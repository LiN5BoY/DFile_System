#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// 包含必要的OpenGL和Qt Quick头文件
#include <QOpenGLFunctions> // 提供OpenGL函数的接口
#include <QQuickFramebufferObject> // 支持在Qt Quick中使用帧缓冲对象
#include <QOpenGLShaderProgram> // 提供OpenGL着色器程序的接口

// OpenGLRenderer类继承自QQuickFramebufferObject::Renderer
class OpenGLRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
public:
    // 构造函数
    OpenGLRenderer();

    // 重写render方法，用于绘制内容
    void render() override;

    // 创建帧缓冲对象，返回一个QOpenGLFramebufferObject指针
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    // 同步数据的方法，更新与QQuickFramebufferObject之间的数据
    void synchronize(QQuickFramebufferObject *item) override;

private:
    // 初始化OpenGL环境的方法
    void initializeOpenGL();

    // 绘制曲线的方法
    void drawCurve();

    // 存储数据点的向量
    QVector<QPointF> dataPoints;

    // OpenGL着色器程序
    QOpenGLShaderProgram shaderProgram;

    // Gluint类型的顶点数组对象
    GLuint vertexBuffer;
};

#endif // OPENGLRENDERER_H
