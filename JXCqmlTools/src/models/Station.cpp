#include "Station.h"

// 构造函数
Station::Station(QObject *parent) : QObject(parent)
{
    // 初始化所有错误计数为0
    errorCounts["BCL电池充电需求报文超时。"] = 0;
    errorCounts["BCP充电参数配置报文超时。"] = 0;
    errorCounts["BCS电池充电状态报文超时。"] = 0;
    errorCounts["BMS达到终止条件停止。"] = 0;
    errorCounts["BMS异常终止充电"] = 0;
    errorCounts["BRM车辆辨识报文超时。"] = 0;
    errorCounts["BRO 报文（0x00）接收超时"] = 0;
    errorCounts["BRO 报文（0xAA）接收超时"] = 0;
    errorCounts["BST电流过大"] = 0;
    errorCounts["BST检测点2电压检测故障"] = 0;
    errorCounts["BST绝缘故障"] = 0;
    errorCounts["BST其他故障"] = 0;
    errorCounts["SAAS手动关单"] = 0;
    errorCounts["车辆BCP报文和实际电压不符。"] = 0;
    errorCounts["充电接口电子锁故障"] = 0;
    errorCounts["充电接口过温故障"] = 0;
    errorCounts["充电控制器与计费控制单元通讯超时"] = 0;
    errorCounts["充电模块故障"] = 0;
    errorCounts["充电桩门禁故障"] = 0;
    errorCounts["充电桩内部通讯故障"] = 0;
    errorCounts["充电桩其他故障"] = 0;
    errorCounts["电表数据异常"] = 0;
    errorCounts["电表通讯故障"] = 0;
    errorCounts["电池电压异常。"] = 0;
    errorCounts["电池反接。"] = 0;
    errorCounts["动力蓄电池绝缘故障。"] = 0;
    errorCounts["功率控制模块通信故障"] = 0;
    errorCounts["急停按键被按下"] = 0;
    errorCounts["继电器外侧电压大于10v"] = 0;
    errorCounts["交流断路器故障"] = 0;
    errorCounts["交流防雷报警"] = 0;
    errorCounts["绝缘监测超时"] = 0;
    errorCounts["绝缘监测故障"] = 0;
    errorCounts["启动充电前直流输出接触器外侧电压小于充电机最小输出电压"] = 0;
    errorCounts["枪口异常"] = 0;
    errorCounts["枪未正确连接"] = 0;
    errorCounts["输出电流过流故障"] = 0;
    errorCounts["无有效电流停止"] = 0;
    errorCounts["桩停止充电响应超时"] = 0;
    all_err_count = 0;
}

/**
 * @brief Station::incrementErrorCount 增加错误计数
 * @param error 错误名称
 */
void Station::incrementErrorCount(const QString &error)
{
    if (errorCounts.contains(error)) {
        all_err_count++;
        errorCounts[error]++;
    }
}

/**
 * @brief Station::getErrorCount 获取错误计数
 * @param error 错误名称
 * @return
 */
int Station::getErrorCount(const QString &error) const
{
    if (errorCounts.contains(error)) {
        return errorCounts[error];
    }
    return 0;
}

/**
 * @brief Station::getAllErrorCounts 获取所有错误计数
 * @return  错误计数
 */
QMap<QString, int> Station::getAllErrorCounts() const
{
    return errorCounts;
}

/**
 * @brief Station::getErrorCount 获取错误总数
 * @return
 */
int Station::getErrorCount() const
{
    return all_err_count;
}
