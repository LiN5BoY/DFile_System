#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b)
{
    return a + b;
}

// 仿函数
struct Multiply
{
    int operator()(int a, int b) const
    {
        return a * b;
    }
};

void gofunction()
{
    // 使用 std::function 来包装普通函数
    std::function<int(int, int)> funcAdd = add;
    std::cout << "Add: " << funcAdd(3, 4) << std::endl;

    // 使用 std::function 来包装仿函数
    Multiply multiplyFunc;
    std::function<int(int, int)> funcMultiply = multiplyFunc;
    std::cout << "Multiply: " << funcMultiply(3, 4) << std::endl;

    // 使用 std::function 来包装 lambda 表达式
    std::function<int(int, int)> funcLambda = [](int a, int b)
    { return a - b; };
    std::cout << "Lambda: " << funcLambda(7, 4) << std::endl;
}