#include <iostream>

using namespace std;
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
//
// NOTE: the -> operator. It is an arrow. This operator goes to an address and looks inside of a structure. Same as (*struct_variable).something = value;
// • First, it dereferences the pointer on the left side of the operator.
// • Second, it accesses the field on the right side of the operator.
//
// variable declaration
// struct car *mycar = malloc(sizeof(struct car));
// field accessing
// (*mycar).year = 2011;
// strcpy((*mycar).plate, “CS50”);
// (*mycar).odometer = 50505;
//
// variable declaration
// struct car *mycar = malloc(sizeof(struct car));
// field accessing
// mycar->year = 2011;
// strcpy(mycar->plate, “CS50”);
// mycar->odometer = 50505;

//* Singly-Linked Lists --------------------------------------------------------------------------------------------------------------------------
template <typename T>
struct sll_node
{
	T value;
	sll_node *next;
};

template <typename T>
void prepend_sll(sll_node<T> *&list, T value);

template <typename T>
void append_sll(sll_node<T> *&list, T value);

template <typename T>
void insert_sorted_sll(sll_node<T> *&list, T value);

template <typename T>
void print_sll(sll_node<T> *list);

template <typename T>
void delete_sll(sll_node<T> *&list);

template <typename T>
void delete_sll_recursive(sll_node<T> *&list);

template <typename T>
void delete_sll_elements_with_the_same_value(sll_node<T> *&list, T value);

template <typename T>
void delete_sll_element_first_occurrence(sll_node<T> *&list, T value);

template <typename T>
bool find_value_in_sll(sll_node<T> *list, T value);

template <typename T>
void find_all_same_values_in_sll(sll_node<T> *list, T value);

template <typename T>
void bubble_sort_sll(sll_node<T> *&list);
//* Singly-Linked Lists --------------------------------------------------------------------------------------------------------------------------

//* Doubly-Linked Lists --------------------------------------------------------------------------------------------------------------------------
template <typename T>
struct dll_node
{
	T value;
	dll_node *previous;
	dll_node *next;
};

template <typename T>
void prepend_dll(dll_node<T> *&list, T value);

template <typename T>
void append_dll(dll_node<T> *&list, T value);

template <typename T>
void insert_sorted_dll(dll_node<T> *&list, T value);

template <typename T>
void print_dll(dll_node<T> *list);

template <typename T>
void delete_dll(dll_node<T> *&list);

template <typename T>
void delete_dll_recursive(dll_node<T> *&list);

template <typename T>
void delete_dll_elements_with_the_same_value(dll_node<T> *&list, T value);

template <typename T>
void delete_dll_element_first_occurrence(dll_node<T> *&list, T value);

template <typename T>
bool find_value_in_dll(dll_node<T> *list, T value);

template <typename T>
void find_all_same_values_in_dll(dll_node<T> *list, T value);

template <typename T>
void bubble_sort_dll(dll_node<T> *&list);
//* Doubly-Linked Lists --------------------------------------------------------------------------------------------------------------------------

//* Binary search tree ---------------------------------------------------------------------------------------------------------------------------
template <typename T>
void insert_bst(dll_node<T> *&list, T value);

template <typename T>
void print_bst(dll_node<T> *list);

template <typename T>
void delete_bst(dll_node<T> *&list);
//* Binary search tree ---------------------------------------------------------------------------------------------------------------------------

