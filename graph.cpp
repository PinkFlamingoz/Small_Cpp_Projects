#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "basic_functions.h"

using namespace std;
// Graph Terms & Properties –
// Adjacency/Neighbor − Two node or vertices's are adjacent if they are connected to each other through an edge.
// Path − Path represents a sequence of edges between the two vertices's.
// Self-Loop − Is an edge that connects a vertex to itself. A simple graph contains no loops.
// Multi Edge − Two or more edges that are connecting to the same two vertices's.
// Simple Graph − Graphs without loops or parallel edges are called simple graphs.
// The degree of a node − The degree of a node is the number of edges incident/attached on it.
// Path − A path can be defined as the sequence of nodes that are followed in order to reach some terminal node E from the initial node A.
// Path length - Number of edges in a path.
// Simple Path − A path is a Simple path if no vertices's(and thus edges) are not repeated
// Cycle − A cycle can be defined as the path which has no repeated edges or vertices's except the first and last vertices's. ( Starts and stops at the same vertex )
// Connectivity - Two vertices's are connected if a path exist between them. A graph is called connected when all vertices's are connected.
//
// Max number of edges - For simple graphs (No multi edge, No self loop)
//	Directed =   0 <= edges <= vertices's(vertices's-1)
//	Undirected = 0 <= edges <= (vertices's(vertices's-1))/2
//
// Some Graph Types –
// 	Weighted Graphs –
// 		A weight is a numerical value attached to each individual edge in the graph.
// 		Weighted Graph will contains weight on each edge where as unweighted does not.
//	Directed(Di-graph) -
//	    A directed graph is a set of vertices's (nodes) connected by edges, with each node having a direction associated with it.
//      Edges are usually represented by arrows pointing in the direction the graph can be traversed.
//	Undirected Graph –
//		In an undirected graph the edges are bidirectional, with no direction associated with them.
//      Hence, the graph can be traversed in either direction.
//      The absence of an arrow tells us that the graph is undirected.
//  Directed (Cyclic) graph -
//		Where it loops
//  Directed Acyclic graph -
// 		Where it only goes one direction only
//  Tree is also a graph -
//
// Graph Applications –
// Dijkstra's Algorithm
// Prims's Algorithm
// Kruskal's Algorithm
// Graphs are used to define the flow of computation.
// Graphs are used to represent networks of communication.
// Graphs are used to represent data organization.
// Graph theory is used to find shortest path in road or a network.
//
// Graphs can be represented by a 2D matrix or a vector array of lists
// Adjacency Matrix –
// An adjacency matrix is a way of representing a graph as a matrix of booleans (0's and 1's).
// A finite graph can be represented in the form of a square matrix on a computer, where the boolean value of the matrix indicates if there is a direct path between two vertices's.
//
// Let's assume the n x n matrix as adj[n][n].
// if there is an edge from vertex i to j, mark adj[i][j] as 1. i.e. adj[i][j] == 1
// if there is no edge from vertex i to j, mark adj[i][j] as 0. i.e. adj[i][j] == 0
//
// Pros:
//  Representation is easier to implement and follow.
// 	Removing an edge takes O(1) time.
// 	Queries like whether there is an edge from vertex 'u' to vertex 'v' are efficient and can be done O(1).
// Cons:
// 	Consumes more space O(V^2).
// 	Even if the graph is sparse(contains less number of edges), it consumes the same space.
// 	Adding a vertex is O(V^2) time.
//
// Adjacency List –
// An array of lists is used. The size of the array is equal to the number of vertices's.
// Let the array be an array[]. An entry array[i] represents the list of vertices's adjacent to the ith vertex.
// This representation can also be used to represent a weighted graph.
// The weights of edges can be represented as lists of pairs.
// Adjacency lists are not well suited for parallelism since the lists require that we traverse the neighbors of a vertex sequentially.
//
// Pros:
//  Requires less space compared to the adjacency matrix representation. It typically takes O(V + E) space, where V is the number of vertices's and E is the number of edges.
//  Efficient for sparse graphs, as it only stores information about existing edges.
//  Adding a vertex is straightforward and takes O(1) time.
//  Adding an edge takes O(1) time if the list is implemented as an array or a linked list.
// Cons:
//  Traversing all the edges in the graph takes O(V + E) time, which can be slower compared to the adjacency matrix representation's O(V^2) time for dense graphs.
//  Checking for the existence of an edge between two vertices's can take O(degree(u)) time, where degree(u) is the number of edges adjacent to vertex 'u'.
//  Removing an edge takes O(degree(u)) time.
//  The implementation and understanding can be slightly more complex compared to the adjacency matrix representation.
//
// Overall, the adjacency list representation is commonly used when dealing with sparse graphs, as it provides efficient space usage and supports most graph operations efficiently.
// However, it may not be as suitable for dense graphs or scenarios where frequent edge existence checks or edge removals are required.
//
// BFS -
// In this traversal algorithm one node is selected and then all of the adjacent nodes are visited one by one.
// After completing all of the adjacent vertices's, it moves further to check another vertices's and checks its adjacent vertices's again.
// Steps -
// 1. Define a Queue
// 2. Set current vertex V
// 3. Add current vertex V to queue
// 4. Print current vertex V
// 5. Add all neighbors(unvisited i.e. previously not in queue) of V to queue(in any order)
// 6. Repeat from step 4 till queue empty
//
// DFS -
// In this algorithm one starting vertex is given, and when an adjacent vertex is found, it moves to that adjacent vertex first and try to traverse in the same manner.
// Steps -
// 1. Define a Stack
// 2. Set current vertex V
// 3. Add current vertex V to stack
// 4. Print current vertex V
// 5. Add any 1 neighbor(unvisited i.e. not in stack previously) of V to stack
// 6. If current vertex has all its neighbors already visited, pop it from stack & backtrack
// 7. Check remaining vertices's in the stack for any unvisited vertices's.
// 8. Repeat till stack empty

