#include "user_manage.h"

// 添加用户
void UserManage::addUser(const std::shared_ptr<User> &user)
{
    users.push_back(user);
}

// 删除用户
void UserManage::deleteUser(const std::string &name)
{
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if ((*it)->getUserName() == name)
        {
            users.erase(it);
            return;
        }
    }
}

// 获取所有用户
std::vector<std::shared_ptr<User>> UserManage::getUsers() const
{
    return users;
}