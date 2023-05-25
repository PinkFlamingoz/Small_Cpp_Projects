#include <iostream>
#include <queue>
#include <math.h>
#include "basic_functions.h"

using namespace std;
// A tree is a non linear data structure that simulates a hierarchical tree structure with a root value and sub trees of children with parent node, represented as set of linked nodes.
//
// Tree terms -
// Root - Root is a special node in a tree. The entire tree is referenced through it.It does not have a parent.
// Parent Node - Parent node is an immediate predecessor of a node.
// Child Node - All immediate successors of a node are its children.
// Siblings - Nodes with the same parent are called Siblings.
// Leaf - Last node in the tree. There is no node after this node.
// Edge - Edge is a connection between one node to another. It is a line between two nodes or a node and a leaf.
// Path - Path is a number of successive edges from source node to destination node.
// Neighbor - Parent or child.
// Ancestor - A node reachable by repeated proceeding from child to parent.
// Descendant - A node reachable by repeated proceeding from parent to child. Also known as subchild.
// Degree - For a given node, its number of children. A leaf has necessarily degree zero.
// Degree of tree - The degree of a tree is the maximum degree of a node in the tree.
// Distance - The number of edges along the shortest path between two nodes.
// Level - The level of a node is the number of edges along the unique path between it and the root node. This is the same as depth.
// Width - The number of nodes in a level.
// Breadth - The number of leaves.
// Forest - A set of one or more disjoint trees.
// 
//Tree terms / properties -
// Tree can be termed as a RECURSIVE data structure.
// In a valid tree for N Nodes we have N - 1 Edges / Links
// Depth of Node - Depth of a node represents the number of edges from the tree's root node to the node.
// Height of Node - Height of a node is the number of edges on the longest path between that node & a leaf.
// Height of Tree - Height of tree represents the height of its root node.
//
// Types of Trees -
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
// Important Binary Tree Terms & Properties -
// A binary tree is called STRICT / PROPER binary tree when each node has 2 or 0 children.
// A binary tree is called COMPLETE binary tree if all levels except the last are completely filled and all nodes are as left as possible.
// A binary tree is called PERFECT binary tree if all levels are completely filled with 2 children each.
// Max number of nodes at a given level 'x' = 2 ^ x
// For a binary tree, maximum number of nodes with height 'h' = 2 ^ (h + 1) - 1
// A binary tree is called BALANCE binary tree, if the difference between the height of left subtree and right subtree for every node is not more than k(usually k = 1).
//
// Sparse vs Dense Binary Tree -
// A dense binary tree is close to perfect(it has close to 2 ^ (h + 1) - 1 nodes).
// A sparse binary tree is closer to a linked list(it has close to h nodes).
//
// A binary tree can be implemented as an array with the LC formula 2 * i + 1 and RC formula 2 * i + 1, i being the index of the current node
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Binary search tree (BST)
// BST is a binary tree data structure, in which the values in the left sub-trees of every node are smaller and the values in the right sub-trees of every node are larger.
//
// Average Time Complexity of Binary Search Tree Operations(balanced) is - Big O(log N).
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// AVL Tree
// AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot be more than one(1) for all nodes. 
// This difference is called the Balance Factor. BF = ( LEFT SUB TREE HEIGHT - RIGHT SUB TREE HEIGHT ) == { -1, 0, 1 }
// 
// NOTE: We always start by calculating the BF for all nodes and then we start balancing on the lowest level imbalanced node, after each operation we check the BF again for each node.
// When we balance a tree, we always consider three nodes from the node where the imbalance is happening, and if we have more nodes with imbalance we first balance the node at the lowest level.
// Then we recalculate the balance for every node, usually the other nodes sometimes balance out, that's why we balance the lowest level imbalanced node first.
// 
// To maintain the balance in AVL tree, we perform Rotations. Depending on different imbalance cases, we have 4 basic types of rotations –
// LEFT LEFT Imbalance/case ---> (RIGHT Rotation)
//		 z                     y      
//		/ \                   / \  
//	   y  T4                 x   z    
//    / \                   / \ / \
//	 x	T3                T1 T2 T3 T4
//  / \
// T1  T2   
//
// RIGHT RIGHT Imbalance/case ---> (LEFT Rotation)
//   z                         y    
//  / \                       / \     
// T1  y                     z   x      
//    / \                   / \ / \                            
//   T2  x                T1 T2 T3 T4                             
//      / \
//     T3 T4
//
// LEFT RIGHT Imbalance/case ---> (LEFT RIGHT Rotation)
//     z         		 z                x                
//    / \         		/ \              / \             
//   y  T4             x  T4            y   z                
//  / \               / \              / \ / \         
// T1  x          	 y	T3           T1 T2 T3 T4          
//    / \           / \                   
//   T2 T3         T1  T2                       
//
// RIGHT LEFT Imbalance/case ---> (RIGHT LEFT Rotation)
//   z                   z                x      
//  / \                 / \              / \       
// T1   y              T1  x            z   y        
//     / \                / \          / \ / \        
//    x  T4              T2  y       T1 T2 T3 T4       
//   / \                    / \            
//  T2 T3                  T3 T4             

