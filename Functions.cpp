#include"Tile.cpp"
#include<SFML\Graphics.hpp>
#include<Windows.h>

// -------Utilizing multi-level inheritance-------
// class to initialize the main board of the game
class Board {
protected:
	mouseClick click;	// instance of enum mouseClick
	Button** buttons;	// double pointer object of Button type to create a 2d dynamic array.
	Mine** mine;		// double pointer of enum Mine type to create a 2d dynamic array. 
	int** board;		// double pointer of int type to create a 2d dynamic array.
	const int x_offset = 10, y_offset = 10, spacing_factor = 32;	// constant x and y distance from the left and upper window edges and the spacing between each tile
	int x, y;			// variables to hold indexes of the clicked button		
	int total_mines = 0; // initializing total mines
	Vector2f mousePos;  // variable to hold the current position of mouse. Vector2f being a 2 dimensional float carrying type.
	int difficulty;		// difficulty variable that tells the difficulty as well as the tiles generated
	bool firstClick = true; // boolean that runs for the first click to ensure that a mine is not placed on the first click

public:

// Parameterized constructor with default parameter of difficulty = 10
	Board(int difficulty = 10) {
		this->difficulty = difficulty;

		srand(time(0));
		allocateMemory();
		Initialize_button();
	}

// Dynamically allocates memory to all the double pointers created
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

// Initializes button by setting their position accordingly
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

// Function to generate mines at the start
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

// Function to initialize values to mine and board arrays
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

// Function to print the board after every iteration
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

// Function to assign coordinates to x and y upon click according to the mouse's position
	void assignCoordinates(RenderWindow* window) {
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

// Virtual destruction to safely deallocate the memory when an object is deleted.
	virtual ~Board() {
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

// Class that holds all the backend functionality of the game when its running
class bombCheck : public Board {
protected:
	int choice;

public:
	bombCheck(int difficulty = 10) : Board(difficulty) {}
	bool gameRunner = true;

// Checks the number of mines around a tile when expandSpace function is called
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

// Checks the number of flags around the tile when expandSpace function is called
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

// Function to place flag on button click
	void placeFlag() {
		if (mine[x][y] == MINE) {
			total_mines--;
			mine[x][y] = FLAG;
		}
		buttons[x][y].setButtonState(ACTIVE);
	}

// Function to remove an already placed flag
	void removeFlag() {
		if (buttons[x][y].getButtonState() == ACTIVE) {
			buttons[x][y].setButtonState(IDLE);
			if (mine[x][y] == FLAG) {
				total_mines++;
				mine[x][y] = MINE;
			}
		}
	}

// Post-game function that indicates loss
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

// Post-game funciton that indicates win
	void win() {
		for (int i = 0; i < difficulty; i++) {
			for (int j = 0; j < difficulty; j++) {
				if (buttons[i][j].getButtonState() != ACTIVE)
					buttons[i][j].setButtonState(USED);
			}
		}
		gameRunner = false;
	}

// Function that reveals a Space if there are no more MINES left around the tile
	void revealSpace() {
		if (mine[x][y] == MINE) {
			buttons[x][y].setButtonState(USED);
			lose();
		}
		else if (mine[x][y] == SPACE) {
			buttons[x][y].setButtonState(USED);
		}
	}

// Function that Expands the space in the tile's radius if the condition is true
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

// Main gameplay class that integrates all the functions in one place and keeps the game running
class Game : public bombCheck {
public:
// Parameterized constructor
	Game(int difficulty = 10) : bombCheck(difficulty) {}

// Function to keep all the functions in one place and check the click conditions to run them accordingly
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
