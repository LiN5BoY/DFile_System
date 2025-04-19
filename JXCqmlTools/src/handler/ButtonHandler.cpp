#include "ButtonHandler.h"
#include "DeviceSnHandler.h"
#include "../include/serial_config.h"

/**
 * @brief ButtonHandler::ButtonHandler 构造函数
 * @param parent
 */
ButtonHandler::ButtonHandler(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort(this);
    timer = new QTimer(this);
    setUidFlag = false;
    timeCount = 0;
    feedbackReceived = false;
    timeoutMsg = "操作超时，未收到反馈";
    timeoutCount = 0;
    dataBuffer.clear();
    connect(timer, &QTimer::timeout, this, &ButtonHandler::onTimerOut);

    // 南网微电轩相关初始化
    NWWDXSerialPort = new QSerialPort(this);
    NWWDXtimer = new QTimer(this);
    NWtimeoutMsg = "操作超时，未收到反馈";
    NWfeedbackReceived = false;
    NWtimeoutCount = 0;
    NWdataBuffer.clear();
    connect(NWWDXtimer, &QTimer::timeout, this, &ButtonHandler::onNWWDXTimerOut);
}

/**
 * @brief 槽函数 处理小桔充电桩资产码设置按钮被点击的事件
 */
void ButtonHandler::onSet_XJ_Charger_Id_Clicked(const QString &uid)
{
    qDebug() << "资产码设置按钮被点击了!";
    // 这里可以处理资产码设置的逻辑
    // 需要判断是否符合规格，规格：16个字符且全为数字，如果不符合则弹出提示框
    if (uid.length() != 16 || !uid.toULongLong())
    {
        qDebug() << "资产码长度不符合规格";
        emit serialdataReceived("资产码长度不符合规格");
        return;
    }
    QString strObj = QString(REQ_SET_XJ_EQID).arg(COM_SET_XJ_EQU_ID, uid);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理小桔充电桩资产码读取按钮被点击的事件
 */
void ButtonHandler::onRead_XJ_Charger_Id_Clicked()
{
    qDebug() << "读取资产码按钮被点击了!";
    // 处理读取资产码的逻辑
    QString strObj = QString(REQ_GET_XJ_EQUID).arg(COM_GET_XJ_EQU_ID);
    setUidFlag = false;
    feedbackReceived = false;
    ; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理小桔充电桩用户名设置按钮被点击的事件
 */
void ButtonHandler::onSet_XJ_Username_Clicked(const QString &username)
{
    qDebug() << "用户名设置按钮被点击了!";
    // 处理用户名设置的逻辑
    QString strObj = QString(REQ_SET_XJ_UNAME).arg(COM_SET_XJ_UNAME, username);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理小桔充电桩密码设置按钮被点击的事件
 */
void ButtonHandler::onSet_XJ_Password_Clicked(const QString &password)
{
    qDebug() << "密码设置按钮被点击了!";
    // 处理密码设置的逻辑
    QString strObj = QString(REQ_SET_XJ_PWD).arg(COM_SET_XJ_PASSWORD, password);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理小桔充电桩密码读取按钮被点击的事件
 */
void ButtonHandler::onRead_XJ_Password_Clicked()
{
    qDebug() << "读取密码按钮被点击了!";
    // 处理读取密码的逻辑
    QString strObj = QString(REQ_GET_XJ_PWD).arg(COM_GET_XJ_PASSWORD);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理串口检测按钮被点击的事件
 */
void ButtonHandler::onSerial_Port_Check_Clicked()
{
    qDebug() << "串口检测按钮被点击了!";
    // 处理串口检测的逻辑
    QStringList serialPortNameList;
    // 获取当前系统上所有可用的串口
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports)
    {
        // 将串口名字添加到列表中
        serialPortNameList << info.portName();
    }
    emit serialPortsUpdated(serialPortNameList);
}

/**
 * @brief 槽函数 处理继电器闭合按钮被点击的事件
 * 
 */
void ButtonHandler::onRelay_On_Clicked()
{
    qDebug() << "继电器闭合按钮被点击了!";
    // 处理继电器闭合的逻辑
    QString strObj = QString(REQ_START_CHARGE_INFO).arg(COM_RELAY_ON);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理自动校准按钮被点击的事件
 * 
 */
void ButtonHandler::onAuto_Cal_Emu_Clicked()
{
    qDebug() << "自动校准按钮被点击了!";
    // 处理自动校准的逻辑
    QString strObj = QString(REQ_AUTO_CAL_EMU_INFO).arg(COM_AUTO_CAL_EMU);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理IC卡UID设置按钮被点击的事件
 * 
 * @param uid 
 */
void ButtonHandler::onSet_Card_Uid_Clicked(const QString &uid)
{
    qDebug() << "IC卡UID设置按钮被点击了!";
    // 这里可以处理IC卡UID设置的逻辑
    // 需要判断是否符合规格，规格：16个字符且全为数字，如果不符合则弹出提示框
    if (uid.length() != 16 || !uid.toULongLong())
    {
        qDebug() << "IC卡UID长度不符合规格";
        emit serialdataReceived("IC卡UID长度不符合规格");
        return;
    }
    QString strObj = QString(REQ_SET_UID).arg(COM_SET_CARD_UID, uid);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}

/**
 * @brief 槽函数 处理IC卡UID读取按钮被点击的事件
 * 
 */
void ButtonHandler::onRead_Card_Uid_Clicked()
{
    qDebug() << "读取IC卡UID按钮被点击了!";
    // 处理读取IC卡UID的逻辑
    QString strObj = QString(REQ_GET_UID).arg(COM_GET_CARD_UID);
    setUidFlag = false;
    feedbackReceived = false; // 重置反馈标志
    writeSerialData(strObj);
    timeCount = 0;
    timer->start(2000);
}


/**
 * @brief ButtonHandler::openSerialPort 打开串口相关操作
 * @param portName 串口名字
 */
void ButtonHandler::openSerialPort(const QString &portName)
{
    qDebug() << "打开串口" << portName;
    if (!serialPort)
    {
        qDebug() << "serialPort对象未初始化";
        return;
    }
    // 这里可以处理打开串口的逻辑
    if (serialPort->isOpen())
    {
        // 如果串口已经打开，先关闭串口
        serialPort->close();
    }
    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    // 设置8位 无校验位 1位停止位
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    if (serialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "打开串口成功：" << portName;
        emit serialdataReceived("打开串口成功");
        connect(serialPort, &QSerialPort::readyRead, this, &ButtonHandler::readSerialData);
    }
    else
    {
        qDebug() << "打开串口失败：" << portName;
        emit serialdataReceived("打开串口失败");
    }
}

/**
 * @brief ButtonHandler::closeSerialPort 关闭串口
 * @param portName 串口名字
 */
void ButtonHandler::closeSerialPort(const QString &portName)
{
    qDebug() << "关闭串口" << portName;
    if (!serialPort)
    {
        qDebug() << "serialPort对象未初始化";
        return;
    }
    // 这里可以处理关闭串口的逻辑
    if (serialPort->isOpen())
    {
        serialPort->close();
        qDebug() << "关闭串口成功：" << portName;
        emit serialdataReceived("关闭串口成功");
    }
    else
    {
        qDebug() << "串口未打开：" << portName;
        emit serialdataReceived("串口未打开");
    }
}

/**
 * @brief ButtonHandler::readData 读取串口数据
 */
void ButtonHandler::readSerialData()
{
    QByteArray data = serialPort->readAll();
    qDebug() << "读取到数据：" << data;
    // 现阶段存储到dataBuffer内
    dataBuffer.append(data);

    // 检查缓冲区内是否包含完整的 JSON 数据
    int jsonStartIndex = dataBuffer.indexOf('{');
    int jsonEndIndex = dataBuffer.lastIndexOf('}');

    if (jsonStartIndex != -1 && jsonEndIndex != -1 && jsonEndIndex > jsonStartIndex)
    {
        // 提取完整的 JSON 数据
        QByteArray jsonData = dataBuffer.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
        // 清空缓冲区
        dataBuffer.remove(0,jsonEndIndex + 1);

        // 移除无效字符
        jsonData.replace("\xFF", "");

        // 处理 JSON 数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        qDebug() << "解析 JSON 数据：" << jsonData;
        qDebug() << "JSON 数据解析结果：" << jsonDoc;
    
        if (!jsonDoc.isObject())
        {
            qDebug() << "收到的数据不是有效的 JSON 对象";
            return;
        }
        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.contains("Command"))
        {
            qDebug() << "JSON 对象中不包含 Command 字段";
            return;
        }

        QString command = jsonObj.value("Command").toString();
        qDebug() << "Command:" << command;
        DeviceSnHandler deviceSnHandler; // 创建 DeviceSnHandler 类的实例
        QString ret_msg;
        if (command == COM_SET_XJ_EQU_ID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "设置XJEQID回复");
        }
        else if (command == COM_GET_XJ_EQU_ID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Data", "获取XJEQID", "XJEquiID");
        }
        else if (command == COM_SET_CARD_UID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "设置IC卡UID回复");
        }
        else if (command == COM_GET_CARD_UID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Data", "获取IC卡UID", "uid");
        }
        else if (command == COM_SET_XJ_UNAME)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "设置XJ用户名回复");
        }
        else if (command == COM_SET_XJ_PASSWORD)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "设置XJ密码回复");
        }
        else if (command == COM_GET_XJ_PASSWORD)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Data", "获取XJ密码", "XJPassword");
        }
        else if (command == COM_RELAY_ON)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "继电器闭合回复");
        }
        else if (command == COM_AUTO_CAL_EMU)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(feedbackReceived, command, jsonObj, "Result", "自动校准回复");
        }
        // 在这里发送 serialdataReceived 信号，发送解析后的消息
        emit serialdataReceived(ret_msg);
    }

    
}

