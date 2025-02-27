#pragma once

class Discarder {
public:
	template<typename T> constexpr inline void operator=(T&) const { }
private:
};

constexpr const Discarder _;