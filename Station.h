#ifndef STATION_H
#define STATION_H
#include "Vector.h"
#include "Deque.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

template<typename T>
class Station
{
private:
	Vector<T> train;
	Stack<T> stack;
	Queue<T> queue;
	T turnTableCar;
	bool empty;
public:
	Station() : empty(true) {}
	~Station() {}

	string addCar(const T& car)
	{
		if (empty)
		{
			turnTableCar = car;
			empty = false;
			return " OK";
		}
		return " Turntable occupied!";
	}

	string removeCar()
	{
		if (empty)
		{
			return " Turntable empty!";
		}
		train.push_back(turnTableCar);
		empty = true;
		return " OK";
	}

	string sizeTrain() const
	{
		stringstream size;
		size << " " << train.size();
		return size.str();
	}

	string trainString() const
	{
		return train.toString();
	}

	string addStack()
	{
		if (empty)
		{
			return " Turntable empty!";
		}
		stack.push(turnTableCar);
		empty = true;
		return " OK";
	}

	string removeStack()
	{
		if (stack.empty())
		{
			return " Stack empty!";
		}
		if (!empty)
		{
			return " Turntable occupied!";
		}
		turnTableCar = stack.top();
		empty = false;
		stack.pop();
		return " OK";
	}

	string topStack()
	{
		if (stack.empty())
		{
			return " Stack empty!";
		}
		stringstream top;
		top << " " << stack.top();
		return top.str();
	}

	string stackString() const
	{
		return stack.toString();
	}

	string sizeStack() const
	{
		stringstream size;
		size << " " << stack.size();
		return size.str();
	}

	string addQueue()
	{
		if (empty)
		{
			return " Turntable empty!";
		}
		queue.push(turnTableCar);
		empty = true;
		return " OK";
	}

	string removeQueue()
	{
		if (queue.empty())
		{
			return " Queue empty!";
		}
		if (!empty)
		{
			return " Turntable occupied!";
		}
		turnTableCar = queue.top();
		empty = false;
		queue.pop();
		return " OK";
	}

	string topQueue()
	{
		if (queue.empty())
		{
			return " Queue empty!";
		}
		stringstream top;
		top << " " << queue.top();
		return top.str();
	}

	string queueString() const
	{
		return queue.toString();
	}

	string sizeQueue() const
	{
		stringstream size;
		size << " " << queue.size();
		return size.str();
	}

	string find(T value)
	{
		string index = "";
		//check in vector
		for (size_t i = 0; i < train.size(); ++i)
		{
			if (train.at(i) == value)
			{
				index = " Train[" + to_string(i) + "]";
				return index;
			}
		}
		//check in stack
		for (size_t i = 0; i < stack.size(); ++i)
		{
			if (stack.at(i) == value)
			{
				index = " Stack[" + to_string((stack.size() - i) - 1) + "]";
				return index;
			}
		}
		//check in queue
		for (size_t i = 0; i < queue.size(); ++i)
		{
			if (queue.at(i) == value)
			{
				index = " Queue[" + to_string(i) + "]";
				return index;
			}
		}
		//check on turntable
		if (turnTableCar == value)
		{
			return " Turntable";
		}
		return " Not Found!";
	}
};

#endif
