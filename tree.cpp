#include <iostream>
#include "basic_functions.h"
#define SPACE 10
using namespace std;
// A tree is a non linear data structure that simulates a hierarchical tree structure with a root value and sub trees of children with parent node, represented as set of linked nodes.
//
// Tree terms �
// Root � Root is a special node in a tree. The entire tree is referenced through it.It does not have a parent.
// Parent Node � Parent node is an immediate predecessor of a node.
// Child Node � All immediate successors of a node are its children.
// Siblings � Nodes with the same parent are called Siblings.
// Leaf � Last node in the tree. There is no node after this node.
// Edge � Edge is a connection between one node to another. It is a line between two nodes or a node and a leaf.
// Path � Path is a number of successive edges from source node to destination node.
//
// Tree terms / properties �
// Tree can be termed as a RECURSIVE data structure.
// In a valid tree for N Nodes we have N - 1 Edges / Links
// Depth of Node � Depth of a node represents the number of edges from the tree's root node to the node.
// Height of Node � Height of a node is the number of edges on the longest path between that node & a leaf.
// Height of Tree � Height of tree represents the height of its root node.
//
// Types of Trees �
// General Tree
// Binary Tree
// Binary Search Tree
// AVL Tree
// Spanning Tree
// B - Tree
// B + Tree
// Heap
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Binary Tree
// A binary tree is a tree data structure in which each node has at most two children, which are referred to as the left child(LC) and the right child(RC).
//
// Important Binary Tree Terms & Properties �
// A binary tree is called STRICT / PROPER binary tree when each node has 2 or 0 children.
// A binary tree is called COMPLETE binary tree if all levels except the last are completely filled and all nodes are as left as possible.
// A binary tree is called PERFECT binary tree if all levels are completely filled with 2 children each.
// Max number of nodes at a given level 'x' = 2 ^ x
// For a binary tree, maximum number of nodes with height 'h' = 2 ^ (h + 1) � 1
// A binary tree is called BALANCE binary tree, if the difference between the height of left subtree and right subtree for every node is not more than k(usually k = 1).
//
// Sparse vs Dense Binary Tree �
// A dense binary tree is close to perfect(it has close to 2 ^ (h + 1) � 1 nodes).
// A sparse binary tree is closer to a linked list(it has close to h nodes).
//
// A binary tree can be implemented as an array with the LC formula 2 * i + 1 and RC formula 2 * i + 1, i being the index of the current node
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Binary search tree (BST)
// BST is a binary tree data structure, in which the values in the left sub-trees of every node are smaller and the values in the right sub-trees of every node are larger.
//
// Average Time Complexity of Binary Search Tree Operations(balanced) is � Big O(log N).
// Hence the searching is much more fast &efficient in BST compared to a linear Data Structure like linked list or array.
//
// Binary tree traversal can be categorized mainly in 2 types - 
// 1) Depth First Search(DFS) - These searches are referred to as depth-first search (DFS), since the search tree is deepened as much as possible on each child before going to the next sibling.
//    a) Pre-order (NLR)(node - left - right) - 
//       - Access the data part of the current node.
//       - Traverse the left subtree by recursively calling the pre-order function.
//       - Traverse the right subtree by recursively calling the pre-order function.
//       The pre-order traversal is a topologically sorted one, because a parent node is processed before any of its child nodes is done.
//    b) In-order (LNR) -
//       - Traverse the left subtree by recursively calling the in-order function.
//       - Access the data part of the current node.
//       - Traverse the right subtree by recursively calling the in-order function.
//       In BST in-order traversal retrieves the keys in ascending sorted order.
//    c) Post-order (LRN) -
//       - Traverse the left subtree by recursively calling the post-order function.
//       - Traverse the right subtree by recursively calling the post-order function.
//       - Access the data part of the current node.
//
// 2) Breadth First Search - Trees can also be traversed in level-order, where we visit every node on a level before going to a lower level. 
// This search is referred to as breadth-first search (BFS), as the search tree is broadened as much as possible on each depth before going to the next depth

// Classes
template <typename K, typename D>
class Node
{
	private:
	// Member variables
	K key;
	D data;
	Node<K, D> *left;
	Node<K, D> *right;

	public:
	// Member functions

	// Constructor
	Node()
	{
		key = K();
		data = D();
		left = nullptr;
		right = nullptr;
	}

	// Parameter constructor
	Node(K key, D data)
	{
		this->key = key;
		this->data = data;
	}

	// Get the key
	K get_key() const
	{
		return key;
	}

	// Get the data
	D get_data() const
	{
		return data;
	}

	// Get left
	Node<K, D> *get_left() const
	{
		return left;
	}

	// Get right
	Node<K, D> *get_right() const
	{
		return right;
	}

	// Set the key
	void set_key(K key)
	{
		this->key = key;
	}

	// Set the data
	void set_data(D data)
	{
		this->data = data;
	}

	// Set left
	void set_left(Node<K, D> *left)
	{
		this->left = left;
	}

	// Set right
	void set_right(Node<K, D> *right)
	{
		this->right = right;
	}
};

template <typename K, typename D>
class Binary_Search_Tree
{
	private:
	// Member variables
	Node<K, D> *root;

	public:
	// Member functions

	// Constructor
	Binary_Search_Tree()
	{
		root = nullptr;
	}

	// Parameter constructor
	Binary_Search_Tree(Node<K, D> *new_root)
	{
		root = new_root;
	}

	// Destructor
	~Binary_Search_Tree()
	{}

	// Get the root of the tree
	Node<K, D> *get_root() const
	{
		return root;
	}

