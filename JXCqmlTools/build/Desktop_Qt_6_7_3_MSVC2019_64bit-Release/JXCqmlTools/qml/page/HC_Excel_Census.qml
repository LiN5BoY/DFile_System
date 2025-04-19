import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI
// import "../window"
import "../global"
import com.hc.handler 1.0

FluScrollablePage{

    launchMode: FluPageType.SingleTask  // 设置页面的启动模式为单任务模式
    animationEnabled: false // 禁用页面切换动画
    header: Item{}  // 顶部工具栏



    FluText{
        font: FluTextStyle.Body
        text: qsTr("该界面用于处理慧充平台导出的EXCEL表格进行数据分析。")
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.35
            id: hc_excel_census_station_name_text_box
            placeholderText: qsTr("请输入场站名称")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("读取且返回异常相关数据（按全部数据处理）")
            id: hc_excel_census_station_judge_err_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: hc_excel_census_station_name_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 25  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                var station_name_text = hc_excel_census_station_name_text_box.text
                hcHandler.onHc_excel_census_station_judge_err_button_Clicked(station_name_text)
            }
        }
    }

    FluScrollablePage {
        Layout.fillWidth: true
        Layout.preferredHeight: 500  // 增加高度
        Layout.topMargin: 10
        padding: 10

        FluMultilineTextBox {
            placeholderText: "反馈信息将在这里显示"
            id: hc_excel_census_message_multiline_text_box
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Connections {
        target: hcHandler
        onSend_err_data: {
            hc_excel_census_message_multiline_text_box.text = data
        }
    }
}
