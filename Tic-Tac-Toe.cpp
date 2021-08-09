#include "Tic-Tac-Toe.h"

using namespace std;

const int grid_size = 3;

class Position {
public:
	int x = 0;
	int y = 0;
	
	Position(int number) {
		x = number / grid_size;
		y = number % grid_size;
	}
};

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

	bool ask_turn() {
		string input;
		puts("Where you woud like to play?");
		getline(cin, input);
		if (input != "") {
			char entered = input.c_str()[0];
			if (entered >= '1' && entered <= '9') {
				int entered_number = entered - '0';
				int index = entered_number - 1;
				
				Position pos = getCoords(index);
				char grid_position = grid[pos.x][pos.y];

				if (grid_position == 'X' || grid_position == 'O') {
					puts("Looks like that grid position has been taken up already.");
				}
				else {
					grid[pos.x][pos.y] = grid_position;
					puts("What would you like to play?");
					getline(cin, input);
					if (input != "") {
						char entered_choice = input.c_str()[0];
						if (entered_choice == 'x' || entered_choice == 'X') {
							grid[pos.x][pos.y] = 'X';
							return true;
						} 
						else if (entered_choice == 'o' || entered_choice == 'O') {
							grid[pos.x][pos.y] = 'O';
							return true;
						}
						else puts("Invalid character used. You may use either X or O.");
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

		return false;
	}

	bool check_for_wins() {
		const char* winning_moves[] = {
			"123",
			"456",
			"789",
			"147",
			"258",
			"369",
			"159",
			"357"
		};
		int amountOfWiningPermutations = 8;

		for (int i = 0; i < amountOfWiningPermutations; i++) {
			bool winner = true;
			char previous_grid = '0';
			const char* winning_move = winning_moves[i];

			for (int j = 0; j < grid_size; j++) {
				char character = winning_move[j];

				int number = character - '0';
				int grid_space = number - 1;

				Position pos = getCoords(grid_space);
				char grid_char = grid[pos.x][pos.y];

				if (previous_grid == '0') {
					previous_grid = grid_char;
				}
				else if (previous_grid == grid_char) {
					continue;
				}
				else {
					winner = false;
					break;
				}
			}

			if (winner) {
				return true;
			}
		}
		return false;
	}

	void compute_player_turn(vector<int> availableMutations) {
		int computer_position = (rand() % availableMutations.size()) + 1;
		int index = computer_position - 1;
		Position pos = getCoords(availableMutations[index]);
		
		int computer_char = (rand() % 2) + 1;
		char computer_pick;

		if (computer_char == 1) {
			computer_pick = 'X';
		}
		else {
			computer_pick = 'O';
		}

		printf("Computer picked %c, (%d; %d)", computer_pick, pos.x, pos.y);
		grid[pos.x][pos.y] = computer_pick;
	}

	vector<int> getPossibleMutations() {
		vector<int> indexArray;
		for (int i = 1; i <= (grid_size * grid_size); i++) {
			Position pos = getCoords(i);
			char charAtPos = grid[pos.x][pos.y];
			if (charAtPos == 'X' || charAtPos == 'O') {
				continue;
			}
			else {
				indexArray.push_back(i);
			}
		}
		return indexArray;
	}

	Position getCoords(int number) {
		Position pos(number);
		return pos;
	}

	Game() {
		generate_grid();
	}
};

int main(int argc, char *argv[]) {
	Game game;
	int turn = 0;

	while (!game.check_for_wins()) {
		game.show_grid();
		vector<int> availableMutations = game.getPossibleMutations();
		if (turn > 0 && availableMutations.size() > 0) {
			puts("Computer's turn, press an key to continue.");
			cin.ignore();
			game.compute_player_turn(availableMutations);
		}
		game.show_grid();
		game.ask_turn();
		turn++;
	}
	puts("To exit, press any key.");
	cin.ignore();
	return 0;
}
