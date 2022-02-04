#ifndef QS_H
#define QS_H

#include "QSInterface.h"

#include<string>
#include<iostream>
#include<sstream>

template<typename T>
class QS : public QSInterface<T>
{
private:
	size_t numElem;
	size_t sortCapacity;
	T* sortArray;
	size_t comparisons;
	size_t exchanges;

	void reallocate()
	{
		//size_t prevCapacity = sortCapacity;
		T* prevArray = sortArray;

		//double capacity
		sortCapacity *= 2;
		//create new array
		sortArray = new T[sortCapacity];
		//copy old data
		for (size_t i = 0; i < numElem; i++)
		{
			sortArray[i] = prevArray[i];
		}
		//clean up the memory
		delete[] prevArray;
	}


public:
	QS() : numElem(0), sortCapacity(0), sortArray(new T[sortCapacity]), comparisons(0), exchanges(0) {} 
	~QS() 
	{
		delete[] sortArray;
	}
	
	void resetStats() 
	{
		comparisons = 0;
		exchanges = 0;
	}

	std::string stats() 
	{
		std::stringstream ss;
		ss << comparisons;
		ss << ","; 
		ss << exchanges;
		return ss.str();
	}
	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element)
	{
		//copy stuff over to new array with double capacity if full
		if (numElem == sortCapacity) 
		{ 
			reallocate();
		}
		//add element and adjust size
		sortArray[numElem] = element;
		++numElem; 
		return true;
	}

	void newQuicksort(size_t capacity)
	{
		delete[] sortArray;
		numElem = 0;
		sortCapacity = capacity;
		sortArray = new T[sortCapacity];
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right)
	{
		// base case 1: reached the last index
		//++comparisons;
		if (left == right)
		{
			return true;
		}
		++comparisons;
		// base case 2: subArray has only 2 elements
		if (right - left == 1)
		{
			++comparisons;	
			if (sortArray[right] < sortArray[left]) 
			{
				std::swap(sortArray[right], sortArray[left]);
				++exchanges;
			}
			return true;
		}
		else
		{
			size_t median = medianOfThree(left, right);
			size_t pivot = partition(left, right, median);
			bool leftHalf = sort(left, pivot);
			bool rightHalf = sort(pivot, right);
			//++comparisons;
			if (leftHalf && rightHalf)
			{
				return true;
			}
			return false;
		}
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll() 
	{
		if (numElem > 1)
		{
			return sort(0, (numElem - 1));
		}
		return false;
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear()
	{
		//check if already empty
		if (numElem != 0) 
		{
			numElem = 0;
			return true;
		}
		return false;
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const 
	{
		return sortCapacity;
	}

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const
	{
		return numElem;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	   middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if  1) the array is empty,
				  2) if either of the given integers is out of bounds,
				  3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right)
	{
		//invalid cases
		if (numElem == 0)
		{
			return -1;
		}
		if (left > right)
		{
			return -1;
		}
		if (right == 0) return -1; 
		//calc middle index
		int middleIndex = (left + right) / 2;
		//ensure not out of bounds 
		if (right == numElem)
		{
			right = right - 1;
		}
		//bubble sort elements at indexes
		triBubbleSort(left, middleIndex, right);
		return middleIndex;
	}
	
	void triBubbleSort(const size_t& left, int middleIndex, const size_t& right)
	{
		++comparisons;
		if (sortArray[left] > sortArray[middleIndex])
		{
			std::swap(sortArray[left], sortArray[middleIndex]);
			++exchanges;
		}
		++comparisons;
		if (sortArray[middleIndex] > sortArray[right])
		{
			std::swap(sortArray[middleIndex], sortArray[right]);
			++exchanges;
		}
		++comparisons;
		if (sortArray[left] > sortArray[middleIndex])
		{
			std::swap(sortArray[left], sortArray[middleIndex]);
			++exchanges;
		} 
	}



	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values less than or equal to the pivot should be placed to the left of the pivot;
	the values greater than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if  1) the array is empty,
				  2) if any of the given indexes are out of bounds,
				  3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex) 
	{
		//invalid cases
		if (numElem == 0)
		{
			return -1;
		}
		if (left >= right || pivotIndex >= right)
		{
			return -1;
		}
		if (left < 0) return -1;
		std::swap(sortArray[left], sortArray[pivotIndex]); 
		//++exchanges;
		int down = right - 1;
		int up = left + 1;
	do 
	{
		while (up != (right - 1) && !(sortArray[left] < sortArray[up]))
		{
			++up;
		}
		while (sortArray[left] < sortArray[down])
		{
			--down;
		}
		if (up < down) 
		{
			std::swap(sortArray[up], sortArray[down]);
			++exchanges;
		}
	} while (up < down);
	std::swap(sortArray[left], sortArray[down]);
	//++exchanges;
	return down;
	}

	friend std::ostream& operator<<(std::ostream& os, const QS& qs)
	{
		os << qs.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		if (numElem == 0) return std::string("Empty");
		for (size_t i = 0; i < numElem; ++i) 
		{
			ss << sortArray[i] << ",";
		}
		std::string returnString = ss.str();
		returnString.pop_back();
		return returnString;
	}
};

#endif
