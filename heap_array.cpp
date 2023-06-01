#include <iostream>
#include <math.h>
#include "basic_functions.h"

using namespace std;
// A Heap is a special Tree - based data structure in which the tree is a complete binary tree.
// It follows the Heap Property -
// Max - Heap: In a Max - Heap the key present at the root node must be greatest among the keys present at all of it's children. The same property must be recursively true for all sub - trees in that Binary Tree.
// Min - Heap : In a Min - Heap the key present at the root node must be minimum among the keys present at all of it's children. The same property must be recursively true for all sub - trees in that Binary Tree.
//
// A heap can be implemented in 2 ways -
// Tree Node Implementation with pointers
// Heap as Array Implementation
//
// Array formulas:
//	Root element at heap[0]
//	heap[i]:
//		heap[ ( i - 1 ) / 2 ] Returns the PARENT node
//		heap[ ( 2 * i ) + 1 ] Returns the LEFT child node
//		heap[ ( 2 * i ) + 2 ] Returns the RIGHT child node
//
// Heap sort is a comparison based sorting technique based on Binary Heap data structure.
// It is similar to selection sort where we first find the minimum element and place the minimum element at the beginning.
// We repeat the same process for the remaining elements.

// Classes
// NOTE: This is min heap implementation if you wanna change for max heap change the following functions:
// - In insert() function -> change set_root_biggest(i);
// - In make_min_or_max() function -> change set_root_biggest(i);
// - In delete_data() function -> change make_min_or_max(data, INT_MAX); extract_max();
// - Swap the extract_min() and extract_max() functions
// - When you have swapped the functions in the new extract_max() function -> change max_heapify(0);
// - The function show_max() will give us now the smallest element
// - And the get_root() function will give us the biggest element
// - In heapify() function -> change max_heapify(i);
// - In heap_sort() function -> change extract_max();
// - Swap out the is_min_heap_sorted() function with is_max_heap_sorted() function
// - Swap out is_valid_min_heap() function with is_valid_max_heap() function
template < typename T>
class Heap
{
	private:
	// Member variables
	int count;
	int size;
	T *arr;

	public:
	// Member functions

