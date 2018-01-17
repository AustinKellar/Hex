#include <iostream>
#include"Point.h"
using namespace std;

//Constructor
Point::Point(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
}

//overload << for output
ostream& operator<<(ostream& out, const Point& p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}
