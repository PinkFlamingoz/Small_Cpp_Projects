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
void prepend_sll(sll_node<T> *&list, T value);

template<typename T>
void append_sll(sll_node<T> *&list, T value);

template<typename T>
void insert_sorted_sll(sll_node<T> *&list, T value);

template<typename T>
void print_sll(sll_node<T> *list);

template<typename T>
void delete_sll(sll_node<T> *&list);

template<typename T>
void delete_sll_recursive(sll_node<T> *&list);

template<typename T>
void delete_sll_elements_with_the_same_value(sll_node<T> *&list, T value);

template<typename T>
void delete_sll_element_first_occurrence(sll_node<T> *&list, T value);

template<typename T>
bool find_value_in_sll(sll_node<T> *list, T value);

template<typename T>
void bubble_sort_sll(sll_node<T> *&list);

int main()
{
	sll_node<int> *list = nullptr; // Create a Singly-Linked Lists with size 0, to indicate that this is an empty list, so we can add upon to it.

	append_sll(list, 3);
	prepend_sll(list, 9);
	prepend_sll(list, 7);
	prepend_sll(list, 11);
	insert_sorted_sll(list, 8);
	insert_sorted_sll(list, 5);
	insert_sorted_sll(list, 0);
	insert_sorted_sll(list, 10);
	insert_sorted_sll(list, 4);
	insert_sorted_sll(list, 1);
	insert_sorted_sll(list, 2);

	print_sll(list);

	find_value_in_sll(list, 2);

	delete_sll_elements_with_the_same_value(list, 3);

	bubble_sort_sll(list);

	print_sll(list);

	delete_sll(list);

	print_sll(list);
}

																																 // With pointer to a pointer                        // With return
																																 //                                                  //
// Prepend, add infront of the linked list O(1)																					 // In main {insert(&list, 1);}                      // In main {list = insert(list, 1);}
template<typename T>                                                                                                             // template<typename T>                             // template <typename T>
void prepend_sll(sll_node<T> *&list, T value)                                                                                    // void insert(sll_node<T>** list_ptr, T value)     // sll_node<T>* insert(sll_node<T>* list, T value)
{                                                                                                                                // {                                                // {
	sll_node<T> *node = new sll_node<T>; // Dynamically allocate space for a new sll_node                                        //		sll_node<T>* node = new sll_node<T>;         //		sll_node<T>* node = new sll_node<T>;
	node->value = value; //---------------- Initialize the node's value field                                                    //		node->value = value;                         //		node->value = value;
	node->next = list; //------------------ Initialize the node's next field, to point at the previous node                      //		node->next = *list_ptr;                      //		node->next = list;
	list = node; //------------------------ Make list point at the last inserted node                                            //		*list_ptr = node;                            //		return node;
}                                                                                                                                // }                                                // }

// Append, add at the end of the linked list O(n)
template<typename T>
void append_sll(sll_node<T> *&list, T value)
{
	sll_node<T> *node = new sll_node<T>; //---------------------------------- Dynamically allocate space for a new sll_node
	node->value = value; //-------------------------------------------------- Initialize the node's value field
	node->next = nullptr; //------------------------------------------------- Initialize the node's next field to point at nullptr because this will be the last element of the linked list

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else //------------------------------------------------------------------ If the list has some values already
	{
		for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ At the end of the list add the value, 3 -> 2, 2 -> 1, 1 -> nullptr add it here so we would have, 3 -> 2 -> 1 -> new -> nullptr
			{
				temp->next = node;
				break; //---------------------------------------------------- To prevent keep adding the same node over and over again
			}
		}
	}
}

