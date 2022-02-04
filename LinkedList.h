#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "LinkedListInterface.h"
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class LinkedList : public LinkedListInterface<T>

{
private:
	struct Node
	{
		T data;
		Node* next = NULL;
	};

	Node* head;

public:
	LinkedList()
	{
		this->head = NULL;
	}
	virtual~LinkedList()
	{
		clear();
	}

	/** Insert Node(value) at beginning of linked list */
	virtual void push_front(const T& value)
	{
		//allocate memory for new node
		Node* newNode = new Node();

		//assign data and next pointer
		newNode->data = value;
		newNode->next = head;
		//place at the front
		head = newNode;
	}

	/** Remove Node at beginning of linked list */
	virtual void pop_front()
	{
		Node* temp = head;
		if (empty())
		{
			throw 0;
		}
		head = head->next;

		delete temp;
	}

	/** Remove all Nodes from linked list */
	virtual void clear()
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
	virtual string toString() const
	{
		//place head into output string stream
		Node* currentNode = head;
		ostringstream outputData;
		outputData << currentNode->data << " ";

		//iterate through list, place the rest in the stream buffer
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			outputData << currentNode->data << " ";
		}
		return outputData.str();
	}
	
	/** Return true if linked list size == 0 */
	virtual bool empty(void) const
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
	
	/** Return the number of nodes in the linked list */
	virtual size_t size(void) const
	{
		size_t numObjects = 0;
		Node* currentNode = head;

		//iterate through list to get object count
		while (currentNode != NULL)
		{
			++numObjects;
			currentNode = currentNode->next;
		}
		return numObjects;
	}

	/** Return reference to value of Node at beginning of linked list */
	virtual T& front(void)
	{
		if (empty())
		{
			throw 1;
		}
		return head->data;
	}

	/** Remove all Nodes with value from linked list */
	virtual void remove(const T& value)
	{
		Node* tempNode = head;
		Node* prevNode = NULL;

		if (empty())
		{
			return;
		}

		while (tempNode != NULL)
		{
			//not a match, move on
			if (tempNode->data != value)
			{
				prevNode = tempNode;
				tempNode = tempNode->next;
				continue;
			}
			//special case: head match (beginning of list)
			if (tempNode == head)
			{
				head = tempNode->next;
				delete tempNode;
				tempNode = head;
				continue;
			}
			//remove node
			prevNode->next = tempNode->next;
			delete tempNode;
			tempNode = prevNode->next;
		}
	}

	/** Reverse Nodes in linked list */
	virtual void reverse(void)
	{
		if (empty())
		{
			throw 2;
		}

		Node* currentNode = head;
		Node* prevNode = NULL;
		Node* nextNode = NULL;

		while (currentNode != NULL)
		{
			nextNode = currentNode->next; //move next
			currentNode->next = prevNode; // what was next becomes previous
			prevNode = currentNode; //move previous to current
			currentNode = nextNode; //what was current becomes next
		}
		head = prevNode;
	}
	
	
};

#endif

