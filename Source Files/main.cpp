/*
	Made by Giorgio Cassata and Ian martin 
	Super Space Game (Copyright 2018)

	**=======================================**
     _____  __    __  ______   _____   _____
    //      ||    ||  ||   \\  ||  \\  ||  \\
    \\____  ||    ||  ||___//  ||___   ||__//
         \\ ||    ||  ||       ||      ||  \\
    _____//  \\__//   ||       ||___// ||   \\

     _____      ______     ___	     _____   _____
    //          ||   \\   // \\	    //	 \\  ||  \\
    \\____	||___//  //___\\   ||        ||___
         \\	||      //     \\  ||        ||
    _____//	||     //       \\  \\____// ||___//

     _____	 ___      __      __  _____
    //   \\     // \\     ||\    /||  ||  \\
   ||   ____   //___\\    || \  / ||  ||___
   ||     ||  //     \\   ||  \/  ||  ||
    \\___//  //       \\  ||      ||  ||___//

	**=======================================**

	not all of these sfml things are used yet, but they
	might at some point so here they are just in case...
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


//player class.
//This should be moved into its own file eventually
//player movement mechanic is temporary:
//idealy left and right keypresses would rotate and
//up would be forward in direction player is facing
class player{
	public:
		void PrintStats();
		sf::CircleShape Disp();

		void InputVel(float velX, float velY);
		void VelDamp();
		void UpdatePos(int width, int height);
		vector<int> GetPos();
	private:
		float _radius = 10;
		int _posX = 0;
		int _posY = 0;
		float _velX = 0;
		float _velY = 0;
		float _maxVel = 12.0;
		float _threshhold = 0.02;
		
};

//player class functions below would also have their own file eventually

//prints the velocity vector of the player
void player::PrintStats() {
	cout << '(' << _velX << ", " << _velY << ')' << endl;
}

//creation of player sprite to be drawn
sf::CircleShape player::Disp() {
	sf::CircleShape shape(_radius);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(_posX, _posY);
	return shape;
}

//adds input to velocity given the velocity does not exceed a maximum threshhold
void player::InputVel(float velX, float velY) {
	if (_velX < _maxVel && _velX > -_maxVel) {
		_velX += velX;
	}
	if (_velY < _maxVel && _velY > -_maxVel) {
		_velY += velY;
	}
}

//reduces the velocity by a small increment
void player::VelDamp() {
	if (_velX > _threshhold) {
		_velX -= 0.1;
	}
	else if (_velX < -_threshhold) {
		_velX += 0.1;
	}
	else {
		_velX = 0;
	}
	if (_velY > _threshhold) {
		_velY -= 0.1;
	}
	else if (_velY < -_threshhold) {
		_velY += 0.1;
	}
	else {
		_velY = 0;
	}
}

//combination update position and keep within window
void player::UpdatePos(int width, int height) {
	if (_posX < 0 || _posX > width - (2 * _radius)){
		_velX = -_velX;
	}
	if (_posY < 0 || _posY > height - (2 * _radius)) {
		_velY = -_velY;
	}
	_posX += _velX;
	
	_posY += _velY;
}

//end of player class funcitons



int main() {
	//window arguments
	const int windowWidth = 640;
	const int windowHeight = 400;
	const string windowTitle = "Super Space Game";

	//render window
    sf::RenderWindow game(sf::VideoMode(windowWidth, windowHeight), windowTitle);
	
	//define clock
	sf::Clock clock;
	

	//game settings
	game.setFramerateLimit(60); // Limit frames per second
	game.setVerticalSyncEnabled(false); // False by default
	//antialiasing is possible

	//birth player1 into this cruel world
	player player1;

	//game loop 
    while (game.isOpen()) {
        
		//process events
		sf::Event event;
		while (game.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {
						//primary click
						
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
					//does no create output when mouse is stationary
					//event.mouseMove.x
					//event.mouseMove.y
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

		/*
			Keypresses are outside of events because keys used to 'stick'
			mouse movement, mouse clicks, and mouse scrolls might also not
			work properly. Maybe try moving them around like I did with
			the keypresses.
		*/

		//uses keypresses to control player1
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player1.InputVel(-0.4, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player1.InputVel(0.4, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player1.InputVel(0, -0.4);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player1.InputVel(0, 0.4);
		}

		//player1.PrintStats();		//for debugging
		
		player1.VelDamp();
		player1.UpdatePos(windowWidth, windowHeight);

		//clear --> draw --> display
        game.clear();
        game.draw(player1.Disp());
        game.display();


		// Get elapsed time since last loop
		sf::Time elapsed1 = clock.getElapsedTime();
		float FrameRate = 1.f / elapsed1.asSeconds();
		clock.restart();
		//cout << FrameRate << endl;	//for debugging

    }

    return 0;
}
