#ifndef BST_H
#define BST_H
#include <string>
#include <sstream>
#include <iostream>
#include "BSTInterface.h"
using namespace std;

template<typename T>
class BST : public BSTInterface<T>
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(T info) : data(info), left(NULL), right(NULL) {}
	};
	Node* root;
	size_t numNodes;

	bool addNode(Node*& node, const T& newData)
	{
		//--------base cases----------
			//check for null (which would include root)
		if (node == NULL)
		{
			node = new Node(newData);
			++numNodes;
			return true;
		}
		//check for duplicate
		if (newData == node->data)
		{
			return false;
		}
		//insert left if left, right if right
		if (newData < node->data)
		{
			return addNode(node->left, newData);
		}
		if (newData > node->data)
		{
			return addNode(node->right, newData);
		}
		else
		{
			return false;
		}
	}

	bool removeNode(Node*& node, const T& item)
	{
		// base case: don't delete
		if (node == NULL)
		{
			return false;
		}
		//find node
		if (item < node->data)
		{
			return removeNode(node->left, item);
		}
		if (item > node->data)
		{
			return removeNode(node->right, item);
		}
		//once found, check if only child or leaf node
		Node* nodeToDelete = node;
		if (node->left == NULL)
		{
			node = node->right;
		}
		else if (node->right == NULL)
		{
			node = node->left;
		}
		else
		{
			Node* predecessor = node->left;
			while (predecessor->right != NULL)
			{
				predecessor = predecessor->right;
			}
			swap(node->data, predecessor->data);
			removeNode(node->left, item);
			return true;
		}
		delete nodeToDelete;
		--numNodes;
		return true;
	}

	bool clearTree(Node*& node)
	{
		//base case: already clear
		if (node == NULL)
		{
			return false;
		}
		//check to left and right until NULL is found
		clearTree(node->left);
		clearTree(node->right);
		//delete nodes
		delete node;
		--numNodes;
		//reassign root to null
		if (numNodes == 0)
		{
			root = NULL;
		}
		return true;

	}

	bool find(Node*& node, const T& item)
	{
		if (node == NULL)
		{
			return false;
		}
		if (node->data == item)
		{
			return true;
		}
		if (item < node->data)
		{
			return find(node->left, item);
		}
		if (item > node->data)
		{
			return find(node->right, item);
		}
		else
		{
			return false;
		}
	}

	/** Output nodes using an inorder traversal */
	string inOrder(Node* node, string& out) const
	{
		if (node == NULL)
		{
			return "";
		}
		inOrder(node->left, out); //left
		out += ",";
		out += node->data;
		inOrder(node->right, out); //right
		return out;
	} 

	std::string trimComma(std::string str) const {
		while (str[0] == ',') //leading
		{
			str.erase(0, 1);
		}
		while (str[str.size() - 1] == ',') //trailing
		{
			str.pop_back();
		}
		return str;
	}

public:
	BST() : root(NULL), numNodes(0) {}
	~BST()
	{
		clearTree();
	}


	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& value)
	{
		return addNode(root, value);
	}


	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& value)
	{
		return removeNode(root, value);
	}


	// return size, or number of nodes
	size_t treeSize() const
	{
		return numNodes;
	}


	bool find(const T& value)
	{
		return find(root, value);
	}

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree()
	{
		return clearTree(root);
	}

	/** Return a level order traversal of a BST as a string */
	virtual string treeToString() const
	{
		string out;
		if (root == NULL)
		{
			out = "empty";
		}
		else
		{
			return trimComma(inOrder(root, out));
		}
		return out;
	} // end toString()

	friend ostream& operator<<(ostream& os, Node* node)
	{
		return os << treeToString();
	}

};

#endif // !BST_H
