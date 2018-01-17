#include <iostream>
#include <vector>
#include"Graph.h"
#include"Move.h"
using namespace std;

const int NIL = -1;
const int INF = -2;

//Board object
//These functions all have a short description inside Board.cpp
//Please see that file for more information

class Board {
	friend ostream& operator<<(ostream& out, const Board& b);
public:
	Board();
	Board(int n);
	void print();
	int getX(int n);
	int getY(int n);
	void play(int x, int y, char type);
	void play(int x, char y, char type);
	void play(char y, int x, char type);
	void play(Point p, char type);
	void playRebuild(int x, int y, char type);
	void reset(Point p);
	void reset(int x, int y);
	bool pathExists(int a, int b, char type);
	bool redWins();
	bool blueWins();
	bool isLegal(int x, char y, char type);
	bool isLegal(char x, int y, char type);
	void resetBoard();
	void rmMove(int x, int y);
	void rebuild();
	void printMoves(); // for testing only
	bool winsHere(int x, int y, char type);
	vector<Move> copyMoves();
	void aiPlay(char type);
private:
	Graph g;
	int gridSize;
	int piecesPlayed;
	vector<Move> moves;
};