/**
 * @brief ButtonHandler::writeSerialData 向串口写数据
 * @param data 要写入的数据
 */
void ButtonHandler::writeSerialData(const QString &data)
{
    qDebug() << "写入数据：" << data;
    QByteArray byteArray;
    byteArray.resize(data.length());
    for (int i = 0; i < data.length(); ++i)
    {
        // 将QString转换为char
        byteArray[i] = static_cast<char>(data.at(i).unicode());
    }
    serialPort->write(byteArray);
}

/**
 * @brief ButtonHandler::onTimerOut 定时器超时处理函数
 */
void ButtonHandler::onTimerOut()
{
    timeoutCount++;
    if (!feedbackReceived)
    {
        timeoutCount++;
        if (timeoutCount > 3)
        {
            timer->stop();
            qDebug() << "定时器超时!";
            // 在这里发送 serialdataReceived 信号，发送超时消息
            emit serialdataReceived("操作超时，未收到反馈");
            return;
        }
    }
}

/**
 * @brief 槽函数 处理南网微电轩串口检测按钮被点击的事件
 */
void ButtonHandler::onNWWDX_Serial_Port_Check_Clicked()
{
    qDebug() << "南网微电轩串口检测按钮被点击了!";
    // 处理南网微电轩串口检测的逻辑
    QStringList serialPortNameList;
    // 获取当前系统上所有可用的串口
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports)
    {
        // 将串口名字添加到列表中
        serialPortNameList << info.portName();
    }
    emit nwwdx_serialPortsUpdated(serialPortNameList);
}

