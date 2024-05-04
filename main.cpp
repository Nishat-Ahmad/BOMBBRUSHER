#include<SFML\Graphics.hpp>
#include<Windows.h>
#include"Functions.cpp"

using namespace sf;

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
	RenderWindow window(VideoMode(340, 340), "BOMBBRUSHER™");
	Event event;

	Game* play = new Game;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			window.clear();
			play->gamecontroller(&window);
			if (play->gameRunner == false) {
				Pause(true, &window, play, event);
				delete play;
				play = new Game;
				play->gameRunner = true;
			}
			window.display();
		}
	}
}