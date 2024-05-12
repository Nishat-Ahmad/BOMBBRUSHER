#include<SFML\Graphics.hpp>
using namespace sf;

enum mouseClick { L, R, I };			// 3 states of mouseClick L = Left click, R = Right click, I = IDLE/noclick
enum btnState { IDLE, ACTIVE, USED };   // 3 states of button IDLE = Tile, Active = Flag, Used = revealed
enum Mine { MINE, SPACE, FLAG };		// 3 states of mine MINE = mine, SPACE = emptyspace FLAG = flag

class Button {
private:
	// Using a rectangle for tile
	RectangleShape shape;
	// pos_x and pos_y store the place of tile placed from left and upper borders of the windo
	int pos_x, pos_y;
	btnState btn_state;

	// All the textures for the Tile
	Texture T_Mine;
	Texture T_Exploded_Mine;
	Texture T_Tile;
	Texture T_Click_Hold;
	Texture T_Revealed;
	Texture T_Flag;

	// For the numbers shown on the Space tiles
	Text text;
	Font font;
public:

	// Main constructor for the Tile
	Button(){
		// Initializes the position to 0
		this->shape.setPosition(0, 0);
		// Initalizes the size to 30 x 30
		this->shape.setSize(Vector2f(30, 30));

		// Pre-loads all the textures
		T_Tile.loadFromFile("images/Tile.png");
		T_Revealed.loadFromFile("images/Tile_Revealed.png");
		T_Click_Hold.loadFromFile("images/Tile_Hold.png");
		T_Flag.loadFromFile("images/Tile_Flag.png");
		T_Mine.loadFromFile("images/Mine.png");
		T_Exploded_Mine.loadFromFile("images/Mine_exploded.png");

		// Initializes the starting texture
		this->shape.setTexture(&T_Tile);
		// Initializes the position as 0, 0
		this->pos_x = 0;
		this->pos_y = 0;
	}

	// setter function to set Button state
	void setButtonState(btnState btn_state) {
		this->btn_state = btn_state;
	}

	// getter function to get Button state
	btnState getButtonState() {
		return btn_state;
	}

	// setter function to set position of the tiles (used in initialization of the board)
	void setPosition(int x, int y) {
		shape.setPosition(y, x);
		pos_x = y;
		pos_y = x;
	}

	// uses the formula provided to return the x_index of a tile
	int getIndex_x(int starting_pos, int spacing_factor) {
		int temp = (pos_x - starting_pos) / spacing_factor;
		return temp;
	}

	// uses the formula provided to return the y_index of a tile
	int getIndex_y(int starting_pos, int spacing_factor) {
		int temp = (pos_y - starting_pos) / spacing_factor;
		return temp;
	}

	// all the mouse Click events where mousePos is the current mouse position from the left and upper borders of the game window
	mouseClick Click(Vector2f mousePos) {
		if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos)) {
			if (Event::MouseButtonReleased && (btn_state == IDLE || btn_state == USED)) {
				return L;
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && shape.getGlobalBounds().contains(mousePos)) {
			if (Event::MouseButtonReleased && btn_state == IDLE) {
				shape.setTexture(&T_Flag);
				return R;
			}
			else if (Event::MouseButtonReleased && btn_state == ACTIVE) {
				shape.setTexture(&T_Tile);
				return R;
			}
		}
		else
			return I;
	}

	// Draws the button
	void RenderButton(RenderWindow* window) {
		window->draw(this->shape);
	}

	//	Initializes the text 
	void setText(int number_of_mines) {
		switch (number_of_mines) {
		case 1: text.setString("1"); break;
		case 2: text.setString("2"); break;
		case 3: text.setString("3"); break;
		case 4: text.setString("4"); break;
		case 5: text.setString("5"); break;
		case 6: text.setString("6"); break;
		case 7: text.setString("7"); break;
		case 8: text.setString("8"); break;
		}
	}

	// Updates the visual appearance of the button
	void UpdateText(int number_of_mines, RenderWindow* window) {
		if (btn_state == USED) {
			text.setPosition(Vector2f(pos_x + 10, pos_y + 5));
			setText(number_of_mines);
			font.loadFromFile("Fonts/minecraft_font.ttf");
			text.setFont(font);
			text.setCharacterSize(20);
			text.setFillColor(Color::Black);
			text.setOutlineColor(Color::Black);
			text.setStyle(Text::Bold);
			window->draw(text);
		}
	}

	// the functions update the textures accordingly
	void updateTexture_Tile() {
		shape.setTexture(&T_Tile);
	}
	void updateTexture_Revealed() {
		shape.setTexture(&T_Revealed);
	}

	void updateTexture_Exploded() {
		shape.setTexture(&T_Exploded_Mine);
	}

	void updateTexture_Flag() {
		shape.setTexture(&T_Flag);
	}

	void updateTexture_Mine() {
		shape.setTexture(&T_Mine);
	}
};
