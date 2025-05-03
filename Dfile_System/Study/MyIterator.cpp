template <typename T>
class MyVec
{
public:
    // 嵌套类定义迭代器
    class iterator
    {
    private:
        T *ptr; // 指向当前元素的指针
    public:
        iterator(T *p) : ptr(p) {}      // 构造函数
        T &operator*() { return *ptr; } // 解引用操作符
        iterator &operator++()          // 前置++操作
        {
            ++ptr;
            return *this;
        }
        bool operator!=(const iterator &other) const
        {
            return ptr != other.ptr; // 不等于操作符
        }
    };

    // 容器的其他实现
    iterator begin() { return iterator(data); }      // 返回迭代器的起始位置
    iterator end() { return iterator(data + size); } // 返回迭代器的结束位置
private:
    T *data;     // 数据存储
    size_t size; // 容器大小
};