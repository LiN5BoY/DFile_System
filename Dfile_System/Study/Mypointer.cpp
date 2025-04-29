#include <iostream>

template <typename T>

class UniquePtr {
private:
	T* ptr;	//原始指针

public:
	explicit UniquePtr(T* p = nullptr) : ptr(p) {}

	// 禁止拷贝构造和拷贝赋值
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	// 转移构造
	UniquePtr& operator=(UniquePtr&& other) noexcept {
		if (this != &other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}

	// 重载 * 和 -> 操作符
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }

	// 获取指针
	T* get() const {return ptr;}

	// 释放所有权
	T* release() {
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	// 重置指针
	void reset(T* p = nullptr) {
		delete ptr;
		ptr = p;
	}

	// 析构函数
	~UniquePtr() {
		delete ptr;
	}

};


template <typename T>
class SharedPtr {
private:
	T* ptr;
	size_t* ref_count;

	void release() {
		if (ref_count && --(*ref_count) == 0) {
			delete ptr;
			delete ref_count;
		}
	}

public:
	// 构造函数
	explicit SharedPtr(T* p = nullptr) : ptr(p) , ref_count(new size_t(1)) {}

	// 拷贝构造
	SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
		if (ref_count) {
			++(*ref_count);
		}
	}

	// 拷贝赋值
	SharedPtr& operator=(const SharedPtr& other) {
		if (this != &other) {
			release();
			ptr = other.ptr;
			ref_count = other.ref_count;
			if (ref_count) {
				++(*ref_count);
			}
		}
	}

	// 重载* 和 ->操作符
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }

	// 获取引用计数
	size_t use_count() const { return ref_count ? *ref_count : 0; }

	// 析构函数
	~SharedPtr() {
		release();
	}
};

template <typename T>
class WeakPtr {
private:
	T* ptr;             // 原始指针
	size_t* ref_count;  // 引用计数

public:
	// 构造函数
	WeakPtr() : ptr(nullptr), ref_count(nullptr) {}

	// 从 shared_ptr 构造
	WeakPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {}

	// 检查指针是否有效
	bool expired() const {
		return !ref_count || *ref_count == 0;
	}

	// 锁定并返回 shared_ptr
	SharedPtr<T> lock() const {
		if (expired()) {
			return SharedPtr<T>();
		}
		return SharedPtr<T>(*this);
	}
};