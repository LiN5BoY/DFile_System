#ifndef STATION_H
#define STATION_H

// Your code here
#include <QString>
#include <QMap>
#include <QObject>

class Station : public QObject
{
    Q_OBJECT

public:
    explicit Station(QObject *parent = nullptr);

    void incrementErrorCount(const QString &error);
    int getErrorCount(const QString &error) const;
    QMap<QString, int> getAllErrorCounts() const;
    int getErrorCount() const;

private:
    QMap<QString, int> errorCounts; // 错误计数
    int all_err_count; // 总错误数
};


#endif // STATION_H