// Constants
#define SPACE 10 // or we can use constexpr auto SPACE = 10;

// Classes
template <typename D>
class Node
{
	private:
	// Member variables
	D data;
	Node<D> *left;
	Node<D> *right;

	public:
	// Member functions

	// Constructor
	Node()
	{
		data = D();
		left = nullptr;
		right = nullptr;
	}

	// Parameter constructor
	Node(D data)
	{
		this->data = data;
	}

	// Get the data
	D get_data() const
	{
		return data;
	}

	// Get left
	Node<D> *get_left() const
	{
		return left;
	}

	// Get right
	Node<D> *get_right() const
	{
		return right;
	}

	// Set the data
	void set_data(D data)
	{
		this->data = data;
	}

	// Set left
	void set_left(Node<D> *left)
	{
		this->left = left;
	}

	// Set right
	void set_right(Node<D> *right)
	{
		this->right = right;
	}
};

template <typename D>
class Binary_Search_Tree
{
	private:
	// Member variables
	Node<D> *root;

	public:
	// Member functions

	// Constructor
	Binary_Search_Tree()
	{
		root = nullptr;
	}

	// Parameter constructor
	Binary_Search_Tree(Node<D> *new_root)
	{
		root = new_root;
	}

	// Destructor
	~Binary_Search_Tree()
	{
		delete_tree();
	}

	// Get the root of the tree
	Node<D> *get_root() const
	{
		return root;
	}

