#include<SFML\Graphics.hpp>
#include<Windows.h>
#include"Functions.cpp"
#include"textBox.cpp"
#include"screenButton.cpp"
#include<iostream>

using namespace sf;
using namespace std;

// Creates a loop that displays a pause screen until the game is unpaused.
// It continuously checks for user input to resume the game or close the window.
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

int main() {
	//	Renders the main window.
	RenderWindow window(VideoMode(400, 400), "BOMBBRUSHER");

	//	Code that runs the easy mode of the game.
	//  openEasyModeWindow is a lambda function.
	auto openEasyModeWindow = [&]() {
		//	Renders the easy game mode.
		RenderWindow easyGameWindow(VideoMode(340, 400), "BOMBBRUSHER");
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

	auto openMediumModeWindow = [&]() {
		//	Renders the easy game mode.
		RenderWindow mediumGameWindow(VideoMode(500, 540), "BOMBBRUSHER");
		Event event;

		Game* play = new Game(15);

		while (mediumGameWindow.isOpen()) {
			while (mediumGameWindow.pollEvent(event)) {
				if (event.type == Event::Closed) {
					mediumGameWindow.close();
				}
				mediumGameWindow.clear();
				play->gamecontroller(&mediumGameWindow);
				if (play->gameRunner == false) {
					Pause(true, &mediumGameWindow, play, event);
					delete play;
					play = new Game(15);
					play->gameRunner = true;
				}
				mediumGameWindow.display();
			}
		}
	};

	auto openHardModeWindow = [&]() {
		//	Renders the easy game mode.
		RenderWindow HardGameWindow(VideoMode(660, 700), "BOMBBRUSHER");
		Event event;

		Game* play = new Game(20);

		while (HardGameWindow.isOpen()) {
			while (HardGameWindow.pollEvent(event)) {
				if (event.type == Event::Closed) {
					HardGameWindow.close();
				}
				HardGameWindow.clear();
				play->gamecontroller(&HardGameWindow);
				if (play->gameRunner == false) {
					Pause(true, &HardGameWindow, play, event);
					delete play;
					play = new Game(20);
					play->gameRunner = true;
				}
				HardGameWindow.display();
			}
		}
	};

	//	Opens highscore game mode window.
	auto openHighScoreWindow = [&](RenderWindow& mainWindow) {
		//	Renders the highscore game mode.
		RenderWindow HighScoreWindow(VideoMode(600, 600), "BOMBBRUSHER");
		Event event;

		ScreenButton backButton(Vector2f(210, 500), Vector2f(200, 50), "Back", [&]() {	//	Object of back button.
			cout << "Back button clicked!\n";
			HighScoreWindow.close();
			mainWindow.create(VideoMode(400, 400), "BOMBBRUSHER");
			});

		ScreenButton easyButton(Vector2f(10, 50), Vector2f(180, 50), "Easy", []() {  	//	Object of easy difficulty button.
			cout << "Easy button clicked!\n";
		});

		ScreenButton mediumButton(Vector2f(210, 50), Vector2f(180, 50), "Medium", []() {   	//	Object of medium difficulty button.
			cout << "Medium button clicked!\n";
		});

		ScreenButton hardButton(Vector2f(410, 50), Vector2f(180, 50), "Hard", []() {	//	Object of hard difficulty button.
			cout << "Hard button clicked!\n";
		});

		while (HighScoreWindow.isOpen()) {
			while (HighScoreWindow.pollEvent(event)) {
				if (event.type == Event::Closed) {
					HighScoreWindow.close();
				}

				// Handles button clicks.
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						Vector2f mousePos = HighScoreWindow.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
						// Handle button click.
						if (backButton.contains(mousePos)) {
							backButton.handleClick();
						}
						else if (easyButton.contains(mousePos)) {
							easyButton.handleClick();
						}
						else if (mediumButton.contains(mousePos)) {
							mediumButton.handleClick();
						}
						else if (hardButton.contains(mousePos)) {
							hardButton.handleClick();
						}
					}
				}

				// Gets mouse position
				Vector2f mousePos = HighScoreWindow.mapPixelToCoords(Mouse::getPosition(HighScoreWindow));

				HighScoreWindow.clear(Color::White);
				// Handle hover effect for buttons.
				backButton.handleHover(mousePos);
				easyButton.handleHover(mousePos);
				mediumButton.handleHover(mousePos);
				hardButton.handleHover(mousePos);

				// Draw the button
				backButton.draw(HighScoreWindow);
				easyButton.draw(HighScoreWindow);
				mediumButton.draw(HighScoreWindow);
				hardButton.draw(HighScoreWindow);

				//	Display window.
				HighScoreWindow.display();
			}
		}
	};

	//	Code for the difficulty selection window. 
	auto openSelectDifficultyWindow = [&](RenderWindow& mainWindow) {
		// Closes the main window.
		window.close();
		RenderWindow selectDifficultyWindow(VideoMode(800, 600), "BOMBBRUSHER");

		// Create the high score button outside of the lambda function
		ScreenButton easyDifficultyButton(Vector2f(300, 150), Vector2f(200, 50), "Easy", [&]() {  	//	Object of easy difficulty button.
			cout << "Easy button clicked!\n";
			selectDifficultyWindow.close();
			openEasyModeWindow();
			});

		ScreenButton mediumDifficultyButton(Vector2f(300, 250), Vector2f(200, 50), "Medium", [&]() {  	//	Object of medium difficulty button.
			cout << "Medium button clicked!\n";
			selectDifficultyWindow.close();
			openMediumModeWindow();
			});

		ScreenButton hardDifficultyButton(Vector2f(300, 350), Vector2f(200, 50), "Hard", [&]() {  	//	Object of hard difficulty button.
			cout << "Hard button clicked!\n";
			selectDifficultyWindow.close();
			openHardModeWindow();
			});

		ScreenButton backButton(Vector2f(300, 450), Vector2f(200, 50), "Back", [&]() {		  	//	Object of back difficulty button.
			cout << "Back button clicked!\n";
			selectDifficultyWindow.close();
			mainWindow.create(VideoMode(400, 400), "BOMBBRUSHER");
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

	//	This loop is running the home window.
	while (window.isOpen()) {
		TextBox textBox(Vector2f(5, 35), Vector2f(400, 150));
		textBox.setTexture();
		// Create the play button.
		ScreenButton playbutton(Vector2f(100, 200), Vector2f(200, 50), "Play", [&]() {
			cout << "Play was pressed" << endl;
			openSelectDifficultyWindow(window);
			});

		// Create the high score button.
		ScreenButton highScoreButton(Vector2f(100, 300), Vector2f(200, 50), "High Score", [&]() {
			cout << "High Score button clicked!\n";
			window.close();
			openHighScoreWindow(window);
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