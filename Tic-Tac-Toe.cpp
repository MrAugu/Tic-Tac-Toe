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
		printf("   -------------\n");
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

	bool ask_turn(char& userSymbol) {
		printf("[You] Where you woud like to play? ");
		
		string input;
		bool selected = false;

		while (!selected) {
			getline(cin, input);
			if (input != "") {
				char entered = input.c_str()[0];
				if (entered >= '1' && entered <= '9') {
					int entered_number = entered - '0';
					int index = entered_number - 1;

					Position pos = getCoords(index);
					char grid_position = grid[pos.x][pos.y];

					if (grid_position == 'X' || grid_position == 'O') {
						printf("[You] Looks like that grid position has been taken up already, chose another.. ");
					}
					else {
						grid[pos.x][pos.y] = userSymbol;
						selected = true;
					}
				}
				else {
					printf("[You] You have to select a number between 1 and 9.. ");
				}
			}
		}
		return selected;
	}

	char check_for_wins() {
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
		char winnerChar = '0';

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
					winnerChar = previous_grid;
					continue;
				}
				else {
					winner = false;
					break;
				}
			}

			if (winner) {
				return winnerChar;
			}
		}
		return winnerChar;
	}

	void compute_player_turn(vector<int> availableMutations, char& computerSymbol) {
		int computer_position = rand() % availableMutations.size();
		Position pos = getCoords(availableMutations[computer_position] - 1);
		grid[pos.x][pos.y] = computerSymbol;
	}

	vector<int> getPossibleMutations() {
		vector<int> indexArray;
		for (int i = 0; i < (grid_size * grid_size); i++) {
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

	void promptSymbol(char& userSymbol, char& computerSymbol) {
		string choiceInput;

		printf("[You] Choose the sign you want to play, it can be X or O.. ");

		while (userSymbol == '0' || computerSymbol == '0') {
			cin >> choiceInput;
			char choiceCharacter = choiceInput.c_str()[0];

			if (choiceCharacter == 'x' || choiceCharacter == 'X') {
				userSymbol = 'X';
				computerSymbol = 'O';
			}
			else if (choiceCharacter == 'o' || choiceCharacter == 'O') {
				userSymbol = 'O';
				computerSymbol = 'X';
			}
			else {
				printf("[You] Invalid sign, pick again.. ");
			}
		}
		printf("[You] Playing as %c!\n", userSymbol);
		printf("[Computer] Playing as %c!\n", computerSymbol);
	}
};

int main(int argc, char *argv[]) {
	puts("################################################################");
	puts("#                   git:MrAugu/Tic-Tac-Toe                     #");
	puts("#                    Made by MrAugu#7017                       #");
	puts("################################################################");
	printf("\n");

	Game game;
	int turn = 0;
	char userSymbol = '0';
	char computerSymbol = '0';

	game.promptSymbol(userSymbol, computerSymbol);
	cin.ignore();

	char winner = '0';
	vector<int> availableMutations = {0,1,2,3,4,5,6,7,8};

	game.show_grid();
	while (winner == '0' && availableMutations.size() > 0) {
		vector<int> availableMutations = game.getPossibleMutations();
		if (turn > 0) {
			printf("[Computer] Computer's turn, press enter to continue.. ");
			cin.ignore();
			game.compute_player_turn(availableMutations, computerSymbol);
			game.show_grid();
		}
		game.ask_turn(userSymbol);
		game.show_grid();
		turn++;
		winner = game.check_for_wins();
	}

	if (winner == '0') {
		puts("---------- EVEN MATCH ----------");
		puts("Nobody won, there are no more possible mutations. ");
		puts("--------------------------------");
	}
	else if (winner == userSymbol) {
		puts("---------- YOU'VE WON ----------");
		puts("You've won the game, congratulations. ");
		puts("--------------------------------");
	}
	else if (winner == computerSymbol) {
		puts("--------- YOU'VE LOST ----------");
		puts("Looks like you've lost this game?!");
		puts("--------------------------------");
	}

	puts("*** To exit, press any key... ***");
	cin.ignore();
	return 0;
}