int main()
{
	/*
	sll_node<int> *sl_list = nullptr; // Create a Singly-Linked Lists with size 0, to indicate that this is an empty list, so we can add upon to it.

	prepend_sll(sl_list, 1);
	prepend_sll(sl_list, 0);
	prepend_sll(sl_list, 10);
	prepend_sll(sl_list, 3);
	prepend_sll(sl_list, 4);
	prepend_sll(sl_list, 2);
	prepend_sll(sl_list, 10);
	prepend_sll(sl_list, 0);
	prepend_sll(sl_list, 1);
	prepend_sll(sl_list, 8);
	prepend_sll(sl_list, 9);
	prepend_sll(sl_list, 5);
	prepend_sll(sl_list, 7);
	prepend_sll(sl_list, 6);
	prepend_sll(sl_list, 10);
	prepend_sll(sl_list, 0);
	prepend_sll(sl_list, 1);

	print_sll(sl_list);

	find_all_same_values_in_sll(sl_list, 1);
	delete_sll_elements_with_the_same_value(sl_list, 1);

	find_value_in_sll(sl_list, 0);
	delete_sll_element_first_occurrence(sl_list, 0);
	find_value_in_sll(sl_list, 0);
	delete_sll_element_first_occurrence(sl_list, 0);
	find_value_in_sll(sl_list, 0);
	delete_sll_element_first_occurrence(sl_list, 0);

	bubble_sort_sll(sl_list);

	print_sll(sl_list);

	delete_sll(sl_list);

	print_sll(sl_list);
	*/
	/*
	dll_node<int> *dl_list = nullptr; // Create a Singly-Linked Lists with size 0, to indicate that this is an empty list, so we can add upon to it.
	prepend_dll(dl_list, 1);
	prepend_dll(dl_list, 0);
	prepend_dll(dl_list, 10);
	prepend_dll(dl_list, 3);
	prepend_dll(dl_list, 4);
	prepend_dll(dl_list, 2);
	prepend_dll(dl_list, 10);
	prepend_dll(dl_list, 0);
	prepend_dll(dl_list, 1);
	prepend_dll(dl_list, 8);
	prepend_dll(dl_list, 9);
	prepend_dll(dl_list, 5);
	prepend_dll(dl_list, 7);
	prepend_dll(dl_list, 6);
	prepend_dll(dl_list, 10);
	prepend_dll(dl_list, 0);
	prepend_dll(dl_list, 1);

	print_dll(dl_list);

	find_all_same_values_in_dll(dl_list, 1);
	delete_dll_elements_with_the_same_value(dl_list, 1);

	find_value_in_dll(dl_list, 0);
	delete_dll_element_first_occurrence(dl_list, 0);
	find_value_in_dll(dl_list, 0);
	delete_dll_element_first_occurrence(dl_list, 0);
	find_value_in_dll(dl_list, 0);
	delete_dll_element_first_occurrence(dl_list, 0);

	bubble_sort_dll(dl_list);

	print_dll(dl_list);

	delete_dll(dl_list);

	print_dll(dl_list);
	*/

	return 0;
}

//* Singly-Linked Lists --------------------------------------------------------------------------------------------------------------------------
																																 // With pointer to a pointer                        // With return
																																 //                                                  //
// Prepend, add in front of the singly linked list O(1)																			 // In main {insert(&list, 1);}                      // In main {list = insert(list, 1);}
template <typename T>                                                                                                             // template <typename T>                             // template <typename T>
void prepend_sll(sll_node<T> *&list, T value)                                                                                    // void insert(sll_node<T>** list_ptr, T value)     // sll_node<T>* insert(sll_node<T>* list, T value)
{                                                                                                                                // {                                                // {
	sll_node<T> *node = new sll_node<T>; // Dynamically allocate space for a new sll_node                                        //		sll_node<T>* node = new sll_node<T>;         //		sll_node<T>* node = new sll_node<T>;
	node->value = value; //---------------- Initialize the node's value field                                                    //		node->value = value;                         //		node->value = value;
	node->next = list; //------------------ Initialize the node's next field, to point at the current head node                  //		node->next = *list_ptr;                      //		node->next = list;
	list = node; //------------------------ Set list to point at the last inserted node aka making it the new head               //		*list_ptr = node;                            //		return node;
}                                                                                                                                // }                                                // }

