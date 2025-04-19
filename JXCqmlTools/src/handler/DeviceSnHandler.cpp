#include "DeviceSnHandler.h"
#include "../include/serial_config.h"

DeviceSnHandler::DeviceSnHandler(QObject *parent)
    : QObject(parent),
      setDeviceIdFlag(false),
      setUidFlag(false),
      setXjusernameFlag(false),
      setXjpasswordFlag(false),
      timer(new QTimer(this))
{
}


/**
 * @brief DeviceSnHandler::handleDeviceSnCommand 处理小桔充电桩命令
 * 
 * @param fdResult 反馈标志
 * @param command 命令
 * @param jsonObj 
 * @param resultField 
 * @param logPrefix 
 * @param dataField 
 * @return QString 
 */
QString DeviceSnHandler::handleDeviceSnCommand(bool &fdResult,const QString &command, const QJsonObject &jsonObj, const QString &resultField, const QString &logPrefix, const QString &dataField)
{
    qDebug() << logPrefix << "回复";
    QJsonValue resultValue = jsonObj.value(resultField);
    // 如果字段未定义，则返回
    if (resultValue.isUndefined())
    {
        qDebug() << resultField << "字段不存在";
        return resultField + "字段不存在";
    }

    // 设置设备序列号
    if (command == COM_SET_XJ_EQU_ID)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            setDeviceIdFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setDeviceIdFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 获取设备序列号
    else if (command == COM_GET_XJ_EQU_ID)
    {
        // 如果字段是数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            QJsonArray dataArray = resultValue.toArray();
            if (dataArray.size() > 0)
            {
                // 获取数组中的第一个对象
                QJsonObject dataObj = dataArray.at(0).toObject();
                // 如果字段存在
                if (dataObj.contains(dataField))
                {
                    QString deviceSn = dataObj.value(dataField).toString();
                    setDeviceIdFlag = true;
                    fdResult = true;
                    timer->stop();
                    qDebug() << logPrefix << "成功：" << deviceSn;
                    return logPrefix + "成功：" + deviceSn;
                }
                else
                {
                    qDebug() << dataField << "字段不存在";
                    return "字段不存在";
                }
            }
            else
            {
                qDebug() << "Data 数组为空";
                return "Data 数组为空";
            }
        }
        else
        {
            qDebug() << "Data 字段不是数组";
            return "Data 字段不是数组";
        }
    }
    // IC卡 UID 写入
    else if (command == COM_SET_CARD_UID)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            setUidFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setUidFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // IC卡 UID 读取
    else if (command == COM_GET_CARD_UID)
    {
        // 先判断字段是否为数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            if (resultValue.isArray())
            {
                // 将字段转换为数组
                QJsonArray dataArray = resultValue.toArray();
                if (dataArray.size() > 0)
                {
                    // 获取数组中的第一个对象
                    QJsonObject dataObj = dataArray.at(0).toObject();
                    // 如果字段存在
                    if (dataObj.contains(dataField))
                    {
                        QString deviceSn = dataObj.value(dataField).toString();
                        setUidFlag = true;
                        fdResult = true;
                        timer->stop();
                        qDebug() << logPrefix << "成功：" << deviceSn;
                        // 保留前16个字符
                        deviceSn = deviceSn.left(16);
                        return logPrefix + "成功：" + deviceSn;
                    }
                    else
                    {
                        qDebug() << dataField << "字段不存在";
                        return "字段不存在";
                    }
                }
                else
                {
                    qDebug() << "Data 数组为空";
                    return "Data 数组为空";
                }
            }
            else
            {
                qDebug() << "Data 字段不是数组";
                return "Data 字段不是数组";
            }
        }
    }
    // 设置小橘用户名
    else if (command == COM_SET_XJ_UNAME)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            setXjusernameFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setXjusernameFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 获取小橘用户名
    else if (command == COM_GET_XJ_UNAME)
    {
        // 先判断字段是否为数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            if (resultValue.isArray())
            {
                // 将字段转换为数组
                QJsonArray dataArray = resultValue.toArray();
                if (dataArray.size() > 0)
                {
                    // 获取数组中的第一个对象
                    QJsonObject dataObj = dataArray.at(0).toObject();
                    // 如果字段存在
                    if (dataObj.contains(dataField))
                    {
                        QString deviceSn = dataObj.value(dataField).toString();
                        setXjusernameFlag = true;
                        fdResult = true;
                        timer->stop();
                        qDebug() << logPrefix << "成功：" << deviceSn;
                        return logPrefix + "成功：" + deviceSn;
                    }
                    else
                    {
                        qDebug() << dataField << "字段不存在";
                        return "字段不存在";
                    }
                }
                else
                {
                    qDebug() << "Data 数组为空";
                    return "Data 数组为空";
                }
            }
            else
            {
                qDebug() << "Data 字段不是数组";
                return "Data 字段不是数组";
            }
        }
    }
    // 设置小橘密码
    else if (command == COM_SET_XJ_PASSWORD)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            setXjpasswordFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setXjpasswordFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 获取小橘密码
    else if (command == COM_GET_XJ_PASSWORD)
    {
        // 先判断字段是否为数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            if (resultValue.isArray())
            {
                // 将字段转换为数组
                QJsonArray dataArray = resultValue.toArray();
                if (dataArray.size() > 0)
                {
                    // 获取数组中的第一个对象
                    QJsonObject dataObj = dataArray.at(0).toObject();
                    // 如果字段存在
                    if (dataObj.contains(dataField))
                    {
                        QString deviceSn = dataObj.value(dataField).toString();
                        setXjpasswordFlag = true;
                        fdResult = true;
                        timer->stop();
                        qDebug() << logPrefix << "成功：" << deviceSn;
                        return logPrefix + "成功：" + deviceSn;
                    }
                    else
                    {
                        qDebug() << dataField << "字段不存在";
                        return "字段不存在";
                    }
                }
                else
                {
                    qDebug() << "Data 数组为空";
                    return "Data 数组为空";
                }
            }
            else
            {
                qDebug() << "Data 字段不是数组";
                return "Data 字段不是数组";
            }
        }
    }
    // 继电器闭合
    else if (command == COM_RELAY_ON)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 自动校准
    else if (command == COM_AUTO_CAL_EMU)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 南网设备IP设置
    else if (command == COM_SET_NW_EQU_IP)
    {
        int result = resultValue.toInt();
        if (result == 0)
        {
            setXjpasswordFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setXjpasswordFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    // 南网设备IP获取
    else if (command == COM_GET_NW_EQU_IP)
    {
        // 先判断字段是否为数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            if (resultValue.isArray())
            {
                // 将字段转换为数组
                QJsonArray dataArray = resultValue.toArray();
                if (dataArray.size() > 0)
                {
                    // 获取数组中的第一个对象
                    QJsonObject dataObj = dataArray.at(0).toObject();
                    // 如果字段存在
                    if (dataObj.contains(dataField))
                    {
                        QString deviceSn = dataObj.value(dataField).toString();
                        setXjpasswordFlag = true;
                        fdResult = true;
                        timer->stop();
                        qDebug() << logPrefix << "成功：" << deviceSn;
                        return logPrefix + "成功：" + deviceSn;
                    }
                    else
                    {
                        qDebug() << dataField << "字段不存在";
                        return "字段不存在";
                    }
                }
                else
                {
                    qDebug() << "Data 数组为空";
                    return "Data 数组为空";
                }
            }
            else
            {
                qDebug() << "Data 字段不是数组";
                return "Data 字段不是数组";
            }
        }
    }
    // 南网设备ID获取
    else if (command == COM_GET_NW_EQU_ID)
    {
        // 先判断字段是否为数组
        if (resultValue.isArray())
        {
            // 将字段转换为数组
            if (resultValue.isArray())
            {
                // 将字段转换为数组
                QJsonArray dataArray = resultValue.toArray();
                if (dataArray.size() > 0)
                {
                    // 获取数组中的第一个对象
                    QJsonObject dataObj = dataArray.at(0).toObject();
                    // 如果字段存在
                    if (dataObj.contains(dataField))
                    {
                        QString deviceSn = dataObj.value(dataField).toString();
                        // deviceSn去掉之间的空格
                        deviceSn = deviceSn.simplified();
                        setXjpasswordFlag = true;
                        fdResult = true;
                        timer->stop();
                        qDebug() << logPrefix << "成功：" << deviceSn;
                        return logPrefix + "成功：" + deviceSn;
                    }
                    else
                    {
                        qDebug() << dataField << "字段不存在";
                        return "字段不存在";
                    }
                }
                else
                {
                    qDebug() << "Data 数组为空";
                    return "Data 数组为空";
                }
            }
            else
            {
                qDebug() << "Data 字段不是数组";
                return "Data 字段不是数组";
            }
        }
    }
    // 南网设备ID设置
    else if (command == COM_SET_NW_EQU_ID)
    {
        int result = resultValue.toInt();
        if (result != 1)
        {
            setXjpasswordFlag = true;
            qDebug() << logPrefix << "失败";
            return logPrefix + "失败";
        }
        else
        {
            setXjpasswordFlag = true;
            fdResult = true;
            timer->stop();
            qDebug() << logPrefix << "成功";
            return logPrefix + "成功";
        }
    }
    else
    {
        qDebug() << "未知命令：" << command;
        return "未知命令";
    }
    return "NULL";
}
