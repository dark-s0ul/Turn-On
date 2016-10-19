#include <iostream>
#include <string>

using namespace std;

char **table;
unsigned moves;
unsigned table_size = 0;

void init() {
	table = new char*[table_size];
	for (int i = 0; i < table_size; i++) {
		table[i] = new char[table_size];
	}
}

void reset() {
	moves = 0;

	for (int i = 0; i < table_size; i++) {
		memset(table[i], 0, table_size);
	}
}

void clear() {
	for (int i = 0; i < table_size; i++) {
		delete [] table[i];
	}
	delete[] table;
}

char check() {
	for (int i = 0; i < table_size; i++) {
		for (int j = 0; j < table_size; j++) {
			if (table[i][j] == 0) { return 0; }
		}
	}
	return 1;
}

#define range(value, min, max) (min <= value && value <= max)
void reverse(int x, int y) {
	if (!range(x, 0, table_size - 1) || !range(y, 0, table_size - 1)) { return; }
	table[x][y] = table[x][y] == 0 ? 1 : 0;
}

void help() {
	system("cls");
	printf("'h' - show help\n'~' - reset table\n'~1-9' - resize table\n'!' - reverse table\n'e' - exit\n");
	system("pause");
}

void draw() {
	system("cls");
	printf("   ");
	for (int i = 1; i <= table_size; i++) {
		printf("  %c ", i + 96);
	}
	printf("\n");
	for (int i = 0; i < table_size; i++) {
		printf("   |");
		for (int i = 0; i < table_size; i++) {
			printf("---|");
		}
		printf("\n");
		printf(" %i ", i + 1);
		for (int j = 0; j < table_size; j++) {
			printf("| %c ", table[i][j] == 1 ? 'X' : ' ');
		}
		printf("|\n");
	}
	printf("   |");
	for (int i = 0; i < table_size; i++) {
		printf("---|", i);
	}
	printf("\n");
}

void read() {
	string input;
	
	printf("Moves: %u\nPlease enter your move: ", moves);
	getline(cin, input);

	if (input.length() == 0) return;

	if (input[0] == '~') {
		int size = atoi(input.c_str() + 1);
		if (range(size, 1, 9)) { table_size = size; }

		reset();
		return;
	}

	if (input == "!") {
		for (int i = 0; i < table_size; i++) {
			for (int j = 0; j < table_size; j++) {
				table[i][j] = table[i][j] == 0 ? 1 : 0;
			}
		}
		return;
	}
	if (input == "h") {
		help();
		return;
	}
	if (input == "e") {
		clear();
		exit(0);
	}

	if (input.length() != 2) { return; }

	int x = input[0] - '1';
	int y = input[1] - 'a';

	if (!range(x, 0, table_size - 1) || !range(y, 0, table_size - 1)) { return; }

	moves++;

	reverse(x, y);
	reverse(x - 1, y);
	reverse(x + 1, y);
	reverse(x, y - 1);
	reverse(x, y + 1);
}

int main() {
	table_size = 5;
	init();
	help();

	while (true) {
		reset();

		while (check() == 0) {
			draw();
			read();
		}
		draw();
		printf("\nCongratulations!\nMoves: %u!\n", moves);
		system("pause");
	}
}
