#include <iostream>
#include"Point.h"
using namespace std;

Point::Point(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
}

ostream& operator<<(ostream& out, const Point& p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}