// Append, add at the end of the singly linked list O(n)
template <typename T>
void append_sll(sll_node<T> *&list, T value)
{
	sll_node<T> *node = new sll_node<T>; //---------------------------------- Dynamically allocate space for a new sll_node
	node->value = value; //-------------------------------------------------- Initialize the node's value field
	node->next = nullptr; //------------------------------------------------- Initialize the node's next field to point at nullptr because this will be the last node of the linked list

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else //------------------------------------------------------------------ If the list has some nodes already
	{
		for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ At the end of the list add the new node, 3 -> 2, 2 -> 1, 1 -> nullptr; add it here so we would have, 3 -> 2 -> 1 -> new -> nullptr
			{
				temp->next = node; //---------------------------------------- Set the last node of the sll to point at the new node
				break; //---------------------------------------------------- To prevent keep adding the same node over and over again
			}
		}
	}
}

// Insert and sort at the same time in a singly linked list
template <typename T>
void insert_sorted_sll(sll_node<T> *&list, T value)
{
	sll_node<T> *node = new sll_node<T>; //---------------------------------- Dynamically allocate space for a new sll_node
	node->value = value; //-------------------------------------------------- Initialize the node's value field
	node->next = nullptr; //------------------------------------------------- Initialize the node's next field to point at nullptr because 1. list might be empty, 2. this new node might go at the end

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else if (node->value < list->value) //----------------------------------- If the new node belongs at beginning of list
	{
		node->next = list; //------------------------------------------------ Set the new node to point at the current head node
		list = node; //------------------------------------------------------ Set list to point at the last inserted node aka making it the new head
	}
	else //------------------------------------------------------------------ If the new node belongs later in list
	{
		for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ If at end of list
			{
				temp->next = node; //---------------------------------------- Set the last node of the sll to point at the new node
				break;
			}
			if (node->value < temp->next->value) //-------------------------- If in middle of list, if the new node value is smaller than the next node value
			{
				node->next = temp->next; //---------------------------------- Set the new node to point at the current node pointer aka the node after the current node
				temp->next = node; //---------------------------------------- Set the current node to point at the new node and this new node also points to the rest of the values in the singly linked list
				break;
			}
		}
	}
}

// Print the singly linked list
template <typename T>
void print_sll(sll_node<T> *list)
{
	sll_node<T> *temp = list; // We create a temp node so we don't change the list values when we traverse the list aka get the pointer to point at the next value
	while (temp != nullptr)
	{
		cout << "Value: " << temp->value << " Debug current address of the element:               " << temp << endl;
		cout << "         Debug the address that this element is pointing at: " << temp->next << endl;
		cout << "---------" << endl;
		temp = temp->next;
	}

	// Another way to print
	//
	// for (sll_node<T> *temp = list; temp != nullptr; temp = temp->next)
	// {
	// 	cout << "Value: " << temp->value << " Debug address: " << temp->next << endl;
	// }
}

// Delete the singly linked list
template <typename T>
void delete_sll(sll_node<T> *&list)
{
	while (list != nullptr)
	{
		sll_node<T> *next = list->next; // Grab the next pointer before deleting this one!
		delete list;
		list = next;
	}
}

// Delete the singly linked list with recursion
template <typename T>
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
template <typename T>
void delete_sll_elements_with_the_same_value(sll_node<T> *&list, T value)
{
	bool found = false;
	sll_node<T> *previous = nullptr;
	sll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (previous == nullptr) //---------------------------------------------------------------------- If the first node matches
			{
				if (current->next == nullptr) //------------------------------------------------------------- If the list has only one element
				{
					list = nullptr; //----------------------------------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
					cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
					delete current;
					found = true;
					break;
				}
				else //-------------------------------------------------------------------------------------- If the list has more than one element
				{
					list = current->next; //----------------------------------------------------------------- Set the head of the list to point at the next node in the list
					cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
					delete current;
					current = list; //----------------------------------------------------------------------- Update the current node because it was deleted
				}
			}
			else //------------------------------------------------------------------------------------------ If a non-first node matches
			{
				previous->next = current->next; //----------------------------------------------------------- We set the previous node pointer to point at the node that the current pointer points at
				cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
				delete current;
				current = previous->next; //----------------------------------------------------------------- Update the current node because it was deleted
			}
			found = true;
		}
		else //---------------------------------------------------------------------------------------------- If the current node doesn't match go to the next nodes
		{
			previous = current;
			current = current->next;
		}
	}
	if (!found)
	{
		cerr << "Node with value: " << value << " not found! " << endl;
	}
}