/**
 * @brief ButtonHandler::onNWWDXTimerOut 南网微电轩定时器超时处理函数
 */
void ButtonHandler::onNWWDXTimerOut()
{
    NWtimeoutCount++;
    if (!NWfeedbackReceived)
    {
        NWtimeoutCount++;
        if (NWtimeoutCount > 3)
        {
            NWWDXtimer->stop();
            qDebug() << "南网微电轩定时器超时!";
            // 在这里发送 nwwdx_serialdataReceived 信号，发送超时消息
            emit nwwdx_serialdataReceived("操作超时，未收到反馈");
            return;
        }
    }
}


/**
 * @brief ButtonHandler::openNWWDXSerialPort 打开南网微电轩串口相关操作
 * @param portName 串口名字
 */
void ButtonHandler::openNWWDXSerialPort(const QString &portName)
{
    qDebug() << "打开南网微电轩串口" << portName;
    if (!NWWDXSerialPort)
    {
        qDebug() << "NWWDXSerialPort对象未初始化";
        return;
    }
    // 这里可以处理打开南网微电轩串口的逻辑
    if (NWWDXSerialPort->isOpen())
    {
        // 如果串口已经打开，先关闭串口
        NWWDXSerialPort->close();
    }
    NWWDXSerialPort->setPortName(portName);
    NWWDXSerialPort->setBaudRate(QSerialPort::Baud115200);
    // 设置8位 无校验位 1位停止位
    NWWDXSerialPort->setDataBits(QSerialPort::Data8);
    NWWDXSerialPort->setParity(QSerialPort::NoParity);
    NWWDXSerialPort->setStopBits(QSerialPort::OneStop);
    if (NWWDXSerialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "打开南网微电轩串口成功：" << portName;
        emit nwwdx_serialdataReceived("打开南网微电轩串口成功");
        connect(NWWDXSerialPort, &QSerialPort::readyRead, this, &ButtonHandler::readNWWDXSerialData);
    }
    else
    {
        qDebug() << "打开南网微电轩串口失败：" << portName;
        emit nwwdx_serialdataReceived("打开南网微电轩串口失败");
    }
}

