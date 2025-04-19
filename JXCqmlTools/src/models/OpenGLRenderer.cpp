#include "OpenGLRenderer.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

#include "OpenGLItem.h"

OpenGLRenderer::OpenGLRenderer()
{
    initializeOpenGL();
}

void OpenGLRenderer::initializeOpenGL()
{
    initializeOpenGLFunctions();
    // 初始化 OpenGL 资源，如着色器、缓冲区等

    // 创建并且编译顶点着色器
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    if (!vertexShader.compileSourceCode(R"(
        #version 330 core   // 使用OpenGL 3.3
        layout(location = 0) in vec2 position; // 声明顶点位置 位置索引为0
        void main()
        {
            // 将输入的顶点位置转换为裁剪空间坐标
            gl_Position = vec4(position, 0.0, 1.0);// z和w分别为0和1
        }
    )"))
    {
        qWarning() << "Vertex Shader Error:" << vertexShader.log();
    }

    // 创建并且编译片段着色器
    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    if (!fragmentShader.compileSourceCode(R"(
        #version 330 core
        out vec4 color; // 输出颜色
        void main()
        {
            // 设置颜色为黑色
            color = vec4(0.0, 0.0, 0.0, 1.0);   // RGBA格式
        }
    )"))
    {
        qWarning() << "Fragment Shader Error:" << fragmentShader.log();
    }

    // 创建着色器程序 并且链接着色器
    shaderProgram.addShader(&vertexShader);   // 添加顶点着色器
    shaderProgram.addShader(&fragmentShader); // 添加片段着色器
    if (!shaderProgram.link())
    {
        qWarning() << "Shader Program Link Error:" << shaderProgram.log();
    }

    // 创建顶点缓冲区
    // 生成一个缓冲区对象，并将其ID存储在 vertexBuffer 中
    glGenBuffers(1, &vertexBuffer);
}

void OpenGLRenderer::render()
{
    qDebug() << "Rendering with" << dataPoints.size() << "data points";
    // 设置视口
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 绘制内容
    drawCurve();
    // 刷新缓冲区
    update();
}

/**
 * @brief 创建一个帧缓冲对象 (Framebuffer Object)
 *
 * 该函数用于创建一个新的 QOpenGLFramebufferObject，具有指定的尺寸和深度/模板附件格式。
 *
 * @param size 帧缓冲对象的尺寸，类型为 QSize。
 * @return 指向新创建的 QOpenGLFramebufferObject 的指针。
 *
 * 帧缓冲对象用于在 OpenGL 渲染过程中离屏渲染图像。设置的附件为 CombinedDepthStencil，这意味着
 * 深度和模板缓冲区将被组合在一起。这样可以有效地利用 GPU 存储和渲染性能。
 */
QOpenGLFramebufferObject *OpenGLRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void OpenGLRenderer::drawCurve()
{
    // 绘制曲线
    // 使用 OpenGL 函数绘制曲线
    if (dataPoints.isEmpty())
    {
        return;
    }
    // 绑定着色器程序
    shaderProgram.bind();

    // 更新顶点缓冲区数据
    // 绑定顶点缓冲区，准备更新数据
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // 更新顶点缓冲区的数据，将数据点传输到GPU
    // GL_DYNAMIC_DRAW表示这些数据会动态改变，适合频繁更新的情况
    glBufferData(GL_ARRAY_BUFFER, dataPoints.size() * sizeof(QPointF), dataPoints.data(), GL_STATIC_DRAW);

    // 设置顶点属性指针，告诉OpenGL如何解析顶点数据
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QPointF), nullptr);
    // 第一个参数0表示顶点属性的位置，2表示每个顶点有2个分量（x和y），
    // GL_FLOAT表示数据类型，GL_FALSE表示不进行归归规范化，sizeof(QPointF)表示每个顶点的字节数
    glEnableVertexAttribArray(0); // 启用顶点属性数组

    // 绘制曲线，使用线段绘制模式
    glDrawArrays(GL_LINE_STRIP, 0, dataPoints.size());
    // GL_LINE_STRIP表示绘制线段，0表示从第一个顶点开始，dataPoints.size()表示顶点的数量

    // 解绑顶点属性数组和顶点缓冲区
    glDisableVertexAttribArray(0);    // 禁用顶点属性数组
    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑当前的顶点缓冲区

    // 释放着色器程序
    shaderProgram.release();
}

void OpenGLRenderer::synchronize(QQuickFramebufferObject *item)
{
    // 同步数据
    // 更新与 QQuickFramebufferObject 之间的数据
    OpenGLItem *openGLItem = static_cast<OpenGLItem *>(item);
    dataPoints = openGLItem->dataPoints();
}
