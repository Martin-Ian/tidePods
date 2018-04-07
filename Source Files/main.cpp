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


int main() {
	//define stuff
    sf::RenderWindow game(sf::VideoMode(640, 400), "tidePods");
	sf::Clock clock;
	
	//game settings
	game.setFramerateLimit(120); // Limit to 60 frames per second
	game.setVerticalSyncEnabled(false); // False by default

	// a sample shape
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    while (game.isOpen()) {
		//process events
        sf::Event event;
        while (game.pollEvent(event)) {
			//close window
            if (event.type == sf::Event::Closed)
                game.close();
        }

		// Get elapsed time since last loop
		sf::Time elapsed1 = clock.getElapsedTime();
		float FrameRate = 1.f / elapsed1.asSeconds();
		std::cout << FrameRate << std::endl;
		clock.restart();


		//clear --> draw --> display
        game.clear();
        game.draw(shape);
        game.display();
    }

    return 0;
}