// Delete sll elements when we first encounter them
template <typename T>
void delete_sll_element_first_occurrence(sll_node<T> *&list, T value)
{
	bool found = false;
	sll_node<T> *previous = nullptr;
	sll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (previous == nullptr) //---------------------------------------------------------------------- If the first node matches
			{
				if (current->next == nullptr) //------------------------------------------------------------- If the list has only one element
				{
					list = nullptr; //----------------------------------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
				}
				else //-------------------------------------------------------------------------------------- If the list has more than one element
				{
					list = current->next; //----------------------------------------------------------------- Set the head of the list to point at the next node in the list
				}
			}
			else //------------------------------------------------------------------------------------------ If a non-first node matches
			{
				previous->next = current->next; //----------------------------------------------------------- Set the previous node pointer to point at the node that the current pointer points at
			}
			cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
			delete current;
			found = true;
			break; //---------------------------------------------------------------------------------------- Exit the loop after the first node is deleted
		}
		else //---------------------------------------------------------------------------------------------- If the current node doesn't match go to the next nodes
		{
			previous = current;
			current = current->next;
		}
	}
	if (!found)
	{
		cerr << "Node with value: " << value << " not found! " << endl;
	}
}

// Find if a value is in the singly linked list
template <typename T>
bool find_value_in_sll(sll_node<T> *list, T value)
{
	sll_node<T> *temp = list; //------------------------------------------------------ Create a traversal pointer pointing to the list's head
	while (temp != nullptr)
	{
		if (temp->value == value) //-------------------------------------------------- If the current node's value field is what we're looking for, report success
		{
			cout << "Found value: " << temp->value << " At address: " << temp << endl;
			return true;
		}
		temp = temp->next; //--------------------------------------------------------- If not, set the traversal pointer to the next pointer in the list
	}
	cout << "Value: " << value << " is not in the list! " << endl;
	return false; //------------------------------------------------------------------ If you've reached the end of the list, report failure
}

// Find all of the same values in the singly linked list
template <typename T>
void find_all_same_values_in_sll(sll_node<T> *list, T value)
{
	bool found = false;
	sll_node<T> *temp = list; //------------------------------------------------------ Create a traversal pointer pointing to the list's head
	while (temp != nullptr)
	{
		if (temp->value == value) //-------------------------------------------------- If the current node's value field is what we're looking for, report success
		{
			cout << "Found value: " << temp->value << " At address: " << temp << endl;
			found = true;
		}
		temp = temp->next; //--------------------------------------------------------- If not, set the traversal pointer to the next pointer in the list
	}
	if (!found)
	{
		cout << "Value: " << value << " is not in the list! " << endl; //-------------- If you've reached the end of the list, report failure
	}
}

// Sort the sll
template <typename T>
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
//* Singly-Linked Lists --------------------------------------------------------------------------------------------------------------------------

//* Doubly-Linked Lists --------------------------------------------------------------------------------------------------------------------------
// Prepend, add in front of the doubly linked list O(1)
template <typename T>
void prepend_dll(dll_node<T> *&list, T value)
{
	dll_node<T> *node = new dll_node<T>; // Dynamically allocate space for a new dll_node
	node->value = value; //---------------- Initialize the node's value field
	node->previous = nullptr; //----------- Initialize the node's previous field, to point at nullptr because if its the first node there is nothing behind it
	node->next = nullptr; //--------------- Initialize the node's next field, to point at nullptr because the list might be empty

	if (list == nullptr) //---------------- Check if the list is empty aka if its just one node then both previous and next will point at null
	{
		list = node; //-------------------- This node is the whole list
	}
	else //-------------------------------- If the list has some nodes already
	{
		list->previous = node; //---------- Set the head of the list to point back to the new node
		node->next = list; //-------------- Set the new node to point at the current head node
		list = node; //-------------------- Set list to point at the last inserted node aka making it the new head
	}
}

