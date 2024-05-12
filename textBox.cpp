#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

class TextBox {
private:
    RectangleShape textBox;
    Text text;
    Font font;
    Texture texture;

public:
    TextBox(Vector2f position, Vector2f size, const string& prompt) {
        // Load font
        if (!font.loadFromFile("minecraft_font.ttf")) {
            cerr << "Error loading font\n";
        }

        // Set up text
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setString(prompt);
        text.setPosition(position.x + 20, position.y + 10);

        // Set up text box
        texture.loadFromFile("images/Title.png");
        textBox.setSize(size);
        textBox.setPosition(position);
    }

    void draw(RenderWindow& window) {
        window.draw(textBox);
        window.draw(text);
    }

    void setTexture() {
        textBox.setTexture(&texture);
    }
};