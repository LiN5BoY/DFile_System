#include "HcHandler.h"

#include "xlsxdocument.h"
#include "../models/Station.h"

#include <QFileDialog>

HcHandler::HcHandler(QObject *parent) : QObject(parent)
{
}

/**
 * @brief 槽函数 处理读取且返回异常相关数据按钮时的事件
 */
void HcHandler::onHc_excel_census_station_judge_err_button_Clicked(const QString &station_name)
{
    qDebug() << "读取且返回异常相关数据按钮被点击了!";
    qDebug() << "站点名称: " << station_name;

    // 弹出打开文件对话框
    QString fileName = QFileDialog::getOpenFileName(nullptr, "打开文件", "", "所有文件 (*.*);;Excel 文件 (*.xlsx)");
    // 检查用户是否选择了文件
    if (!fileName.isEmpty()) {
        qDebug() << "用户选择的文件: " << fileName;
        // 在这里处理文件
        QXlsx::Document xlsx(fileName);
        int row = 0 , col = 0;
        // 获取最大行数
        row = xlsx.dimension().rowCount();
        // 获取最大列数
        col = xlsx.dimension().columnCount();
        qDebug() << "行数: " << row;
        qDebug() << "列数: " << col;
        Station station = Station();
        int all_orders_count = 0;
        // 根据行数遍历
        for(int i = 1 ; i <= row ; i++){
            // 根据第11列的内容进行判断 首先拿取
            QString cell = xlsx.read(i, 11).toString();
            QString currcent_station_name = xlsx.read(i, 3).toString();
            // 判断current_station_name是否与station_name相等
            if(currcent_station_name != station_name){
                continue;
            }
            // 统一判断 是否为如下的其中之一匹配
            // BCL电池充电需求报文超时。
            // BCP充电参数配置报文超时。
            // BCS电池充电状态报文超时。
            // BMS达到终止条件停止。
            // BMS异常终止充电
            // BRM车辆辨识报文超时。
            // BRO 报文（0x00）接收超时
            // BRO 报文（0xAA）接收超时
            // BST电流过大
            // BST检测点2电压检测故障
            // BST绝缘故障
            // BST其他故障
            // SAAS手动关单
            // 车辆BCP报文和实际电压不符。
            // 充电接口电子锁故障
            // 充电接口过温故障
            // 充电控制器与计费控制单元通讯超时
            // 充电模块故障
            // 充电桩门禁故障
            // 充电桩内部通讯故障
            // 充电桩其他故障
            // 电表数据异常
            // 电表通讯故障
            // 电池电压异常。
            // 电池反接。
            // 动力蓄电池绝缘故障。
            // 功率控制模块通信故障
            // 急停按键被按下
            // 继电器外侧电压大于10v
            // 交流断路器故障
            // 交流防雷报警
            // 绝缘监测超时
            // 绝缘监测故障
            // 启动充电前直流输出接触器外侧电压小于充电机最小输出电压
            // 枪口异常
            // 枪未正确连接
            // 输出电流过流故障
            // 无有效电流停止
            // 桩停止充电响应超时
            station.incrementErrorCount(cell);
            all_orders_count++;
        }
        // 格式化错误统计
        QString formattedStats = formatErrorStatistics(station);
        // 最后加上总订单数
        formattedStats.append(QString("\n总订单数: %1 , 总异常数：%2 \n").arg(all_orders_count).arg(station.getErrorCount()));
        // 发出信号
        emit send_err_data(formattedStats);

    } else {
        qDebug() << "用户取消了文件选择";
    }

}

QString HcHandler::formatErrorStatistics(const Station &stats) const
{
    QStringList formattedList;
    QMap<QString, int> allCounts = stats.getAllErrorCounts();
    for (auto it = allCounts.begin(); it != allCounts.end(); ++it) {
        formattedList.append(QString("%1: %2\n").arg(it.key()).arg(it.value()));
    }
    return formattedList.join("\n");
}