// Insert and sort at the same time
template<typename T>
void insert_sorted_sll(sll_node<T> *&list, T value)
{
	sll_node<T> *node = new sll_node<T>;
	node->value = value;
	node->next = nullptr;

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else if (node->value < list->value) //----------------------------------- If the value belongs at beginning of list
	{
		node->next = list;
		list = node;
	}
	else //------------------------------------------------------------------ If the value belongs later in list
	{
		for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ If at end of list
			{
				temp->next = node; //---------------------------------------- Append node
				break;
			}
			if (node->value < temp->next->value) //-------------------------- If in middle of list, if the node value is smaller than the next node value, set the node pointer to point at the current temp pointer, and set the current temp pointer to point at the node
			{
				node->next = temp->next; //---------------------------------- Set the nullptr of the node that we are trying to insert to point at the bigger temp value
				temp->next = node; //---------------------------------------- Make the current temp point at the node we are trying to insert and this also points to the rest of the values in the linked list
				break;
			}
		}
	}
}

// Print the list
template<typename T>
void print_sll(sll_node<T> *list)
{
	sll_node<T> *temp = list; // We create a temp variable so we dont change the list values
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

// Delete all of the list
template<typename T>
void delete_sll(sll_node<T> *&list)
{
	while (list != nullptr)
	{
		sll_node<T> *next = list->next; // Grab the next pointer before deleting this one!
		delete list;
		list = next;
	}
}

// Delete all of the list with recursion
template<typename T>
void delete_sll_recursive(sll_node<T> *&list)
{
	// Base case
	if (list == nullptr)
	{
		return;
	}
	// Recursive case
	delete_sll_recursive(list->next); // Delete the rest of the list
	delete list; //--------------------- Free the current node
	list = nullptr; //------------------ Set the current pointer to null
}

// Delete sll elements with the same values
// [   3  ]
// [ next ] -> [   2  ]
//             [ next ] -> [   1  ]
//                         [ next ] -> [  NULL  ]
//
// START : current -> 3; previous -> nullptr; target 2; list = 3, 2 ,1;
// NEXT  : previous -> current = 3; current -> current_next = 2;
// FOUND : previous_next = 2 -> current_next = 1;
//         delete current = 2;
//         current -> previous_next = 1;
// DONE;
//
// ===============================================================================
// list = 2, 3, 3, 2, 3, 1; target = 3;
//
// p[       ]
//  [  NULL ]
//
// c[   2  ]
//  [ next ] -> c[   3  ]
//               [ next ] -> c[   3  ]
//                            [ next ] -> c[  2   ]
//                                         [ next ] -> c[  3   ]
//                                                      [ next ] -> c[  1   ]
//                                                                   [ next ] -> [  NULL  ]
//
// NEXT ========================================================================== p = c; c = c_next
//
// p[   2  ]
//  [ next ] -> p[   3  ]
//               [ next ] -> p[   3  ]
//                            [ next ] -> p[  2   ]
//                                         [ next ] -> P[  3   ]
//                                                      [ next ] -> p[  1   ]
//                                                                   [ next ] -> [  NULL  ]
// c[   3  ]
//  [ next ] -> c[   3  ]
//               [ next ] -> c[   2  ]
//                            [ next ] -> c[  3   ]
//                                         [ next ] -> [  1   ]
//                                                     [ next ] -> [  NULL  ]
//
// FOUND ========================================================================== p_next = c_next; del c; c = p_next
//
// p[   2  ]
//  [ next ] -> p[   3  ]
//               [ next ] -> p[   2  ]
//                            [ next ] -> P[  3   ]
//                                         [ next ] -> p[  1   ]
//                                                      [ next ] -> [  NULL  ]
//
// c[   3  ]
//  [ next ] -> c[   2  ]
//               [ next ] -> c[  3   ]
//                            [ next ] -> [  1   ]
//                                        [ next ] -> [  NULL  ]
// FOUND ========================================================================== p_next = c_next; del c; c = p_next
//
// p[   2  ]
//  [ next ] -> p[   2  ]
//               [ next ] -> P[  3   ]
//                            [ next ] -> p[  1   ]
//                                         [ next ] -> [  NULL  ]
//
// c[   2  ]
//  [ next ] -> c[  3   ]
//               [ next ] -> [  1   ]
//                           [ next ] -> [  NULL  ]
// NEXT ========================================================================== p = c; c = c_next
//
// p[   2  ]
//  [ next ] -> p[   3  ]
//               [ next ] -> P[  1   ]
//                            [ next ] -> [  NULL  ]
//
// c[   3  ]
//  [ next ] -> c[  1   ]
//               [ next ] -> [  NULL  ]
// FOUND ========================================================================== p_next = c_next; del c; c = p_next
//
// p[   2  ]
//  [ next ] -> p[   1  ]
//               [ next ] -> [  NULL  ]
//
// c[   1  ]
//  [ next ] -> [  NULL  ]
//
// DONE ===========================================================================
template<typename T>
void delete_sll_elements_with_the_same_value(sll_node<T> *&list, T value)
{
	sll_node<T> *previous = nullptr;
	sll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (previous == nullptr) //----------- If the first node matches
			{
				list = current->next;
				delete current;
				current = list; //---------------- Update the current node because it was deleted
			}
			else //------------------------------- If a non-first node matches
			{
				previous->next = current->next; // We set the previous element pointer to point at the next element that the current pointer points at
				delete current;
				current = previous->next; //------ Update the current node because it was deleted
			}
		}
		else //----------------------------------- If the current node doesn't match
		{
			previous = current;
			current = current->next;
		}
	}
}