	// Constructor
	Heap()
	{
		count = 0;
		size = get_heap_size();
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = T();
		}
	}

	// Destructor
	~Heap()
	{
		delete[] arr;
	}

	// Get count
	int get_count() const
	{
		return count;
	}

	// Get size
	int get_size() const
	{
		return size;
	}

	// Get the size of the heap we want to create
	int get_heap_size()
	{
		do
		{
			size = get_valid_input<int>("Enter heap size: ");
		} while (size < 1);
		return size;
	}

	// Show root
	T get_root() const
	{
		return arr[0];
	}

	// Is the heap full
	bool is_full() const
	{
		if (count == size)
		{
			return true;
		}
		return false;
	}

	// Is the heap empty
	bool is_empty() const
	{
		if (count == 0)
		{
			return true;
		}
		return false;
	}

	// Swap values
	void swap(T &node1, T &node2)
	{
		T temp = node1;
		node1 = node2;
		node2 = temp;
	}

	// Linear search algorithm compare the number with each value in the array until found
	T linear_search(T data) const
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == data)
			{
				cout << "[" << i << "]: ";
				return arr[i];
			}
		}
		cout << "\nData not found!" << endl;
		return T();
	}

	// Binary search algorithm (Divide and Conquer)
	T binary_search(T data) const
	{
		int start = 0;
		int end = count;

		while (start <= end)
		{
			int mid = start + (end - start) / 2;

			if (arr[mid] == data)
			{
				cout << "[" << mid << "]: ";
				return arr[mid];
			}
			else if (arr[mid] < data)
			{
				start = mid + 1;
			}
			else if (arr[mid] > data)
			{
				end = mid - 1;
			}
		}
		cout << "\nData not found!" << endl;
		return T();
	}

	// Get the index of a element in the heap data structure and limit it by the count size so the user doesn't select something out of bounds
	int get_index(string prompt) const
	{
		int index = 0;
		do
		{
			index = get_valid_input<int>(prompt);
		} while (index < 0 || index > count - 1);
		return index;
	}

	// Get the index of a parent of a node
	int parent(int i) const
	{
		return (i - 1) / 2;
	}

	// Show parent
	void show_parent() const
	{
		int index = get_index("Enter index of node you wish to see parent of: ");

		cout << "\nParent of [" << index << "]: " << arr[index] << " is : [" << parent(index) << "]: " << arr[parent(index)] << endl;
	}

	// Get the index of a left child
	int left_child(int i) const
	{
		return  (2 * i) + 1;
	}

	// Get the index of a right child
	int right_child(int i) const
	{
		return (2 * i) + 2;
	}

	// Show children
	void show_children() const
	{
		int index = get_index("Enter index of node you wish to see children of: ");

		int left_index = left_child(index);
		int right_index = right_child(index);

		if (left_index > size - 1)
		{
			cout << "\nLeft child does not exist!" << endl;
		}
		else
		{
			cout << "\nLeft child of [" << index << "]: " << arr[index] << " is : [" << left_index << "]: " << arr[left_index] << endl;
		}

		if (right_index > size - 1)
		{
			cout << "\nRight child does not exist!" << endl;
		}
		else
		{
			cout << "\nRight child of [" << index << "]: " << arr[index] << " is : [" << right_index << "]: " << arr[right_index] << endl;
		}
	}

	// Make the parent smallest
	void set_root_smallest(int i)
	{
		while (i != 0 && arr[parent(i)] > arr[i]) // Make sure the parent is smaller than the child in min heap
		{
			swap(arr[i], arr[parent(i)]);
			i = parent(i); //----------------------- Check now for the swapped value if its again smaller than its ancestors
		}
	}

	// Make the parent biggest
	void set_root_biggest(int i)
	{
		while (i != 0 && arr[parent(i)] < arr[i]) // Make sure the parent is bigger than the child in max heap
		{
			swap(arr[i], arr[parent(i)]);
			i = parent(i); //----------------------- Check now for the swapped value if its again smaller than its ancestors
		}
	}

	// Insert min heap
	void insert(T data)
	{
		if (is_full())
		{
			cout << "\nOverflow, heap is full!" << endl;
			return;
		}

		int i = count; //------------------------------------ Get the index of the next value in line to add
		arr[i] = data;
		count++;

		cout << "\nData: " << arr[i] << " inserted!" << endl;

		set_root_smallest(i); //----------------------------- Make the parent smallest
	}

	// Make the node we want to delete the smallest and then swap it in the position of the root
	void make_min_or_max(int i, int new_value)
	{
		arr[i] = new_value;
		set_root_smallest(i);
		// set_root_biggest(i); use this for max
	}

	// Delete node by making the node we want to delete the smallest in the data structure and swap it to the root position then simply just extract it
	void delete_data(T data)
	{
		make_min_or_max(data, INT_MIN);
		extract_min();

		cout << "\nNode deleted!" << endl;
	}

	// Min heapify
	void min_heapify(int i)
	{
		int left_index = left_child(i);
		int right_index = right_child(i);
		int smallest = i;

		if (left_index < count && arr[left_index] < arr[smallest]) //-- Check if the left child is smaller than the new root, if it is make the smallest index be that left child
		{
			smallest = left_index;
		}

		if (right_index < count && arr[right_index] < arr[smallest]) // Check if the right child is smaller than the new root or its sibling (if the left child previously was smaller), if it is make the smallest index be that right child
		{
			smallest = right_index;
		}

		if (smallest != i) //------------------------------------------ Check if the smallest value is at the root position if its not we have found a smaller value
		{
			swap(arr[i], arr[smallest]);
			min_heapify(smallest); //---------------------------------- Recursively call the same function but for the swapped element, keep in mind after the swap we have now on the position of the smallest the value that was previously on the root
		}
	}

	// Max heapify
	void max_heapify(int i)
	{
		int left_index = left_child(i);
		int right_index = right_child(i);
		int biggest = i;

		if (left_index < count && arr[left_index] > arr[biggest]) //-- Check if the left child is bigger than the new root, if it is make the biggest index be that left child
		{
			biggest = left_index;
		}

		if (right_index < count && arr[right_index] > arr[biggest]) // Check if the right child is bigger than the new root or its sibling (if the left child previously was bigger), if it is make the biggest index be that right child
		{
			biggest = right_index;
		}

		if (biggest != i) //------------------------------------------ Check if the biggest value is at the root position if its not we have found a bigger value
		{
			swap(arr[i], arr[biggest]);
			max_heapify(biggest); //---------------------------------- Recursively call the same function but for the swapped element, keep in mind after the swap we have now on the position of the biggest the value that was previously on the root
		}
	}

	// Extract min heap
	T extract_min()
	{
		if (is_empty())
		{
			return 0;
		}

		if (count == 1) //------ If we have only one element
		{
			count--;
			return arr[0];
		}

		//---------------------- If we have more than one element
		T root = arr[0];
		arr[0] = arr[count - 1];
		arr[count - 1] = 0;
		count--;

		min_heapify(0); //------ Recreate the new heap data structure starting from the root

		return root;
	}

	// Show the max
	T show_max()
	{
		if (!is_min_heap_sorted())
		{
			heap_sort();
		}

		return arr[count - 1];
	}

	// Extract max heap
	T extract_max()
	{
		if (is_empty())
		{
			return 0;
		}

		if (!is_min_heap_sorted())
		{
			heap_sort();
		}

		if (count == 1) //------- If we have only one element
		{
			count--;
			return arr[0];
		}

		//----------------------- If we have more than one element
		T max = arr[count - 1];
		arr[count - 1] = 0;
		count--;

		return max;
	}

	// Heapify the array before sorting
	void heapify()
	{
		for (int i = size / 2 - 1; i >= 0; i--) // Heapify all nodes from bottom to top and exclude the leaf level
		{
			min_heapify(i);
		}
	}

	// Heap sort
	void heap_sort()
	{
		int temp_count = count;

		int *temp = new int[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = extract_min();
		}

		for (int i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}

		count = temp_count;

		delete[] temp;
	}

	// Check if a min heap is sorted
	bool is_min_heap_sorted() const
	{
		for (int i = 0; i < count - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				return false;
			}
		}
		return true;
	}

	// Check if a max heap is sorted
	bool is_max_heap_sorted() const
	{
		for (int i = 0; i < count - 1; i++)
		{
			if (arr[i] < arr[i + 1])
			{
				return false;
			}
		}
		return true;
	}

	// Check if its a valid min heap
	bool is_valid_min_heap() const
	{
		for (int i = 0; i < count; i++)
		{
			int left_index = left_child(i);
			int right_index = right_child(i);

			if (left_index < count && arr[left_index] < arr[i]) //-- Check if left child exists and is smaller than the parent
			{
				return false;
			}

			if (right_index < count && arr[right_index] < arr[i]) // Check if right child exists and is smaller than the parent
			{
				return false;
			}
		}
		return true;
	}

	// Check if its a valid max heap
	bool is_valid_max_heap() const
	{
		for (int i = 0; i < count; i++)
		{
			int left_index = left_child(i);
			int right_index = right_child(i);

			if (left_index < count && arr[left_index] > arr[i]) //-- Check if left child exists and is bigger than the parent
			{
				return false;
			}

			if (right_index < count && arr[right_index] > arr[i]) // Check if right child exists and is bigger than the parent
			{
				return false;
			}
		}
		return true;
	}

	// Change a value in a current position
	void change(int position, T data)
	{
		if (position >= count || position < 0)
		{
			cerr << "\nHeap out of bounds!" << endl;
		}
		else
		{
			arr[position] = data;
			cout << "\nData changed at location: " << position << endl;
		}
	}

	// Get height of the heap "tree"
	int height() const
	{
		return ceil(log2(count + 1)) - 1;
	}

	// Get height of a node
	int height_of_node() const
	{
		int node_depth = floor(log2(get_index("Enter index of node you wish to see height of: ") + 1));
		int height_of_heap = height();
		return height_of_heap - node_depth;
	}

	// Get depth of a node
	int depth_of_node() const
	{
		return floor(log2(get_index("Enter index of node you wish to see depth of: ") + 1));
	}

	// Print heap
	void display() const
	{
		for (int i = 0; i < count; i++)
		{
			cout << "[" << i << "]: " << arr[i] << " ";
		}
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Heap<int> h1;
	int choice = 0;
	int data = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				h1.insert(get_valid_input<int>("Enter data to insert: "));
				break;
			case 2:
				data = h1.linear_search(get_valid_input<int>("Enter data to search for: "));
				cout << "Data found: " << data << endl;
				break;
			case 3:
				if (!h1.is_min_heap_sorted())
				{
					h1.heap_sort();
				}
				data = h1.binary_search(get_valid_input<int>("Enter data to search for: "));
				cout << "Data found: " << data << endl;
				break;
			case 4:
				h1.heap_sort();
				cout << "Heap sorted!" << endl;
				break;
			case 5:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					h1.delete_data(h1.get_index("Enter index of data to delete: "));
				}
				break;
			case 6:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Min node is the root node: " << h1.get_root() << endl;
				}
				break;
			case 7:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Extracted min node: " << h1.extract_min() << endl;
				}
				break;
			case 8:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Max node is the last node: " << h1.show_max() << endl;
				}
				break;
			case 9:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Extracted max node: " << h1.extract_max() << endl;
				}
				break;
			case 10:
				h1.change(get_valid_input<int>("Enter position of node to edit: "), get_valid_input<int>("Enter new data of node: "));
				break;
			case 11:
				cout << "Height of heap is: " << h1.height() << endl;
				break;
			case 12:
				cout << "Size of heap is: " << h1.get_size() << endl;
				break;
			case 13:
				if (h1.is_full())
				{
					cout << "Heap is full!" << endl;
				}
				else
				{
					cout << "Heap is not full!" << endl;
				}
				break;
			case 14:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Heap is not empty!" << endl;
				}
				break;
			case 15:
				if (h1.is_min_heap_sorted())
				{
					cout << "Heap is sorted!" << endl;
				}
				else
				{
					cout << "Heap is not sorted!" << endl;
				}
				break;
			case 16:
				if (h1.is_valid_min_heap())
				{
					cout << "Min heap is valid!" << endl;
				}
				else
				{
					cout << "Min heap is not valid!" << endl;
				}
				break;
			case 17:
				cout << "Total elements in heap: " << h1.get_count() << endl;
				break;
			case 18:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << "Root of heap is: " << h1.get_root() << endl;
				}
				break;
			case 19:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					h1.show_parent();
				}
				break;
			case 20:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					h1.show_children();
				}
				break;
			case 21:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << h1.height_of_node() << " is height!" << endl;
				}
				break;
			case 22:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					cout << h1.depth_of_node() << " is depth!" << endl;
				}
				break;
			case 23:
				if (h1.is_empty())
				{
					cout << "Heap is empty!" << endl;
				}
				else
				{
					h1.display();
				}
				break;
			case 24:
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
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. Insert node" << endl;
	cout << "2. Linear search" << endl;
	cout << "3. Binary search" << endl;
	cout << "4. Sort heap" << endl;
	cout << "5. Delete node" << endl;
	cout << "6. Get min" << endl;
	cout << "7. Extract min" << endl;
	cout << "8. Get max" << endl;
	cout << "9. Extract max" << endl;
	cout << "10. Change data of a node" << endl;
	cout << "11. Height of heap" << endl;
	cout << "12. Show size of heap" << endl;
	cout << "13. Is the heap full" << endl;
	cout << "14. Is the heap empty" << endl;
	cout << "15. Is the heap sorted" << endl;
	cout << "16. Is the min heap valid" << endl;
	cout << "17. Show count" << endl;
	cout << "18. Show root" << endl;
	cout << "19. Show parent of a node" << endl;
	cout << "20. Show children of a node" << endl;
	cout << "21. Show height of a node" << endl;
	cout << "22. Show depth of a node" << endl;
	cout << "23. Print Heap array" << endl;
	cout << "24. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 24);
	return choice;
}