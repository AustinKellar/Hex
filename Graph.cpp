#include <iostream>
#include <vector>
#include"Graph.h"
using namespace std;

// default constructor
Graph::Graph() {
	numVerts = 0;
	numEdges = 0;
}

//constructor from integer
Graph::Graph(int n) {
	adj.resize(n);
	types.resize(n);
	for(int i=0; i<n; i++) types[i] = 'O';
	numVerts = n;
	numEdges = 0;
}

//conversion constructor
Graph::Graph(vector<Edge> e) {
	int len = static_cast<int>(e.size());
	Graph g(len + 1);
	numVerts = len + 1;
	numEdges = len;
	adj.resize(numVerts);
	types.resize(numVerts);
	for(int i=0; i<numVerts; i++) types[i] = 'O';
	for(int i=0; i<len; i++) {
		adj[e[i].getSrc()].push_back(e[i].getDest());
		adj[e[i].getDest()].push_back(e[i].getSrc());
	}
	edges = e;
}

char Graph::getType(int n) {
	return types[n];
}

void Graph::setType(int n, char t) {
	types[n] = t;
}

//returns the number of neighbors that a specified node has
int Graph::neighborCount(int n) {
	return static_cast<int>(adj[n].size());
}

bool inVector(vector<int> v, int target) {
	for(auto i : v) {
		if(i == target) {
			return true;
		}
	}
	return false;
}

//add edge x->y to the graph with weight w
void Graph::add(int x, int y, double w) {
	if(!inVector(adj[x], y) && !inVector(adj[y], x)) {
		adj[x].push_back(y);
		adj[y].push_back(x);
		edges.push_back(Edge(x, y, w));
		numEdges++;
	}
}

//remove edge x->y from the graph if it exists
void Graph::remove(int x, int y) {
	bool altered = false;
	for(int i=0; i<neighborCount(x); i++) {
		if(adj[x][i] == y) {
			adj[x].erase(adj[x].begin() + i);
			altered = true;
		}
	}

	for(int i=0; i<neighborCount(y); i++) {
		if(adj[y][i] == x) {
			adj[y].erase(adj[y].begin() + i);
			altered = true;
		}
	}

	for(int i=0; i<numEdges; i++) {
		if((edges[i].getSrc() == x && edges[i].getDest() == y) || (edges[i].getSrc() == y && edges[i].getDest() == x)) {
			edges.erase(edges.begin() + i);
			altered = true;
		}
	}
	if(altered) {
		numEdges--;
	}
}

//return the weight of edge x->y if it exists, else return UNDEFINED (const for -1)
double Graph::getEdgeWeight(int x, int y) {
	for(int i=0; i<numEdges; i++) {
		Edge e = edges[i];
		if((e.getSrc() == x && e.getDest() == y) || (e.getSrc() == y && e.getDest() == x)) {
			return e.getWeight();
		}
	}
	return static_cast<double>(UNDEFINED);
}

//set the weight for edge x->y to weight w
void Graph::setEdgeWeight(int x, int y, double w) {
	for(int i=0; i<numEdges; i++) {
		Edge e = edges[i];
		if((e.getSrc() == x && e.getDest() == y) || (e.getSrc() == y && e.getDest() == x)) {
			edges[i].setWeight(w);
		}
	}
}

//return node n's list of neighbors
vector<int> Graph::getNeighbors(int n) {
	return adj[n];
}

//returns true if edges x and y are adjacent
bool Graph::adjacent(int x, int y) {
	for(int i=0; i<neighborCount(x); i++) {
		if(adj[x][i] == y) {
			return true;
		}
	}
	return false;
}

//returns the edge set of this graph
vector<Edge> Graph::getEdges() {
	return edges;
}

//returns number of vertices in the graph
int Graph::V() {
	return numVerts;
}

//returns number of edges in the graph
int Graph::E() {
	return numEdges;
}

//returns the sum of all the edge weights in the graph
double Graph::getGraphWeight() {
	double sum = 0;
	for(int i=0; i<numEdges; i++) {
		sum += edges[i].getWeight();
	}
	return sum;
}

//returns the edge object associated with integers x and y if it exists
Edge Graph::getEdge(int x, int y) {
	for(int i=0; i<numEdges; i++) {
		Edge e = edges[i];
		if((e.getSrc() == x && e.getDest() == y) || (e.getSrc() == y && e.getDest() == x)) {
			return edges[i];
		}
	}
}

vector<int> Graph::getLikeNeighbors(int n) {
	char type = getType(n);
	vector<int> start = getNeighbors(n);
	vector<int> end;
	for(int i=0; i<static_cast<int>(start.size()); i++) {
		if(getType(start[i]) == type) {
			end.push_back(start[i]);
		}
	}
	return end;
}

vector<int> Graph::openNodes() {
	vector<int> open;
	for(int i=0; i<static_cast<int>(types.size()); i++) {
		if(getType(types[i]) == 'O') {
			open.push_back(i);
		}
	}
	return open;
}

//overload << operator
ostream& operator<<(ostream& out, const vector<int>& v) {
	int len = static_cast<int>(v.size());
	for(int i=0; i<len; i++) {
		if(i  < len-1) {
			out << v[i] << ", ";
		} else {
			out << v[i];
		}
	}
	return out;
}

//overload << operator
ostream& operator<<(ostream& out, const Graph& g) {
	for(int i=0; i<g.numVerts; i++) {
		out << i << ": " << g.adj[i] << endl;
	}
	return out;
}
