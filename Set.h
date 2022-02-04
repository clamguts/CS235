#ifndef SET_H
#define SET_H
#include <string>
#include "SetInterface.h"
#include "BST.h"
using namespace std;

template<typename T>
class Set : public SetInterface<T>
{
private:
	BST<T> set;
public:
	Set() {}
	~Set() {}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value. */
	virtual bool insert(const T& item)
	{
		return set.addNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear()
	{
		set.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const
	{
		return set.treeSize();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item)
	{
		bool itemFound = set.find(item);
		size_t itemCount = 0;
		if (itemFound)
		{
			itemCount = 1;
			return itemCount;
		}
		return itemCount;
	}

	/** @return: string representation of items in Set. */
	virtual string toString() const
	{
		return set.treeToString();
	}

	friend std::ostream& operator<<(std::ostream& os, const Set& object)
	{
		os << object.toString();
		return os;
	}
};


#endif // !SET_H

