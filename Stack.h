#ifndef STACK_H
#define STACK_H
#include "Deque.h"
#include <string>
using namespace std;

template<typename T>
class Stack
{
private:
	Deque<T> stack;
public:
	Stack() {}
	~Stack() {}

	void push(const T& value)
	{
		stack.push_front(value);
	}

	void pop()
	{
		stack.pop_front();
	}

	T& top()
	{
		return stack.front();
	}

	size_t size() const
	{
		return stack.size();
	}

	T& at(size_t index)
	{
		return stack.at(index);
	}

	string toString() const
	{
		return stack.reverseToString();
	}

	bool empty()
	{
		return stack.empty();
	}

};
#endif