// Delete sll elements when we first encounter them
template<typename T>
void delete_sll_element_first_occurrence(sll_node<T> *&list, T value)
{
	sll_node<T> *previous = nullptr;
	sll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (previous == nullptr) //-------- If the first node matches
			{
				list = current->next;
			}
			else //---------------------------- If a non-first node matches
			{
				previous->next = current->next;
			}
			delete current;
			break; //-------------------------- Exit the loop after the first node is deleted
		}
		else //-------------------------------- If the current node doesn't match
		{
			previous = current;
			current = current->next;
		}
	}
}

// Find if a value is in the list
template<typename T>
bool find_value_in_sll(sll_node<T> *list, T value)
{
	sll_node<T> *temp = list; //--------------------------- Create a traversal pointer pointing to the list's head.
	while (temp != nullptr)
	{
		if (temp->value == value) //----------------------- If the current node's value field is what we're looking for, report success.
		{
			cout << "Found value: " << temp->value << endl;
			return true;
		}
		temp = temp->next; //------------------------------ If not, set the traversal pointer to the next pointer in the list.
	}
	cout << "Value is not in list: " << value << endl;
	return false; //--------------------------------------- If you've reached the end of the list, report failure.
}

// Sort the sll
template<typename T>
void bubble_sort_sll(sll_node<T> *&list)
{
	int swap_counter = -1;
	T help;
	while (swap_counter != 0)
	{
		swap_counter = 0;
		for (sll_node<T> *temp = list; temp != nullptr && temp->next != nullptr; temp = temp->next)
		{
			if (temp->value > temp->next->value)
			{
				help = temp->value;
				temp->value = temp->next->value;
				temp->next->value = help;
				swap_counter++;
			}
		}
	}
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
//		   b. If the current node's value field is what we're looking for, report success.
//         c. If not, set the traversal pointer to the next pointer in the list and go back to step b.
//         d. If you've reached the end of the list, report failure.
//      3. Insert a new node into the linked list.
//		   a. Dynamically allocate space for a new sll_node.
//		   b. Check to make sure we didn't run out of memory.
//		   c. Populate and insert the node at the beginning of the linked list. Why because it is O(1) steps to do insertion if we do it at the end it is O(n).
//		   d. Return a pointer to the new head of the linked list.
//      4. Delete a single element from a linked list.
//      5. Delete an entire linked list recursive.
//		   a. If you've reached a null pointer, stop.
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