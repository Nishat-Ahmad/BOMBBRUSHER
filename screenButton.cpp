#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

using namespace sf;
using namespace std; 

//  Has the code of buttons on the main screen.
class ScreenButton{
private:
    RectangleShape shape;
    Text text;
    Font font;
    function<void()> onClick;   //  It represents a general-purpose, type-safe function wrapper. You can attach any functinoality with onclick.
    Color hoverColor;
    Color defaultColor;

public:
    ScreenButton(Vector2f position, Vector2f size, const string& buttonText, function<void()> onClickFunc, 
        Color defaultCol = Color::Transparent, Color hoverCol = Color::Cyan) : defaultColor(defaultCol), hoverColor(hoverCol) {

        if (!font.loadFromFile("minecraft_font.ttf")) {
            cerr << "Error loading font\n";
        }

        // Set up text
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setString(buttonText);

        // Center text within the button
        FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);   //  x, y axis
        text.setPosition(position + size / 2.0f);

        // Set up shape
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(defaultColor);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color::Black);

        onClick = onClickFunc;
    }

    void draw(RenderWindow& window) {   //  Draws shape and text on the window.
        window.draw(shape);
        window.draw(text);
    }

    bool contains(Vector2f point) {     //  Determines whether a given point is inside a shape by checking if the shape's bounding rectangle contains that point.
        return shape.getGlobalBounds().contains(point);
    }

    void handleClick() {                //  Handles what happen on click.
        if (onClick) {
            onClick();
        }
    }

    void handleHover(Vector2f mousePos) {   //  Changing colour when the mouse is inside the bound of the shape.
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(hoverColor);
        }
        else {
            shape.setFillColor(defaultColor);
        }
    }
};