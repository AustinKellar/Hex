#include <iostream>
#include <vector>
#include"Board.h"
using namespace std;
#include<ctime>
#include<algorithm>


//helper function to convert x, y coordinates into a graph node
int convert(int x, int y, int n) {
	return x * n + y;
}

//function to convert letters typed in by the user into numbers usable by the board object
int convert(char c) {
	switch(c) {
	case 'A': return 0;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	case 'G': return 6;
	case 'H': return 7;
	case 'I': return 8;
	case 'J': return 9;
	case 'K': return 10;
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'e': return 4;
	case 'f': return 5;
	case 'g': return 6;
	case 'h': return 7;
	case 'i': return 8;
	case 'j': return 9;
	default: return 10;
	}
}
//returns an x coordinate from a graph node number
int Board::getX(int n) {
	return n/gridSize;
}
//returns a y coordinate from a graph node number
int Board::getY(int n) {
	return n%gridSize;
}

//faster way to retrieve the size of a vector of ints
int size(vector<int> v) {
	return static_cast<int>(v.size());
}

//default constructor: creates a correctly connected 11x11 hex board
Board::Board():g(11*11) {
	gridSize = 11;
	piecesPlayed = 0;
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

//primary constructor: creates a correctly connected n*n hex board
Board::Board(int n):g(n*n) {
	gridSize = n;
	piecesPlayed = 0;
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

//play a pice of color: type at coordinates x, y
void Board::play(int x, int y, char type) {
	g.setType(convert(x, y, gridSize), type);
	moves.push_back(Move(x, y, type));
	piecesPlayed++;
}

//play a piece of color: type at point(x,y)
void Board::play(Point p, char type) {
	g.setType(convert(p.x, p.y, gridSize), type);
	moves.push_back(Move(p.x, p.y, type));
	piecesPlayed++;
}
//play a piece of color: type at coordinates x, y where y is a letter that must be converted
void Board::play(int x, char y, char type) {
	int yCoord = convert(y);
	g.setType(convert(x, yCoord, gridSize), type);
	moves.push_back(Move(x, yCoord, type));
	piecesPlayed++;
}
//play a piece of color: type at coordinates x, y where x is a letter that must be converted
void Board::play(char x, int y, char type) {
	int xCoord = convert(x);
	g.setType(convert(xCoord, y, gridSize), type);
	moves.push_back(Move(xCoord, y, type));
	piecesPlayed++;
}

//play at coordinates x, y without tracking the move in the moves vector
void Board::playRebuild(int x, int y, char type) {
	g.setType(convert(x, y, gridSize), type);
	piecesPlayed++;
}

//remove a move(x,y) from the moves vector
void Board::rmMove(int x, int y) {
	for(int i=0; i<static_cast<int>(moves.size()); i++) {
		if(moves[i].x == x && moves[i].y == y) {
			moves.erase(moves.begin() + i);
		}
	}
}

//reset the piece at point p to the empty state
void Board::reset(Point p) {
	g.setType(convert(p.x, p.y, gridSize), 'O');
	rmMove(p.x, p.y);
	piecesPlayed--;
}

//reset the piece at coordinates x, y to the empty state
void Board::reset(int x, int y) {
	g.setType(convert(x, y, gridSize), 'O');
	rmMove(x, y);
	piecesPlayed--;
}

//reset the board to its original state
//Note: this does not reset the moves vector
void Board::resetBoard() {
	for(int i=0; i<gridSize*gridSize; i++) {
		g.setType(i, 'O');
	}
	piecesPlayed = 0;
}

//rebuild the board according to the past moves that were made
//i.e. play all of the moves currently stored in the moves vector
void Board::rebuild() {
	for(auto m : moves) {
		playRebuild(m.x, m.y, m.color);
	}
}

//Uses BFS to determine whether a path exists between nodes a and b on the board
bool Board::pathExists(int a, int b, char type) {
	if(g.getType(a) == 'O' || g.getType(b) == 'O' || g.getType(a) != g.getType(b) || g.getType(a) != type || g.getType(b) != type) {
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

//uses pathExists to determine if the red player has won
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
			if(pathExists(a, b, 'R')) {
				return true;
			}
		}
	}
	return false;
}

//uses pathExists to determine if the blue player has won
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
			if(pathExists(a, b, 'B')) {
				return true;
			}
		}
	}
	return false;
}

