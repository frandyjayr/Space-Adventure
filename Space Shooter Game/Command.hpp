#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <stdlib.h> 

#include <SFML/Graphics.hpp>

class Command
{
	public:
									Command(sf::RenderWindow& window);
		bool						isPressed();
		void						processKeyBoardEvents();
		void						closeGameWindow();
		sf::Keyboard::Key			giveCommand();
		static bool					gameWindowIsOpen();
	private:

		void						handleKeyBoardInput(sf::Keyboard::Key key, bool isPressed);

	private:
		sf::RenderWindow&			window;
		sf::Keyboard::Key			key;
		bool						pressed;
		static bool					gameIsRunning;

};
#endif
