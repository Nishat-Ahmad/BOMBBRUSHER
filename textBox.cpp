#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class TextBox {
private:
    //  Making objects of classes.
    RectangleShape textBox;
    Text text;
    Font font;
    Texture texture;

public:
    TextBox(Vector2f position, Vector2f size) {  //  Parameterized constructor for logo on main screen.
        // Load font
        if (!font.loadFromFile("Fonts/minecraft_font.ttf")) {
            cerr << "Error loading font\n";
        }

        // Set up text in the textbox.
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setPosition(position.x + 20, position.y + 10);

        // Set up text box in which text will exist.
        texture.loadFromFile("images/Title.png");
        textBox.setSize(size);
        textBox.setPosition(position);
    }

    TextBox(Vector2f position, Vector2f size, const string& prompt) {   //  Parameterized constructur to set a string inside textbox.
        // Load font
        if (!font.loadFromFile("Fonts/minecraft_font.ttf")) {
            cerr << "Error loading font\n";
        }

        // Set up text
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setString(prompt);
        text.setFillColor(Color::White);
        text.setOutlineThickness(2);
        text.setPosition(position.x + 20, position.y + 10);

        // Set up text box
        texture.loadFromFile("images/Title.png");
        textBox.setSize(size);
        textBox.setPosition(position);
    }

    void draw(RenderWindow& window) {   //  Renders the window.
        window.draw(textBox);
        window.draw(text);
    }

    void setTexture() {                 //  Setting up texture for textbox.
        textBox.setTexture(&texture);
    }
};
