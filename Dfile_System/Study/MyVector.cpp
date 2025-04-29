// 实现一个支持 C++11 特性并具备异常安全（strong exception safety）的 `std::vector`，需要遵循以下步骤：
// 核心步骤
//1. **使用 `std::allocator_traits`**:
//   - `std::allocator_traits` 提供了对分配器的统一接口，支持 `std::allocator` 和自定义分配器。
//   - 使用 `std::allocator_traits` 操作内存时，能够适应不同类型的分配器。
//2. **异常安全保证（strong exception safety）**:
//   - 在操作（如插入、删除、扩容等）失败时，确保不会破坏原有数据状态。
//   - 通过 RAII 技术和临时数据结构来实现异常安全，避免直接操作原始数据。
//3. **动态扩容**:
//   - 使用 `std::allocator_traits` 分配和释放动态内存。
//   - 实现动态扩容策略，通常为当前容量的两倍。
//4. **迭代器失效管理**:
//   - 对于插入或删除操作，需要正确处理迭代器失效问题。

#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iterator>

// 这意味着在没有指定 Allocator 的情况下，模板将使用标准的 std::allocator 来处理内存分配。
// 这种设计使得容器在使用时可以灵活指定不同的分配器，支持自定义内存策略。
template <typename T, typename Allocator = std::allocator<T>>

class MyVector {
private:
	T* data_;	// 存储元素的指针
	size_t size_;	//当前元素数量
	size_t capacity_;	// 容器容量
	Allocator allocator_;	//分配器

	using AllocTraits = std::allocator_traits<Allocator>;

	// 分配内存且构造对象
	void allocate_and_construct(size_t n) {
		data_ = AllocTraits::allocate(allocator_, n);
		size_ = 0;
		capacity_ = n;
	}

	// 销毁并释放内存
	void destroy_and_deallocate() {
		for (size_t i = 0; i < size_; ++i) {
			AllocTraits::destory(allocator_, &data_[i]);
		}
		AllocTraits::deallocate(allocator_, data_, capacity_);
		data_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}

	// 扩容函数，确保新容量大于特定指定容量
	void reallocate(size_t new_capacity) {
		T* new_data = AllocTraits::allocate(allocator_, new_capacity);
		size_t i = 0;
		try {
			for (; i < size_; i++) {
				AllocTraits::construct(allocator_, &new_data[i], std::move_if_noexcept(data_[i]));
			}
		}
		catch (...) {
			// 回滚操作，释放新分配空间并抛出异常
			for (size_t j = 0; j < i; ++j) {
				AllocTraits::destory(allocator_, &new_data[j]);
			}
			AllocTraits::deallocate(allocator_, new_data, new_capacity);
			throw;
		}
		
		// 销毁旧内存并释放内存
		destroy_and_deallocate();

		data_ = new_data;
		capacity_ = new_capacity;
	}

	// 确保容量足够
	void ensure_capacity(size_t new_capacity) {
		if (new_capacity > capacity_) {
			size_t new_cap = std::max(new_capacity, capacity_ ? capacity_ * 2 : 1);
			reallocate(new_cap);
		}
	}

public:
	// 构造函数
	// 使用 explicit 可以提高代码的清晰度和安全性，防止意外的类型转换，从而减少潜在的错误。
	explicit MyVector(const Allocator & alloc = Allocator())
		: data_(nullptr) , size_(0),capacity_(0),allocator_(alloc){}

	explicit MyVector(size_t n, const T& value = T(), const Allocator& alloc = Allocator())
		: allocator_(alloc) {
		allocate_and_construct(n);
		try {
			for (size_t i = 0; i < n; ++i) {
				AllocTraits::construct(allocator_, &data_[i], value);
			}
			size_ = n;
		}
		catch (...) {
			destroy_and_deallocate();
			throw;
		}
	}

	// 拷贝构造函数
	MyVector(const MyVector& other)
		: allocator_(AllocTraits::select_on_container_copy_construction(other.allocator_)) {
		allocate_and_construct(other.size_);
		try {
			for (size_t i = 0; i < other.size_; ++i) {
				AllocTraits::construct(allocator_, &data_[i], other.data_[i]);
			}
			size_ = other.size_;
		}
		catch (...) {
			destroy_and_deallocate();
			throw;
		}
	}

	// 移动构造函数
	MyVector(MyVector&& other) noexcept
		: data_(other.data_), size_(other.size_), capacity_(other.capacity_), allocator_(std::move(other.allocator_)) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	// 析构函数
	~MyVector() {
		destroy_and_deallocate();
	}

	// 拷贝复制运算符
	MyVector& operator=(const MyVector& other) {
		if (this != &other) {
			MyVector temp(other); // 强异常安全保证
			swap(temp);
		}
		return *this;
	}

	// 移动赋值运算符
	MyVector& operator=(MyVector&& other) noexcept {
		if (this != &other) {
			destroy_and_deallocate();
			data_ = other.data_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			allocator_ = std::move(other.allocator_);
			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}
		return *this;
	}

	// 返回当前大小
	size_t size() const noexcept {
		return size_;
	}

	// 返回当前容量
	size_t capacity() const noexcept {
		return capacity_;
	}

	// 检查是否为空
	bool empty() const noexcept {
		return size_ == 0;
	}

	// 元素访问
	T& operator[](size_t index) {
		if (index >= size_) {
			throw std::out_of_range("Index out of range");
		}
		return data_[index];
	}

	const T& operator[](size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Index out of range");
		}
		return data_[index];
	}

	// 添加元素到末尾
	void push_back(const T& value) {
		ensure_capacity(size_ + 1);
		AllocTraits::construct(allocator_, &data_[size_], value);
		++size_;
	}

	void push_back(T&& value) {
		ensure_capacity(size_ + 1);
		AllocTraits::construct(allocator_, &data_[size_], std::move(value));
		++size_;
	}

	// 移除末尾元素
	void pop_back() {
		if (size_ > 0) {
			--size_;
			AllocTraits::destroy(allocator_, &data_[size_]);
		}
	}

	// 清空容器
	void clear() noexcept {
		for (size_t i = 0; i < size_; ++i) {
			AllocTraits::destroy(allocator_, &data_[i]);
		}
		size_ = 0;
	}

	// 交换内容
	void swap(MyVector& other) noexcept {
		using std::swap;
		swap(data_, other.data_);
		swap(size_, other.size_);
		swap(capacity_, other.capacity_);
		swap(allocator_, other.allocator_);
	}

};