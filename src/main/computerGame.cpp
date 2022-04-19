#include <iostream>
#include <vector>
#include <string>
#include "../../include/ai/AIGame.h"
#include <regex>
#include <cctype>
#include <cstdlib>

int main() {
	int playerNum;

	do {
		std::cout << "Enter your number (1/2): ";
		std::cin >> playerNum;
	} while(playerNum != 1 && playerNum != 2);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	AIGame game(playerNum);
	std::regex input_rgx("(add|remove) (\\d)");

	std::cout << "---------------------------------------------------------------------------\n"; 
	while (!game.finished()) {
		game.displayBoard();

		std::string move = "";
		int slot_num;
		int x = -1;
		int y = -1;

		std::cout << "---------------------------------------------------------------------------\n"; 

		string slots =
			"           1 -- 2 -- 3\n"
			"          /    /    /     << Slot Numbers\n"
			"         4 -- 5 -- 6\n"
			"        /    /    /        Move Format: add/remove slot#\n"
			"       7 -- 8 -- 9         Make a Move: ";
		std::cout << slots;

		bool fail = false;

		do {
			if (fail) {
				std::cout << "                           Make a Move: ";
			}

			std::string input;
			std::getline(std::cin, input);
			std::smatch matches;

			if (std::regex_search(input, matches, input_rgx)) {
				move = matches.str(1);
				for(int i = 0; i < move.size(); i++)
					move[i] = static_cast<char>(toupper(move[i]));
				slot_num = stoi(matches.str(2)) - 1;
				x = slot_num % 3;
				y = slot_num / 3;	
			}

			fail = true;
		} while(!game.makeMove(move, x, y));

		std::cout << "---------------------------------------------------------------------------\n\n"; 
	}

	game.displayBoard();

	if (game.winner() == playerNum) {
		cout << "                           PLAYER WINS!" << endl;
	}
	else if (game.winner()) {
		cout << "                           COMPUTER WINS!" << endl;
	}
	else {
		cout << "                           DRAW" << endl;
	}

	return 0;
}
