import QtQuick
import FluentUI

import "./global"


FluWindow {
    id: window
    width: 900
    height: 600
    visible: true
    // title: qsTr("JXCTools")
    // 窗口固定大小
    fixSize: true
    // 设置窗口的启动模式为单任务模式，即窗口不会启动多个实例
    launchMode: FluWindowType.SingleTask
    // 使窗口自适应 AppBar 大小
    fitsAppBarWindows: true

    // backgroundColor : "#EEF4F9"

    // 创建 FluAppBar，作为窗口的顶部工具栏
    appBar: FluAppBar {
        height: 30  // 设置 AppBar 的高度为 30 像素
        // 设置 AppBar 是否显示暗色模式的背景，`showDark: true` 使其显示暗色主题
        showDark: true
        // 定义关闭按钮的点击事件监听器，当关闭按钮被点击时，打开 `dialog_close` 对话框
        closeClickListener: () => { dialog_close.open() }
        // 设置该 AppBar 在窗口的 z-index 层级，z:7 确保它位于其他控件之上
        z: 7
    }


    FluContentDialog{
        id: dialog_close
        title: qsTr("Quit")  // 对话框标题为“Quit”
        message: qsTr("Are you sure you want to exit the program?")  // 对话框消息提示用户是否确定要退出程序
        negativeText: qsTr("Minimize")  // 负面按钮文本为“Minimize”
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton | FluContentDialogType.PositiveButton  // 对话框包含负面、中立和正面按钮
        onNegativeClicked: {
            timer_window_hide_delay.restart()
        }
        positiveText: qsTr("Quit")  // 正面按钮文本为“Quit”
        neutralText: qsTr("Cancel")  // 中立按钮文本为“Cancel”
        onPositiveClicked:{
            // 当用户点击正面按钮（Quit）时，退出程序
            FluRouter.exit(0)
        }
    }

    Component{
        id: nav_item_right_menu
        FluMenu{
            width: 186
            FluMenuItem{
                text: qsTr("Open in Separate Window")
                font: FluTextStyle.Caption
                onClicked: {
                    FluRouter.navigate("/pageWindow",{title:modelData.title,url:modelData.url})
                }
            }
        }
    }

    Flipable{
        id: flipable
        anchors.fill: parent
        property bool flipped: false  // 定义一个布尔属性，用于表示是否翻转
        property real flipAngle: 0    // 定义一个实数属性，用于表示翻转角度
        transform: Rotation {
            id: rotation
            origin.x: flipable.width / 2  // 设置旋转的原点为组件的中心
            origin.y: flipable.height / 2
            axis { x: 0; y: 1; z: 0 }     // 设置旋转轴为Y轴
            angle: flipable.flipAngle     // 绑定旋转角度到 flipAngle 属性
        }
        states: State {
            PropertyChanges { target: flipable; flipAngle: 180 }  // 当状态改变时，将 flipAngle 设置为 180 度
            when: flipable.flipped  // 当 flipped 属性为 true 时，触发状态改变
        }
        transitions: Transition {
            NumberAnimation {
                target: flipable
                property: "flipAngle"
                duration: 1000  // 动画持续时间为 1000 毫秒
                easing.type: Easing.OutCubic  // 使用缓动函数
            }
        }
        back: Item{
            anchors.fill: flipable
            visible: flipable.flipAngle !== 0 // 当 flipAngle 不为 0 时，显示该页面
            Row{
                id:layout_back_buttons
                z:8
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: FluTools.isMacos() ? 20 : 5 // 如果是 macOS 系统，设置顶部边距为 20 像素，否则设置为 5 像素
                    leftMargin: 5
                }
                FluIconButton{
                    iconSource: FluentIcons.ChromeBack
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        flipable.flipped = false // 当点击按钮时，将 flipped 属性设置为 false，翻转到正面
                    }
                }
                FluIconButton{
                    iconSource: FluentIcons.Sync
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        loader.reload() // 当点击按钮时，重新加载页面
                    }
                }
            }
        }
        front: Item {
            id: page_front
            visible: flipable.flipAngle !== 180  // 当 flipAngle 不为 180 时，显示 front 面
            anchors.fill: flipable
            FluNavigationView {
                property int clickCount: 0  // 定义一个整型属性，用于记录点击次数
                id: nav_view
                width: parent.width
                height: parent.height
                z: 999
                pageMode: FluNavigationViewType.NoStack  // 设置页面模式为 NoStack
                items: ItemsOriginal
                footerItems: ItemsFooter
                topPadding: {
                    if (window.useSystemAppBar) {
                        return 0
                    }
                    return FluTools.isMacos() ? 20 : 0  // 根据操作系统设置上边距
                }
                displayMode: GlobalModel.displayMode
                logo: "qrc:/image/jxc_logo"  // 设置导航视图的 logo
                title: "JXC Tools"
                onLogoClicked: {
                    clickCount += 1
                    showSuccess("%1:%2".arg(qsTr("Click Time")).arg(clickCount))  // 显示点击次数
                    if (clickCount === 5) {
                        loader.reload()  // 当点击次数为 5 时，重新加载内容并翻转
                        flipable.flipped = true
                        clickCount = 0
                    }
                }
                autoSuggestBox: FluAutoSuggestBox {
                    iconSource: FluentIcons.Search
                    items: ItemsOriginal.getSearchData()
                    placeholderText: qsTr("Search")
                    onItemClicked: (data) => {
                        ItemsOriginal.startPageByItem(data)  // 点击搜索结果时，启动相应页面
                    }
                }
                Component.onCompleted: {
                    ItemsOriginal.navigationView = nav_view
                    ItemsOriginal.paneItemMenu = nav_item_right_menu
                    ItemsFooter.navigationView = nav_view
                    ItemsFooter.paneItemMenu = nav_item_right_menu
                    window.setHitTestVisible(nav_view.buttonMenu)
                    window.setHitTestVisible(nav_view.buttonBack)
                    window.setHitTestVisible(nav_view.imageLogo)
                    setCurrentIndex(0)
                }
            }
        }
    }


}
