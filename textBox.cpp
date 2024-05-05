#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

class TextBox {
private:
    RectangleShape textBox;
    Text text;
    Font font;

public:
    TextBox(Vector2f position, Vector2f size, const string& prompt) {
        // Load font
        if (!font.loadFromFile("minecraft_font.ttf")) {
            cerr << "Error loading font\n";
        }

        // Set up text
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setString(prompt);
        text.setPosition(position.x + 20, position.y + 10);

        // Set up text box
        textBox.setSize(size);
        textBox.setFillColor(Color::Cyan);
        textBox.setOutlineThickness(2);
        textBox.setOutlineColor(Color::Blue);
        textBox.setPosition(position);
    }

    void draw(RenderWindow& window) {
        window.draw(textBox);
        window.draw(text);
    }
};