// Append, add at the end of the doubly linked list O(n)
template <typename T>
void append_dll(dll_node<T> *&list, T value)
{
	dll_node<T> *node = new dll_node<T>; //---------------------------------- Dynamically allocate space for a new dll_node
	node->value = value; //-------------------------------------------------- Initialize the node's value field
	node->previous = nullptr; //--------------------------------------------- Initialize the node's previous field, to point at nullptr because if its the first node there is nothing behind it
	node->next = nullptr; //------------------------------------------------- Initialize the node's next field to point at nullptr because this will be the last element of the linked list

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else //------------------------------------------------------------------ If the list has some nodes already
	{
		for (dll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ At the end of the list add the new node, 3 -> 2, 2 -> 1, 1 -> nullptr; add it here so we would have, 3 -> 2 -> 1 -> new -> nullptr
			{
				node->previous = temp; //------------------------------------ Set the new node to point back at the node that will be behind it
				temp->next = node; //---------------------------------------- Set the last node of the dll to point at the new node
				break; //---------------------------------------------------- To prevent keep adding the same node over and over again
			}
		}
	}
}

// Insert and sort at the same time in a doubly linked list
template <typename T>
void insert_sorted_dll(dll_node<T> *&list, T value)
{
	dll_node<T> *node = new dll_node<T>; //---------------------------------- Dynamically allocate space for a new dll_node
	node->value = value; //-------------------------------------------------- Initialize the node's value field
	node->previous = nullptr; //--------------------------------------------- Initialize the node's previous field to point at nullptr because 1. list might be empty
	node->next = nullptr; //------------------------------------------------- Initialize the node's next field to point at nullptr because 1. list might be empty, 2. this new node might go at the end

	if (list == nullptr) //-------------------------------------------------- If the list is empty
	{
		list = node; //------------------------------------------------------ This node is the whole list
	}
	else if (node->value < list->value) //----------------------------------- If the new node belongs at beginning of list
	{
		list->previous = node; //-------------------------------------------- Set the head of the list to point back to the new node
		node->next = list; //------------------------------------------------ Set the new node to point at the current head node
		list = node; //------------------------------------------------------ Set list to point at the last inserted node aka making it the new head
	}
	else //------------------------------------------------------------------ If the new node belongs later in list
	{
		for (dll_node<T> *temp = list; temp != nullptr; temp = temp->next) // Iterate over nodes in the list till the end
		{
			if (temp->next == nullptr) //------------------------------------ If at end of list
			{
				node->previous = temp; //------------------------------------ Set the new node to point back at the node that will be behind it
				temp->next = node; //---------------------------------------- Set the last node of the dll to point at the new node
				break;
			}
			if (node->value < temp->next->value) //-------------------------- If in middle of list, if the new node value is smaller than the next node value
			{
				node->previous = temp; //------------------------------------ Set the new node to point back at the node that will be behind it'
				node->next = temp->next; //---------------------------------- Set the new node to point at the current node pointer aka the node after the current node
				temp->next->previous = node; //------------------------------ Set the node after the current node to point back at the new node
				temp->next = node; //---------------------------------------- Set the current node to point at the new node and this new node also points to the rest of the values in the doubly linked list
				break;
			}
		}
	}
}

