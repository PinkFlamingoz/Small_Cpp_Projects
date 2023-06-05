#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include "basic_functions.h"

using namespace std;
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
	//                       It can be any type of sequence container such as vector, deque, or even a user-defined type, as long as it supports certain operations like front(), push_back(), and pop_back(). 
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
		for (auto &distance : distances)
		{
			cout << "\nDistance from " << source_key << " to " << distance.first << " is " << distance.second << endl;
		}

		//---------------------------------------------------------------------------------------------------------- Print paths as well
		for (auto &prev : previous)
		{
			cout << "\n11Path to " << prev.first << ": ";
			for (T key = prev.first; key != source_key; key = previous[key])
			{
				cout << key << " <- ";
			}
			cout << source_key << endl;
		}

		//---------------------------------------------------------------------------------------------------------- If there is a path from source_key to target_key
		if (previous.find(target_key) != previous.end())
		{
			cout << "\nShortest path from " << source_key << " to " << target_key << ": ";
			for (T key = target_key; key != source_key; key = previous[key])
			{
				cout << key << " <- ";
			}
			cout << source_key << endl;

			cout << "The distance is " << distances[target_key] << endl;
		}
		else
		{
			cout << "\nNo path from " << source_key << " to " << target_key << " exists." << endl;
		}
	}

	// Check if the graph is connected
	bool is_graph_connected() 
	{
    	if (vertices.empty()) 
		{
        	return true; //------------------------------------------------ An empty graph is considered connected
    	}

    	stack<Vertex<T, D>> dfs_stack; //---------------------------------- Define a stack for DFS
    	unordered_map<T, bool> visited; //--------------------------------- Create an unordered_map to store visited vertices

   	 	auto start_vertex = vertices.begin()->second; //------------------- Start from the first vertex in the map
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
				break;
			case 13:
				break;
			case 14:
			    if(g1.is_graph_connected())
				{
					cout << "Graph is connected" << endl;
				}
				else
				{
					cout << "Graph is not connected" << endl;
				}
				break;
			case 15:
				break;
			case 16:
				break;
			case 17:
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
	cout << "9. Check if two vertices are neighbors" << endl;
	cout << "10. Does a path exist between two vertices" << endl;
	cout << "11. What is the path of least length between two vertices Dijkstra's Algorithm" << endl;
	cout << "12. Does a path exist that uses every edge exactly once" << endl; // not
	cout << "13. Does a path exist that uses every vertex exactly once" << endl; // not
	cout << "14. Is the graph connected" << endl;
	cout << "15. Max number of edges that this graph can have with current vertices" << endl; // not
	cout << "16. Does the graph contain cycles" << endl; // not
	cout << "17. Given a set of k colors, can we assign colors to each vertex so that no two neighbors are assigned the same color" << endl; // not
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
	} while (weight < 0);
	return weight;
}