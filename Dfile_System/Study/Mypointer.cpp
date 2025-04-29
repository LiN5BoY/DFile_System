#include <iostream>

template <typename T>

class UniquePtr {
private:
	T* ptr;	//ԭʼָ��

public:
	explicit UniquePtr(T* p = nullptr) : ptr(p) {}

	// ��ֹ��������Ϳ�����ֵ
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	// ת�ƹ���
	UniquePtr& operator=(UniquePtr&& other) noexcept {
		if (this != &other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}

	// ���� * �� -> ������
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }

	// ��ȡָ��
	T* get() const {return ptr;}

	// �ͷ�����Ȩ
	T* release() {
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	// ����ָ��
	void reset(T* p = nullptr) {
		delete ptr;
		ptr = p;
	}

	// ��������
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
	// ���캯��
	explicit SharedPtr(T* p = nullptr) : ptr(p) , ref_count(new size_t(1)) {}

	// ��������
	SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
		if (ref_count) {
			++(*ref_count);
		}
	}

	// ������ֵ
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

	// ����* �� ->������
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }

	// ��ȡ���ü���
	size_t use_count() const { return ref_count ? *ref_count : 0; }

	// ��������
	~SharedPtr() {
		release();
	}
};

template <typename T>
class WeakPtr {
private:
	T* ptr;             // ԭʼָ��
	size_t* ref_count;  // ���ü���

public:
	// ���캯��
	WeakPtr() : ptr(nullptr), ref_count(nullptr) {}

	// �� shared_ptr ����
	WeakPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {}

	// ���ָ���Ƿ���Ч
	bool expired() const {
		return !ref_count || *ref_count == 0;
	}

	// ���������� shared_ptr
	SharedPtr<T> lock() const {
		if (expired()) {
			return SharedPtr<T>();
		}
		return SharedPtr<T>(*this);
	}
};