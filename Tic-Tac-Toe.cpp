#include "Snake-Game.h"

using namespace std;

const int grid_size = 3;

class Game {
private:
	char grid[grid_size][grid_size];
public:
	void generate_grid() {
		int currentPosition = 1;
		for (int x = 0; x < grid_size; x++) {
			for (int y = 0; y < grid_size; y++) {
				grid[x][y] = to_string(currentPosition).c_str()[0];
				currentPosition++;
			}
		}
	};

	void show_grid() {
		printf("\n   -------------\n");
		for (int x = 0; x < grid_size; x++) {
			for (int y = 0; y < grid_size; y++) {
				string toDisplay = "";
				if (y == 0) toDisplay = "   |";
				toDisplay += " %c |";
				printf(toDisplay.c_str(), grid[x][y]);
			}
			printf("\n   -------------\n");
		}
	};

	void ask_turn() {
		string input;
		puts("Where you woud like to play?");
		getline(cin, input);
		if (input != "") {
			char entered = input.c_str()[0];
			if (entered >= '1' && entered <= '9') {
				int entered_number = entered - '0';
				int index = entered_number - 1;
				int x = index / 3;
				int y = index % 3;
				char grid_position = grid[x][y];

				if (grid_position == 'X' || grid_position == 'O') {
					puts("Looks like that grid position has been taken up already.");
				}
				else {
					grid[x][y] = grid_position;
					puts("What would you like to play?");
					getline(cin, input);
					if (input != "") {
						char entered_choice = input.c_str()[0];
						if (entered_choice == 'x' || entered_choice == 'X') grid[x][y] = 'X';
						else if (entered_choice == 'o' || entered_choice == 'O') grid[x][y] = 'O';
					}
					else {
						puts("You have to choose between x or o.");
					}
				}
			}
			else {
				puts("You have to plat through range 1-9.");
			}
		}
		else {
			puts("You need to enter something.");
		}
	}

	Game() {
		generate_grid();
		while (true) {
			show_grid();
			ask_turn();
		}
	}
};

int main(int argc, char *argv[]) {
	Game game;
	return 0;
}
