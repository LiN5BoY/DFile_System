#ifndef HCHANDLER_H
#define HCHANDLER_H


#include <QObject>
#include <QString>
#include <QTimer>
#include "../models/Station.h"

class HcHandler : public QObject    // 定义一个类，继承自QObject
{
    Q_OBJECT    // 使用Q_OBJECT宏
public:
    explicit HcHandler(QObject *parent = nullptr);  // 构造函数

signals:
    void send_err_data(const QString &data);

public slots:
    void onHc_excel_census_station_judge_err_button_Clicked(const QString &station_name);

private:
    // 成员函数声明末尾的 const 关键字表示该成员函数是一个常量成员函数（const member function）。
    // 这意味着该函数不会修改所属对象的任何成员变量。
    // 换句话说，常量成员函数保证了在函数内部不会改变对象的状态。
    QString formatErrorStatistics(const Station &stats) const;

};





#endif // HCHANDLER_H