	// Set root
	void set_root(Node<D> *root)
	{
		this->root = root;
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

	// Check if the current node are empty
	bool is_empty_node(Node<D> *&root) const
	{
		if (root == nullptr)
		{
			return true;
		}
		return false;
	}

	// Rotate left
	Node<D> *rotate_left(Node<D> *node)
	{
		Node<D> *right = node->get_right(); //----- Get the right node of the parent aka this node will now be in the place of the parent
		Node<D> *left_child = right->get_left(); // Get the left children if that node has any because in that place we will set the previous parent

		//----------------------------------------- Perform the rotation
		right->set_left(node); //------------------ Set the previous parent to the new location
		node->set_right(left_child); //-------------- Set the left children of the right node to be the right children of the previous parent

		return right;
	}

	// Rotate right
	Node<D> *rotate_right(Node<D> *node)
	{
		Node<D> *left = node->get_left(); //-------- Get the left node of the parent aka this node will now be in the place of the parent
		Node<D> *right_child = left->get_right(); // Get the right children if that node has any because in that place we will set the previous parent

		//------------------------------------------ Perform the rotation
		left->set_right(node); //------------------- Set the previous parent to the new location
		node->set_left(right_child); //------------- Set the right children of the left node to be the left children of the previous parent

		return left;
	}

	// Get balance factor for each node
	int get_balance_factor(Node<D> *node) const
	{
		if (node == nullptr)
		{
			return -1;
		}
		return (height(node->get_left() - height(node->get_right())));
	}
	
	// Is tree balanced
	bool is_tree_balanced(Node<D> *root) const
	{	
		// Base case
		if (root == nullptr)
		{
        	return true;
    	}
		// Recursive case
		int left_height = height(root->get_left());
    	int right_height = height(root->get_right());
   		// Check if current node is balanced and recursively check for left and right subtrees
    	return abs(leftHeight - rightHeight) <= 1 && is_tree_balanced(root->get_left()) && is_tree_balanced(root->get_right());
	}

	// Balance a tree when inserting a node
	Node<D> *balance_tree_when_inserting(Node<D> *root, Node<D> *new_node)
	{
		int bf = get_balance_factor(root);
		if (bf == 1 || bf == -1 || bf == 0)
		{
			return root;
		}

		if (bf > 1 && new_node-get_value() < root->get_left()->get_value()) //-- LEFT LEFT Imbalance/case ---> (RIGHT Rotation)
		{
			return rotate_right(root);
		}

		if (bf < -1 && new_node-get_value() > root->get_right()->get_value()) // RIGHT RIGHT Imbalance/case ---> (LEFT Rotation)
		{
			return rotate_left(root);
		}

		if (bf > 1 && new_node-get_value() > root->get_left()->get_value()) //-- LEFT RIGHT Imbalance/case ---> (LEFT RIGHT Rotation) 
		{
			root->set_left(rotate_left(root->get_left()));
			return rotate_right(root);
		}

		if (bf < -1 && new_node-get_value() < root->get_right()->get_value()) // RIGHT LEFT Imbalance/case ---> (RIGHT LEFT Rotation)
		{
			root->set_right(rotate_right(root->get_right()));
			return rotate_left(root);
		}
	}

	// Balance a tree when deleting a node
	Node<D> *balance_tree_when_deleting(Node<D> *root, Node<D> *new_node)
	{
		int bf = get_balance_factor(root);
		if (bf == 1 || root == -1 || root == 0)
		{
			return root;
		}

		if (bf == 2 && get_balance_factor(root->get_left()) >= 0) //-- LEFT LEFT Imbalance/case ---> (RIGHT Rotation)
		{
			return rotate_right(root);
		}

		if (bf == -2 && get_balance_factor(root->get_right()) <= 0) // RIGHT RIGHT Imbalance/case ---> (LEFT Rotation) 
		{
			return rotate_left(root);	
		}

		if (bf == 2 && get_balance_factor(root->get_left()) == -1) //- LEFT RIGHT Imbalance/case ---> (LEFT RIGHT Rotation) 
		{
			root->set_left(rotate_left(root->get_left()));
			return rotate_right(root);
			
		}

		if (bf == -2 && get_balance_factor(root->get_right()) == 1) // RIGHT LEFT Imbalance/case ---> (RIGHT LEFT Rotation)
		{
			root->set_right(rotate_right(root->get_right()));
			return rotate_left(root);
		}
	}

	// Insert node in tree // CASE 1: IF THE TREE IS EMPTY, CASE 2: IF WE HAVE THE SAME VALUES, CASE 3: IF ITS SMALLER, CASE 4: IF ITS BIGGER
	void insert(Node<D> *new_node)
	{
		if (root == nullptr) //--------------------------------------------------------------------------------- CASE 1: If the tree is empty
		{
			root = new_node;
			cout << "\nNew node with data: " << new_node->get_data() << " added successfully!" << endl;
		}
		else
		{
			Node<D> *trav_ptr = root;
			while (trav_ptr != nullptr)
			{
				if (new_node->get_data() == trav_ptr->get_data()) //-------------------------------------------- CASE 2: If we have the same data
				{
					cerr << "\nNode already exists with this data: " << new_node->get_data() << endl;
					return;
				}

				if ((new_node->get_data() < trav_ptr->get_data() && (trav_ptr->get_left() == nullptr))) //------ CASE 3: If the data is smaller then the previous data and its a leaf node
				{
					trav_ptr->set_left(new_node);
					cout << "\nNode inserted to the left of: " << trav_ptr->get_data() << endl;
					break;
				}
				else if (new_node->get_data() < trav_ptr->get_data()) //---------------------------------------- CASE 3.1: If the data is smaller then the previous data and its not a leaf node
				{
					trav_ptr = trav_ptr->get_left();
				}
				else if ((new_node->get_data() > trav_ptr->get_data() && (trav_ptr->get_right() == nullptr))) // CASE 4: If the data is bigger then the previous data and its a leaf node
				{
					trav_ptr->set_right(new_node);
					cout << "\nNode inserted to the right of: " << trav_ptr->get_data() << endl;
					break;
				}
				else if (new_node->get_data() > trav_ptr->get_data()) //---------------------------------------- CASE 4.1: If the data is bigger then the previous data and its not a leaf node
				{
					trav_ptr = trav_ptr->get_right();
				}
			}
		}
	}

	// Insert node in tree recursive // CASE 1: IF THE TREE IS EMPTY, CASE 2: IF WE HAVE THE SAME VALUES, CASE 3: IF ITS SMALLER, CASE 4: IF ITS BIGGER
	Node<D> *insert_recursive(Node<D> *root, Node<D> *new_node)
	{
		// Base case
		if(root == nullptr) //--------------------------------------------------------------- CASE 1: If the tree is empty
		{
			root = new_node;
			return root;
		}
		// Recursive case
		if (new_node->get_data() < root->get_data()) //-------------------------------------- CASE 3: If the data is smaller then the previous data
		{
			root->set_left(insert_recursive(root->get_left(), new_node));
		}
		else if (new_node->get_data() > root->get_data()) //--------------------------------- CASE 4: If the data is bigger then the previous data
		{
			root->set_right(insert_recursive(root->get_right(), new_node));
		}
		else //------------------------------------------------------------------------------ CASE 2: If we have the same data
		{
			cerr << "\nNode already exists with this data: " << new_node->get_data() << endl;
			return root;
		}

		root = balance_tree_when_inserting(root, new_node);

		return root;
	}

	// Search (Divide and Conquer)
	Node<D> *search(D data) const
	{
		Node<D> *temp = root;
		while (temp != nullptr)
		{
			if (data == temp->get_data())
			{
				return temp;
			}
			else if (data < temp->get_data())
			{
				temp = temp->get_left();
			}
			else
			{
				temp = temp->get_right();
			}
		}
		return nullptr;
	}

	Node<D> *search_recursive(Node<D> * root, D data) const
	{
		// Base case
		if (root == nullptr || root->get_data() == data)
		{
			return root;
		}
		// Recursive case
		if (data < root->get_data())
		{
			return search_recursive(root->get_left(), data);
		}
		else
		{
			return search_recursive(root->get_right(), data);
		}
  	}

	// Delete node in tree // CASE 1: DELETE A LEAF NODE, CASE 2: DELETE A NODE WITH ONE CHILD, CASE 3: DELETE A NODE WITH TWO CHILDREN
	Node<D> *delete_node(Node<D> *root, D data)
	{
		// Base case
		if (root == nullptr)
		{
			return nullptr;
		}
		// Recursive case
		else if (data < root->get_data()) //----------------------------------------- If the key to be deleted is smaller than the root's key, then it lies in left subtree
		{
			root->set_left(delete_node(root->get_left(), data));
		}
		else if (data > root->get_data()) //----------------------------------------- If the key to be deleted is greater than the root's key, then it lies in right subtree
		{
			root->set_right(delete_node(root->get_right(), data));
		}
		else //---------------------------------------------------------------------- If key is same as root's key, then this is the node to be deleted
		{ //------------------------------------------------------------------------- CASE 1 & 2: Node with only one child or no child
			if (root->get_left() == nullptr) //-------------------------------------- Node with only right child or no child
			{
				Node<D> *temp = root->get_right();
				delete root;
				return temp;
			}
			else if (root->get_right() == nullptr) //-------------------------------- Node with only left child
			{
				Node<D> *temp = root->get_left();
				delete root;
				return temp;
			}
			else //------------------------------------------------------------------ CASE 3: Node with two children
			{
				Node<D> *temp = min_node(root->get_right()); //---------------------- Get the in_order successor (smallest in the right subtree)
				root->set_data(temp->get_data()); //--------------------------------- Copy the in_order successor's content to this node
				root->set_right(delete_node(root->get_right(), temp->get_data())); // Delete the in_order successor

				// Node<D> *temp = max_node(root->get_left()); //-------------------- Get the in_order successor (smallest in the left subtree)
				// root->set_data(temp->get_data()); //------------------------------ Copy the in_order successor's content to this node
				// root->set_left(delete_node(root->get_left(),temp->get_data())); // Delete the in_order successor
			}
		}

		root = balance_tree_when_deleting(root, new_node);

		return root;
	}

	// Get the min node by going down to find the left most leaf
	Node<D> *min_node(Node<D> *node) const
	{
		Node<D> *current = node;
		while (current->get_left() != nullptr)
		{
			current = current->get_left();
		}
		return current;
	}

	// Get the max node by going down to find the right most leaf
	Node<D> *max_node(Node<D> *node) const
	{
		Node<D> *current = node;
		while (current->get_right() != nullptr)
		{
			current = current->get_right();
		}
		return current;
	}

	// Print tree rotated 90 deg, this is just reverse in_order but with spaces and new lines in between
	void print_tree_2D(Node<D> *root, int space) const
	{
		// Base case
		if (root == nullptr) // or use is_empty_leaf in recursive cases
		{
			return;
		}
		// Recursive case
		space += SPACE;
		print_tree_2D(root->get_right(), space);

		cout << endl;
		for (int i = SPACE; i < space; i++)
		{
			cout << " ";
		}
		cout << root->get_data() << endl;

		print_tree_2D(root->get_left(), space);
	}

	// Print pre_order (NLR)
	void print_pre_order(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return;
		}
		// Recursive case
		cout << " [" << root->get_left() << "] <--- [" << root << "]: " << root->get_data() << " ---> [" << root->get_right() << "] ";
		print_pre_order(root->get_left());
		print_pre_order(root->get_right());
	}

