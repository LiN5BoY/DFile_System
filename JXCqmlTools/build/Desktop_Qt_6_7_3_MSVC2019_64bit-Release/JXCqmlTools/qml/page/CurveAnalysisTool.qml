import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI
// import "../window"
import "../global"
import com.models.openglitem 1.0

FluScrollablePage{

    launchMode: FluPageType.SingleTask  // 设置页面的启动模式为单任务模式
    animationEnabled: false // 禁用页面切换动画
    header: Item{}  // 顶部工具栏



    FluText{
        id: curve_analysis_tool_text
        font: FluTextStyle.Body
        text: qsTr("高帧率实时曲线（如电流/电压波形）显示，支持大规模数据点的流畅渲染。")
    }

    OpenGLItem {
        id: openGLItem
        Layout.alignment: Qt.AlignCenter
        Layout.fillWidth: true
        Layout.preferredHeight: 300

        Component.onCompleted: {
            // 设置数据点
            this.setDataPoints([
                Qt.point(0.0, 0.0),
                Qt.point(0.5, 0.5),
                Qt.point(1.0, 0.0)
            ]);
        }

    }


}