/**
 * @brief ButtonHandler::closeNWWDXSerialPort 关闭南网微电轩串口
 * @param portName 串口名字
 */
void ButtonHandler::closeNWWDXSerialPort(const QString &portName)
{
    qDebug() << "关闭南网微电轩串口" << portName;
    if (!NWWDXSerialPort)
    {
        qDebug() << "NWWDXSerialPort对象未初始化";
        return;
    }
    // 这里可以处理关闭南网微电轩串口的逻辑
    if (NWWDXSerialPort->isOpen())
    {
        NWWDXSerialPort->close();
        qDebug() << "关闭南网微电轩串口成功：" << portName;
        emit nwwdx_serialdataReceived("关闭南网微电轩串口成功");
    }
    else
    {
        qDebug() << "南网微电轩串口未打开：" << portName;
        emit nwwdx_serialdataReceived("南网微电轩串口未打开");
    }
}

/**
 * @brief ButtonHandler::readNWWDXSerialData 读取南网微电轩串口数据
 */
void ButtonHandler::readNWWDXSerialData()
{
    QByteArray data = NWWDXSerialPort->readAll();
    qDebug() << "读取到南网微电轩数据：" << data;
    // 现阶段存储到dataBuffer内
    dataBuffer.append(data);

    // 检查缓冲区内是否包含完整的 JSON 数据
    int jsonStartIndex = dataBuffer.indexOf('{');
    int jsonEndIndex = dataBuffer.lastIndexOf('}');

    if (jsonStartIndex != -1 && jsonEndIndex != -1 && jsonEndIndex > jsonStartIndex)
    {
        // 提取完整的 JSON 数据
        QByteArray jsonData = dataBuffer.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
        // 清空缓冲区
        dataBuffer.remove(0,jsonEndIndex + 1);

        // 移除无效字符
        jsonData.replace("\xFF", "");

        // 处理 JSON 数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        qDebug() << "解析 JSON 数据：" << jsonData;
        qDebug() << "JSON 数据解析结果：" << jsonDoc;
    
        if (!jsonDoc.isObject())
        {
            qDebug() << "收到的数据不是有效的 JSON 对象";
            return;
        }
        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.contains("Command"))
        {
            qDebug() << "JSON 对象中不包含 Command 字段";
            return;
        }

        QString command = jsonObj.value("Command").toString();
        qDebug() << "Command:" << command;
        DeviceSnHandler deviceSnHandler; // 创建 DeviceSnHandler 类的实例
        QString ret_msg;
        if (command == COM_SET_NW_EQU_IP)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(NWfeedbackReceived, command, jsonObj, "Result", "设置南网微电轩IP回复");
        }
        else if (command == COM_GET_NW_EQU_IP)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(NWfeedbackReceived, command, jsonObj, "Data", "获取南网微电轩IP", "NWip");
        }
        else if (command == COM_SET_NW_EQU_ID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(NWfeedbackReceived, command, jsonObj, "Result", "设置南网微电轩资产码回复");
        }
        else if (command == COM_GET_NW_EQU_ID)
        {
            ret_msg = deviceSnHandler.handleDeviceSnCommand(NWfeedbackReceived, command, jsonObj, "Data", "获取南网微电轩资产码", "NWEquiID");
        }
        // 在这里发送 nwwdx_serialdataReceived 信号，发送解析后的消息
        emit nwwdx_serialdataReceived(ret_msg);
    }
}

