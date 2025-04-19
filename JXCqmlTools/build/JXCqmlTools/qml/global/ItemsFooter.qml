pragma Singleton

import QtQuick 2.15
import FluentUI


FluObject {

    property var navigationView //  导航视图
    property var paneItemMenu   //  侧边栏菜单

    id: footer_items

    FluPaneItemSeparator{}

    FluPaneItem{
        title:qsTr("About")
        menuDelegate: paneItemMenu
        icon: FluentIcons.Contact
        onTapListener: function(){
            // FluRouter.navigate("/about")
        }
    }


}