//determines if an input move is legal to play
bool Board::isLegal(int x, char y, char type) {
	int yCoord = convert(y);
	return g.getType(convert(x, yCoord, gridSize)) == 'O';
}

//determines if an input move is legal to play
bool Board::isLegal(char x, int y, char type) {
	int xCoord = convert(x);
	return g.getType(convert(xCoord, y, gridSize)) == 'O';
}

//helper function which copies the moves vector into a new outputed vector
vector<Move> Board::copyMoves() {
	vector<Move> m;
	for(auto mov : moves) {
		m.push_back(mov);
	}
	return m;
}

//Primary function used in the ai play function
//This function plays at the given x, y coordinates, then plays out the rest of the
//game randomly. Then it returns true if the inputted player type wins and false otherwise.
//After running the test, the board will be reset to the state that it was in before calling this function.
//This function will be run 1500 times per location on the board to come up with a probability 
//Of whether the player will win if it plays in the input location.
bool Board::winsHere(int x, int y, char type) {
	char player = type;
	g.setType(convert(x, y, gridSize), player);
	piecesPlayed++;
	if(player == 'R') player = 'B';
	else player = 'R';
	vector<int> openNodes;
	for(int i=0; i<gridSize*gridSize; i++) {
		if(g.getType(i) == 'O') openNodes.push_back(i);
	}
	random_shuffle(openNodes.begin(), openNodes.end());
	for(auto node : openNodes) {
		g.setType(node, player);
		piecesPlayed++;
		if(player == 'R') player = 'B';
		else player = 'R';
	}
	bool returnVal;
	if(type == 'R') returnVal = redWins();
	else returnVal = blueWins();

	resetBoard();
	rebuild();

	return returnVal;
}

//call this function to make the ai play in a location.
//It will call winsHere() 1500 times on every open board location
//and determine a probability that the ai will win at each open location.
//then it simply picks the board location with the highest probability of winning
//and plays there.
void Board::aiPlay(char type) {
	vector<double> probs;
	double winCount;
	vector<int> open;
	for(int i=0; i<gridSize*gridSize; i++) {
		if(g.getType(i) == 'O') open.push_back(i);
	}
	for(auto node : open) {
		winCount = 0;
		for(int i=0; i<1500; i++) {
			if(winsHere(getX(node), getY(node), type)) {
				winCount++;
			}
		}
		probs.push_back(winCount/1500);
	}
	double max = -1;
	for(int i=0; i<static_cast<int>(probs.size()); i++) {
		if(probs[i] > max) max = probs[i];
	}
	for(int i=0; i<static_cast<int>(probs.size()); i++) {
		if(probs[i] == max) {
			play(getX(open[i]), getY(open[i]), type);
			return;
		}
	}
}

//prints the board in its current state
void Board::print() {
	char a = 'A';
	cout << "  ";
	for(int i=0; i<gridSize; i++) {
		cout << a++ << "   ";
	}
	cout << endl << "   -----------------------------------------" << endl;
	for(int i=0; i<gridSize; i++) {
		for(int k=0; k<i; k++) {
			cout << "  ";
		}
		cout << i << ":  ";
		for(int j=0; j<gridSize; j++) {
			cout << g.getType(convert(i, j, gridSize)) << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

//purely for testing...this prints out the moves vector
void Board::printMoves() {
	for(auto m: moves) {
		cout << "(" << m.x << ", " << m.y << ", " << m.color << ")" << " ";
	}
}


