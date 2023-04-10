#include <iostream>

using namespace std;

// Singly-Linked Lists
template <typename T>
struct sll_node
{
	T value;
	sll_node *next;
};

template<typename T>
void insert_sll(sll_node<T> *&list, T value);

template<typename T>
void print_sll(sll_node<T> *&list);

template<typename T>
void free_sll(sll_node<T> *&list);

template<typename T>
void free_sll_recursive(sll_node<T> *&list);

template<typename T>
void free_sll_one_element(sll_node<T> *&list, T value);

template<typename T>
bool find_value_of_sll(sll_node<T> *&list, T value);

int main()
{
	sll_node<int> *list = nullptr; // Create a Singly-Linked Lists with size 0, to indicate that this is an empty list, so we can add upon to it.
	insert_sll(list, 1);
	insert_sll(list, 2);
	insert_sll(list, 3);

	print_sll(list);

	find_value_of_sll(list, 2);

	free_sll_one_element(list, 2);
}

																																 // With pointer to a pointer                        // With return
																																 //                                                  //
																																 // In main {insert(&list, 1);}                      // In main {list = insert(list, 1);}
template<typename T>                                                                                                             // template<typename T>                             // template <typename T>
void insert_sll(sll_node<T> *&list, T value)                                                                                     // void insert(sll_node<T>** list_ptr, T value)     // sll_node<T>* insert(sll_node<T>* list, T value)
{                                                                                                                                // {                                                // {
	sll_node<T> *node = new sll_node<T>; // Dynamically allocate space for a new sll_node                                        //		sll_node<T>* node = new sll_node<T>;         //		sll_node<T>* node = new sll_node<T>;
	node->value = value; //---------------- Initialize the node's value field                                                    //		node->value = value;                         //		node->value = value;
	node->next = list; //------------------ Initialize the node's next field, to point at the previous node                      //		node->next = *list_ptr;                      //		node->next = list;
	list = node; //------------------------ Make list point at the last inserted node                                            //		*list_ptr = node;                            //		return node;
}                                                                                                                                // }                                                // }

template<typename T>
void print_sll(sll_node<T> *&list)
{
	sll_node<T> *temp = list;
	while (temp != nullptr)
	{
		cout << "Value: " << temp->value << " Debug address thats pointing to the next value: " << temp->next << endl;
		temp = temp->next;
	}

	// Another way to print
	//
	// for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next)
	// {
	// 	cout << "Value: " << temp->value << " Debug address: " << temp->next << endl;
	// }
}

template<typename T>
void free_sll(sll_node<T> *&list)
{
	sll_node<T> *temp = list;
	while (temp != nullptr)
	{
		sll_node<T> *next = temp->next;
		delete temp;
		temp = next;
	}
}

template<typename T>
void free_sll_recursive(sll_node<T> *&list)
{
	// Base case
	if (list == nullptr)
	{
		return;
	}
	// Recursive case
	free_sll_recursive(list->next); // Delete the rest of the list
	delete list; //------------------- Free the current node
	list = nullptr; //---------------- Set the current pointer to null
}

// START : current -> 3; previous -> nullptr; target 2; list = 3, 2 ,1;
// NEXT  : previous -> current = 3; current -> current_next = 2;
// FOUND : previous_next = 2 -> current_next = 1;
//         delete current = 2;
//         current -> previous_next = 1;
// DONE;
template<typename T>
void free_sll_one_element(sll_node<T> *&list, T value)
{
	sll_node<T> *current = list;
	sll_node<T> *previous = nullptr;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (previous == nullptr) //----------- If the first node matches
			{
				list = current->next;
				delete current;
				current = list; //---------------- Update the current node
			}
			else //------------------------------- If a non-first node matches
			{
				previous->next = current->next; // Previous next here is the element we want to delete so we set it to equal the current next
				delete current;
				current = previous->next; //------ Update the current node
			}
		}
		else //----------------------------------- If the current node doesn't match
		{
			previous = current;
			current = current->next;
		}
	}
}

template<typename T>
bool find_value_of_sll(sll_node<T> *&list, T value)
{
	sll_node<T> *temp = list; //--------------------------- Create a traversal pointer pointing to the list's head.
	while (temp != nullptr)
	{
		if (temp->value == value) //----------------------- If the current node's val field is what we're looking for, report success.
		{
			cout << "Found value: " << temp->value << endl;
			return true;
		}
		temp = temp->next; //------------------------------ If not, set the traversal pointer to the next pointer in the list.
	}
	cout << "Value is not in list: " << value << endl;
	return false; //--------------------------------------- If you've reached the end of the list, report failure.
}
// • Arrays
//  • Insertion is bad – lots of shifting to fit an element in the middle
//  • Deletion is bad – lots of shifting after removing an element
//  • Lookup is great – random access, constant time
//  • Relatively easy to sort
//  • Relatively small size - wise
//  • Stuck with a fixed size, no flexibility
//
// • Linked lists
//  • Insertion is easy – just tack onto the front
//  • Deletion is easy – once you find the element
//  • Lookup is bad – have to rely on linear search
//  • Relatively difficult to sort – unless you're willing to compromise on super - fast insertion and instead sort as you construct
//  • Relatively small size - wise(not as small as arrays)
//    • In order to work with linked lists effectively, there are a number of operations that we need to understand :
//      1. Create a linked list when it doesn't already exist.
//		   a. Dynamically allocate space for a new sll_node.
//		   b. Check to make sure we didn't run out of memory.
//		   c. Initialize the node's value field.
//		   d. Initialize the node's next field.
//		   e. Return a pointer to the newly created sll_node.
//      2. Search through a linked list to find an element.
//		   a. Create a traversal pointer pointing to the list's head.
//		   b. If the current node's val field is what we're looking for, report success.
//         c. If not, set the traversal pointer to the next pointer in the list and go back to step b.
//         d. If you've reached the end of the list, report failure.
//      3. Insert a new node into the linked list.
//		   a. Dynamically allocate space for a new sll_node.
//		   b. Check to make sure we didn’t run out of memory.
//		   c. Populate and insert the node at the beginning of the linked list. Why because it is O(1) steps to do insertion if we do it at the end it is O(n).
//		   d. Return a pointer to the new head of the linked list.
//      4. Delete a single element from a linked list.
//      5. Delete an entire linked list.
//		   a. If you’ve reached a null pointer, stop.
//		   b. Delete the rest of the list.
//		   c. Free the current node.
//
// • Hash tables
//  • Insertion is a two - step process – hash, then add
//  • Deletion is easy – once you find the element
//  • Lookup is on average better than with linked lists because you have he benefit of a real - world constant factor
//  • Not an ideal data structure if sorting is the goal – just use an array
//  • Can run the gamut of size
//
// • Tries
//  • Insertion is complex – a lot of dynamic memory allocation, but gets easier as you go
//  • Deletion is easy – just free a node
//  • Lookup is fast – not quite as fast as an array, but almost
//  • Already sorted – sorts as you build in almost all situations
//  • Rapidly becomes huge, even with very little data present, not great if space is at a premium