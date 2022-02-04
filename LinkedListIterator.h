#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class LinkedList

{
private:
	struct Node
	{
		T data;
		Node* next = NULL;
	};

	Node* head;

public:
	LinkedList() : head(NULL) {}
	~LinkedList()
	{
		clear();
	}

	friend ostream& operator<< (ostream& os, LinkedList<T>& linkedList)
	{
		for (Iterator iter = linkedList.begin(); iter != linkedList.end(); ++iter)
		{
			os << *iter << " ";
		}
		return os;
	}

	class Iterator
	{
	private:
		Node* iNode;
	public:
		Iterator(Node* head) : iNode(head) {}
		Iterator() : iNode(NULL) {}
		~Iterator() {}

		bool operator!=(const Iterator& rhs) const
		{
			if (iNode == rhs.iNode)
			{
				return false;
			}
			return true;
		}

		Iterator& operator++()
		{
			if (iNode == NULL) //iterator not valid
			{
				return *this;
			}
			if (iNode->next != NULL) // iterator is valid
			{
				iNode = iNode->next;
				return *this;
			}
			iNode = NULL; 
			return *this;
		}

		T& operator*() const
		{
			 return iNode->data;
		}
	};

	/** Return iterator pointing to the first value in linked list */
	Iterator begin(void)
	{
		return LinkedList<T>::Iterator(head);
	}

	/** Return iterator pointing to something not in linked list */
	Iterator end(void)
	{
		return LinkedList<T>::Iterator(NULL);
	}

	/** Return iterator pointing found value in linked list */
	Iterator find(Iterator first, Iterator last, const T& value)
	{
		Iterator currentIt = first;
		bool found;
		while (currentIt != last)
		{
			if (*currentIt == value)
			{
				found = true;
				return LinkedList<T>::Iterator(currentIt);
			}
			++currentIt;
			found = false;
		}
		if (!found)
		{
			throw 0;
		}
	
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert(Iterator position, const T& value)
	{
		Node* tempNode = head;
		Node* prevNode = NULL;
		Node* newNode = new Node();
		while (tempNode != NULL)
		{
			//not a match, next one
			if (tempNode->data != *position)
			{
				prevNode = tempNode;
				tempNode = tempNode->next;
				continue;
			}
			//special case: head match
			if (head->data == *position)
			{
				newNode->data = value;
				newNode->next = tempNode;
				head = newNode;
				break;
			}
			//place new node in front of temp and reassign accordingly
			newNode->data = value;
			newNode->next = tempNode;
			prevNode->next = newNode;
			tempNode = tempNode->next;
			break;
		}
		//create iterator to point to new node
		Iterator tempIt = begin();
		Iterator prevIt = NULL;
		Iterator tailIt = end();
		Iterator newIt = Iterator(newNode);
		while (tempIt != tailIt)
		{
			if (tempIt != position)
			{
				prevIt = tempIt;
				tempIt = ++tempIt;
				continue;
			}
			if (*begin() == *position)
			{
				*newIt = value;
				++newIt = tempIt;
				begin() = newIt;
				return newIt;
			}
			*newIt = value;
			++newIt = tempIt;
			++prevIt = newIt;
			tempIt = ++tempIt;
			return newIt;
		}
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert_after(Iterator position, const T& value)
	{
		//inserting new Node (object)
		Node* tempNode = head;
		Node* prevNode = NULL;
		Node* newNode = new Node();
		while (tempNode != NULL)
		{
			//not a match
			if (tempNode->data != *position)
			{
				prevNode = tempNode;
				tempNode = tempNode->next;
				continue;
			}
			//shuffle nodes before and after to accomodate new node
			prevNode = tempNode;
			newNode->data = value;
			newNode->next = tempNode->next;
			prevNode->next = newNode;
			tempNode = tempNode->next->next;
			break;
		}
		//creating iterator to point to the Node
		Iterator tempIt = begin();
		Iterator prevIt = NULL;
		Iterator tailIt = end();
		Iterator newIt = Iterator(newNode);
		while (tempIt != tailIt)
		{
			if (tempIt != position)
			{
				prevIt = tempIt;
				tempIt = ++tempIt;
				continue;
			}
			prevIt = tempIt;
			*newIt = value;
			++newIt = ++tempIt;
			++prevIt = newIt;
			tempIt = ++tempIt, ++tempIt;
			return newIt;
		}
	}

	/** Return iterator pointing to next item after deleted node linked list */
	Iterator erase(Iterator position)
	{
		Node* tempNode = head;
		Node* prevNode = NULL;
		Iterator tempIt = begin();
		Iterator prevIt = NULL;
		while (tempNode != NULL)
		{
			if (tempNode->data != *position)
			{
				prevNode = tempNode;
				tempNode = tempNode->next;
				prevIt = tempIt;
				++tempIt;
				continue;
			}
			if (head->data == *position)
			{
				head = tempNode->next;
				begin() = ++tempIt;
				delete tempNode;
				tempNode = head;
				return tempIt;
			}
			prevNode->next = tempNode->next;
			++prevIt = ++tempIt;
			delete tempNode;
			tempNode = prevNode->next;
			return tempIt;
		}
	}

	/** Replace first found old_value(s) with new_value */
	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
	{
		Iterator tempIt = first;
		Iterator prevIt = NULL;
		while (tempIt != last)
		{
			//if not a match, move on
			if (*tempIt != old_value)
			{
				prevIt = tempIt;
				++tempIt;
				continue;
			}
			//replace the value and increment pointer
			*tempIt = new_value;
			++tempIt;
		}
	}


	/** Insert Node(value) at beginning of linked list */
	void push_front(const T& value)
	{
		//allocate memory for new node
		Node* newNode = new Node();

		//assign data and next pointer
		newNode->data = value;
		newNode->next = head;
		//place at the front
		head = newNode;
	}


	/** Remove all Nodes from linked list */
	void clear()
	{
		Node* currentNode = head;
		Node* nextNode = NULL;

		//iterate through list
		while (currentNode != NULL)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
		//reassign head to null
		head = NULL;
	}

	/* Return contents of Linked List as a string */
	string toString() const
	{
		//place head into output string stream
		Node* currentNode = head;
		ostringstream outputData;
		outputData << currentNode->data << " ";

		//iterate through list, place the rest in the stream buffer
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			outputData << currentNode->data << (currentNode->next != NULL ? " " : "");
		}
		return outputData.str();
	}

	/** Return true if linked list size == 0 */
	bool empty(void) const
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

#endif


