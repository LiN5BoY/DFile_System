#ifndef JXCBUTTONHANDLER_H
#define JXCBUTTONHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>


class ButtonHandler : public QObject    // 定义一个类，继承自QObject
{
    Q_OBJECT    // 使用Q_OBJECT宏
public:
    explicit ButtonHandler(QObject *parent = nullptr);  // 构造函数

signals:
    void serialPortsUpdated(const QStringList &ports);  // 串口更新信号
    void serialdataReceived(const QString &data);  // 定义一个信号，用于传递串口读取到的数据
    // 南网微电轩相关信号
    void nwwdx_serialPortsUpdated(const QStringList &ports);  // 南网微电轩串口更新信号
    void nwwdx_serialdataReceived(const QString &data);  // 南网微电轩串口数据接收信号

public slots:
    void onSet_XJ_Charger_Id_Clicked(const QString &uid);
    void onRead_XJ_Charger_Id_Clicked();
    void onSet_XJ_Username_Clicked(const QString &username);
    void onSet_XJ_Password_Clicked(const QString &password);
    void onRead_XJ_Password_Clicked();
    void onRelay_On_Clicked();
    void onAuto_Cal_Emu_Clicked();
    void onSet_Card_Uid_Clicked(const QString &uid);
    void onRead_Card_Uid_Clicked();
    void onSerial_Port_Check_Clicked();
    void openSerialPort(const QString &portName);
    void closeSerialPort(const QString &portName);
    void readSerialData();
    void writeSerialData(const QString &data);
    void onTimerOut();
    // 南网微电轩相关操作
    void onNWWDX_Serial_Port_Check_Clicked();
    void openNWWDXSerialPort(const QString &portName);
    void closeNWWDXSerialPort(const QString &portName);
    void readNWWDXSerialData();
    void writeNWWDXSerialData(const QString &data);
    void onNWWDXTimerOut();
    void onSet_NWWDX_Charger_Id_Clicked(const QString &uid);
    void onRead_NWWDX_Charger_Id_Clicked();
    void onSet_NWWDX_IP_Port_Clicked(const QString &ip, const QString &port);
    void onRead_NWWDX_IP_Port_Clicked();

private:
    QSerialPort *serialPort;    // 串口对象
    QTimer *timer;              // 定时器
    bool setUidFlag;            // 标志位 记录当前Uid是否设置成功
    int timeCount;              // 计时器
    QString timeoutMsg;         // 超时消息
    bool feedbackReceived;          // 反馈标志位 记录是否收到反馈
    int timeoutCount;           // 超时计数
    QByteArray dataBuffer;         // 数据缓冲区

    // 以下是针对南网需要的相关信息操作
    QSerialPort *NWWDXSerialPort;    // 南网微电轩串口对象
    QTimer *NWWDXtimer;              // 南网微电轩定时器
    QString NWtimeoutMsg;         // 南网微电轩超时消息
    bool NWfeedbackReceived;          // 南网微电轩反馈标志位 记录是否收到反馈
    int NWtimeoutCount;           // 南网微电轩超时计数
    QByteArray NWdataBuffer;         // 南网微电轩数据缓冲区
};





#endif
