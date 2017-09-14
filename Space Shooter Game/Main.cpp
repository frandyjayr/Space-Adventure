#include <memory>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "Command.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "LoseScreen.hpp"
#include "Menu.hpp"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800, 800, 32), "Space Shooter");
	Command	command(window);

	while (command.gameWindowIsOpen())
	{
		std::unique_ptr<GameState> menu(new Menu(window));
		menu->run();
		std::unique_ptr<GameState> game(new Game(window));
		game->run();
		std::unique_ptr<GameState> loseScreen(new LoseScreen(window));
		loseScreen->run();
	}
	return 0;
}