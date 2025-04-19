#ifndef DEVICESNHANDLER_H
#define DEVICESNHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>

class DeviceSnHandler : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSnHandler(QObject *parent = nullptr);
    QString handleDeviceSnCommand(bool &fdResult,const QString &command, const QJsonObject &jsonObj, const QString &resultField, const QString &logPrefix, const QString &dataField = QString());



private:
    bool setDeviceIdFlag;   // 标志位 记录当前设备ID是否设置成功
    bool setUidFlag;        // 标志位 记录当前Uid是否设置成功
    bool setXjusernameFlag; // 标志位 记录当前小橘用户名是否设置成功
    bool setXjpasswordFlag; // 标志位 记录当前小橘密码是否设置成功
    QTimer *timer;
};


#endif // DEVICESNHANDLER_H
