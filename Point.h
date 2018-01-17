#include <iostream>
using namespace std;

//simple point class to represent x,y coordinates

class Point {
	friend ostream& operator<<(ostream& out, const Point& p);
public:
	Point(int xCoord=0, int yCoord=0);
	int x;
	int y;
};
