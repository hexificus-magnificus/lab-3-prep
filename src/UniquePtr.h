#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>

// Your implementation here
template <typename T>
class UniquePtr {
public:
	UniquePtr() : mPtr(nullptr) {};
	UniquePtr(T* ptr) : mPtr(ptr) {};
        UniquePtr(const UniquePtr<T> &p) = delete;
	UniquePtr(UniquePtr<T> &&p) : mPtr(p.mPtr) {
		p.mPtr = nullptr;
	};
	template <typename U>
	UniquePtr(UniquePtr<U> &&p) : mPtr(p.release()) {};

	UniquePtr& operator=(const UniquePtr<T> &p) = delete;
	UniquePtr& operator=(UniquePtr<T> &&p) {
		if (&p == this)
			return *this;
		delete mPtr;
		mPtr = p.mPtr;
		p.mPtr = nullptr;
		return *this;
	};
	T& operator*() const {
		return *mPtr;
	};
	T* operator->() const {
		return mPtr;
	};
	bool operator==(const UniquePtr<T>& other) const {
		return mPtr == other.mPtr;
	};
	
	operator bool() const {
		return mPtr != nullptr;
	};

	T* get() const {
		return mPtr;
	};
	void swap(UniquePtr<T>& other) {
		T* tmp(mPtr);
		mPtr = other.mPtr;
		other.mPtr = tmp;
	};

	T* release() {
		T* tmp(mPtr);
		mPtr = nullptr;
		return tmp;
	};
	void reset(T* newPtr = nullptr) {
		delete mPtr;
		mPtr = newPtr;
	};
	~UniquePtr() {
		delete mPtr;
	};

private:
	T* mPtr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
	T* p(new T(args...));
	UniquePtr<T> q(p);
	return q;
}

#endif