// Classes
template < typename T>
class Edge
{
	private:
	// Member variables
	T connection_vertex_key;
	int weight;

	public:
	// Member functions

	// Constructor
	Edge()
	{
		connection_vertex_key = T();
		weight = 0;
	}

	// Parameter constructor
	Edge(T connection_vertex_key, int weight)
	{
		this->connection_vertex_key = connection_vertex_key;
		this->weight = weight;
	}

	// Get the edge connection
	T get_connection_vertex_key() const
	{
		return connection_vertex_key;
	}

	// Get the weight of the edge
	int get_edge_weight() const
	{
		return weight;
	}

	// Set the edge connection
	void set_connection_vertex_key(T connection_vertex_key)
	{
		this->connection_vertex_key = connection_vertex_key;
	}

	// Set the weight of the edge
	void set_edge_weight(int weight)
	{
		this->weight = weight;
	}
};

template < typename T, typename D>
class Vertex
{
	private:
	// Member variables
	T key;
	D data;
	list<Edge<T>> edges;

	public:
	// Member functions

	// Constructor
	Vertex()
	{
		key = T();
		data = D();
	}

	// Parameter constructor
	Vertex(T key, D data)
	{
		this->key = key;
		this->data = data;
	}

	// Get the edge connection
	T get_key() const
	{
		return key;
	}

	// Get the weight of the edge
	D get_data() const
	{
		return data;
	}

	// Get the edges of a vertex
	list<Edge<T>> get_edges() const
	{
		return edges;
	}

	// Set the edge connection
	void set_key(T key)
	{
		this->key = key;
	}

	// Set the weight of the edge
	void set_data(D data)
	{
		this->data = data;
	}
};

template < typename T, typename D>
class Graph
{
	private:
	// Member variables
	vector<Vertex<T, D>> vertices;

	public:
	// Member functions

	// Check if vertex exist
	bool check_vertex_exist_by_key(T new_key)
	{
		for (const auto &vertex : vertices)
		{
			if (vertex.get_key() == new_key)
			{
				return true;
			}
		}
		return false;

		//for(int i = 0; i < vertices.size(); i++)
		//{
		//	if(vertices.at(i) == new_key)
		//	{
		//		return true;
		//	}
		//}
		//return false;
	}

	// Add vertex
	void add_vertex(Vertex<T, D> new_vertex)
	{
		if (check_vertex_exist_by_key(new_vertex.get_key()))
		{
			cerr << "\nVertex already exists with this key: " << new_vertex.get_key() << endl;
			return;
		}

		vertices.push_back(new_vertex);
		cout << "\nVertex added!" << endl;
	}

	// Create vertex
	static Vertex<T, D> create_vertex()
	{
		Vertex<T, D> vertex;
		cout << "\n================= Create vertex =================\n";
		vertex.set_key(get_valid_input<T>("Set the key: "));
		vertex.set_data(get_valid_input<D>("Set the data: "));
		cout << "=================================================\n";
		return vertex;
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Graph<int, int> g1;
	int choice = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				g1.add_vertex(Graph<int, int>::create_vertex());
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			case 16:
				break;
			case 17:
				break;
			case 18:
				break;
			case 19:
				break;
			case 20:
				break;
			case 21:
				break;
			case 22:
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
	// Dijkstra's Algorithm
	// Prims's Algorithm
	// Kruskal's Algorithm
	// Traveling sales man problem
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. Add vertex" << endl;
	cout << "2. Update vertex" << endl;
	cout << "3. Delete vertex" << endl;
	cout << "4. Add edge" << endl;
	cout << "5. Update edge" << endl;
	cout << "6. Delete edge" << endl;
	cout << "7. BFS" << endl;
	cout << "8. DFS" << endl;
	cout << "9. Check if two vertices's are neighbors" << endl;
	cout << "10. What is the path length between two vertices's" << endl;
	cout << "11. What is the path of least length between two vertices's" << endl;
	cout << "12. Does a path exist between two vertices's" << endl;
	cout << "13. Does a path exist that uses every edge exactly once" << endl;
	cout << "14. Does a path exist that uses every vertex exactly once" << endl;
	cout << "15. Is the graph connected" << endl;
	cout << "16. Max number of edges" << endl;
	cout << "17. Does the graph contain cycles" << endl;
	cout << "18. Given a set of k colors, can we assign colors to each vertex so that no two neighbors are assigned the same color" << endl;
	cout << "19. Degree of a vertex" << endl;
	cout << "20. Print all neighbors of a vertex" << endl;
	cout << "21. Print graph" << endl;
	cout << "22. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 22);
	return choice;
}