// Print the doubly linked list
template <typename T>
void print_dll(dll_node<T> *list)
{
	dll_node<T> *temp = list; // We create a temp variable so we don't change the list values when we traverse the list aka get the pointer to point at the next value
	while (temp != nullptr)
	{
		cout << "Value: " << temp->value << " Prev: " << temp->previous << " Curr: " << temp << " Next: " << temp->next << endl;
		cout << "---------" << endl;
		temp = temp->next;
	}

	// Another way to print
	//
	// for (dll_node<T> *temp = list; temp != nullptr; temp = temp->next)
	// {
	// 	cout << "Value: " << temp->value << " Debug address: " << temp->next << endl;
	// }
}

// Delete the doubly linked list
template <typename T>
void delete_dll(dll_node<T> *&list)
{
	while (list != nullptr)
	{
		dll_node<T> *next = list->next; // Grab the next pointer before deleting this one!
		delete list;
		list = next;
	}
}

// Delete the doubly linked list with recursion
template <typename T>
void delete_dll_recursive(dll_node<T> *&list)
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
template <typename T>
void delete_dll_elements_with_the_same_value(dll_node<T> *&list, T value)
{
	bool found = false;
	dll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (current->previous == nullptr) //------------------------------------------------------------- If the first node matches
			{
				if (current->next == nullptr) //------------------------------------------------------------- If the list has only one element
				{
					list = nullptr; //----------------------------------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
					cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
					delete current;
					found = true;
					break;
				}
				else //-------------------------------------------------------------------------------------- If the list has more than one element
				{
					list = current->next; //----------------------------------------------------------------- Set the head of the list to point at the next node in the list
					list->previous = nullptr; //------------------------------------------------------------- Set the head of the list to point back at nothing because we deleted that node
					cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
					delete current;
					current = list; //----------------------------------------------------------------------- Update the current node because it was deleted
				}
			}
			else if (current->next == nullptr) //------------------------------------------------------------ If the last node matches
			{
				current->previous->next = nullptr; //-------------------------------------------------------- Set the node behind the last one to point at nothing because we deleted the last one
				cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
				delete current;
				found = true;
				break;
			}
			else //------------------------------------------------------------------------------------------ If a non-first node matches
			{
				dll_node<T> *temp = current->next;
				current->previous->next = current->next; //-------------------------------------------------- Set the previous node pointer to point at the node that the current pointer points at
				current->next->previous = current->previous; //---------------------------------------------- Set the next node to point back at the node before the deleted node
				cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
				delete current;
				current = temp;
			}
			found = true;
		}
		else //---------------------------------------------------------------------------------------------- If the current node doesn't match go to the next nodes
		{
			current = current->next;
		}
	}
	if (!found)
	{
		cerr << "Node with value: " << value << " not found! " << endl;
	}
}

// Delete dll elements when we first encounter them
template <typename T>
void delete_dll_element_first_occurrence(dll_node<T> *&list, T value)
{
	bool found = false;
	dll_node<T> *current = list;
	while (current != nullptr)
	{
		if (current->value == value)
		{
			if (current->previous == nullptr) //------------------------------------------------------------- If the first node matches
			{
				if (current->next == nullptr) //------------------------------------------------------------- If the list has only one element
				{
					list = nullptr; //----------------------------------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
				}
				else //-------------------------------------------------------------------------------------- If the list has more than one element
				{
					list = current->next; //----------------------------------------------------------------- Set the head of the list to point at the next node in the list
					list->previous = nullptr; //------------------------------------------------------------- Set the head of the list to point back at nothing because we deleted that node
				}
			}
			else if (current->next == nullptr) //------------------------------------------------------------ If the last node matches
			{
				current->previous->next = nullptr; //-------------------------------------------------------- Set the node behind the last one to point at nothing because we deleted the last one
			}
			else //------------------------------------------------------------------------------------------ If a non-first node matches
			{
				current->previous->next = current->next; //-------------------------------------------------- Set the previous node pointer to point at the node that the current pointer points at
				current->next->previous = current->previous; //---------------------------------------------- Set the next node to point back at the node before the deleted node
			}
			cout << "Node: " << current << " With value: " << current->value << " Deleted! " << endl;
			delete current;
			found = true;
			break; //---------------------------------------------------------------------------------------- Exit the loop after the first node is deleted
		}
		else //---------------------------------------------------------------------------------------------- If the current node doesn't match go to the next nodes
		{
			current = current->next;
		}
	}
	if (!found)
	{
		cerr << "Node with value: " << value << " not found! " << endl;
	}
}

