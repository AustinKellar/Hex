#include <iostream>
using namespace std;

class Point {
	friend ostream& operator<<(ostream& out, const Point& p);
public:
	Point(int xCoord=0, int yCoord=0);
	int x;
	int y;
};