	// Print in_order (LNR), just reverse R and L if we wanna get the reverse in_order version of this aka it will print in descending order
	void print_in_order(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return;
		}
		// Recursive case
		print_in_order(root->get_left());
		cout << " [" << root->get_left() << "] <--- [" << root << "]: " << root->get_data() << " ---> [" << root->get_right() << "] ";
		print_in_order(root->get_right());
	}

	// Print post_order (LRN)
	void print_post_order(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return;
		}
		// Recursive case
		print_post_order(root->get_left());
		print_post_order(root->get_right());
		cout << " [" << root->get_left() << "] <--- [" << root << "]: " << root->get_data() << " ---> [" << root->get_right() << "] ";
	}

	// Print nodes at a given level
	void print_given_level(Node<D> *root, int level) const
	{
		// Base case
		if (root == nullptr)
		{
			return;
		}
		else if (level == 0)
		{
			cout << root->get_data() << " "; //--------- Reached the desired level, print the value
		}
		// Recursive case
		print_given_level(root->get_left(), level - 1);
		print_given_level(root->get_right(), level - 1);
	}

	// Print tree in Breadth First Search
	void print_BFS_tree(Node<D> *root) const
	{
		int height = get_height(root);
		for (int i = 0; i <= height; i++)
		{
			cout << "Level " << i << ": ";
			print_given_level(root, i);
			cout << endl;
		}
	}

	// Print path from root to node
	void print_path_to_node(D data) const
	{
		Node<D> *temp = root;
		while (temp != nullptr)
		{
			if (data == temp->get_data())
			{
				cout << "[" << temp << "]: " << temp->get_data() << endl;
				return;
			}
			else if (data < temp->get_data())
			{
				cout << "[" << temp << "]: " << temp->get_data() << " ---> ";
				temp = temp->get_left();
			}
			else
			{
				cout << "[" << temp << "]: " << temp->get_data() << " ---> ";
				temp = temp->get_right();
			}
		}
		return;
	}

	// Show parent of a node test for node thats not in tree
	void show_parent(Node<D> *root, Node<D> *node) const
	{
		Node<D> *parent = find_parent(root, node);

		if (parent == nullptr)
		{
			cout << "\nNode [" << node << "]: " << node->get_data() << " is the root node." << endl;
		}
		else
		{
			cout << "\nParent of node [" << node << "]: " << node->get_data() << " is: [" << parent << "]: " << parent->get_data() << endl;
		}
	}

	// Find the parent of a node in the binary search tree
	Node<D> *find_parent(Node<D> *root, Node<D> *node) const
	{
		// Base case
		if (root == nullptr || root == node)
		{
			return nullptr;  //-------------------------------------- Node not found or root node reached
		}

		if (root->get_left() == node || root->get_right() == node)
		{
			return root; //------------------------------------------ Found the parent node
		}
		// Recursive case
		Node<D> *left_parent = find_parent(root->get_left(), node);
		if (left_parent != nullptr)
		{
			return left_parent; //----------------------------------- Found parent in the left subtree
		}

		Node<D> *right_parent = find_parent(root->get_right(), node);
		if (right_parent != nullptr)
		{
			return right_parent; //---------------------------------- Found parent in the right subtree
		}

		return nullptr; //------------------------------------------- Parent not found
	}

	// Show children of a node
	void show_children(Node<D> *node) const
	{
		Node<D> *temp_node = node;

		if (temp_node->get_left() == nullptr && temp_node->get_right() == nullptr)
		{
			cout << "\nChildren of node [" << temp_node << "]: " << temp_node->get_data() << " are:\nLeft: nullptr\nRight: nullptr" << endl;
		}
		else if (temp_node->get_left() == nullptr)
		{
			cout << "\nChildren of node [" << temp_node << "]: " << temp_node->get_data() << " are:\nLeft: nullptr\nRight: [" << temp_node->get_right() << "]: " << temp_node->get_right()->get_data() << endl;
		}
		else if (temp_node->get_right() == nullptr)
		{
			cout << "\nChildren of node [" << temp_node << "]: " << temp_node->get_data() << " are:\nLeft: [" << temp_node->get_left() << "]: " << temp_node->get_left()->get_data() << "\nRight: nullptr" << endl;
		}
		else
		{
			cout << "\nChildren of node [" << temp_node << "]: " << temp_node->get_data() << " are:\nLeft: [" << temp_node->get_left() << "]: " << temp_node->get_left()->get_data() << "\nRight: [" << temp_node->get_right() << "]: " << temp_node->get_right()->get_data() << endl;
		}
	}

	// Get the depth of a node
	int get_depth(Node<D> *root, Node<D> *node) const
	{
		// Base case
		if (root == nullptr || node == nullptr)
		{
			return -1;
		}

		if (root == node)
		{
			return 0;
		}

		// Recursive case
		int depth = get_depth(root->get_left(), node);
		if (depth >= 0)
		{
			return depth + 1;
		}

		depth = get_depth(root->get_right(), node);
		if (depth >= 0)
		{
			return depth + 1;
		}

		return -1;
	}

	// Get the height of the tree where we compare the left and right paths of the tree
	int get_height(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return -1;
		}
		// Recursive case
		int left_height = get_height(root->get_left());
		int right_height = get_height(root->get_right());

		if (left_height > right_height)
		{
			return (left_height + 1);
		}
		else
		{
			return (right_height + 1);
		}
	}

	// Count nodes in tree
	int count_nodes(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return 0;
		}
		// Recursive case
		int left_count = count_nodes(root->get_left());
		int right_count = count_nodes(root->get_right());

		// Add 1 for the current node
		return 1 + left_count + right_count;
	}

	// Count the number of nodes on a specific level of a binary tree
	int count_nodes_on_level(Node<D> *root, int level) const
	{
		// Base case
		if (root == nullptr)
		{
			return 0;
		}
		else if (level == 0)
		{
			return 1; //----------------------------------------------------- Reached the desired level, return 1 for the current node
		}
		// Recursive case
		int left_count = count_nodes_on_level(root->get_left(), level - 1);
		int right_count = count_nodes_on_level(root->get_right(), level - 1);

		return left_count + right_count;
	}

	// Print leaf nodes of a tree
	void print_leaf_nodes(Node<D> *root) const
	{
		// Base case
		if (root == nullptr)
		{
			return;
		}
		else if (root->get_left() == nullptr && root->get_right() == nullptr)
		{
			cout << root->get_data() << " ";
		}
		// Recursive case
		print_leaf_nodes(root->get_left());
		print_leaf_nodes(root->get_right());
	}

	// Check if the tree is complete
	// In a complete binary tree, all levels, except possibly the last one, are completely filled, and all nodes are left - justified.
	// This means that during a level - order traversal, all nodes at each level should be visited before moving to the next level.
	// If we encounter a nullptr node before visiting all the nodes at a particular level, it indicates that the tree is not complete.
	//		 1
	//		/ \
	//	   2   3
	//    / \   \
	//	 4   5   6
	// During a level-order traversal, we visit nodes in the following order: 1, 2, 3, 4, 5, 6.
	// If we encounter a nullptr node after visiting the node with value 5, it indicates that there is a gap in the tree at the third level.
	// In this case, the node with value 3 is missing a left child, and the tree is not complete.
	bool is_it_complete_tree() const
	{
		if (root == nullptr)
		{
			return true; //------------------ If the tree is empty, it is considered complete
		}

		queue<Node<D> *> q; //--------------- Create a queue to perform level-order traversal

		q.push(root); //--------------------- Push the root node into the queue

		bool end_reached = false; //--------- Flag to track if a nullptr node is encountered

		while (!q.empty()) //---------------- Continue until the queue becomes empty
		{
			Node<D> *current = q.front(); //- Dequeue the front node
			q.pop();

			if (current == nullptr)	//------- Check if the current node is nullptr
			{
				end_reached = true; //------- If it is, mark that an end point has been reached
			}
			else //-------------------------- If the current node is not nullptr
			{
				if (end_reached) //---------- Check if an end point has been reached previously
				{
					return false; //--------- If yes, it means the tree is not complete
				}

				//--------------------------- Enqueue the left and right child nodes of the current node
				q.push(current->get_left());
				q.push(current->get_right());
			}
		}

		return true; //---------------------- If the loop completes without returning false, the tree is complete
	}

	// Check if a binary tree is perfect
	bool is_it_perfect_tree(Node<D> *root) const
	{
		if (root == nullptr)
		{
			return true;
		}

		int tree_height = get_height(root);
		int expected_node_count = pow(2, tree_height + 1) - 1;
		int actual_node_count = count_nodes(root);

		return expected_node_count == actual_node_count;
	}

	// Delete the tree
	void delete_tree()
	{
		delete_subtree(root);
		root = nullptr;
		cout << "\nTree deleted!" << endl;
	}

	// Delete the sub tree
	void delete_subtree(Node<D> *node)
	{
		// Base case
		if (node == nullptr)
		{
			return;
		}
		// Recursive case
		delete_subtree(node->get_left());
		delete_subtree(node->get_right());

		delete node;
	}

	// Create a node
	static Node<D> *create_node()
	{
		Node<D> *node = new Node<D>;
		cout << "\n================= Create node =================\n";
		node->set_data(get_valid_input<D>("Set the data: "));
		cout << "===============================================\n";
		return node;
	}
};