// Find if a value is in the doubly linked list
template <typename T>
bool find_value_in_dll(dll_node<T> *list, T value)
{
	dll_node<T> *temp = list; //------------------------------------------------------ Create a traversal pointer pointing to the list's head.
	while (temp != nullptr)
	{
		if (temp->value == value) //-------------------------------------------------- If the current node's value field is what we're looking for, report success.
		{
			cout << "Found value: " << temp->value << " At address: " << temp << endl;
			return true;
		}
		temp = temp->next; //--------------------------------------------------------- If not, set the traversal pointer to the next pointer in the list.
	}
	cout << "Value: " << value << " is not in the list! " << endl;
	return false; //------------------------------------------------------------------ If you've reached the end of the list, report failure.
}

// Find all of the same values in the doubly linked list
template <typename T>
void find_all_same_values_in_dll(dll_node<T> *list, T value)
{
	bool found = false;
	dll_node<T> *temp = list; //------------------------------------------------------ Create a traversal pointer pointing to the list's head.
	while (temp != nullptr)
	{
		if (temp->value == value) //-------------------------------------------------- If the current node's value field is what we're looking for, report success.
		{
			cout << "Found value: " << temp->value << " At address: " << temp << endl;
			found = true;
		}
		temp = temp->next; //--------------------------------------------------------- If not, set the traversal pointer to the next pointer in the list.
	}
	if (!found)
	{
		cout << "Value: " << value << " is not in the list! " << endl; //-------------- If you've reached the end of the list, report failure.
	}
}

// Sort the dll
template <typename T>
void bubble_sort_dll(dll_node<T> *&list)
{
	int swap_counter = -1;
	T help;
	while (swap_counter != 0)
	{
		swap_counter = 0;
		for (dll_node<T> *temp = list; temp != nullptr && temp->next != nullptr; temp = temp->next)
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
//* Doubly-Linked Lists --------------------------------------------------------------------------------------------------------------------------

//* Binary search tree ---------------------------------------------------------------------------------------------------------------------------
// Insert like a binary search tree for a dll
template <typename T>
void insert_bst(dll_node<T> *&list, T value)
{
	dll_node<T> *temp = list;
	dll_node<T> *previous = list;
	dll_node<T> *node = new dll_node<T>;
	node->value = value;
	node->previous = nullptr;
	node->next = nullptr;

	if (list == nullptr)
	{
		list = node;
		return;
	}
	while (temp != nullptr)
	{
		if (temp->value > value)
		{
			previous = temp;
			temp = temp->previous;
		}
		else if (temp->value < value)
		{
			previous = temp;
			temp = temp->next;
		}
	}
	if (previous->value > value)
	{
		previous->previous = node;
	}
	else
	{
		previous->next = node;
	}
}

// Print the binary search tree
template <typename T>
void print_bst(dll_node<T> *list)
{
	if (list == nullptr)
	{
		return;
	}
	print_binary_tree_dll(list->previous);
	cout << "Value: " << list->value << " Left: " << list->previous << " Curr: " << list << " Right: " << list->next << endl;
	cout << "---------" << endl;
	print_binary_tree_dll(list->next);
}

// Delete binary search tree
template <typename T>
void delete_bst(dll_node<T> *&list)
{
	if (list == nullptr)
	{
		return;
	}
	delete_bst(list->previous);
	delete_bst(list->next);
	delete list;
}
//* Binary search tree ---------------------------------------------------------------------------------------------------------------------------