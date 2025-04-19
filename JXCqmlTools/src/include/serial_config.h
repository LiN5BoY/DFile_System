#ifndef SERIAL_CONFIG_H
#define SERIAL_CONFIG_H

// 命令集合
#define COM_SET_CARD_UID                "COM_SET_CARD_UID"              // IC卡 UID 写入
#define COM_GET_CARD_UID                "COM_GET_CARD_UID"              // IC卡 UID 读取
#define COM_SET_XJ_EQU_ID               "COM_SET_XJ_EQU_ID"                //设置设备ID
#define COM_SET_XJ_UNAME                "COM_SET_XJ_UNAME"                 //设置小橘用户名
#define COM_SET_XJ_PASSWORD             "COM_SET_XJ_PASSWORD"              //设置小橘密码

#define COM_GET_XJ_EQU_ID               "COM_GET_XJ_EQU_ID"                //获取设备ID
#define COM_GET_XJ_UNAME                "COM_GET_XJ_UNAME"                 //获取小橘用户名
#define COM_GET_XJ_PASSWORD             "COM_GET_XJ_PASSWORD"              //获取小橘密码

#define COM_RELAY_ON				"COM_RELAY_ON"		//继电器闭合
#define COM_AUTO_CAL_EMU			"COM_AUTO_CAL_EMU"	//自动校准

//开启充电
#define REQ_START_CHARGE_INFO "{\"Command\" : \"%1\" }\r\n"

//自动校准
#define REQ_AUTO_CAL_EMU_INFO "{\"Command\" : \"%1\" }\r\n"

// 设置UID
#define REQ_SET_UID "{\"Command\" : \"%1\", \"Data\":[{ \"uid\": \"%2\" }]}\r\n"

// 设置小橘 EQID
#define REQ_SET_XJ_EQID "{\"Command\" : \"%1\", \"Data\":[{ \"XJEquiID\": \"%2\" }]}\r\n"

// 设置小橘 用户名
#define REQ_SET_XJ_UNAME "{\"Command\" : \"%1\", \"Data\":[{ \"XJUname\": \"%2\" }]}\r\n"

// 设置小橘 密码
#define REQ_SET_XJ_PWD "{\"Command\" : \"%1\", \"Data\":[{ \"XJPassword\": \"%2\" }]}\r\n"

// 获取小橘EQUID
#define REQ_GET_XJ_EQUID "{\"Command\" : \"%1\" }\r\n"

// 获取小橘密码
#define REQ_GET_XJ_PWD "{\"Command\" : \"%1\" }\r\n"

// 获取UID
#define REQ_GET_UID "{\"Command\" : \"%1\" }\r\n"

//自动校准
#define REQ_AUTO_CAL_EMU_INFO "{\"Command\" : \"%1\" }\r\n"

// --------------------------------------------------------  南网协议  -------------------------------------------------------- //
    
#define COM_SET_NW_EQU_IP              "COM_SET_NW_EQU_IP"                //设置南网设备IP
#define COM_SET_NW_EQU_ID              "COM_SET_NW_EQU_ID"                //设置南网设备ID

#define COM_GET_NW_EQU_IP              "COM_GET_NW_EQU_IP"                //获取南网设备IP
#define COM_GET_NW_EQU_ID              "COM_GET_NW_EQU_ID"                //获取南网设备ID

// 设置南网设备ID
#define REQ_SET_NW_EQU_ID "{\"Command\" : \"%1\", \"Data\":[{ \"NWEquiID\": \"%2\" }]}\r\n"
// 获取南网设备ID
#define REQ_GET_NW_EQU_ID "{\"Command\" : \"%1\" }\r\n"
// 设置南网设备IP
#define REQ_SET_NW_EQU_IP "{\"Command\" : \"%1\", \"Data\":[{ \"NWip\": \"%2:%3\" }]}\r\n"
// 获取南网设备IP
#define REQ_GET_NW_EQU_IP "{\"Command\" : \"%1\" }\r\n"

// --------------------------------------------------------  南网协议  -------------------------------------------------------- //

#endif // SERIAL_CONFIG_H

