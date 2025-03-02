#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "../Module/user.h"
#include <vector>
#include <memory>

// UserManage类的声明
class UserManage
{
public:
    // 添加用户
    void addUser(const std::shared_ptr<User> &user);
    // 删除用户
    void deleteUser(const std::string &name);
    // 获取所有用户
    std::vector<std::shared_ptr<User>> getUsers() const;

private:
    // 用户列表
    std::vector<std::shared_ptr<User>> users;
};

#endif // USER_MANAGE_H