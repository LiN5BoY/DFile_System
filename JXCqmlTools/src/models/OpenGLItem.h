#ifndef OPENGLITEM_H
#define OPENGLITEM_H

#include <QQuickFramebufferObject>
#include "OpenGLRenderer.h"

/**
 * @brief OpenGLItem 类
 *
 * 该类继承自 QQuickFramebufferObject，用于在 Qt Quick 中实现 OpenGL 渲染。
 * 它提供了一个属性 dataPoints，用于存储和更新渲染数据点。
 */
class OpenGLItem : public QQuickFramebufferObject
{
    // Q_OBJECT 使得类具有 Qt 的信号与槽机制和元对象功能。
    Q_OBJECT
    // Q_PROPERTY 定义了一个可读可写的属性，并且在属性值变化时发出通知信号，
    // 使得属性可以在 QML 等界面中方便地访问和绑定。
    Q_PROPERTY(QVector<QPointF> dataPoints READ dataPoints WRITE setDataPoints NOTIFY dataPointsChanged)
public:
    /**
     * @brief 创建渲染器
     *
     * 重写 createRenderer() 方法以返回一个新的 OpenGLRenderer 实例。
     *
     * @return 返回新创建的 OpenGLRenderer 对象指针。
     */
    Renderer *createRenderer() const override
    {
        return new OpenGLRenderer();
    }

    /**
     * @brief 获取数据点
     *
     * @return 返回当前存储的数据点 QVector<QPointF>。
     */
    QVector<QPointF> dataPoints() const
    {
        return m_dataPoints;
    }

    /**
     * @brief 设置数据点
     *
     * 如果新的数据点与当前数据点不同，则更新数据点并发出信号。
     *
     * @param points 要设置的新数据点 QVector<QPointF>。
     */
    Q_INVOKABLE void setDataPoints(const QVector<QPointF> &points)
    {
        if (m_dataPoints != points)
        {
            m_dataPoints = points;
            emit dataPointsChanged();
            update(); // 请求重新渲染
        }
    }

signals:
    /**
     * @brief 数据点改变信号
     *
     * 当数据点更新时发出此信号，以通知相关的视图更新。
     */
    void dataPointsChanged();

private:
    QVector<QPointF> m_dataPoints; ///< 存储数据点的 QVector
};

#endif // OPENGLITEM_H
