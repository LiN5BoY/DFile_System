// ʵ��һ��֧�� C++11 ���Բ��߱��쳣��ȫ��strong exception safety���� `std::vector`����Ҫ��ѭ���²��裺
// ���Ĳ���
//1. **ʹ�� `std::allocator_traits`**:
//   - `std::allocator_traits` �ṩ�˶Է�������ͳһ�ӿڣ�֧�� `std::allocator` ���Զ����������
//   - ʹ�� `std::allocator_traits` �����ڴ�ʱ���ܹ���Ӧ��ͬ���͵ķ�������
//2. **�쳣��ȫ��֤��strong exception safety��**:
//   - �ڲ���������롢ɾ�������ݵȣ�ʧ��ʱ��ȷ�������ƻ�ԭ������״̬��
//   - ͨ�� RAII ��������ʱ���ݽṹ��ʵ���쳣��ȫ������ֱ�Ӳ���ԭʼ���ݡ�
//3. **��̬����**:
//   - ʹ�� `std::allocator_traits` ������ͷŶ�̬�ڴ档
//   - ʵ�ֶ�̬���ݲ��ԣ�ͨ��Ϊ��ǰ������������
//4. **������ʧЧ����**:
//   - ���ڲ����ɾ����������Ҫ��ȷ���������ʧЧ���⡣

#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iterator>

// ����ζ����û��ָ�� Allocator ������£�ģ�彫ʹ�ñ�׼�� std::allocator �������ڴ���䡣
// �������ʹ��������ʹ��ʱ�������ָ����ͬ�ķ�������֧���Զ����ڴ���ԡ�
template <typename T, typename Allocator = std::allocator<T>>

class MyVector {
private:
	T* data_;	// �洢Ԫ�ص�ָ��
	size_t size_;	//��ǰԪ������
	size_t capacity_;	// ��������
	Allocator allocator_;	//������

	using AllocTraits = std::allocator_traits<Allocator>;

	// �����ڴ��ҹ������
	void allocate_and_construct(size_t n) {
		data_ = AllocTraits::allocate(allocator_, n);
		size_ = 0;
		capacity_ = n;
	}

	// ���ٲ��ͷ��ڴ�
	void destroy_and_deallocate() {
		for (size_t i = 0; i < size_; ++i) {
			AllocTraits::destory(allocator_, &data_[i]);
		}
		AllocTraits::deallocate(allocator_, data_, capacity_);
		data_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}

	// ���ݺ�����ȷ�������������ض�ָ������
	void reallocate(size_t new_capacity) {
		T* new_data = AllocTraits::allocate(allocator_, new_capacity);
		size_t i = 0;
		try {
			for (; i < size_; i++) {
				AllocTraits::construct(allocator_, &new_data[i], std::move_if_noexcept(data_[i]));
			}
		}
		catch (...) {
			// �ع��������ͷ��·���ռ䲢�׳��쳣
			for (size_t j = 0; j < i; ++j) {
				AllocTraits::destory(allocator_, &new_data[j]);
			}
			AllocTraits::deallocate(allocator_, new_data, new_capacity);
			throw;
		}
		
		// ���پ��ڴ沢�ͷ��ڴ�
		destroy_and_deallocate();

		data_ = new_data;
		capacity_ = new_capacity;
	}

	// ȷ�������㹻
	void ensure_capacity(size_t new_capacity) {
		if (new_capacity > capacity_) {
			size_t new_cap = std::max(new_capacity, capacity_ ? capacity_ * 2 : 1);
			reallocate(new_cap);
		}
	}

public:
	// ���캯��
	// ʹ�� explicit ������ߴ���������ȺͰ�ȫ�ԣ���ֹ���������ת�����Ӷ�����Ǳ�ڵĴ���
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

	// �������캯��
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

	// �ƶ����캯��
	MyVector(MyVector&& other) noexcept
		: data_(other.data_), size_(other.size_), capacity_(other.capacity_), allocator_(std::move(other.allocator_)) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	// ��������
	~MyVector() {
		destroy_and_deallocate();
	}

	// �������������
	MyVector& operator=(const MyVector& other) {
		if (this != &other) {
			MyVector temp(other); // ǿ�쳣��ȫ��֤
			swap(temp);
		}
		return *this;
	}

	// �ƶ���ֵ�����
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

	// ���ص�ǰ��С
	size_t size() const noexcept {
		return size_;
	}

	// ���ص�ǰ����
	size_t capacity() const noexcept {
		return capacity_;
	}

	// ����Ƿ�Ϊ��
	bool empty() const noexcept {
		return size_ == 0;
	}

	// Ԫ�ط���
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

	// ���Ԫ�ص�ĩβ
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

	// �Ƴ�ĩβԪ��
	void pop_back() {
		if (size_ > 0) {
			--size_;
			AllocTraits::destroy(allocator_, &data_[size_]);
		}
	}

	// �������
	void clear() noexcept {
		for (size_t i = 0; i < size_; ++i) {
			AllocTraits::destroy(allocator_, &data_[i]);
		}
		size_ = 0;
	}

	// ��������
	void swap(MyVector& other) noexcept {
		using std::swap;
		swap(data_, other.data_);
		swap(size_, other.size_);
		swap(capacity_, other.capacity_);
		swap(allocator_, other.allocator_);
	}

};