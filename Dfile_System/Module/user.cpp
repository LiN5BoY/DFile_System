#include "user.h"
// <stdexcept> 是 C++ 标准库中的一个头文件，定义了一系列与标准异常相关的类。
// 这些异常类用于在程序运行时处理错误和异常情况，帮助开发者更好地管理和调试代码。
#include <stdexcept>

// 构造函数
User::User(const std::string &name, std::string password) : username(name), password(password) {}

// 析构函数的实现
User::~User() {}

// 获取用户名称的实现
std::string User::getUserName() const
{
    return username;
}

// 获取用户密码的实现
std::string User::getUserPassword() const
{
    return password;
}

// 设置用户密码的实现
void User::setUserPassword(const std::string &passwords)
{
    password = passwords;
}

// 设置用户名的实现
void User::setUserName(const std::string &name)
{
    username = name;
}