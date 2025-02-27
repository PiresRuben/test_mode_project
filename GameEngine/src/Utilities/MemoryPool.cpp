#include "Utilities/MemoryPool.hpp"

#include <iostream>


MemoryPool::MemoryPool() {
	std::cout << "Memory Pool Instance Created\n";
	capacity = 1'048'576; // 1 MiB (mebibyte) the initial pool capacity
	std::byte* ptr = reinterpret_cast<std::byte*>(operator new(capacity));
	allocPtr.push_back(ptr);
	pool.emplace(ptr, capacity);
}

MemoryPool::~MemoryPool() {
	std::cout << "Memory Pool Instance Destroyed\n";

	for (std::byte* ptr : allocPtr) {
		operator delete(ptr);
	}

	pool.clear();
	allocPtr.clear();
}


MemoryPool& MemoryPool::Instance() {
	static MemoryPool instance;
	return instance;
}

std::byte* MemoryPool::Allocate(size_t size) {
	std::cout << "Memory Pool Allocation of " << size << " bytes at: ";

	{ // artificial scope for the mutex because flemme
		std::scoped_lock lock(mtx);
		std::byte* ptr;

		for (auto& [key, value] : pool) {
			if (size > value) { continue; }

			ptr = key;

			if (size < value) {
				pool.emplace(key + size, value - size);
			}

			pool.erase(key);
			std::cout << ptr << '\n';
			return ptr;
		}

		size < capacity ? Extend(capacity) : Extend(size);
	}

	return Allocate(size);
}

void MemoryPool::Deallocate(std::byte* ptr, size_t size) {
	std::cout << "Memory Pool Deallocation of pointer: " << ptr << " of size: " << size << '\n';

	{ // artificial scope for the mutex because flemme
		std::scoped_lock lock(mtx);

		pool.emplace(ptr, size);
	}

	MergeChunks(pool.find(ptr));
}

void MemoryPool::Extend(size_t size) {
	std::cout << "Memory Pool Extention of " << size << " bytes\n";
	std::byte* ptr;

	{ // artificial scope for the mutex because flemme
		std::scoped_lock lock(mtx);
		ptr = reinterpret_cast<std::byte*>(operator new(size));

		allocPtr.push_back(ptr);
		pool.emplace(ptr, size);
		capacity += size;
	}

	MergeChunks(pool.find(ptr));
}

void MemoryPool::MergeChunks(const std::map<std::byte*, size_t>::iterator& it) {
	std::scoped_lock lock(mtx);

	if (it == pool.end()) { return; }

	const auto& next = std::next(it);
	if (next != pool.end()) {
		if (it->first + it->second == next->first) {
			std::cout << "Memory Pool Merging chunks " << it->first << " of size: " << it->second << " with " << next->first << " of size: " << next->second << '\n';
			it->second += next->second;
			std::cout << "Resulting chunk " << it->first << " of size: " << it->second << '\n';
			pool.erase(next);
		}
	}

	if (it == pool.begin()) { return; }

	const auto& previous = std::prev(it);
	if (previous->first + previous->second == it->first) {
		std::cout << "Memory Pool Merging chunks " << previous->first << " of size: " << previous->second << " with " << it->first << " of size: " << it->second << '\n';
		previous->second += it->second;
		std::cout << "Resulting chunk " << previous->first << " of size: " << previous->second << '\n';
		pool.erase(it);
	}
}