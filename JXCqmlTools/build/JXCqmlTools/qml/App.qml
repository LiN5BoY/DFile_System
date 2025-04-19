import QtQuick
import FluentUI

FluLauncher {

    id: app

    Component.onCompleted: {
        // 初始化 FluentUI 应用
        FluApp.init(app)

        // 设置是否使用系统的 AppBar（应用程序顶部的工具栏）
        // 默认为 false，表示使用自定义的 AppBar，而不是系统默认的
        FluApp.useSystemAppBar = false

        // 设置是否启用动画效果，默认为 true
        // 若设置为 false，UI 动画效果将被禁用
        FluTheme.animationEnabled = true

        // 设置是否使用系统的字体，默认为 true
        // 如果为 true，应用将使用系统默认的字体；如果为 false，使用自定义字体
        FluTheme.nativeText = true

        // 设置路由映射，指定应用的默认首页为指定的 QML 文件
        FluRouter.routes = {
            "/" : "qrc:/qt/qml/JXCqmlTools/qml/MainWindow.qml",  // 将根路径映射到 QML 文件 MainWindow.qml
        }

        // 导航到应用的首页（"/"），启动应用时会显示 MainWindow.qml
        FluRouter.navigate("/")


    }

}
