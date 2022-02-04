#ifndef QUEUE_H
#define QUEUE_H
#include "Deque.h"
#include <string>
using namespace std;

template<typename T>
class Queue
{
private:
	Deque<T> queue;
public:
	Queue() {}
	~Queue() {}

	void push(const T& value)
	{
		queue.push_back(value);
	}

	void pop()
	{
		queue.pop_front();
	}

	T& top()
	{
		return queue.front();
	}

	size_t size() const
	{
		return queue.size();
	}

	T& at(size_t index)
	{
		return queue.at(index);
	}

	string toString() const
	{
		return queue.toString();
	}

	bool empty()
	{
		return queue.empty();
	}
};

#endif
