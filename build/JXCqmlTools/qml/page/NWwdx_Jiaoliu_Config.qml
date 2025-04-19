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

    FluText{
        font: FluTextStyle.Body
        text: qsTr("该界面用于配置南网协议所需要的设备ID,IP,端口等信息。")
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
                nwwdx_message_multiline_text_box.text += data + "\n";
            }
        }
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.5
            id: nwwdx_charger_id_text_box
            placeholderText: qsTr("请输入设备ID信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("设备ID设置")
            id: nwwdx_charger_id_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nwwdx_charger_id_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                var chargerId = nwwdx_charger_id_text_box.text;
                buttonHandler.onSet_NWWDX_Charger_Id_Clicked(chargerId)
            }
        }

        FluButton {
            text: qsTr("读取设备ID")
            id: nwwdx_charger_id_read_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nwwdx_charger_id_set_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                buttonHandler.onRead_NWWDX_Charger_Id_Clicked()
            }

        }
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.35
            id: nwwdx_charger_ip_text_box
            placeholderText: qsTr("请输入IP地址信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluTextBox {
            width: parent.width * 0.25
            id: nwwdx_charger_port_text_box
            placeholderText: qsTr("请输入端口信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nwwdx_charger_ip_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 20  // 添加一些左边距，增加间隔
        }

        FluButton {
            text: qsTr("设备IP设置")
            id: nwwdx_charger_ip_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nwwdx_charger_port_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 25  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                var nwwdx_ip_text = nwwdx_charger_ip_text_box.text;
                var nwwdx_port_text = nwwdx_charger_port_text_box.text;
                buttonHandler.onSet_NWWDX_IP_Port_Clicked(nwwdx_ip_text, nwwdx_port_text)
            }
        }

        FluButton {
            text: qsTr("读取设备IP")
            id: nwwdx_charger_ip_read_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nwwdx_charger_ip_set_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 25  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                buttonHandler.onRead_NWWDX_IP_Port_Clicked()
            }

        }
    }

    FluScrollablePage {
        Layout.fillWidth: true
        Layout.preferredHeight: 300  // 增加高度
        Layout.topMargin: 10
        padding: 10

        FluMultilineTextBox {
            placeholderText: "反馈信息将在这里显示"
            id: nwwdx_message_multiline_text_box
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
