#include <iostream>
// 模板特化相关
// 1. 模板特化是指为特定类型或特定值提供不同的实现。
// 2. 模板特化可以分为全特化和偏特化。
// ——全特化是为某个具体类型提供实现，偏特化是为某个类型的某个特定部分提供实现。
template <typename T>
class Box
{
public:
    void display()
    {
        std::cout << "Generic Box" << std::endl;
    }
};

// 全特化
template <>
class Box<int>
{
public:
    void display()
    {
        std::cout << "Integer Box" << std::endl;
    }
};

void test_1()
{
    Box<double> box1; // 使用默认模板
    box1.display();   // 输出: Generic Box

    Box<int> box2;  // 使用全特化模板
    box2.display(); // 输出: Integer Box
}

// 偏特化
template <typename T1, typename T2>
class Pair
{
};

// 偏特化：当两个类型相同时
template <typename T>
class Pair<T, T>
{
public:
    void display()
    {
        std::cout << "Pair of same types" << std::endl;
    }
};

void test_2()
{
    Pair<int, int> pair1; // 使用偏特化模板
    pair1.display();      // 输出: Pair of same types

    Pair<int, double> pair2; // 使用默认模板
    // pair2.display();       // 错误: 没有定义 display() 方法
}

// SFINALE 使用情况
#include <type_traits>
// 主模板
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value)
{
    std::cout << "Integral value: " << value << std::endl;
}

// 特化版本
template <typename T>
typename std::enable_if<!std::is_integral<T>::value, void>::type
print(T value)
{
    std::cout << "Non-integral value: " << value << std::endl;
}

// 模板模板参数
#include <vector>
#include <list>
template <template <typename...> class Container, typename T>
class Wrapper
{
private:
    Container<T> data; // 使用模板模板参数 定义容器
public:
    void add(const T &value)
    {
        data.push_back(value); // 假设容器支持 push_back 方法
    }
    void display() const
    {
        for (const auto &item : data)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// 在编译期计算阶乘的模板例子
// 主模板 计算阶乘
template <int N>
struct Factorial
{
    // constexpr 是一个关键字，用于在编译时计算常量表达式。
    // 它可以用于变量、函数和类的成员函数，
    // 主要目的是提高程序的性能和安全性。
    static constexpr int value = N * Factorial<N - 1>::value; // 递归计算阶乘
};

// 基准条件 N = 0时 返回1
template <>
struct Factorial<0>
{
    static constexpr int value = 1; // 阶乘的基准条件
};