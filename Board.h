#include <iostream>
#include <vector>
#include"Graph.h"
using namespace std;

const int NIL = -1;
const int INF = -2;

class Board {
	friend ostream& operator<<(ostream& out, const Board& b);
public:
	Board();
	Board(int n);
	void print();
	void play(int x, int y, char type);
	bool pathExists(Point a, Point b);
	bool pathExists(int a, int b);
	bool redWins();
	bool blueWins();
private:
	Graph g;
	int gridSize;
};
