#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// Functions
void hello_world();
void hello_there(string prompt);
void for_each(const vector<int> &values, void(*function)(int));
void print(char letter);
void another_for_each(const vector<char> &letters, void(*call_me)(char));
void do_something_for_each(const vector<int> &numbers, void(*call_me)(int));
void capture_outside_something_for_each(const vector<int> &numbers, const function<void(int)> &call_me);

int main()
{
	//void(*/*CUSTOM FUNCTION VARIABLE NAME*/)(/*PARAMETERS*/) = nullptr; // A function pointer
	void(*funki_funk)() = nullptr; //  Store the memory address where that function is located
	funki_funk = hello_world;
	funki_funk();

	typedef void(*fanki_funk)();
	fanki_funk hey_new_name = nullptr;
	hey_new_name = hello_world;
	hey_new_name();

	auto function = hello_world;
	function();

	void(*helo_there)(string) = nullptr;
	helo_there = hello_there;
	helo_there("Sexy");

	typedef void(*heli_there)(string);
	heli_there hey_new_phone = nullptr;
	hey_new_phone = hello_there;
	hey_new_phone("My my oh my!");

	auto helo = hello_there;
	helo("Hello there!");

	vector<int> values = { 1,2,3,4,5 };
	for_each(values, [](int value)
	{
		cout << "Value: " << value << endl;
	});

	vector<char> letters = { 'a','b','c','d','e' };
	another_for_each(letters, print);

	vector<int> numbers = { 100,200,300,400,500 };
	auto lambda = [](int value)
	{
		cout << value * value << endl;
	};
	do_something_for_each(numbers, lambda);

	string ulala = "I AM HERE ";
	string me_to = "Me too";
	auto outside_capture = [&](int value) // The [] represents what the function can capture out side of the lambda function
	{
		cout << value * value + value << endl;
		cout << ulala << endl;
		cout << me_to << endl;
	};
	// [] Captures nothing
	// [=] Captures everything by value
	// [&] Captures everything by reference
	// [a,&b,c ... etc] pass in individual values
	// [this] captures the current object by reference
	capture_outside_something_for_each(numbers, outside_capture);

	auto outside_capture_mutable = [=](int value) mutable // If we pass in by value we have to use the mutable if we wanna edit the values
	{
		me_to = "YES";
		cout << value * value + value << endl;
		cout << ulala << endl;
		cout << me_to << endl;
	};
	capture_outside_something_for_each(numbers, outside_capture_mutable);

	auto it = find_if(values.begin(), values.end(), [](int value)
	{
		return value > 3;
	}); // Return a iterator thats greater than 3

	cout << *it << endl;

	// Get an iterator to the edge
	// find_if(vertex->get_edges().begin(), vertex->get_edges().end(), [key](const Edge<T> &edge){...});
	// This line is using the find_if function from the Standard Library to find an edge in the vector of edges that meets a certain condition.
	// find_if is a function template that takes three arguments : two iterators that specify the range to search, and a unary predicate that specifies the condition to meet.
	//
	//		vertex->get_edges().begin() and vertex->get_edges().end()
	//      specify the range to search. These are iterators to the beginning and past - the - end of the from_edges vector, respectively.
	//
	//		[key](const Edge<T> &edge){return edge.get_connection_vertex_key() == key;}
	//      is a lambda function(an anonymous function) that takes an edge and returns true if the edge's connection vertex key is equal to key.
	//
	// find_if returns an iterator pointing to the first element in the range[vertex->get_edges().begin(), vertex->get_edges().end()) that satisfies the predicate.
	// If no such element is found, it returns an iterator equal to vertex->get_edges().end().
	// auto get_edge_by_key(typename vector<Vertex<T, D>>::iterator vertex, T key) const
	// {
	// 	 return find_if(vertex->get_edges().begin(), vertex->get_edges().end(), [key](const Edge<T> &edge)
	// 	 {
	// 		 return edge.get_connection_vertex_key() == key;
	// 	 });
	// }
}

// for each function pointer
void hello_world()
{
	cout << "Hello world!" << endl;
}

// for each function pointer
void hello_there(string prompt)
{
	cout << prompt << endl;
}

// For each function
void for_each(const vector<int> &values, void(*function)(int)) // This uses a lambda that is a anonymous function that doesn't need to be declared
{
	for (int value : values)
	{
		function(value);
	}
}

// Call me function
void print(char letter)
{
	cout << letter << endl;
}

// Another for each function
void another_for_each(const vector<char> &letters, void(*call_me)(char)) // For each objects in the vector execute a given function
{
	for (char letter : letters)
	{
		call_me(letter);
	}
}

// Another for each function
void do_something_for_each(const vector<int> &numbers, void(*call_me)(int))
{
	for (int number : numbers)
	{
		call_me(number);
	}
}

// Another for each function
void capture_outside_something_for_each(const vector<int> &numbers, const function<void(int)> &call_me) // We cant use a raw function pointer like the above examples we must declare it as a function
{
	for (int number : numbers)
	{
		call_me(number);
	}
}
// Lambdas are mostly used in find if function to find something specific in a list vector etc