// Functions
void print_menu();
int get_choice();
int get_level(int hight);

int main()
{
	Binary_Search_Tree<int> bst1;
	Node<int> *bst_node = nullptr;
	int choice = 0;
	int level = 0;
	int bst_node_data = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				bst1.insert(Binary_Search_Tree<int>::create_node());
				break;
			case 2:
				bst_node = bst1.search(get_valid_input<int>("Enter data to search for: "));
				if (bst_node != nullptr)
				{
					bst1.show_parent(bst1.get_root(), bst_node);
					cout << endl;
					cout << "Found node: " << "[" << bst_node << "]: " << bst_node->get_data() << endl;
					bst1.show_children(bst_node);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 3:
				bst1.set_root(bst1.insert_recursive(bst1.get_root(), Binary_Search_Tree<int>::create_node()));
				break;
			case 4:
				bst_node = bst1.search_recursive(bst1.get_root(), get_valid_input<int>("Enter data to search for: "));
				if (bst_node != nullptr)
				{
					bst1.show_parent(bst1.get_root(), bst_node);
					cout << endl;
					cout << "Found node: " << "[" << bst_node << "]: " << bst_node->get_data() << endl;
					bst1.show_children(bst_node);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 5:
				bst_node_data = get_valid_input<int>("Enter data to delete: ");
				bst_node = bst1.search(bst_node_data);
				if (bst_node != nullptr)
				{
					bst1.set_root(bst1.delete_node(bst1.get_root(), bst_node_data));
					cout << "Node deleted!" << endl;
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 6:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					bst1.print_tree_2D(bst1.get_root(), 5);
				}
				break;
			case 7:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					bst1.print_pre_order(bst1.get_root());
				}
				break;
			case 8:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					bst1.print_in_order(bst1.get_root());
				}
				break;
			case 9:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					bst1.print_post_order(bst1.get_root());
				}
				break;
			case 10:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					bst1.print_BFS_tree(bst1.get_root());
				}
				break;
			case 11:
				bst_node_data = get_valid_input<int>("Enter data to print path for: ");
				bst_node = bst1.search(bst_node_data);
				if (bst_node != nullptr)
				{
					bst1.print_path_to_node(bst_node_data);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 12:
				bst_node = bst1.search(get_valid_input<int>("Enter data to see parent of: "));
				if (bst_node != nullptr)
				{
					bst1.show_parent(bst1.get_root(), bst_node);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 13:
				bst_node = bst1.search(get_valid_input<int>("Enter data to see siblings for: "));
				if (bst_node != nullptr)
				{
					level = bst1.get_depth(bst1.get_root(), bst_node);
					cout << "Siblings on level " << level << ": ";
					bst1.print_given_level(bst1.get_root(), level);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 14:
				bst_node = bst1.search(get_valid_input<int>("Enter data to see children for: "));
				if (bst_node != nullptr)
				{
					bst1.show_children(bst_node);
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 15:
				bst_node = bst1.search(get_valid_input<int>("Enter data of to see depth for: "));
				if (bst_node != nullptr)
				{
					cout << "Depth of current node is: " << bst1.get_depth(bst1.get_root(), bst_node) << endl;
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 16:
				bst_node = bst1.search(get_valid_input<int>("Enter data of to see height for: "));
				if (bst_node != nullptr)
				{
					cout << "Height of current node is: " << bst1.get_height(bst_node) << endl;
				}
				else
				{
					cout << "No node with that data exists!" << endl;
				}
				break;
			case 17:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Tree is not empty!" << endl;
				}
				break;
			case 18:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Root of tree is: [" << bst1.get_root() << "]: " << bst1.get_root()->get_data() << endl;
				}
				break;
			case 19:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Height of tree is: " << bst1.get_height(bst1.get_root()) << endl;
				}
				break;
			case 20:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Total number of levels in the tree: " << bst1.get_height(bst1.get_root()) << endl;
				}
				break;
			case 21:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Total number of nodes in the tree: " << bst1.count_nodes(bst1.get_root()) << endl;
				}
				break;
			case 22:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					level = get_level(bst1.get_height(bst1.get_root()));
					cout << "Number of nodes on level " << level << ": " << bst1.count_nodes_on_level(bst1.get_root(), level);
				}
				break;
			case 23:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					level = get_level(bst1.get_height(bst1.get_root()));
					cout << "Nodes on level " << level << ": ";
					bst1.print_given_level(bst1.get_root(), level);
				}
				break;
			case 24:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Leafs in the tree are: ";
					bst1.print_leaf_nodes(bst1.get_root());
				}
				break;
			case 25:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Min node in the tree is: [" << bst1.min_node(bst1.get_root()) << "]: " << bst1.min_node(bst1.get_root())->get_data();
				}
				break;
			case 26:
				if (bst1.is_empty())
				{
					cout << "Tree is empty!" << endl;
				}
				else
				{
					cout << "Max node in the tree is: [" << bst1.max_node(bst1.get_root()) << "]: " << bst1.max_node(bst1.get_root())->get_data();
				}
				break;
			case 27:
				if (bst1.is_it_complete_tree())
				{
					cout << "The tree is complete!" << endl;
				}
				else
				{
					cout << "The tree is not complete!" << endl;
				}
				break;
			case 28:
				if (bst1.is_it_perfect_tree(bst1.get_root()))
				{
					cout << "The tree is perfect!" << endl;
				}
				else
				{
					cout << "The tree is not perfect!" << endl;
				}
				break;
			case 28:
				if (bst1.is_tree_balanced(bst1.get_root()))
				{
					cout << "The tree is balanced!" << endl;
				}
				else
				{
					cout << "The tree is not balanced!" << endl;
				}
				break;
			case 29:
				bst1.delete_tree();
				break;
			case 30:
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
	// Finding the lowest common ancestor of two nodes
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. Insert Node NOTE: This will not add a balanced node" << endl;
	cout << "2. Search Node" << endl;
	cout << "3. Insert Node Recursive" << endl;
	cout << "4. Search Node Recursive" << endl;
	cout << "5. Delete Node" << endl;
	cout << "6. Print/Traversal BST 2D" << endl;
	cout << "7. Print/Traversal BST PRE  ORDER" << endl;
	cout << "8. Print/Traversal BST IN   ORDER" << endl;
	cout << "9. Print/Traversal BST POST ORDER" << endl;
	cout << "10. Print/Traversal BST BFS ORDER" << endl;
	cout << "11. Print path to node" << endl;
	cout << "12. Show parent of a node" << endl;
	cout << "13. Show siblings of a node" << endl;
	cout << "14. Show children of a node" << endl;
	cout << "15. Show depth of a node" << endl;
	cout << "16. Show hight of a node" << endl;
	cout << "17. Is the Tree empty" << endl;
	cout << "18. Root of Tree" << endl;
	cout << "19. Height of Tree" << endl;
	cout << "20. Count levels in Tree" << endl;
	cout << "21. Count nodes in Tree" << endl;
	cout << "22. Count nodes on a specific level" << endl;
	cout << "23. Print nodes on a specific level" << endl;
	cout << "24. Print leaf nodes in Tree" << endl;
	cout << "25. Print Min node in Tree" << endl;
	cout << "26. Print Max node in Tree" << endl;
	cout << "27. Is it a complete Tree" << endl;
	cout << "28. Is it a perfect Tree" << endl;
	cout << "29. Is it a balanced Tree" << endl;
	cout << "30. Delete Tree" << endl;
	cout << "31. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 31);
	return choice;
}

// Get the level of a tree
int get_level(int hight)
{
	int level = 0;
	do
	{
		cout << "Max hight is: " << hight << endl;
		level = get_valid_input<int>("Enter the given level: ");
	} while (level < 0 || level > hight);
	return level;
}