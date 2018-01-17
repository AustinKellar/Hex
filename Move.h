#include <iostream>
using namespace std;

//simple class to represent a hex move. It stores x,y coordinates as well as the 
//player color

class Move {
public:
	Move(int xCoord, int yCoord, char c);
	int x;
	int y;
	char color;
};
