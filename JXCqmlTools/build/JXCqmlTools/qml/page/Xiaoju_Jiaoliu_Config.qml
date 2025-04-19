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
    function handleSerialPortsUpdated(ports) {
        serial_model.clear()
        // 信号处理函数 onSerialPortsUpdated 会自动接收 serialPortsUpdated 信号传递的参数。
        // 参数名称与 C++ 信号声明中的参数名称一致，即 port
        for (var i = 0; i < ports.length; ++i) {
            serial_model.append({text: ports[i]})
        }
    }

    FluText{
        text: qsTr("该界面用于配置交流桩的资产码，登录到小桔的用户名，以及密码的信息。")
    }

    FluText{
        text: qsTr("同时，该界面也用来进行继电器，以及自动校准相关操作的配置。")
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.65
            id: xj_charger_id_text_box
            placeholderText: qsTr("请输入资产码信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("资产码设置")
            id: xj_charger_id_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_charger_id_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                var chargerId = xj_charger_id_text_box.text;
                buttonHandler.onSet_XJ_Charger_Id_Clicked(chargerId)
            }
        }

        FluButton {
            text: qsTr("读取资产码")
            id: xj_charger_id_read_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_charger_id_set_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔

            // 绑定点击事件到 C++ 方法
            onClicked: {
                buttonHandler.onRead_XJ_Charger_Id_Clicked()
            }

        }

    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.65
            id: xj_username_text_box
            placeholderText: qsTr("请输入用户名信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("写入用户名")
            id: xj_username_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_username_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: {
                var username = xj_username_text_box.text;
                buttonHandler.onSet_XJ_Username_Clicked(username)
            }
        }

        // FluButton {
        //     text: qsTr("读取用户名")
        //     id: xj_username_read_button
        //     anchors.verticalCenter: parent.verticalCenter
        //     anchors.left: xj_username_set_button.right  // 直接使用 anchors 属性
        //     anchors.leftMargin: 10  // 添加一些左边距，增加间隔
        // }

    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.65
            id: xj_password_text_box
            placeholderText: qsTr("请输入密码信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("写入密码")
            id: xj_password_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_password_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: {
                var password = xj_password_text_box.text;
                buttonHandler.onSet_XJ_Password_Clicked(password)
            }
        }

        FluButton {
            text: qsTr("读取密码")
            id: xj_password_read_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_password_set_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: {
                buttonHandler.onRead_XJ_Password_Clicked()
            }
        }

    }


    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluButton {
            text: qsTr("检查串口")
            id: charger_serial_port_check_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: buttonHandler.onSerial_Port_Check_Clicked()
        }

        FluText {

            id: charger_serial_port_text
            text: "请选择串口"
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_check_button.right
                leftMargin: 10
            }

        }


        Column{
            id: charger_serial_port_column
            spacing: 5
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_text.right
                leftMargin: 10
            }
            FluComboBox {
                id: serialPortComboBox
                model: ListModel {
                    id: serial_model
                }
            }
        }

        FluFilledButton{
            id: charger_serial_open_button
            text: qsTr("打开串口")
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_port_column.right
                leftMargin : 10
            }
            onClicked: {
                var selectedPort = serialPortComboBox.currentText;
                if (selectedPort) {
                    buttonHandler.openSerialPort(selectedPort);
                } else {
                    console.log("请选择一个串口");
                }
            }
        }

        FluFilledButton{
            id: charger_serial_close_button
            text: qsTr("关闭串口")
            anchors{
                verticalCenter: parent.verticalCenter
                left: charger_serial_open_button.right
                leftMargin : 10
            }
            onClicked: {
                var selectedPort = serialPortComboBox.currentText;
                if (selectedPort) {
                    buttonHandler.closeSerialPort(selectedPort);
                } else {
                    console.log("请选择一个串口");
                }
            }
        }



        Connections {
            target: buttonHandler
            // QML 使用 on 前缀加上信号名称来自动识别信号处理函数(首字母大写)
            function onSerialPortsUpdated(ports) {
                handleSerialPortsUpdated(ports)
            }
            function onSerialdataReceived(data) {
                charger_setting_message_multiline_text_box.text += data + "\n";
            }
        }
        

        FluButton {
            text: qsTr("继电器闭合")
            id: charger_relay_on_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: charger_serial_close_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 100  // 添加一些左边距，增加间隔
            // 绑定点击事件到 C++ 方法
            onClicked: {
                buttonHandler.onRelay_On_Clicked()
            }
        }

        FluButton {
            text: qsTr("自动校准")
            id: charger_auto_calibrate_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: charger_relay_on_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 30  // 添加一些左边距，增加间隔
            // 绑定点击事件到 C++ 方法
            onClicked: {
                buttonHandler.onAuto_Cal_Emu_Clicked()
            }
        }

    }

    FluScrollablePage {
        Layout.fillWidth: true
        Layout.preferredHeight: 150  // 增加高度
        Layout.topMargin: 10
        padding: 10

        FluMultilineTextBox {
            id: charger_setting_message_multiline_text_box
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 68
        Layout.topMargin: 10
        padding: 10

        FluTextBox {
            width: parent.width * 0.65
            id: xj_card_info_text_box
            placeholderText: qsTr("请输入卡号信息")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left  // 直接使用 anchors 属性
        }

        FluButton {
            text: qsTr("写入卡号")
            id: xj_card_info_set_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_card_info_text_box.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: {
                var cardInfo = xj_card_info_text_box.text;
                buttonHandler.onSet_Card_Uid_Clicked(cardInfo)
            }
        }

        FluButton {
            text: qsTr("读取卡号")
            id: xj_card_info_read_button
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xj_card_info_set_button.right  // 直接使用 anchors 属性
            anchors.leftMargin: 10  // 添加一些左边距，增加间隔
            onClicked: {
                buttonHandler.onRead_Card_Uid_Clicked()
            }
        }

    }

}
