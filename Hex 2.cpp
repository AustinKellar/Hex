//============================================================================
// Name        : Hex.cpp
// Author      : Austin Kellar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include"Board.h"
using namespace std;

int main() {
	Board b;
	b.play(5, 0, 'B');
	b.play(5, 1, 'B');
	b.play(5, 2, 'B');
	b.play(5, 3, 'B');
	b.play(5, 4, 'B');
	//b.play(5, 5, 'B');
	b.play(5, 6, 'B');
	b.play(5, 7, 'B');
	b.play(5, 8, 'B');
	b.play(5, 9, 'B');
	b.play(5, 10, 'B');
	b.print();
	cout << b.blueWins();

	return 0;
}
