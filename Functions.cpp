#include"Tile.cpp"
#include<SFML\Graphics.hpp>
#include<Windows.h>

class Board {
protected:
	mouseClick click;
	Button** buttons;
	Mine** mine;
	int** board;
	const int x_offset = 10, y_offset = 10, spacing_factor = 32;
	int x, y;
	int total_mines = 0;
	Vector2f mousePos;
	int difficulty;
	bool firstClick = true;

public:
	Board(int difficulty = 10) {
		int numberOfMines;
		this->difficulty = difficulty;

		srand(time(0));
		allocateMemory();
		Initialize_button();
	}
	void allocateMemory() {
		buttons = new Button * [difficulty];
		mine = new Mine * [difficulty];
		board = new int* [difficulty];
		for (int i = 0; i < difficulty; i++) {
			buttons[i] = new Button[difficulty];
			mine[i] = new Mine[difficulty];
			board[i] = new int[difficulty];
		}
	}
	void Initialize_button() {
		int coor_x = x_offset;
		int coor_y = y_offset;
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				mine[i][j] = SPACE;
				buttons[i][j].setPosition(coor_x, coor_y);
				buttons[i][j].setButtonState(IDLE);
				coor_x += spacing_factor;
			}
			coor_y += spacing_factor;
			coor_x = x_offset;
		}
	}
	void Randomize_mines() {
		int numberOfMines;
		switch (difficulty) {
		case 10:
			numberOfMines = 20;
			break;
		case 15:
			numberOfMines = 30;
			break;
		case 20:
			numberOfMines = 40;
			break;
		}
		while (total_mines < numberOfMines) {
			int i = rand() % difficulty;
			int j = rand() % difficulty;
			if (mine[i][j] != MINE && !(i == x && j == y)) {
				mine[i][j] = MINE;
				total_mines++;
			}
		}
	}

	void Initialize_board() {
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				if (mine[i][j] == SPACE) {
					board[i][j] = 0;
					for (int k = -1; k <= 1; k++) {
						for (int l = -1; l <= 1; l++) {
							int y = j + k;
							int x = i + l;
							if (x >= 0 && x < difficulty && y >= 0 && y < difficulty && mine[x][y] == MINE) {
								board[i][j]++;
							}
						}
					}
				}
			}
		}
	}

	void Print(RenderWindow* window) {
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				if (buttons[i][j].getButtonState() == USED && mine[i][j] != MINE)
					buttons[i][j].updateTexture_Revealed();
				buttons[i][j].RenderButton(window);

				if (buttons[i][j].getButtonState() == USED)
					buttons[i][j].UpdateText(board[i][j], window);
			}
		}
	}

	void assignCoordinates(RenderWindow* window) {
		int numberOfMines;
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				click = buttons[i][j].Click(Vector2f(static_cast<float>(Mouse::getPosition(*window).x), static_cast<float>(Mouse::getPosition(*window).y)));
				if (click != I) {
					x = buttons[i][j].getIndex_x(x_offset, spacing_factor);
					y = buttons[i][j].getIndex_y(y_offset, spacing_factor);
					return;
				}
			}
		}

	}

	~Board() {
		for (int i = 0; i < difficulty; i++) {
			delete[] buttons[i];
			delete[] mine[i];
			delete[] board[i];
		}
		delete[] buttons;
		delete[] mine;
		delete[] board;
	}
};

class bombCheck : public Board {
protected:
	int choice;

public:
	bombCheck(int difficulty = 10) : Board(difficulty) {}
	bool gameRunner = true;
	void checkEmpty() {

	}
	int checkMine() {
		int mine_counter = 0;
		if (mine[x][y] == SPACE && buttons[x][y].getButtonState() == USED) {
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					int i = x + k;
					int j = y + l;
					if (i >= 0 && i < difficulty && j >= 0 && j < difficulty && mine[i][j] == MINE) {
						mine_counter++;
					}
				}
			}
			return mine_counter;
		}
		else {
			return 9;
		}
	}

	int checkFlag() {
		int flag_Counter = 0;
		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				int i = x + k;
				int j = y + l;
				if (i >= 0 && i < difficulty && j >= 0 && j < difficulty) {
					if (buttons[i][j].getButtonState() == ACTIVE) {
						flag_Counter++;
					}
				}
			}
		}
		return flag_Counter;
	}

	void placeFlag() {
		if (mine[x][y] == MINE) {
			total_mines--;
			mine[x][y] = FLAG;
		}
		buttons[x][y].setButtonState(ACTIVE);
	}

	void removeFlag() {
		if (buttons[x][y].getButtonState() == ACTIVE) {
			buttons[x][y].setButtonState(IDLE);
			if (mine[x][y] == FLAG) {
				total_mines++;
				mine[x][y] = MINE;
			}
		}
	}

	void lose() {
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				if (mine[i][j] == MINE)
					buttons[i][j].updateTexture_Mine();
			}
		}
		buttons[x][y].updateTexture_Exploded();
		gameRunner = false;
	}

	void win() {
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				if (buttons[i][j].getButtonState() != ACTIVE)
					buttons[i][j].setButtonState(USED);
			}
		}
		gameRunner = false;
	}

	void revealSpace() {
		if (mine[x][y] == MINE) {
			buttons[x][y].setButtonState(USED);
			lose();
		}
		else if (mine[x][y] == SPACE) {
			buttons[x][y].setButtonState(USED);
		}
	}

	void expandSpace(RenderWindow* window) {
		int mine_Counter = checkMine();
		int flag_Counter = checkFlag();
		if (mine_Counter == 0) {
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					int i = x + k;
					int j = y + l;
					if (i >= 0 && i < difficulty && j >= 0 && j < difficulty) {
						if (buttons[i][j].getButtonState() != ACTIVE) {
							buttons[i][j].setButtonState(USED);

						}
					}
				}
			}
		}
		else if (flag_Counter == board[x][y] && mine_Counter <= flag_Counter && mine_Counter > 0) {
			lose();
		}
	}
};

class Game : public bombCheck {
public:
	Game(int difficulty = 10) : bombCheck(difficulty) {}
	void gamecontroller(RenderWindow* window) {
		click = I;
		Print(window);
		assignCoordinates(window);

		if (click != I)
			Sleep(30);
		if (firstClick) {
			Randomize_mines();
			Initialize_board();
			firstClick = false;
		}
		switch (click) {
		case L:
			if (buttons[x][y].getButtonState() == USED)
				expandSpace(window);
			else if (buttons[x][y].getButtonState() == IDLE) {
				revealSpace();
				buttons[x][y].setButtonState(USED);
			}
			break;
		case R:
			if (buttons[x][y].getButtonState() == ACTIVE)
				removeFlag();
			else if (buttons[x][y].getButtonState() == IDLE)
				placeFlag();
			break;
		}
		if (total_mines == 0)
			win();
		return;
	}
};
