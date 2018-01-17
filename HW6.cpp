#include <iostream>
#include"Board.h"
#include<ctime>
using namespace std;

inline int randomInRange(int min, int max) {
	return rand()%(max-min + 1) + min;
}

//The main method here should be fairly self explanatory since it mostly includes print statements
//Use the print statements to get an idea of what its doing.

int main() {
	srand((unsigned)time(0));
	int n;
	cout << "What size Hex board do you want? Please enter a number 4-11 (Recommended 7-9)" << endl;
	cin >> n;

	Board b(n);

	int choice;
	cout << "Do you want to 1) Play against the AI or 2) Watch the AI play against itself?" << endl;
	cin >> choice;

	if(choice == 1) {
		int rand = randomInRange(1,2);
		char player = 'R';
		char ai = 'B';

		if(rand == 1) {
			player = 'B';
			ai = 'R';
		}

		if(player == 'R') cout << "You are playing as Red. Your token is R and you will be going second." << endl << endl;
		else cout << "You are playing as Blue. Your token is B and you will be going first." << endl << endl;

		char turn = 'B';
		int num;
		char ch;

		b.print();

		while(!b.redWins() && !b.blueWins()) {
			if(turn == 'B' && player == 'B') {
				cout << "Your Turn!" << endl << "Enter a board location of the following format: number [NO SPACE] letter." << endl << endl;
				cin >> num;
				cin >> ch;
				b.play(num, ch, player);
				turn = 'R';
				b.print();
			} else if(turn == 'R' && ai == 'R') {
				cout << "Please wait while the AI takes its turn..." << endl << endl;
				b.aiPlay(ai);
				turn = 'B';
				b.print();
			} else if(turn == 'B' && ai == 'B') {
				cout << "Please wait while the AI takes its turn..." << endl << endl;
				b.aiPlay(ai);
				turn = 'R';
				b.print();
			} else {
				cout << "Your Turn!" << endl << "Enter a board location of the following format: number [NO SPACE] letter." << endl << endl;
				cin >> num;
				cin >> ch;
				b.play(num, ch, player);
				turn = 'B';
				b.print();
			}
		}
		if(b.redWins()) cout << "Red Wins!" << endl;
		else cout << "Blue Wins!" << endl;
	} else {
		char player = 'R';
		b.print();
		while(!b.redWins() && !b.blueWins()) {
			if(player == 'R') cout << "Red's turn!" << endl;
			else cout << "Blue's turn!" << endl;
			cout << "Thinking..." << endl;
			b.aiPlay(player);
			if(player == 'R') player = 'B';
			else player = 'R';
			b.print();
		}
		if(b.redWins()) cout << "Red Wins!" << endl;
		else cout << "Blue Wins!" << endl;
	}
}