/**
 * @brief ButtonHandler::writeNWWDXSerialData 向南网微电轩串口写数据
 * @param data 要写入的数据
 */
void ButtonHandler::writeNWWDXSerialData(const QString &data)
{
    qDebug() << "写入南网微电轩数据：" << data;
    QByteArray byteArray;
    byteArray.resize(data.length());
    for (int i = 0; i < data.length(); ++i)
    {
        // 将QString转换为char
        byteArray[i] = static_cast<char>(data.at(i).unicode());
    }
    NWWDXSerialPort->write(byteArray);
}

/**
 * @brief ButtonHandler::onSet_NWWDX_Charger_Id_Clicked 南网微电轩资产码设置按钮被点击的事件
 * 
 * @param uid 
 */
void ButtonHandler::onSet_NWWDX_Charger_Id_Clicked(const QString &uid)
{
    qDebug() << "南网微电轩资产码设置按钮被点击了!";
    // 这里可以处理资产码设置的逻辑
    // 需要判断是否符合规格，规格：16个字符且全为数字，如果不符合则弹出提示框
    if (uid.length() != 16 || !uid.toULongLong())
    {
        qDebug() << "资产码长度不符合规格";
        emit nwwdx_serialdataReceived("资产码长度不符合规格");
        return;
    }
    QString strObj = QString(REQ_SET_NW_EQU_ID).arg(COM_SET_NW_EQU_ID, uid);
    NWfeedbackReceived = false;
    writeNWWDXSerialData(strObj);
    NWWDXtimer->start(2000);
}

/**
 * @brief ButtonHandler::onRead_NWWDX_Charger_Id_Clicked 南网微电轩资产码读取按钮被点击的事件
 * 
 */
void ButtonHandler::onRead_NWWDX_Charger_Id_Clicked()
{
    qDebug() << "南网微电轩读取资产码按钮被点击了!";
    // 处理读取资产码的逻辑
    QString strObj = QString(REQ_GET_NW_EQU_ID).arg(COM_GET_NW_EQU_ID);
    NWfeedbackReceived = false;
    writeNWWDXSerialData(strObj);
    NWWDXtimer->start(2000);
}

/**
 * @brief ButtonHandler::onSet_NWWDX_Username_Clicked 南网微电轩用户名设置按钮被点击的事件
 * 
 * @param ip 
 * @param port 
 */
void ButtonHandler::onSet_NWWDX_IP_Port_Clicked(const QString &ip, const QString &port)
{
    qDebug() << "南网微电轩IP端口设置按钮被点击了!";
    // 这里可以处理IP端口设置的逻辑
    // 需要判断是否符合规格，规格：IP地址和端口号
    if (ip.isEmpty() || port.isEmpty())
    {
        qDebug() << "IP地址或端口号为空";
        emit nwwdx_serialdataReceived("IP地址或端口号为空");
        return;
    }
    QString strObj = QString(REQ_SET_NW_EQU_IP).arg(COM_SET_NW_EQU_IP).arg(ip).arg(port);
    qDebug() << "strObj:" << strObj;
    NWfeedbackReceived = false;
    writeNWWDXSerialData(strObj);
    NWWDXtimer->start(2000);
}

/**
 * @brief ButtonHandler::onRead_NWWDX_IP_Port_Clicked 南网微电轩IP端口读取按钮被点击的事件
 * 
 */
void ButtonHandler::onRead_NWWDX_IP_Port_Clicked()
{
    qDebug() << "南网微电轩读取IP端口按钮被点击了!";
    // 处理读取IP端口的逻辑
    QString strObj = QString(REQ_GET_NW_EQU_IP).arg(COM_GET_NW_EQU_IP);
    NWfeedbackReceived = false;
    writeNWWDXSerialData(strObj);
    NWWDXtimer->start(2000);
}
