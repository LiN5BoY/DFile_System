pragma Singleton

import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI

FluObject{
    property var navigationView // 导航视图
    property var paneItemMenu   // 侧边栏菜单

    function rename(item, newName){
        // 如果新名称不为空且不为空格
        if(newName && newName.trim().length>0){
            item.title = newName
        }
    }


    FluPaneItemExpander{
        title: qsTr("交流桩相关")
        icon:FluentIcons.Wifi
        // 第一个子项 设置为串口配置
        FluPaneItem{
            title: qsTr("交流——小桔信息绑定")
            // 指定菜单委托，用于显示子项的上下文菜单
            menuDelegate: paneItemMenu
            // 指向要加载的 QML 页面的 URL
            url: "qrc:/qml/page/Xiaoju_Jiaoliu_Config.qml"
            onTap: { navigationView.push(url) } // 点击时，将页面推入导航视图
        }
        // 第二个子项 设置为南网信息绑定
        FluPaneItem{
            title: qsTr("交流——南网信息绑定")
            // 指定菜单委托，用于显示子项的上下文菜单
            menuDelegate: paneItemMenu
            // 指向要加载的 QML 页面的 URL
            url: "qrc:/qml/page/NWwdx_Jiaoliu_Config.qml"
            onTap: { navigationView.push(url) } // 点击时，将页面推入导航视图
        }
    }

    FluPaneItemExpander{
        title: qsTr("直流桩相关")
        icon:FluentIcons.Bluetooth
        // 第一个子项 设置为串口配置
        FluPaneItem{
            title: qsTr("直流——小桔信息绑定")
            // 指定菜单委托，用于显示子项的上下文菜单
            menuDelegate: paneItemMenu
            // 指向要加载的 QML 页面的 URL
            // url: "qrc:/qml/page/Xiaoju_Jiaoliu_Config.qml"
            // onTap: { navigationView.push(url) } // 点击时，将页面推入导航视图
        }
    }

    // 获取最近添加的数据
    function getRecentlyAddedData(){
        // 创建一个数组，用于存储最近添加的数据
        var arr = []
        // 获取导航视图中的所有项
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            // 获取当前项
            var item = items[i]
            // 如果当前项是 FluPaneItem 类型，并且有额外数据，并且有 recentlyAdded 属性
            if(item instanceof FluPaneItem && item.extra && item.extra.recentlyAdded){
                arr.push(item) // 将符合条件的项添加到数组中
            }
        }
        // 按照额外数据中的 order 属性排序
        arr.sort(function(o1,o2){ return o2.extra.order-o1.extra.order })
        return arr
    }

    // 获取最近更新的数据
    function getRecentlyUpdatedData(){
        // 创建一个数组，用于存储最近更新的数据
        var arr = []
        // 获取导航视图中的所有项
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            // 获取当前项
            var item = items[i]
            // 如果当前项是 FluPaneItem 类型，并且有额外数据，并且有 recentlyUpdated 属性
            if(item instanceof FluPaneItem && item.extra && item.extra.recentlyUpdated){
                arr.push(item) // 将符合条件的项添加到数组中
            }
        }
        return arr
    }

    // 获取搜索数据
    function getSearchData(){
        if(!navigationView){
            return  // 如果导航视图不存在，则返回
        }
        var arr = []    // 创建一个数组，用于存储搜索数据
        var items = navigationView.getItems();   // 获取导航视图中的所有项
        for (var i = 0; i < items.length; i++) {
            var item = items[i]  // 逐个遍历每个项
            if (item instanceof FluPaneItem) {
                // 检查项的父级是否为 FluPaneItemExpander
                if (item.parent instanceof FluPaneItemExpander) {
                    // 将父项标题和当前项标题组合，并保存键值
                    arr.push({ title: `${item.parent.title} -> ${item.title}`, key: item.key });
                } else {
                    // 直接保存当前项的标题和键值
                    arr.push({ title: item.title, key: item.key });
                }
            }
        }
        return arr  // 返回搜索结果数组
    }

    function startPageByItem(data){
        navigationView.startPageByItem(data)
    }

}
