#include<SFML\Graphics.hpp>
#include<Windows.h>
#include"Functions.cpp"
#include"textBox.cpp"
#include"screenButton.cpp"
#include<iostream>

using namespace sf;
using namespace std;

void Pause(bool game_pause, RenderWindow* window, Game* play, Event event) {
	while (game_pause) {
		window->clear();
		play->Print(window);
		window->display();
		if (event.type == Event::Closed) {
			window->close();
		}
		if (Keyboard::isKeyPressed(Keyboard::P)) {
			game_pause = false;
			return;
		}
	}
}
 
int main(){
	//	Renders the main window.
	RenderWindow window(VideoMode(800, 600), "BOMBBRUSHER");

	//	Code that runs the easy mode of the game.
	auto openEasyModeWindow = [&]() {
		//	Renders the easy game mode.
		RenderWindow easyGameWindow(VideoMode(340, 340), "BOMBBRUSHER");
		Event event;

		Game* play = new Game;

		while (easyGameWindow.isOpen()) {
			while (easyGameWindow.pollEvent(event)) {
				if (event.type == Event::Closed) {
					easyGameWindow.close();
				}
				easyGameWindow.clear();
				play->gamecontroller(&easyGameWindow);
				if (play->gameRunner == false) {
					Pause(true, &easyGameWindow, play, event);
					delete play;
					play = new Game;
					play->gameRunner = true;
				}
				easyGameWindow.display();
			}
		}
	};
	//	This is test.
	//	Code for the difficulty selection window. 
	auto openSelectDifficultyWindow = [&](RenderWindow& mainWindow) {
		// Closes the main window.
		window.close();
		RenderWindow selectDifficultyWindow(VideoMode(800, 600), "BOMBBRUSHER");

		// Create the high score button outside of the lambda function
		ScreenButton easyDifficultyButton(Vector2f(300, 150), Vector2f(200, 50), "Easy", [&]() {
			cout << "Easy button clicked!\n";
			selectDifficultyWindow.close();
			openEasyModeWindow();
			});

		ScreenButton mediumDifficultyButton(Vector2f(300, 250), Vector2f(200, 50), "Medium", []() {
			cout << "Medium button clicked!\n";
			});

		ScreenButton hardDifficultyButton(Vector2f(300, 350), Vector2f(200, 50), "Hard", []() {
			cout << "Hard button clicked!\n";
			});

		ScreenButton backButton(Vector2f(300, 450), Vector2f(200, 50), "Back", [&]() {
			cout << "Back button clicked!\n";
			selectDifficultyWindow.close();
			mainWindow.create(VideoMode(800, 600), "BOMBBRUSHER");
			});

		while (selectDifficultyWindow.isOpen()) {
			Event event;
			TextBox textBox(Vector2f(250, 50), Vector2f(300, 50), "Diffculty Selection");

			while (selectDifficultyWindow.pollEvent(event)) {
				if (event.type == Event::Closed)
					selectDifficultyWindow.close();

				// Handles button clicks.
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						Vector2f mousePos = selectDifficultyWindow.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
						// Handle easyButton click.
						if (easyDifficultyButton.contains(mousePos)) {
							easyDifficultyButton.handleClick();
						}
						// Handle mediumButton click.
						else if (mediumDifficultyButton.contains(mousePos)) {
							mediumDifficultyButton.handleClick();
						}
						// Handle hardButton click.
						else if (hardDifficultyButton.contains(mousePos)) {
							hardDifficultyButton.handleClick();
						}
						// Handle backButton click.
						else if (backButton.contains(mousePos)) {
							backButton.handleClick();
						}
					}
				}

				// Gets mouse position
				Vector2f mousePos = selectDifficultyWindow.mapPixelToCoords(Mouse::getPosition(selectDifficultyWindow));

				// Handle hover effect for buttons.
				easyDifficultyButton.handleHover(mousePos);
				mediumDifficultyButton.handleHover(mousePos);
				hardDifficultyButton.handleHover(mousePos);
				backButton.handleHover(mousePos);

				//	Needs to be here, as if it is after Draw, it will hide buttons.
				selectDifficultyWindow.clear(Color::White);

				// Draw the button
				easyDifficultyButton.draw(selectDifficultyWindow);
				mediumDifficultyButton.draw(selectDifficultyWindow);
				hardDifficultyButton.draw(selectDifficultyWindow);
				backButton.draw(selectDifficultyWindow);
				textBox.draw(selectDifficultyWindow);

				//	Display window.
				selectDifficultyWindow.display();
			}
		}
	};

	//	This loop is running the main window.
	while (window.isOpen()) {
		TextBox textBox(Vector2f(300, 100), Vector2f(200, 40), "BOMBBRUSHER");

		// Create the play button.
		ScreenButton playbutton(Vector2f(300, 200), Vector2f(200, 50), "Play", [&]() {
			openSelectDifficultyWindow(window);
		});

		// Create the high score button.
		ScreenButton highScoreButton(Vector2f(300, 300), Vector2f(200, 50), "High Score", [](){
			cout << "High Score button clicked!\n";
		});

		//	Running the main window.
		while (window.isOpen()) {
			// Process events
			Event event;

			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)   
					window.close();
				 
				//	Handles button click for main window.
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
						//	Runs when "Play" on main screen is clicked.
						if (playbutton.contains(mousePos)) {
							playbutton.handleClick();
						}
						//	Runs when "High Score" on main screen is clicked.
						else if (highScoreButton.contains(mousePos)) {
							highScoreButton.handleClick();
						}
					}
				}
			}

			window.clear(Color::White);

			// Get mouse position
			Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

			// Handle hover effect for button.
			highScoreButton.handleHover(mousePos);
			playbutton.handleHover(mousePos);
			 
			// Draw all the buttons and the text box.
			textBox.draw(window);
			playbutton.draw(window);
			highScoreButton.draw(window);

			window.display(); 
		} 
	}
}