#ifndef PAIR_H
#define PAIR_H
#include "Set.h"
#include <string>
#include <sstream>


template<typename T1, typename T2>
struct Pair
{
	T1 first;
	T2 second;
	// Construct a pair from two values.
	Pair(const T1& x, const T2& y) : first(x), second(y) {}

	// Construct a default pair.
	Pair() : first(T1()), second(T2()) {}

	// Construct a default pair.
	Pair(const T1& x) : first(x), second(T2()) {}

	// Construct an assignable pair
	template<typename Other_T1, typename Other_T2>
	Pair(const pair<Other_T1, Other_T2>& other)
	{
		first = other.first;
		second = other.second;
	}

	/*bool operator==(const Pair<T1, T2>& rhs)
	{
		return this->second == rhs.second;
	}*/

	/*bool operator!=(const Pair<T1, T2>& rhs)
	{
		return (!this == rhs);
	}*/

	std::string toString() const {
		std::stringstream str;
		str << first;
		str << "->";
		str << second;
		if (str.str() == "->") std::stringstream("");
		return str.str();
	}

	friend std::ostream& operator<<(std::ostream& os, const Pair& object)
	{
		os << object.toString();
		return os;
	}
};

#endif // PAIR_H
