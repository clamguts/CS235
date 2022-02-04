#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "HashMapInterface.h"
#include "Pair.h"
#include "Set.h"
using namespace std;

template <typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:
	size_t capacity;
	Pair<K, V>* pairs;
	size_t numPairs;

	/*size_t pow(size_t base, size_t power)
	{
		for (size_t i = 0; i < power; ++i)
		{
			base *= base;
		}
		return base;
	}*/

	size_t getIndex(const K& key)
	{
		size_t index = 0;
		for (size_t i = 0; i < key.size(); ++i) {
			index += key[i] * (size_t)pow(HASH_CONSTANT, key.size() - (i + 1)); //formula from textbook
		}
		return index % capacity;
	}

	/*void rehash()
	{
		size_t newCapacity = capacity * 2;
		Pair<K, V>* prevArray = pairs;

		size_t prevCapacity = capacity;
		capacity = newCapacity;

		pairs = new Pair<K, V>[newCapacity];

		Pair<K, V> blankPair = Pair<K,V>();

		for (size_t i = 0; i < prevCapacity; ++i)
		{
			string voidComp = prevArray[i].first;
			if (voidComp == blankPair.first) continue;
			K key = prevArray[i].first;
			int k = 0;
			//int k = -1;
			size_t index = getIndex(key);
			size_t origIndex = index;
			while (1)
			{
				if (pairs[index].first != K())
				{
					if (pairs[index].first == key)
					{
						break;
					}
					k++;
					//k += 2;
					//cout << "collision of " << key << " and " << pairs[index].first << " " << k << endl;
					//index = (index + k) % capacity;
					index = (origIndex + pow(k,2)) % capacity;
					continue;
				}
				pairs[index] = prevArray[ii];
				break;
			}
		}
		delete[] oldArray;
	}*/


public:
	HashMap<K, V>() : capacity(DEFAULT_MAP_HASH_TABLE_SIZE), pairs(new Pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE]), numPairs(0) {}
	~HashMap() 
	{
		clear();
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key)
	{
		/*if (max_size() > LOAD_THRESHOLD)
		{
			rehash();
		}*/
		size_t index = getIndex(key);
		//size_t origIndex = index;
		//int k = 0;
		int k = -1;
		while (1)
		{
			if (pairs[index].first != K())
			{
				if (pairs[index].first == key)
				{
					break;
				}
				//k++;
				k += 2;
				//cout << "collision in " << key << " and " << pairs[index].first << k << endl;
				index = (index + k) % capacity;
				//index = (origIndex + pow(k, 2));
				//index = index % capacity;
				continue;
			}
			pairs[index].first = key;
			++numPairs;
			break;
		}
		return pairs[index].second;
	}
	

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key)
	{
		size_t numMatches = 0;
		for (size_t i = 0; i < capacity; ++i)
		{
			if (pairs[i].first == key)
			{
				++numMatches;
			}
		}
		return numMatches;
	}

	/** Removes all items from the Map. */
	virtual void clear(void)
	{
		delete[] pairs;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size(void) const
	{
		return numPairs;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size(void) const
	{
		size_t size_max = (numPairs * 100) / capacity;
		return size_max;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual string toString(void) const
	{
		stringstream ss;
		ss << numPairs << "/" << capacity << endl;
		for (size_t i = 0; i < capacity; ++i) {
			string temp = pairs[i].first;
			if (temp != "") {
				ss << "  [" << i << ":" << pairs[i] << "]" << endl;
			}
		}
		return ss.str();
	}

	friend ostream& operator<<(ostream& os, Pair<K, V>* pair)
	{
		return os << pair.toString();
	}
};

#endif