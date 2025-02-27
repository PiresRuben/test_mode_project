#pragma once

#include <iostream>
#include <typeindex>

#include "MemoryPool.hpp"


template<typename T>
T* PoolAllocator<T>::allocate(size_t n) {
    std::cout << "Pool Allocator Allocating " << n << " elements of type: " << typeid(T).name() << '\n';
    if (n > std::allocator_traits<PoolAllocator>::max_size(*this)) {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(MemoryPool::Instance().Allocate(n * sizeof(T)));
}

template<typename T>
void PoolAllocator<T>::deallocate(T* ptr, size_t n) noexcept {
    std::cout << "Pool Allocator Deallocating " << n << " elements of type: " << typeid(T).name() << " at " << ptr << '\n';
    MemoryPool::Instance().Deallocate(reinterpret_cast<std::byte*>(ptr), n * sizeof(T));
}

template<typename T>
template<typename U, typename... Args>
void PoolAllocator<T>::construct(U* ptr, Args&&... args) {
    std::cout << "Pool Allocator Construction of an element of type: " << typeid(U).name() << " at " << ptr << '\n';
    new (ptr) U(std::forward<Args>(args)...);
}

template<typename T>
template<typename U>
void PoolAllocator<T>::destroy(U* ptr) noexcept {
    std::cout << "Pool Allocator Destruction of an element of type: " << typeid(U).name() << " at " << ptr << '\n';
    ptr->~U();
}