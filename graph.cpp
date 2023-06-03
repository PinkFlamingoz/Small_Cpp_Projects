#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include "basic_functions.h"

using namespace std;
// Graph Terms & Properties –
// Adjacency/Neighbor − Two node or vertices are adjacent if they are connected to each other through an edge.
// Path − Path represents a sequence of edges between the two vertices.
// Self-Loop − Is an edge that connects a vertex to itself. A simple graph contains no loops.
// Multi Edge − Two or more edges that are connecting to the same two vertices.
// Simple Graph − Graphs without loops or parallel edges are called simple graphs.
// The degree of a node − The degree of a node is the number of edges incident/attached on it.
// Path − A path can be defined as the sequence of nodes that are followed in order to reach some terminal node E from the initial node A.
// Path length - Number of edges in a path.
// Simple Path − A path is a Simple path if no vertices(and thus edges) are not repeated
// Cycle − A cycle can be defined as the path which has no repeated edges or vertices except the first and last vertices. ( Starts and stops at the same vertex )
// Connectivity - Two vertices are connected if a path exist between them. A graph is called connected when all vertices are connected.
//
// Max number of edges - For simple graphs (No multi edge, No self loop)
//	Directed =   0 <= edges <= vertices(vertices-1)
//	Undirected = 0 <= edges <= (vertices(vertices-1))/2
//
// Some Graph Types –
// 	Weighted Graphs –
// 		A weight is a numerical value attached to each individual edge in the graph.
// 		Weighted Graph will contains weight on each edge where as unweighted does not.
//	Directed(Di-graph) -
//	    A directed graph is a set of vertices (nodes) connected by edges, with each node having a direction associated with it.
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
// A finite graph can be represented in the form of a square matrix on a computer, where the boolean value of the matrix indicates if there is a direct path between two vertices.
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
// An array of lists is used. The size of the array is equal to the number of vertices.
// Let the array be an array[]. An entry array[i] represents the list of vertices adjacent to the ith vertex.
// This representation can also be used to represent a weighted graph.
// The weights of edges can be represented as lists of pairs.
// Adjacency lists are not well suited for parallelism since the lists require that we traverse the neighbors of a vertex sequentially.
//
// Pros:
//  Requires less space compared to the adjacency matrix representation. It typically takes O(V + E) space, where V is the number of vertices and E is the number of edges.
//  Efficient for sparse graphs, as it only stores information about existing edges.
//  Adding a vertex is straightforward and takes O(1) time.
//  Adding an edge takes O(1) time if the list is implemented as an array or a linked list.
// Cons:
//  Traversing all the edges in the graph takes O(V + E) time, which can be slower compared to the adjacency matrix representation's O(V^2) time for dense graphs.
//  Checking for the existence of an edge between two vertices can take O(degree(u)) time, where degree(u) is the number of edges adjacent to vertex 'u'.
//  Removing an edge takes O(degree(u)) time.
//  The implementation and understanding can be slightly more complex compared to the adjacency matrix representation.
//
// Overall, the adjacency list representation is commonly used when dealing with sparse graphs, as it provides efficient space usage and supports most graph operations efficiently.
// However, it may not be as suitable for dense graphs or scenarios where frequent edge existence checks or edge removals are required.
//
// BFS -
// In this traversal algorithm one node is selected and then all of the adjacent nodes are visited one by one.
// After completing all of the adjacent vertices, it moves further to check another vertices and checks its adjacent vertices again.
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
// 7. Check remaining vertices in the stack for any unvisited vertices.
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
	list<Edge<T>> &get_edges()
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

	// Add edge ,in the context of (const Edge<T>& edge), the & means that edge is being passed by reference. The const means that this function promises not to modify edge.
	// In short, (const Edge<T>& edge) is more efficient than (Edge<T> edge) when the Edge object is large, because it avoids making a copy of the Edge object. And it's safer because it promises not to modify the Edge object.
	void add_edge(const Edge<T> &edge)
	{
		edges.push_back(edge);
	}

	// Print edges
	int count_edges()
	{
		return get_edges().size();
	}

	// Print edges
	void print_edges()
	{
		cout << "| ";
		for (auto &edge : get_edges())
		{
			cout << "--- (" << edge.get_edge_weight() << ") ---> [" << edge.get_connection_vertex_key() << "], ";
		}
		cout << "|";
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

	// Get vertices we return a const reference to avoid copying of unnecessary data
	vector<Vertex<T, D>> &get_vertices()
	{
		return vertices;
	}

	// Check if vertex exist
	bool check_vertex_exist_by_key(T new_key) const
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
		//	if(vertices.at(i).get_key() == new_key)
		//	{
		//		return true;
		//	}
		//}
		//return false;
	}

	// Get vertex by key
	typename vector<Vertex<T, D>>::iterator get_vertex_by_key(T key)
	{
		for (auto it = vertices.begin(); it != vertices.end(); it++)
		{
			if (it->get_key() == key)
			{
				return it;
			}
		}
		return vertices.end();
	}

	// Check if vertex exist, by looping through the edges of the vertex key_1 and see if it has an edge corresponding to the key of the vertex that we want to set the edge
	bool check_edge_exist_by_key(const typename vector<Vertex<T, D>>::iterator &key_1, const typename vector<Vertex<T, D>>::iterator &key_2) const
	{
		for (auto &edge : key_1->get_edges())
		{
			if (edge.get_connection_vertex_key() == key_2->get_key())
			{
				return true;
			}
		}
		return false;
	}

	// Get an iterator to the edge, This is the same as using the lambda function
	typename list<Edge<T>>::iterator get_edge_by_key(const typename vector<Vertex<T, D>>::iterator &vertex, T key) const
	{
		// auto &edges = vertex->get_edges();
		// This line is creating a reference to the vector of edges associated with the vertex referred to by from.
		// auto & is a way to create a reference to a type that is automatically inferred by the compiler.
		// This means edges directly refers to the actual edges vector of the vertex, not a copy of it.
		auto &edges = vertex->get_edges();
		for (auto it = edges.begin(); it != edges.end(); it++)
		{
			if (it->get_connection_vertex_key() == key)
			{
				return it;
			}
		}
		return edges.end(); //-------------------------------- Return end() if not found
	}

	// Add vertex
	void add_vertex(const Vertex<T, D> &new_vertex)
	{
		if (check_vertex_exist_by_key(new_vertex.get_key()))
		{
			cerr << "\nVertex already exists with this key: " << new_vertex.get_key() << endl;
			return;
		}

		vertices.push_back(new_vertex);
		cout << "\nVertex added!" << endl;
	}

	// Update vertex
	void update_vertex(T key, D data)
	{
		auto vertex = get_vertex_by_key(key);
		if (vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key << endl;
			return;
		}

		vertex->set_data(data);

		cout << "\nVertex updated successfully!" << endl;
	}

	// Delete vertex
	void delete_vertex(T key)
	{
		auto vertex = get_vertex_by_key(key);
		if (vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key << endl;
			return;
		}

		auto &edges = vertex->get_edges();
		for (auto it = edges.begin(); it != edges.end(); it++)
		{
			delete_edge_between_vertices(it->get_connection_vertex_key(), key);
		}

		vertices.erase(vertex);

		cout << "\nVertex deleted successfully!" << endl;
	}

	// Add edge between vertices
	void add_edge_between_vertices(T key_1, T key_2, int weight = 0)
	{
		auto from = get_vertex_by_key(key_1);
		if (from == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key_1 << endl;
			return;
		}

		auto to = get_vertex_by_key(key_2);;
		if (to == vertices.end())
		{
			cerr << "\nNo vertex found with those key: " << key_2 << endl;
			return;
		}

		if (check_edge_exist_by_key(from, to))
		{
			cerr << "\nVertices are already connected!" << endl;
			return;
		}

		Edge<T> edge_1(key_2, weight);
		from->add_edge(edge_1);
		cout << "\nEdge added [" << from->get_key() << "]: " << from->get_data() << " ---> [" << to->get_key() << "]: " << to->get_data() << endl;

		Edge<T> edge_2(key_1, weight);
		to->add_edge(edge_2);
		cout << "\nEdge added [" << to->get_key() << "]: " << to->get_data() << " ---> [" << from->get_key() << "]: " << from->get_data() << endl;
	}

	// Update edge between vertices
	void update_edge_between_vertices(T key_1, T key_2, int weight = 0)
	{
		auto from = get_vertex_by_key(key_1);;
		if (from == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key_1 << endl;
			return;
		}

		auto to = get_vertex_by_key(key_2);;
		if (to == vertices.end())
		{
			cerr << "\nNo vertex found with those key: " << key_2 << endl;
			return;
		}

		auto from_edge = get_edge_by_key(from, key_2);
		if (from_edge == from->get_edges().end())
		{
			cerr << "\nNo edge found between: [" << from->get_key() << "]: " << from->get_data() << " ---> [" << to->get_key() << "]: " << to->get_data() << endl;
			return;
		}

		auto to_edge = get_edge_by_key(to, key_1);
		if (to_edge == to->get_edges().end())
		{
			cerr << "\nNo edge found between: [" << to->get_key() << "]: " << to->get_data() << " ---> [" << from->get_key() << "]: " << from->get_data() << endl;
			return;
		}

		from_edge->set_edge_weight(weight);
		cout << "\nEdge updated [" << from->get_key() << "]: " << from->get_data() << " ---> [" << to->get_key() << "]: " << to->get_data() << endl;

		to_edge->set_edge_weight(weight);
		cout << "\nEdge updated [" << to->get_key() << "]: " << to->get_data() << " ---> [" << from->get_key() << "]: " << from->get_data() << endl;
	}

	// Delete an edge between vertices
	void delete_edge_between_vertices(T key_1, T key_2)
	{
		auto from = get_vertex_by_key(key_1);;
		if (from == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key_1 << endl;
			return;
		}

		auto to = get_vertex_by_key(key_2);;
		if (to == vertices.end())
		{
			cerr << "\nNo vertex found with those key: " << key_2 << endl;
			return;
		}

		auto &from_edges = from->get_edges();
		auto from_edge = get_edge_by_key(from, key_2);
		if (from_edge == from_edges.end())
		{
			cerr << "\nNo edge found between: [" << from->get_key() << "]: " << from->get_data() << " ---> [" << to->get_key() << "]: " << to->get_data() << endl;
			return;
		}

		auto &to_edges = to->get_edges();
		auto to_edge = get_edge_by_key(to, key_1);
		if (to_edge == to_edges.end())
		{
			cerr << "\nNo edge found between: [" << to->get_key() << "]: " << to->get_data() << " ---> [" << from->get_key() << "]: " << from->get_data() << endl;
			return;
		}

		from_edges.erase(from_edge);
		cout << "\nEdge deleted [" << from->get_key() << "]: " << from->get_data() << " ---> [" << to->get_key() << "]: " << to->get_data() << endl;

		to_edges.erase(to_edge);
		cout << "\nEdge deleted [" << to->get_key() << "]: " << to->get_data() << " ---> [" << from->get_key() << "]: " << from->get_data() << endl;
	}

	// Degree of a vertex
	int degree_of_a_vertex(T key)
	{
		auto vertex = get_vertex_by_key(key);
		if (vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key << endl;
			return 0;
		}

		return vertex->count_edges();
	}

	// Print graph
	// auto: This keyword tells the compiler to automatically determine the appropriate type of the variable.
	//       In this case, it's used to deduce the type of elements that vertices container holds.
	//       This is very handy when the type of elements is complex or lengthy to write out.
	// const: This keyword means that the variable vertex cannot be modified inside the loop.
	//        In other words, you're promising not to change vertex within the loop body.
	// &: This symbol indicates that vertex is a reference to the element in the vertices container, not a copy of it.
	//    This can improve performance because it avoids unnecessary copying of elements.
	//    Combined with const, this means you're getting a read-only reference to each element, one at a time.
	// vertex: Is the name of the variable that will represent each element in the vertices container.
	// : is what separates the element type and element variable name on the left, and the container on the right.
	// vertices: Is the container that you're iterating over. It could be an array, vector, list, etc.
	//
	// In each iteration of the loop, vertex is bound to the current element in the vertices container. The loop continues until it has gone through all elements.
	// In summary, this line of code can be read as "For each vertex in vertices, where vertex is a constant reference to the actual element in the container".
	// If we want to modify the element we need to remove the const and keep the reference. If we remove the reference as well only the local element will be affected.
	void print_graph()
	{
		for (auto &vertex : vertices)
		{
			cout << "[" << vertex.get_key() << "]: " << vertex.get_data() << " --- ";
			vertex.print_edges();
			cout << endl;
		}
	}

	// Print neighbors of a vertex
	void print_neighbors(T key)
	{
		auto vertex = get_vertex_by_key(key);;
		if (vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key << endl;
			return;
		}

		vertex->print_edges();
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
	auto vertex_1 = g1.get_vertices().end();
	auto vertex_2 = g1.get_vertices().end();
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
				g1.update_vertex(get_valid_input<int>("Enter key of vertex to update: "), get_valid_input<int>("Set the data: "));
				break;
			case 3:
				g1.delete_vertex(get_valid_input<int>("Enter key of vertex to delete: "));
				break;
			case 4:
				g1.add_edge_between_vertices(get_valid_input<int>("Enter key of vertex from: "), get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter edge weight: "));
				break;
			case 5:
				g1.update_edge_between_vertices(get_valid_input<int>("Enter key of vertex from: "), get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter edge weight: "));
				break;
			case 6:
				g1.delete_edge_between_vertices(get_valid_input<int>("Enter key of vertex from: "), get_valid_input<int>("Enter key of vertex to: "));
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				vertex_1 = g1.get_vertex_by_key(get_valid_input<int>("Enter key of vertex from: "));
				if (vertex_1 == g1.get_vertices().end())
				{
					cerr << "No vertex found!" << endl;
					break;
				}
				vertex_2 = g1.get_vertex_by_key(get_valid_input<int>("Enter key of vertex to: "));
				if (vertex_2 == g1.get_vertices().end())
				{
					cerr << "No vertex found!" << endl;
					break;
				}

				if (g1.check_edge_exist_by_key(vertex_1, vertex_2))
				{
					cerr << "Edge found between: [" << vertex_1->get_key() << "]: " << vertex_1->get_data() << " ---> [" << vertex_2->get_key() << "]: " << vertex_2->get_data() << endl;
				}
				else
				{
					cout << "Edge does not exist!" << endl;
				}
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
				cout << g1.degree_of_a_vertex(get_valid_input<int>("Enter key of vertex to see degree for: ")) << " is the degree!" << endl;
				break;
			case 20:
				g1.print_neighbors(get_valid_input<int>("Enter key of vertex to see neighbors for: "));
				break;
			case 21:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					cout << "Graph is not empty!" << endl;
				}
				break;
			case 22:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					g1.print_graph();
				}
				break;
			case 23:
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
	cout << "7. BFS" << endl; // not
	cout << "8. DFS" << endl; // not
	cout << "9. Check if two vertices are neighbors" << endl;
	cout << "10. What is the path length between two vertices" << endl; // not
	cout << "11. What is the path of least length between two vertices'" << endl; // not
	cout << "12. Does a path exist between two vertices" << endl; // not
	cout << "13. Does a path exist that uses every edge exactly once" << endl; // not
	cout << "14. Does a path exist that uses every vertex exactly once" << endl; // not
	cout << "15. Is the graph connected" << endl; // not
	cout << "16. Max number of edges that this graph can have with current vertices" << endl; // not
	cout << "17. Does the graph contain cycles" << endl; // not
	cout << "18. Given a set of k colors, can we assign colors to each vertex so that no two neighbors are assigned the same color" << endl; // not
	cout << "19. Degree of a vertex" << endl;
	cout << "20. Print all neighbors of a vertex" << endl;
	cout << "21. Is graph empty" << endl;
	cout << "22. Print graph" << endl;
	cout << "23. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 23);
	return choice;
}