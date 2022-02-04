#ifndef VECTOR_H
#define VECTOR_H
#include "Deque.h"
#include <string>
using namespace std;

template <typename T>
class Vector
{
private:
	Deque<T> vector;

public:
	Vector() {}
	~Vector() {}

	void push_back(const T& value)
	{
		vector.push_back(value);
	}

	void pop_back()
	{
		vector.pop_back();
	}

	T& back()
	{
		return vector.back();
	}

	size_t size() const
	{
		return vector.size();
	}

	T& at(size_t index)
	{
		return vector.at(index);
	}

	string toString() const
	{
		return vector.toString();
	}

	bool empty()
	{
		return vector.empty();
	}

};
#endif

