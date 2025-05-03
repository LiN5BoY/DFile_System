#include <mutex>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
// ******************* 线程安全的单例模式 *******************//

class Singleton
{
public:
    static Singleton &getInstance()
    {
        static Singleton instance; // 局部静态变量，线程安全
        return instance;
    }

private:
    Singleton() {}                                    // 私有构造函数，防止外部实例化
    Singleton(const Singleton &) = delete;            // 禁用拷贝构造函数
    Singleton &operator=(const Singleton &) = delete; // 禁用赋值操作符
    ~Singleton() {}                                   // 私有析构函数，防止外部删除实例
};

// ******************* 线程安全的单例模式 *******************//

// ******************* 生产者消费者模型 *******************//

std::queue<int> buffer;     // 共享缓冲区
std::mutex mtx;             // 互斥锁
std::condition_variable cv; // 条件变量
const int maxSize = 10;     // 缓冲区最大容量

void producer(int id)
{
    for (int i = 0; i < 20; i++)
    {
        std::unique_lock<std::mutex> lock(mtx); // 上锁
        // 这里的[]{}是lambda表达式，表示条件变量的等待条件
        cv.wait(lock, []
                { return buffer.size() < maxSize; }); // 等待条件变量，直到缓冲区不满
        buffer.push(i);                               // 生产数据
        std::cout << "Producer " << id << " produced: " << i << std::endl;
        cv.notify_all(); // 通知消费者
    }
}

void consumer(int id)
{
    for (int i = 0; i < 20; i++)
    {
        std::unique_lock<std::mutex> lock(mtx); // 上锁
        cv.wait(lock, []
                { return !buffer.empty(); }); // 等待条件变量，直到缓冲区不空
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed " << item << std::endl;
        cv.notify_all(); // 通知生产者
    }
}

// ******************* 生产者消费者模型 *******************//