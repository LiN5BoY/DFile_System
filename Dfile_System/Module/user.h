#ifndef USER_H
#define USER_H

#include <string>

// User 声明
class User
{
public:
    // 构造函数
    User(const std::string &name, std::string password);
    // 析构函数
    ~User();
    // 获取用户名
    std::string getUserName() const;
    // 获取密码
    std::string getUserPassword() const;
    // 设置密码
    // 使用引用（&）而不是值（std::string）可以避免复制整个字符串对象。
    // 当传递一个大的字符串时，复制操作会消耗额外的时间和内存。引用只传递了一个指向原始对象的指针，因此效率更高。
    void setUserPassword(const std::string &passwords);
    // 设置用户名
    void setUserName(const std::string &name);

private:
    std::string username; // 用户名
    std::string password; // 密码
};

#endif