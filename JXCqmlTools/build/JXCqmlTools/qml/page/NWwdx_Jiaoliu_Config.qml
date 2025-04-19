import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI
// import "../window"
import "../global"
import com.button.handler 1.0

FluScrollablePage{

    launchMode: FluPageType.SingleTask  // 设置页面的启动模式为单任务模式
    animationEnabled: false // 禁用页面切换动画
    header: Item{}  // 顶部工具栏

    // 串口更新处理方法
    function nwwdx_handleSerialPortsUpdated(ports) {
        nwwdx_serial_model.clear()
        // 信号处理函数 onSerialPortsUpdated 会自动接收 serialPortsUpdated 信号传递的参数。
        // 参数名称与 C++ 信号声明中的参数名称一致，即 port
        for (var i = 0; i < ports.length; ++i) {
            nwwdx_serial_model.append({text: ports[i]})
        }
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluButton {
            text: qsTr("检查串口")
            id: charger_serial_port_check_button_in_NWwdx
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: buttonHandler.onNWWDX_Serial_Port_Check_Clicked()
        }

        FluText {

            id: charger_serial_port_text_in_NWwdx
            text: "请选择串口"
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_check_button_in_NWwdx.right
                leftMargin: 50
            }

        }


        Column{
            id: charger_serial_port_column_in_NWwdx
            spacing: 5
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_text_in_NWwdx.right
                leftMargin: 50
            }
            FluComboBox {
                id: serialPortComboBox_in_NWwdx
                model: ListModel {
                    id: nwwdx_serial_model
                }
            }
        }

        FluFilledButton{
            id: charger_serial_open_button_in_NWwdx
            text: qsTr("打开串口")
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_column_in_NWwdx.right
                leftMargin : 50
            }
            onClicked: {
                var selectedPort = serialPortComboBox_in_NWwdx.currentText;
                if (selectedPort) {
                    buttonHandler.openNWWDXSerialPort(selectedPort);
                } else {
                    console.log("请选择一个串口");
                }
            }
        }

        FluFilledButton{
            id: charger_serial_close_button_in_NWwdx
            text: qsTr("关闭串口")
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_open_button_in_NWwdx.right
                leftMargin : 50
            }
            onClicked: {
                var selectedPort = serialPortComboBox_in_NWwdx.currentText;
                if (selectedPort) {
                    buttonHandler.closeNWWDXSerialPort(selectedPort);
                } else {
                    console.log("请选择一个串口");
                }
            }
        }
        Connections {
            target: buttonHandler
            // QML 使用 on 前缀加上信号名称来自动识别信号处理函数(首字母大写)
            function onNwwdx_serialPortsUpdated(ports) {
                nwwdx_handleSerialPortsUpdated(ports)
            }
            function onNwwdx_serialdataReceived(data) {
                charger_setting_message_multiline_text_box.text += data + "\n";
            }
        }
    }
}
