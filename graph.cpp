#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include "headers/basic_functions.h"

using namespace std;
// NOTE:
// map: A map in C++ is a container in the STL that is used to store key-value pairs in an ordered manner.
// The key values are sorted by their own comparison operation, which by default is std::less<Key>, but this can be customized.
// Maps are often used when there's a need to quickly access data associated with a specific key.
// Searching, removing, and inserting operations are efficient and have logarithmic complexity.
//
// unordered_map: An unordered map in C++ is a container that stores key - value pairs in an arbitrary order.
// The order of the elements does not remain constant and can change every time the program is run.
// This is unlike map where the order is always ascending.
// The underlying data structure is a hash table, so the insertion, deletion and access operations typically take constant time, O(1), on average.
//
// set: A set in C++ is a container that stores unique elements following a specific order.
// By default, it uses the less comparison function to maintain an ascending order of elements.
// Insertion, removal, and search have logarithmic complexity.
// Sets are usually used when there is a need to prevent duplicate elements and maintain a certain order.
//
// unordered_set: An unordered set is similar to a set but it doesn't maintain any order of elements.
// The elements are stored using a hash table which provides constant time complexity on average for insertions, deletions and access.
// Just like set, unordered_set also stores unique elements only.
//
// The primary difference between a set and a map in C++ is that a set only stores a single value for each element, whereas a map stores paired values - a key and a value associated with that key.
// Set: A set only contains keys and not values. The key itself is the value. You can think of a set as a map where only keys exist, and there are no values. Because keys are unique in a map, the elements in a set are also unique.
// Map : A map contains key - value pairs, where each key is associated with a value. You use the key to access or change its associated value. The keys are unique, so each key can only appear once in a map, and it can only be associated with one value.
//
// Graph representation
// | [ key ] [ data ] [ (list) { (edge) [ direction_to_key ] [ weight ], ... more edges } ] |
// | [ key ] [ data ] [ (list) { (edge) [ direction_to_key ] [ weight ], ... more edges } ] |
// | [ key ] [ data ] [ (list) { (edge) [ direction_to_key ] [ weight ], ... more edges } ] |
// | [ key ] [ data ] [ (list) { (edge) [ direction_to_key ] [ weight ], ... more edges } ] |
// | [ key ] [ data ] [ (list) { (edge) [ direction_to_key ] [ weight ], ... more edges } ] |
//
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
//
// Dijkstra's Algorithm:
// This is a famous graph search algorithm that solves the shortest - path problem for a graph with non - negative edge path costs, producing a shortest path tree.
// It is widely used in networking for routing of packets.
// It's also used in various fields like physical sciences, AI, operational research, etc.

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
		for (const auto &edge : key_1->get_edges())
		{
			if (edge.get_connection_vertex_key() == key_2->get_key())
			{
				return true;
			}
		}
		return false;
	}

	// Get an iterator to the edge, This is the same as using the lambda function
	typename list<Edge<T>>::iterator get_edge_by_key(const typename vector<Vertex<T, D>>::iterator &vertex, T key)
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
	void add_edge_between_vertices(int weight, T key_2, T key_1)
	{
		if (key_1 == key_2)
		{
			cerr << "\nSource and destination vertices are the same. Self-loops are not allowed." << endl;
			return;
		}

		auto from = get_vertex_by_key(key_1);
		if (from == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key_1 << endl;
			return;
		}

		auto to = get_vertex_by_key(key_2);;
		if (to == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << key_2 << endl;
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
	void update_edge_between_vertices(int weight, T key_2, T key_1)
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
			cerr << "\nNo vertex found with key: " << key_2 << endl;
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
	void delete_edge_between_vertices(T key_2, T key_1)
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
			cerr << "\nNo vertex found with key: " << key_2 << endl;
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

	// BFS
	// 1.Declare a queue, bfs_queue, to store iterators to Vertex objects. This avoids duplicating vertex objects when they're added to the queue.
	// 2.Declare an unordered_map named visited to store visited vertices. The keys are the vertex keys, and the values are iterators to the Vertex objects. This helps to quickly lookup a vertex by its key.
	// 3.Check if the start vertex exists in the graph. If it does not, print an error message and return from the function.
	// 4.Add a iterator to the start vertex to bfs_queue, and add the start vertex key and a iterator to the vertex to visited.
	// 5.While bfs_queue is not empty, do the following:
	//   5.1. Get the iterator to the current vertex from bfs_stack.
	//	 5.2. Dequeue a vertex from bfs_queue.
	//   5.3. Print the current vertex
	//	 5.4. For each edge of the dequeued vertex, do the following:
	//        5.4.1. Get the key of the connected vertex.
	//		  5.4.2. If the connected vertex has not been visited, add a iterator to it to bfs_queue, and add the vertex key and the iterator to the vertex to visited.
	void BFS(T start_key)
	{
		//---------------------------------------------------------------------------------------------- Check if the start vertex exists in the graph
		auto start_vertex = get_vertex_by_key(start_key);
		if (start_vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << start_key << endl;
			return;
		}

		queue<decltype(start_vertex)> bfs_queue; //----------------------------------------------------- Define a queue for BFS
		unordered_map<T, decltype(start_vertex)> visited; //-------------------------------------------- Create a map to store visited vertices

		//---------------------------------------------------------------------------------------------- Add the start vertex to the queue and visited map
		bfs_queue.push(start_vertex);
		visited[start_key] = start_vertex;

		//---------------------------------------------------------------------------------------------- BFS Algorithm
		while (!bfs_queue.empty())
		{
			//------------------------------------------------------------------------------------------ Get the iterator to the current vertex from the queue and remove it from the queue and print it
			auto current_vertex = bfs_queue.front();
			bfs_queue.pop();
			cout << "[" << current_vertex->get_key() << "]: " << current_vertex->get_data() << " ---> ";

			for (auto &edge : current_vertex->get_edges()) //------------------------------------------- Add all unvisited neighbors to the queue
			{
				T neighbor_key = edge.get_connection_vertex_key();

				if (visited.find(neighbor_key) == visited.end()) //------------------------------------- Check if the neighbor has been visited before
				{
					//---------------------------------------------------------------------------------- If not, mark it as visited and add it to the queue
					auto neighbor_vertex = get_vertex_by_key(neighbor_key);
					bfs_queue.push(neighbor_vertex);
					visited[neighbor_key] = neighbor_vertex;
				}
			}
		}
	}
	// The decltype is used to automatically determine the type of start_vertex, which is the return type of get_vertex_by_key().

	// DFS
	// 1. Define a Stack named dfs_stack to store iterators to Vertex objects.
	// 2. Define an unordered_map named visited to store visited vertices.
	// 3. Check if the start vertex exists in the graph.If it does not, print an error message and return from the function.
	// 4. Add the iterator to the start vertex to dfs_stack, and add the start vertex key and its iterator to visited.
	// 5. While dfs_stack is not empty, do the following:
	//    5.1. Get the iterator to the current vertex from dfs_stack.
	//    5.2. Pop it from the stack.
	//	  5.3. Print the current vertex.
	//    5.4. For each edge of the current vertex, do the following:
	//         5.4.1 Get the key of the connected vertex.
	//         5.4.2 If the connected vertex has not been visited, add the iterator to it to dfs_stack, and add the vertex key and its iterator to visited.
	void DFS(T start_key)
	{
		//---------------------------------------------------------------------------------------------- Check if the start vertex exists in the graph
		auto start_vertex = get_vertex_by_key(start_key);
		if (start_vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << start_key << endl;
			return;
		}

		stack<decltype(start_vertex)> dfs_stack; //----------------------------------------------------- Define a stack for DFS
		unordered_map<T, decltype(start_vertex)> visited; //-------------------------------------------- Create an unordered_map to store visited vertices

		//---------------------------------------------------------------------------------------------- Add the start vertex to the stack and visited map
		dfs_stack.push(start_vertex);
		visited[start_key] = start_vertex;

		//---------------------------------------------------------------------------------------------- DFS Algorithm
		while (!dfs_stack.empty())
		{
			//------------------------------------------------------------------------------------------ Get the iterator to the current vertex from the stack and remove it from the stack and print it
			auto current_vertex = dfs_stack.top();
			dfs_stack.pop();
			cout << "[" << current_vertex->get_key() << "]: " << current_vertex->get_data() << " ---> ";

			for (auto &edge : current_vertex->get_edges()) //------------------------------------------- Add all unvisited neighbors to the stack
			{
				T neighbor_key = edge.get_connection_vertex_key();

				if (visited.find(neighbor_key) == visited.end()) //------------------------------------- Check if the neighbor has been visited before
				{
					//---------------------------------------------------------------------------------- If not, mark it as visited and add it to the stack
					auto neighbor_vertex = get_vertex_by_key(neighbor_key);
					dfs_stack.push(neighbor_vertex);
					visited[neighbor_key] = neighbor_vertex;
				}
			}
		}
	}
	// The decltype is used to automatically determine the type of start_vertex, which is the return type of get_vertex_by_key().

	// Check if a path exists between two vertices
	bool path_exists_DFS(T end_key, T start_key)
	{
		//----------------------------------------------------------------- Check if the start and end vertices exist in the graph
		auto start_vertex = get_vertex_by_key(start_key);
		if (start_vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << start_key << endl;
			return false;
		}

		auto end_vertex = get_vertex_by_key(end_key);
		if (end_vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << end_key << endl;
			return false;
		}

		stack<decltype(start_vertex)> dfs_stack; //------------------------ Define a stack for DFS
		unordered_map<T, bool> visited; //--------------------------------- Create an unordered_map to store visited vertices

		//----------------------------------------------------------------- Add the start vertex to the stack and mark it as visited
		dfs_stack.push(start_vertex);
		visited[start_key] = true;

		while (!dfs_stack.empty())
		{
			auto current_vertex = dfs_stack.top();
			dfs_stack.pop();

			if (current_vertex->get_key() == end_key) //------------------- If we've reached the end vertex, a path exists
			{
				return true;
			}

			for (auto &edge : current_vertex->get_edges()) //-------------- Add all unvisited neighbors to the stack
			{
				T neighbor_key = edge.get_connection_vertex_key();

				if (!visited[neighbor_key]) //----------------------------- Check if the neighbor has been visited before
				{
					auto neighbor_vertex = get_vertex_by_key(neighbor_key);
					dfs_stack.push(neighbor_vertex);
					visited[neighbor_key] = true;
				}
			}
		}

		return false; //--------------------------------------------------- If we've exhausted all reachable vertices without finding the end vertex, no path exists
	}

	// Check if the graph is connected
	bool is_graph_connected(T start_key)
	{
		if (vertices.empty())
		{
			return true; //------------------------------------------------ An empty graph is considered connected
		}

		//----------------------------------------------------------------- Check if the start vertex exists in the graph
		auto start_vertex = get_vertex_by_key(start_key);
		if (start_vertex == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << start_key << endl;
			return false;
		}

		stack<decltype(start_vertex)> dfs_stack; //------------------------ Define a stack for DFS
		unordered_map<T, bool> visited; //--------------------------------- Create an unordered_map to store visited vertices

		dfs_stack.push(start_vertex); //----------------------------------- Add the start vertex to the stack
		visited[start_vertex->get_key()] = true; //------------------------ Mark it as visited

		//----------------------------------------------------------------- DFS Algorithm
		while (!dfs_stack.empty())
		{
			auto current_vertex = dfs_stack.top(); //---------------------- Get the vertex from the stack
			dfs_stack.pop(); //-------------------------------------------- Remove it from the stack

			for (auto &edge : current_vertex->get_edges()) //-------------- Visit all the neighbors of the current vertex
			{
				T neighbor_key = edge.get_connection_vertex_key();

				if (!visited[neighbor_key]) //----------------------------- If the neighbor has not been visited, mark it as visited and add it to the stack
				{
					auto neighbor_vertex = get_vertex_by_key(neighbor_key);
					dfs_stack.push(neighbor_vertex);
					visited[neighbor_key] = true;
				}
			}
		}

		return visited.size() == vertices.size(); //----------------------- If the number of visited vertices is equal to the total number of vertices, the graph is connected
	}

	// DFS_Cycle(vertex_key, visited, parent):
	// 1. Mark vertex_key as visited
	// 2. For each edge in the edges of vertex_key:
	//    2.1. Extract neighbor_key from the edge
	//    2.2. If neighbor_key is not visited:
	//		   2.2.1. Call DFS_Cycle with neighbor_key, visited, and vertex_key as the parent
	//         2.2.2. If DFS_Cycle returns true (which indicates a cycle), return true
	//    2.3. Else if neighbor_key is visited and it is not the parent, return true (it indicates a cycle)
	// 3. If no cycles are found after traversing all edges, return false
	bool DFS_cycle(T vertex_key, unordered_map<T, bool> &visited, T parent)
	{
		visited[vertex_key] = true; //--------------------------- Mark the current node as visited

		//------------------------------------------------------- Recur for all the vertices adjacent to this vertex
		auto vertex = get_vertex_by_key(vertex_key);
		for (auto &edge : vertex->get_edges())
		{
			T neighbor_key = edge.get_connection_vertex_key();

			//--------------------------------------------------- If an adjacent vertex is not visited, then recur for that adjacent
			if (!visited[neighbor_key])
			{
				if (DFS_cycle(neighbor_key, visited, vertex_key))
				{
					return true;
				}
			}
			//--------------------------------------------------- If an adjacent vertex is visited and is not a parent of the current vertex, then there is a cycle
			else if (neighbor_key != parent)
			{
				return true;
			}
		}

		return false;
	}

	// Contains_Cycle :
	// 1. Create an empty map "visited" to keep track of visited vertices
	// 2. For each vertex in the graph:
	//    2.1. If the vertex is not visited:
	//         2.1.1. Call DFS_Cycle with the vertex_key, visited map, and vertex_key as the parent
	//         2.1.2. If DFS_Cycle returns true, return true (since a cycle is detected)
	// 3. After checking all vertices, if no cycles are found, return false
	//
	// This graph forms a cycle A -> B -> C -> A.
	// Now, let's see how Depth First Search (DFS) algorithm works.
	// If we start DFS from A, it could go to B first (based on the ordering of neighbors). So for B, the parent node is A. Then DFS would go to C from B. For C, the parent node is B.
	// The key point here is that in an undirected graph, the parent of the current node(from which we came to the current node) is considered as an already visited node.
	// Hence, we should not consider it as a back edge.
	// So when we are at node C, we see that it has two neighbors: B and A.B is the parent of C in the DFS tree, so we ignore it.
	// But A is also a neighbor of C and A is visited and is not the parent of C, so this forms a cycle.
	// That's why we check neighbor_key != parent. If we don't, we would incorrectly identify the edge between the current node and its parent in the DFS tree as a back edge, leading to a false identification of a cycle.
	bool contains_cycle()
	{
		unordered_map<T, bool> visited; //--------------------------------- Initialize visited map

		for (auto &vertex : vertices) //----------------------------------- Do a DFS traversal for all vertices
		{
			if (!visited[vertex.get_key()])
			{
				//--------------------------------------------------------- Don't send any parent vertex for the first vertex
				if (DFS_cycle(vertex.get_key(), visited, vertex.get_key()))
				{
					return true;
				}
			}
		}

		return false;
	}

	// Is graph Eulerian or semi-Eulerian
	// An Eulerian graph is one where all vertices have an even degree, and it contains an Eulerian cycle, a path in the graph that visits every edge exactly once and starts and ends at the same vertex.
	// A semi-Eulerian graph, on the other hand, is a graph where exactly two vertices have an odd degree and it contains an Eulerian path, a path in the graph that visits every edge exactly once but does not necessarily start and end at the same vertex.
	// To ensure that we always find the correct Eulerian path or cycle, we need to choose the correct starting vertex.
	// In an Eulerian cycle, any vertex can be a starting point.
	// But in an Eulerian path, the path should start at one of the vertices with an odd degree.
	pair<int, vector<T>> is_graph_eulerian()
	{
		if (!is_graph_connected(vertices.front().get_key())) // A graph is Eulerian or semi-Eulerian only if it is connected, which means there is a path between every pair of vertices
		{
			return make_pair(-1, vector<T>()); //-------------- Return empty vector and -1
		}

		int odd = 0; //---------------------------------------- A counter variable odd is declared and initialized to zero. This variable will be used to count the vertices with an odd degree in the graph
		vector<T> odd_vertices;
		for (auto &vertex : vertices)
		{
			if ((vertex.get_edges().size()) % 2 != 0) //------- Checks whether the current vertex has an odd degree. The degree of a vertex in an undirected graph is the number of edges connected to it. vertex.get_edges().size() gives the degree of vertex. If this degree is odd, odd is incremented by 1
			{
				odd += 1;
				odd_vertices.push_back(vertex.get_key()); //--- Store vertices with odd degree
			}
		}

		if (odd == 0)
		{
			return make_pair(0, odd_vertices);
		}
		else if (odd == 2)
		{
			return make_pair(2, odd_vertices);
		}

		return make_pair(-1, vector<T>()); //------------------ Return empty vector and -1 if graph is not Eulerian or semi-Eulerian
	}
	// After counting the vertices with an odd degree, the function checks whether their number odd is either 0 or 2.
	// If odd is 0, it means all vertices have an even degree, and the graph is Eulerian.
	// If odd is 2, it means exactly two vertices have an odd degree, and the graph is semi-Eulerian.
	// In both these cases, the function returns true. If odd is neither 0 nor 2, the function returns false, indicating that the graph is neither Eulerian nor semi-Eulerian.

	// Print an Eulerian path or cycle in a graph
	// An unordered map visited_edges is initialized to keep track of the edges that have been visited.
	// The outer map's keys are the vertices, and its values are another unordered map.
	// The inner map's keys are also vertices, representing connections to the outer map's vertex.
	// The inner map's values are booleans, indicating whether the edge between the outer and inner vertices has been visited. Initially, all edges are marked as not visited.
	//
	// A stack current_path and a vector eulerian_path are defined to keep track of the current path and the final Eulerian path, respectively.
	//
	// The function then enters a loop, which continues until the current_path stack is empty.
	// Inside the loop, it checks for each edge of the current vertex.
	// If an edge connecting to a neighbor has not been visited(!visited_edges[current_vertex][edge.get_connection_vertex_key()]), it marks that edge as visited and pushes the current vertex into the current_path stack.
	// Then, it moves to the neighbor by setting current_vertex to edge.get_connection_vertex_key().
	// If all edges from the current vertex have been visited, it means we are "stuck".
	// In this case, it adds the current vertex to the eulerian_path vector and backtracks by setting current_vertex to the top of the current_path stack and popping the stack.
	//
	//  After the loop, eulerian_path contains the vertices of the Eulerian path, but in reverse order because of the backtracking process.
	// The function then prints these vertices in the correct order by iterating over eulerian_path in reverse.
	//
	//     A
	//   /
	//	B     C
	//	 \   / \
	//	   D --- E
	//
	// We start from an arbitrary vertex. Let's pick 'A'. We put 'A' on the current_path stack and set current_vertex to 'A'.
	//
	// From 'A', we have one unvisited edge: (A, B). Let's go with (A, B).
	// We mark (A, B) as visited and put 'B' on the current_path stack.
	//
	// Now current_vertex is 'B'.
	// From 'B', we have one unvisited edge: (B, D). Let's go with (B, D).
	// We mark (B, D) as visited and put 'D' on the current_path stack.
	//
	// Now current_vertex is 'D'.
	// From 'D', we have two unvisited edges: (D, C), and (D, E). Let's go with (D, E).
	// We mark (D, E) as visited and put 'E' on the current_path stack.
	//
	// Now current_vertex is 'E'.
	// From 'E' we have one unvisited edge: (E, C). Let's go with (E, C).
	// We mark (E, C) as visited and put 'C' on the current_path stack.
	//
	// Now current_vertex is 'C'.
	// 'C' has no unvisited edges. So we backtrack. We pop 'C' from the current_path stack and add it to eulerian_path.
	//
	// Now current_vertex is 'E'.
	// 'E' has no unvisited edges. So we backtrack. We pop 'E' from the current_path stack and add it to eulerian_path.
	//
	// Now current_vertex is 'D'.
	// 'D' has no unvisited edges. So we backtrack. We pop 'D' from the current_path stack and add it to eulerian_path.
	//
	// Now current_vertex is 'B'.
	// 'B' has no unvisited edges. So we backtrack. We pop 'B' from the current_path stack and add it to eulerian_path.
	//
	// Now current_vertex is 'A'.
	// 'A' has no unvisited edges. So we backtrack. We pop 'A' from the current_path stack and add it to eulerian_path.
	//
	// Now current_path is empty. We have visited all edges once. The eulerian_path has the order of the vertices visited.
	// Finally, we print the eulerian_path in reverse order : A -> B -> D -> E -> C -> D which gives us an Eulerian path.
	void print_eulerian()
	{
		pair<int, vector<T>> eulerian = is_graph_eulerian();
		if (eulerian.first == -1)
		{
			cout << "\nThe graph does not have an Eulerian path or cycle" << endl;
			return;
		}

		unordered_map<T, unordered_map<T, bool>> visited_edges; //------------------------------- Create a map to keep track of edges that have been visited.

		for (const auto &vertex : vertices) //--------------------------------------------------- Initialize visited_edges for every vertex in the graph
		{
			visited_edges[vertex.get_key()] = unordered_map<T, bool>();
		}

		//--------------------------------------------------------------------------------------- Create a stack to keep track of the current path and a vector to store the final Eulerian path
		stack<T> current_path;
		vector<T> eulerian_path;

		//--------------------------------------------------------------------------------------- Start from the first vertex with odd degree (if any), or the first vertex in the graph
		T current_vertex;
		if (eulerian.first == 0) //-------------------------------------------------------------- Eulerian, can start from any vertex so we start from the first vertex
		{
			current_vertex = vertices.begin()->get_key();
		}
		else if (eulerian.first == 2) //--------------------------------------------------------- Semi-Eulerian, must start from vertex with odd degree
		{
			current_vertex = eulerian.second[0];
		}
		current_path.push(current_vertex);

		//--------------------------------------------------------------------------------------- Traverse the graph DFS
		while (!current_path.empty())
		{
			bool stuck = true; //---------------------------------------------------------------- Boolean variable to check if all edges from the current vertex are visited

			for (auto &edge : get_vertex_by_key(current_vertex)->get_edges()) //----------------- Traverse all neighbors of the current vertex
			{
				if (!visited_edges[current_vertex][edge.get_connection_vertex_key()]) //--------- If this edge has not been visited yet
				{
					//--------------------------------------------------------------------------- Mark the edge as visited, since it is an undirected graph we do this for both edges aka back and forth
					visited_edges[current_vertex][edge.get_connection_vertex_key()] = true;
					visited_edges[edge.get_connection_vertex_key()][current_vertex] = true;

					//--------------------------------------------------------------------------- Add the current vertex to the stack and move to the next vertex
					current_path.push(current_vertex);
					current_vertex = edge.get_connection_vertex_key();

					stuck = false; //------------------------------------------------------------ We found an unvisited edge, so we are not stuck
					break;
				}
			}

			if (stuck) //------------------------------------------------------------------------ If all edges are visited (we are stuck), add the current vertex to the Eulerian path and move to the previous vertex in the current path
			{
				eulerian_path.push_back(current_vertex);
				current_vertex = current_path.top();
				current_path.pop();
			}
		}

		//--------------------------------------------------------------------------------------- Print the Eulerian path or cycle. NOTE: as we are pushing back elements into eulerian_path in reverse order, we have to print it in reverse, hence we use reverse iterators
		cout << endl;
		for (auto it = eulerian_path.rbegin(); it != eulerian_path.rend(); ++it)
		{
			cout << *it << " ---> ";
		}
		cout << endl;
	}

	// Check if a path exists from the current vertex that includes all vertices
	// It first adds the current vertex to the path and marks it as visited.
	// It then checks if all vertices have been visited and added to the path.
	// If so, it means a Hamiltonian Path has been found and the function returns true.
	// If not all vertices have been visited, it goes through each neighbor of the current vertex.
	// For each neighbor, if the neighbor hasn't been visited yet, it calls is_current_parth_hamiltonian() recursively on that neighbor.
	// If the recursive call returns true, it means a Hamiltonian Path has been found from the current vertex and the function returns true.
	// If no valid path can be found from any of the neighbors, the function "backtracks".
	// It removes the current vertex from the path, marks it as unvisited, and returns false.
	// Backtracking means that the function will go back to previous steps and try different paths.
	bool is_current_parth_hamiltonian(list<T> &path, map<T, bool> &visited, T vertex_key)
	{
		// Base case
		path.push_back(vertex_key); //----------------------------------------------------------------- Add the current vertex to the path

		if (path.size() == vertices.size()) //--------------------------------------------------------- If all vertices are in the path, then we have found a Hamiltonian Path
		{
			return true;
		}

		visited[vertex_key] = true; //----------------------------------------------------------------- Mark the current vertex as visited

		// Recursive case
		auto current_vertex = get_vertex_by_key(vertex_key); //---------------------------------------- Retrieve the current vertex

		for (auto &edge : current_vertex->get_edges()) //---------------------------------------------- Check all adjacent vertices
		{
			T neighbor_key = edge.get_connection_vertex_key();

			if (!visited[neighbor_key] && is_current_parth_hamiltonian(path, visited, neighbor_key)) // If the vertex hasn't been visited yet, then check if a path exists from there
			{
				return true;
			}
		}

		//--------------------------------------------------------------------------------------------- If no valid path is found then backtrack, remove the vertex from the path and mark it as unvisited
		path.pop_back();
		visited[vertex_key] = false;

		return false;
	}

	// Check if a Hamiltonian Path exists in the graph
	bool is_hamiltonian_path()
	{
		for (auto &vertex : vertices)
		{
			//------------------------------------------------------------------- Create a path and a visited map
			list<T> path;
			map<T, bool> visited;

			if (is_current_parth_hamiltonian(path, visited, vertex.get_key())) // If a Hamiltonian Path exists starting from this vertex, then return true
			{
				//--------------------------------------------------------------- Print the path
				cout << "\nHamiltonian path found: ";
				for (auto &key : path)
				{
					cout << key << " ---> ";
				}
				cout << endl;
				return true;
			}
		}

		//----------------------------------------------------------------------- If no Hamiltonian Path is found after checking all vertices, then return false
		cout << "\nNo Hamiltonian path found in this graph." << endl;
		return false;
	}

	// Check if we can assign colors to each vertex so that no two neighbors are assigned the same color
	bool color_graph(int k)
	{
		unordered_map<T, int> color_map; //---------------------------------------------------------------- Keeps track of colors assigned to each vertex
		for (auto &vertex : vertices)
		{
			color_map[vertex.get_key()] = -1; //----------------------------------------------------------- Initialize all vertices as uncolored (-1)
		}

		color_map[vertices.front().get_key()] = 0; //------------------------------------------------------ Color the first vertex with color 0

		vector<bool> available_colors(k, true); //--------------------------------------------------------- Temporary array to store available colors of size k. If available_colors[current_color] is false, then the color current_color is assigned to one of its neighbors

		//------------------------------------------------------------------------------------------------- Assign colors to remaining V-1 vertices
		for (auto &vertex : vertices)
		{
			if (vertex.get_key() == vertices.front().get_key()) //----------------------------------------- Skip the first vertex
			{
				continue;
			}

			//--------------------------------------------------------------------------------------------- Process all neighboring vertices and flag their color as unavailable, if that vertex thats connecting to the current vertex has a color it will flag it as false
			for (auto &edge : vertex.get_edges())
			{
				if (color_map[edge.get_connection_vertex_key()] != -1)
				{
					available_colors[color_map[edge.get_connection_vertex_key()]] = false; //-------------  The color_map here returns a color of a connecting vertex, if we have 2 colors it will return either 0 or 1
				}
			}

			//--------------------------------------------------------------------------------------------- Find the first available color
			int current_color;
			for (current_color = 0; current_color < k; current_color++)
			{
				if (available_colors[current_color])
				{
					break;
				}
			}

			if (current_color == k) //--------------------------------------------------------------------- If no color could be assigned, return false
			{
				return false;
			}

			color_map[vertex.get_key()] = current_color; //------------------------------------------------ Assign the found color to this vertex

			//--------------------------------------------------------------------------------------------- Reset the values back to true for the next iteration, only for the uncolored vertices, we keep the color of the current vertex
			for (auto &edge : vertex.get_edges())
			{
				if (color_map[edge.get_connection_vertex_key()] != -1)
				{
					available_colors[color_map[edge.get_connection_vertex_key()]] = true;
				}
			}
		}

		//------------------------------------------------------------------------------------------------- If we made it here, it means we were able to color all the vertices with k colors, print the color map here if you want
		for (auto &vertex : vertices)
		{
			cout << "Vertex " << vertex.get_key() << " ---> Color " << color_map[vertex.get_key()] << endl;
		}

		return true;
	}

	// Dijkstra's Algorithm
	// The function takes two arguments: source_key and target_key. These represent the keys of the source and target vertices, respectively.
	//
	// The function uses two maps(std::map) called distances and previous.
	//	   distances keeps track of the shortest distance from the source vertex to every other vertex that has been encountered so far.
	//     previous is used to keep track of the shortest path found so far.
	//
	// The function also uses a priority queue(std::priority_queue) called queue.
	//     This priority queue is used to decide which vertex to visit next.
	//     The priority queue is a useful data structure for this algorithm because it can quickly give us the vertex with the smallest distance.
	//
	// After initializing distances(to INT_MAX, which represents infinity here) and previous, the function sets the distance to the source vertex to 0 and pushes it to queue.
	//
	// The function then enters a loop, which continues until there are no more vertices in the queue.
	//
	// Inside the loop, the function does the following:
	//     It first removes the vertex with the smallest distance from queue. This is the current vertex.
	//     Then it iterates over all edges of the current vertex. For each edge, it checks if the distance to the vertex at the other end of the edge(the "adjacent" vertex) can be reduced by going through the current vertex.
	//     If so, it updates the distance and the path in distances and previous, respectively, and adds the adjacent vertex to queue.
	//
	// After the loop, the function checks if a path from source_key to target_key was found.
	// If so, it prints the path by following the previous links from target_key to source_key and also prints the total distance of the path.
	// If no path was found, it informs the user.
	//
	// The initialization of distances to INT_MAX (representing "infinity" in this context) is an important part of Dijkstra's algorithm.
	// The distances map holds the shortest known distances from the source vertex to all other vertices.
	// Initially, the shortest distance from the source vertex to any other vertex is unknown.
	// We could say it's "infinitely large" since we haven't yet explored any path to the vertex.
	// This is why we initialize all distances to INT_MAX.
	// As Dijkstra's algorithm progresses, it explores different paths starting from the source vertex and updates the distances in the map.
	// The algorithm guarantees that once a vertex's distance is updated, it is the shortest distance from the source vertex to that vertex.
	// In other words, we start by assuming that all vertices are "infinitely" far away, and then Dijkstra's algorithm "discovers" the true distances by exploring the graph.
	// This is a common approach when dealing with shortest path algorithms or generally in situations where you want to find a minimum value, and you start with the largest possible value as an initial condition.
	//
	// The priority_queue is a container adapter that provides a restricted form of a container that always keeps the greatest element at the top (or the least, based on the comparator function provided).
	// It is defined with three parameters:
	// pair<int, T>: This is the type of data that will be stored in the priority queue.
	//				 Here, it's a pair, where the first element is an integer (representing the weight or distance in this context), and the second element is of type T (representing the vertex).
	// vector<pair<int, T>>: This is the underlying container that is used to store the elements.
	//                       It can be any type of sequence container such as vector, dequeue, or even a user-defined type, as long as it supports certain operations like front(), push_back(), and pop_back().
	//                       Here, we are using vector of pair<int, T>.
	// greater<pair<int, T>>: This is a comparison function that determines the order of the elements inside the queue.
	//                        By default, priority_queue is a max heap (meaning it always pops the maximum element).
	//                        But in this case, we want it to be a min heap (i.e., it should always pop the minimum element).
	//                        greater<> is a built-in function object class that defines the function call operator with the same functionality as the relational operator >.
	//                        By providing greater<pair<int, T>>, we are making the priority queue behave like a min heap instead of a max heap.
	//
	// A --2-- B --2-- D --1-- E
	// |               |
	// |               |
	// | __1__ C __3__ |
	//
	// Step 1: Initialize the distances array to INT_MAX and distance to the source vertex (A) to 0.
	// The priority queue is initialized with (0, A). Also, the predecessor map initially contains only the source vertex with no predecessor.
	// Distances map:
	// A: 0
	// B: INT_MAX
	// C: INT_MAX
	// D: INT_MAX
	// E: INT_MAX
	//
	// Priority queue:
	// (0, A)
	//
	// Predecessor map:
	// A: None
	//
	// Step 2: Process vertex A from the priority queue.
	// Update the distances to its adjacent vertices (B and C).
	// The new distance to B will be 0 + 2 = 2, and to C will be 0 + 1 = 1.
	// Since these are smaller than the current distances, update the distances and add the new distances along with the vertices to the priority queue.
	// Distances map:
	// A: 0
	// B: 2
	// C: 1
	// D: INT_MAX
	// E: INT_MAX
	//
	// Priority queue:
	// (1, C)
	// (2, B)
	//
	// Predecessor map:
	// A: None
	// B: A
	// C: A
	//
	// Step 3: Process the vertex with the smallest distance in the priority queue, which is C.
	// Update the distance to its adjacent vertices.
	// In this case, C only connects to D. The new distance to D will be 1 (distance to C) + 3 (weight of edge CD) = 4.
	// Since this is smaller than the current distance to D, update it.
	// Distances map:
	// A: 0
	// B: 2
	// C: 1
	// D: 4
	// E: INT_MAX
	//
	// Priority queue:
	// (2, B)
	// (4, D)
	//
	// Predecessor map:
	// A: None
	// B: A
	// C: A
	// D: C
	//
	// Step 4: Process vertex B. Update the distance to its adjacent vertices (D).
	// The new distance to D will be 2 (distance to B) + 2 (weight of edge BD) = 4.
	// Since this is equal to the current distance to D, we do not update it.
	// Distances map:
	// A: 0
	// B: 2
	// C: 1
	// D: 4
	// E: INT_MAX
	//
	// Priority queue:
	// (4, D)
	//
	// Predecessor map:
	// A: None
	// B: A
	// C: A
	// D: C
	//
	// Step 5: Process vertex D.
	// Update the distance to its adjacent vertices (E).
	// The new distance to E will be 4 (distance to D) + 1 (weight of edge DE) = 5.
	// Since this is smaller than the current distance to E, update it.
	// Distances map:
	// A: 0
	// B: 2
	// C: 1
	// D: 4
	// E: 5
	//
	// Priority queue:
	// (Empty)
	//
	// Predecessor map:
	// A: None
	// B: A
	// C: A
	// D: C
	// E: D
	//
	// At the end of the algorithm, the distances map gives the shortest distance from A to all other vertices, and the predecessor map can be used to construct the shortest path from A to any other vertex.
	// For example, the shortest path from A to E is A --> B --> D --> E with a total weight of 5.
	void dijkstra(T target_key, T source_key)
	{
		//---------------------------------------------------------------------------------------------------------- Check if the start and end vertices exist in the graph
		auto vertex_from = get_vertex_by_key(source_key);
		if (vertex_from == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << source_key << endl;
			return;
		}

		auto vertex_to = get_vertex_by_key(target_key);
		if (vertex_to == vertices.end())
		{
			cerr << "\nNo vertex found with key: " << target_key << endl;
			return;
		}

		map<T, int> distances;
		map<T, T> previous;
		priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> queue;

		for (auto &vertex : vertices)
		{
			distances[vertex.get_key()] = INT_MAX; //--------------------------------------------------------------- Initialize distances from the source vertex to all other vertices as infinity
		}

		distances[source_key] = 0; //------------------------------------------------------------------------------- Distance from source to itself is 0
		queue.push({ 0, source_key }); //--------------------------------------------------------------------------- Push the source vertex into the queue

		while (!queue.empty())
		{
			//------------------------------------------------------------------------------------------------------ The first vertex in pair is the minimum distance vertex, extract it from priority queue.
			T current_vertex_key = queue.top().second;
			queue.pop();

			auto current_vertex = get_vertex_by_key(current_vertex_key); //----------------------------------------- 'current_vertex' is pointer to the vertex that matches the current_vertex_key in vertices list

			for (auto &edge : current_vertex->get_edges())
			{
				T neighbor_key = edge.get_connection_vertex_key();

				if (distances[neighbor_key] > distances[current_vertex_key] + edge.get_edge_weight()) //------------ If there is a shorter path to v through u
				{
					//---------------------------------------------------------------------------------------------- Update distance of v
					distances[neighbor_key] = distances[current_vertex_key] + edge.get_edge_weight();
					queue.push({ distances[neighbor_key], neighbor_key });

					previous[neighbor_key] = current_vertex_key; //------------------------------------------------- Store the path
				}
			}
		}

		//---------------------------------------------------------------------------------------------------------- Print shortest distances from source to all other vertices
		cout << endl;
		for (auto &distance : distances)
		{
			cout << "Distance from " << source_key << " to " << distance.first << " is " << distance.second << endl;
		}

		//---------------------------------------------------------------------------------------------------------- Print paths as well
		cout << endl;
		for (auto &prev : previous)
		{
			cout << "Path to " << prev.first << ": ";
			for (T key = prev.first; key != source_key; key = previous[key])
			{
				cout << key << " <--- ";
			}
			cout << source_key << endl;
		}

		//---------------------------------------------------------------------------------------------------------- If there is a path from source_key to target_key
		if (previous.find(target_key) != previous.end())
		{
			cout << "\nShortest path from " << source_key << " to " << target_key << ": ";
			for (T key = target_key; key != source_key; key = previous[key])
			{
				cout << key << " <--- ";
			}
			cout << source_key << endl;

			cout << "The distance is " << distances[target_key] << endl;
		}
		else
		{
			cout << "\nNo path exists from " << source_key << " to " << target_key << " exists." << endl;
		}
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

		return vertex->get_edges().size();
	}

	// How many edges can a graph have with the current vertices (n is the number of vertices)
	// For an undirected graph without self - loops, the maximum number of edges is n * (n - 1) / 2, because each vertex can connect to n - 1 other vertices(not counting itself), and since it's an undirected graph, each edge is counted twice (once for each vertex it connects).
	// For an undirected graph with    self - loops, the maximum number of edges is n * n            because each vertex can connect to n vertices including itself.
	// For a directed graph    without self - loops, the maximum number of edges is n * (n - 1)      because each vertex can have an outgoing edge to n - 1 other vertices and an incoming edge from n - 1 other vertices.
	// For a directed graph    with    self - loops, the maximum number of edges is n * n            because each vertex can have an outgoing and an incoming edge from each of the n vertices including itself.
	int max_edges() const
	{
		int n = vertices.size();
		return n * (n - 1) / 2;
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
		auto vertex = get_vertex_by_key(key);
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
int get_weight();
int get_colors();

int main()
{
	Graph<int, int> g1;
	int choice = 0;
	auto vertex_1 = g1.get_vertices().end();
	auto vertex_2 = g1.get_vertices().end();
	int colors = 0;
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
				g1.add_edge_between_vertices(get_weight(), get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter key of vertex from: "));
				break;
			case 5:
				g1.update_edge_between_vertices(get_weight(), get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter key of vertex from: "));
				break;
			case 6:
				g1.delete_edge_between_vertices(get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter key of vertex from: "));
				break;
			case 7:
				g1.BFS(get_valid_input<int>("Enter key of vertex to start BFS from: "));
				break;
			case 8:
				g1.DFS(get_valid_input<int>("Enter key of vertex to start DFS from: "));
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
					cout << "Edge found between: [" << vertex_1->get_key() << "]: " << vertex_1->get_data() << " ---> [" << vertex_2->get_key() << "]: " << vertex_2->get_data() << endl;
				}
				else
				{
					cout << "Edge does not exist!" << endl;
				}
				break;
			case 10:
				if (g1.path_exists_DFS(get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter key of vertex from: ")))
				{
					cout << "Path exists!" << endl;
				}
				else
				{
					cout << "Path does not exist!" << endl;
				}
				break;
			case 11:
				g1.dijkstra(get_valid_input<int>("Enter key of vertex to: "), get_valid_input<int>("Enter key of vertex from: "));
				break;
			case 12:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					g1.print_eulerian();
				}
				break;
			case 13:
				if (g1.is_hamiltonian_path())
				{
					cout << "Path exists!" << endl;
				}
				else
				{
					cout << "Path does not exist!" << endl;
				}
				break;
			case 14:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					if (g1.is_graph_connected(get_valid_input<int>("Enter key of vertex to start from: ")))
					{
						cout << "Graph is connected!" << endl;
					}
					else
					{
						cout << "Graph is not connected!" << endl;
					}
				}
				break;
			case 15:
				cout << "Max number of edges this graph can currently have is: " << g1.max_edges() << " edges with a total of: " << g1.get_vertices().size() << " vertices!" << endl;
				break;
			case 16:
				if (g1.contains_cycle())
				{
					cout << "Graph has cycles!" << endl;
				}
				else
				{
					cout << "Graph doesn't have cycles!" << endl;
				}

				break;
			case 17:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					colors = get_colors();
					if (g1.color_graph(colors))
					{
						cout << "The graph can be colored using " << colors << " colors!" << endl;
					}
					else
					{
						cout << "The graph cannot be colored using " << colors << " colors!" << endl;
					}
				}
				break;
			case 18:
				cout << g1.degree_of_a_vertex(get_valid_input<int>("Enter key of vertex to see degree for: ")) << " is the degree!" << endl;
				break;
			case 19:
				g1.print_neighbors(get_valid_input<int>("Enter key of vertex to see neighbors for: "));
				break;
			case 20:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					cout << "Graph is not empty!" << endl;
				}
				break;
			case 21:
				if (g1.get_vertices().empty())
				{
					cout << "Graph is empty!" << endl;
				}
				else
				{
					g1.print_graph();
				}
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
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. Add vertex" << endl;
	cout << "2. Update vertex" << endl;
	cout << "3. Delete vertex" << endl;
	cout << "4. Add edge" << endl;
	cout << "5. Update edge" << endl;
	cout << "6. Delete edge" << endl;
	cout << "7. BFS" << endl;
	cout << "8. DFS" << endl;
	cout << "9. Check if two vertices are neighbors" << endl;
	cout << "10. Does a path exist between two vertices" << endl;
	cout << "11. What is the path of least length between two vertices Dijkstra's Algorithm" << endl;
	cout << "12. Does a path exist that uses every edge exactly once" << endl;
	cout << "13. Does a path exist that uses every vertex exactly once" << endl;
	cout << "14. Is the graph connected" << endl;
	cout << "15. Max number of edges that this graph can have with current vertices" << endl;
	cout << "16. Does the graph contain cycles" << endl;
	cout << "17. Given a set of k colors, can we assign colors to each vertex so that no two neighbors are assigned the same color" << endl;
	cout << "18. Degree of a vertex" << endl;
	cout << "19. Print all neighbors of a vertex" << endl;
	cout << "20. Is graph empty" << endl;
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

// Get the weight for the edge
int get_weight()
{
	int weight = 0;
	do
	{
		weight = get_valid_input<int>("Enter edge weight: ");
	} while (weight < 1);
	return weight;
}

// Get the colors
int get_colors()
{
	int colors = 0;
	do
	{
		colors = get_valid_input<int>("Enter number of colors to give: ");
	} while (colors < 1);
	return colors;
}