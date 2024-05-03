#include <iostream>
#include "functions.cpp"


#include<SFML\Graphics.hpp>
#include"Functions.cpp"

using namespace std;
using namespace sf;


int main(){
    bombCheck C;
    C.gameController();
}

int main() {
	RenderWindow window(VideoMode(800, 600), "Title");
	Event event;

	Game play;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			window.clear();
			play.gamecontroller(&window);
			if (play.gameRunner == false) {
				window.close();
				break;
			}
			window.display();
		}
	}
}