#include <iostream>
#include <vector>
#include"Board.h"
using namespace std;

int convert(int x, int y, int n) {
	return x * n + y;
}

int getX(int n, int size) {
	return n/size;
}

int getY(int n, int size) {
	return n%size;
}

Board::Board():g(11*11) {
	gridSize = 11;
	for(int i=0; i<gridSize*gridSize; i++) {
		int left = i-1;
		int right = i+1;
		int topLeft = i-gridSize;
		int topRight = i-gridSize+1;
		int bottomLeft = i+gridSize-1;
		int bottomRight = i+gridSize;
		if(i == 0) { //top left corner
			g.add(i, right);
			g.add(i, bottomRight);
		} else if(i < gridSize-1) { //top row
			g.add(i, left);
			g.add(i, right);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else if(i == gridSize-1) {//top right corner
			g.add(i, left);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else if(i%gridSize == 0 && i != (gridSize*(gridSize-1))) { //left side excluding bottom left corner
			g.add(i, right);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, bottomRight);
		} else if(i == gridSize*(gridSize-1)) { //bottom left corner
			g.add(i, topRight);
			g.add(i, topLeft);
			g.add(i, right);
		} else if(i > gridSize*(gridSize-1) && i < (gridSize*gridSize)-1) { // bottom row excluding bottom right corner
			g.add(i, left);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, right);
		} else if(i == (gridSize*gridSize)-1){ // bottom right corner
			g.add(i, left);
			g.add(i, topLeft);
		} else if(i%gridSize == gridSize-1 && i != gridSize-1 && i != (gridSize*gridSize)-1) { // right side
			g.add(i, topLeft);
			g.add(i, left);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else { // middle of board (general case)
			g.add(i, left);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, right);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		}
	}
}

Board::Board(int n):g(n*n) {
	gridSize = n;
	for(int i=0; i<gridSize*gridSize; i++) {
		int left = i-1;
		int right = i+1;
		int topLeft = i-gridSize;
		int topRight = i-gridSize+1;
		int bottomLeft = i+gridSize-1;
		int bottomRight = i+gridSize;
		if(i == 0) { //top left corner
			g.add(i, right);
			g.add(i, bottomRight);
		} else if(i < gridSize-1) { //top row
			g.add(i, left);
			g.add(i, right);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else if(i == gridSize-1) {//top right corner
			g.add(i, left);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else if(i%gridSize == 0 && i != (gridSize*(gridSize-1))) { //left side excluding bottom left corner
			g.add(i, right);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, bottomRight);
		} else if(i == gridSize*(gridSize-1)) { //bottom left corner
			g.add(i, topRight);
			g.add(i, topLeft);
			g.add(i, right);
		} else if(i > gridSize*(gridSize-1) && i < (gridSize*gridSize)-1) { // bottom row excluding bottom right corner
			g.add(i, left);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, right);
		} else if(i == (gridSize*gridSize)-1){ // bottom right corner
			g.add(i, left);
			g.add(i, topLeft);
		} else if(i%gridSize == gridSize-1 && i != gridSize-1 && i != (gridSize*gridSize)-1) { // right side
			g.add(i, topLeft);
			g.add(i, left);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		} else { // middle of board (general case)
			g.add(i, left);
			g.add(i, topLeft);
			g.add(i, topRight);
			g.add(i, right);
			g.add(i, bottomLeft);
			g.add(i, bottomRight);
		}
	}
}

void Board::play(int x, int y, char type) {
	g.setType(convert(x, y, gridSize), type);
}

bool Board::pathExists(Point a, Point b) {
	//run BFS on the graph to see if there is a path between the two points
	if(g.getType(convert(a.x, a.y, gridSize)) == 'O' || g.getType(convert(b.x, b.y, gridSize)) == 'O' || g.getType(convert(a.x, a.y, gridSize)) != g.getType(convert(b.x, b.y, gridSize))) {
		return false;
	}
	int len = gridSize*gridSize;
	int s = convert(a.x, a.y, gridSize);
	int dest = convert(b.x, b.y, gridSize);
	vector<int> color(len, 0); //set all colors to white
	vector<int> d(len, INF); //set all d to INF
	vector<int> p(len, NIL); //set all p to NIL

	color[s] = 1; //gray
	d[s] = 0;
	vector<int> queue;
	queue.push_back(s);
	while(queue.size() > 0) {
		int x = queue[0];
		queue.erase(queue.begin());
		vector<int> adj = g.getLikeNeighbors(x);
		for(auto y : adj) {
			if(color[y] == 0) { // white
				color[y] = 1; // gray
				d[y] = d[x] + 1;
				p[y] = x;
				queue.push_back(y);
			}
		}
		color[x] = 2; //black
	}

	//if the destination node was discovered by BFS, return true, else return false
	return color[dest] != 0;
}

bool Board::pathExists(int a, int b) {
	if(g.getType(a) == 'O' || g.getType(b) == 'O' || g.getType(a) != g.getType(b)) {
		return false;
	}
	//run BFS on the graph to see if there is a path between the two points
	int len = gridSize*gridSize;
	int s = a;
	int dest = b;
	vector<int> color(len, 0); //set all colors to white
	vector<int> d(len, INF); //set all d to INF
	vector<int> p(len, NIL); //set all p to NIL

	color[s] = 1; //gray
	d[s] = 0;
	vector<int> queue;
	queue.push_back(s);
	while(queue.size() > 0) {
		int x = queue[0];
		queue.erase(queue.begin());
		vector<int> adj = g.getLikeNeighbors(x);
		for(auto y : adj) {
			if(color[y] == 0) { // white
				color[y] = 1; // gray
				d[y] = d[x] + 1;
				p[y] = x;
				queue.push_back(y);
			}
		}
		color[x] = 2; //black
	}

	//if the destination node was discovered by BFS, return true, else return false
	return color[dest] != 0;
}

bool Board::redWins() {
	vector<int> start;
	vector<int> end;
	for(int i=0; i<gridSize; i++) {
		start.push_back(i);
	}
	for(int i=gridSize*(gridSize-1); i<(gridSize*gridSize); i++) {
		end.push_back(i);
	}
	for(auto a : start) {
		for(auto b : end) {
			if(pathExists(a, b)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::blueWins() {
	vector<int> start;
	vector<int> end;
	for(int i=0; i<gridSize; i++) {
		start.push_back(i*gridSize);
	}
	for(int i=1; i<=gridSize; i++) {
		end.push_back((i*gridSize)-1);
	}
	for(auto a : start) {
		for(auto b : end) {
			if(pathExists(a, b)) {
				return true;
			}
		}
	}
	return false;
}

void Board::print() {
	for(int i=0; i<gridSize; i++) {
		for(int k=0; k<i; k++) {
			cout << "  ";
		}
		for(int j=0; j<gridSize; j++) {
			cout << g.getType(convert(i, j, gridSize)) << "   ";
		}
		cout << endl;
	}
}


