/*
	not all of these sfml things are used yet, but they
	might at some point so here they are.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

//#include "any header files.h"


using namespace std;
using namespace sf;

//process events
void UserInput() {
	while (game.isOpen()) {
		sf::Event event;
		while (game.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//primary click
					posx = event.mouseButton.x;
					posy = event.mouseButton.y;
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					//secondary click
					//event.mouseButton.x
					//event.mouseButton.y
				}
				else if (event.mouseButton.button == sf::Mouse::Middle) {
					//mousewheel click
					//event.mouseButton.x
					//event.mouseButton.y
				}
				break;
			case sf::Event::MouseMoved:
				//event.mouseMove.x
				//event.mouseMove.y
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::W:
					//

					break;
				case sf::Keyboard::A:
					//

					break;
				case sf::Keyboard::S:
					//

					break;
				case sf::Keyboard::D:
					//

					break;
				case sf::Keyboard::Escape:
					//

					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta > 0) {
					//scroll up
				}
				else if (event.mouseWheelScroll.delta < 0) {
					//scroll down
				}
				break;
			case sf::Event::Closed:
				game.close();
				break;
			default:
				break;
			}
		}
	}
}

int main() {
	//define stuff
    sf::RenderWindow game(sf::VideoMode(640, 400), "tidePods");
	sf::Clock clock;
	int posx = 0;
	int posy = 0;

	//game settings
	game.setFramerateLimit(120); // Limit frames per second
	game.setVerticalSyncEnabled(false); // False by default

	// a sample shape
	sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Red);

	sf::Thread thread(&UserInput);
	thread.launch();


    while (game.isOpen()) {
        

		cout << posx << endl;
		cout << posy << endl;

		// Get elapsed time since last loop
		sf::Time elapsed1 = clock.getElapsedTime();
		float FrameRate = 1.f / elapsed1.asSeconds();
		//cout << FrameRate << endl;
		clock.restart();


		//clear --> draw --> display
        game.clear();
        game.draw(shape);
        game.display();
    }

    return 0;
}