	// Check if the tree is empty
	bool is_empty() const
	{
		if (root == nullptr)
		{
			return true;
		}
		return false;
	}

	// Insert node in tree
	void insert(Node<K,D> *new_node)
	{
		if(root == nullptr)
		{
			root == new_node;
			cout << "\nNew node with key[" << new_node->get_key() << "] and data: " << new_node->get_data() << " added successfully!" << endl;
		}
		else
		{
			Node<K,D> *trav_ptr - root;
			while(trav_ptr != nullptr)
			{
				if(new_node->get_data() == trav_ptr->get_data())
				{
					cerr << "\nNode already exists with this data: " << new_node->get_data() << endl;
					return;
				}
				else if(new_node->get_key() == trav_ptr->get_key())
				{
					cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
					return;
				}

				if((new_node->get_value() < trav_ptr->get_value() && (trav_ptr->get_left() == nullptr)))
				{
					trav_ptr->set_left(new_node);
					cout << "\nNode inserted to the left of: [" << trav_ptr->get_key() << "]: " << trav_ptr->get_data() << endl;
					break;
				}
				else if(new_node->get_value() < trav_ptr->get_value())
				{
					trav_ptr = trav_ptr->get_left();
				}
				else if((new_node->get_value() > trav_ptr->get_value() && (trav_ptr->get_right() == nullptr)))
				{
					trav_ptr->set_right(new_node);
					cout << "\nNode inserted to the right of: [" << trav_ptr->get_key() << "]: " << trav_ptr->get_data() << endl;
					break;
				}
				else if(new_node->get_value() > trav_ptr->get_value())
				{
					trav_ptr = trav_ptr->get_right();
				}
			}
		}
	}
	
	// Insert node in tree with recursion
	Node<K,D> *insert_recursive(Node<K,D> *root, Node<K,D> *new_node)
	{
		if(root == NULL)
		{
			root = new_node;
			cout << "Insertion successful" << endl;
			return root;
		}
	
		if(new_node->get_data() < root->get_data())
		{
			root->set_left(insertRecursive(root->get_left(), new_node));
		}
		else if (new_node->value > root->get_data())  
	    {
			root->set_right(insertRecursive(root->get_right(),new_node));
	    }
	    else
	    {
	     	cout << "No duplicate values allowed!" << endl;
	     	return root; 
	    }
		return root;
	}

	// Print tree
	void print_tree_2D(Node<K,D>*root, int space) const
	{
		if(is_empty())
		{
			retrun;
		}

		space += SPACE;

		print_tree_2D(root->get_right(),space);
		
		cout << endl;
		for (int i = SPACE; i < space; i++)
		{
			cout << " ";
		}
		cout << root->get_data() << endl;

		print_tree_2D(root->get_left(),space);
	}

	// Print pre_order (NLR)
	void print_pre_order(Node<K,D> *root)
	{
		// Base case
		if(root == nullptr)
		{
			return;
		}
		// Recursive case
		cout << " [" << root->get_key() << "]: " << root->get_data() << endl;
		print_pre_order(root->get_left());
		print_pre_order(root->get_right());
	}

	// Print in_order (LNR)
	void print_in_order(Node<K,D> *root)
	{
		// Base case
		if(root == nullptr)
		{
			return;
		}
		// Recursive case
		print_in_order(root->get_left());
		cout << " [" << root->get_key() << "]: " << root->get_data() << endl;
		print_in_order(root->get_right());
	}
	
	// Print post_order (LRN)
	void print_post_order(Node<K,D> *root)
	{
		// Base case
		if(root == nullptr)
		{
			return;
		}
		// Recursive case
		print_post_order(root->get_left());
		print_post_order(root->get_right());
		cout << " [" << root->get_key() << "]: " << root->get_data() << endl;
	}
	
	// Create a node
	static Node<K, D> *create_node()
	{
		Node<K, D> *node = new Node<K, D>;
		cout << "\n================= Create node =================\n";
		node->set_key(get_valid_input<K>("Set key: "));
		node->set_data(get_valid_input<D>("Set the data: "));
		cout << "===============================================\n";
		return node;
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	BST<int, int> bst1;
	int choice = 0;
	int key = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				bst1.insert(BST<int, int>::create_node());
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				bst1.print_tree_2D(bst1.get_root(),5);
				break;
			case 5:
				bst1.print_pre_order(bst1.get_root());
				break;
			case 6:
				bst1.print_in_order(bst1.get_root());
				break;
			case 7:
				bst1.print_post_order(bst1.get_root());
				break;
			case 8:
				break;
			case 9:
				system("cls");
				break;
			default:
				cout << "Try again" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	} while (choice != 0);

	return 0;
}

// Print the menu
void print_menu()
{
	// Add, is it complete,
	// is it perfect,
	// max number of nodes at a given level,
	// max number of nodes with a given hight,
	// count,
	// peek,
	// depth of a node,
	// hight of a node,
	// show root,
	// show parents of a node,
	// show siblings of a node,
	// show children of a node,
	// show leafs,
	// print path to a node from root,
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. Insert Node" << endl;
	cout << "2. Search Node" << endl;
	cout << "3. Delete Node" << endl;
	cout << "4. Print/Traversal BST values 2D" << endl;
	cout << "5. Print/Traversal BST values PRE  ORDER" << endl;
	cout << "6. Print/Traversal BST values IN   ORDER" << endl;
	cout << "7. Print/Traversal BST values POST ORDER" << endl;
	cout << "8. Height of Tree" << endl;
	cout << "9. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 9);
	return choice;
}