#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "SceneNode.hpp"

class ScoreBoard : public SceneNode
{
	public:
											ScoreBoard(sf::RenderWindow& window, ResourceHolder& resourceHolder);
		virtual void						drawCurrent(sf::RenderWindow& window);
		virtual void						updateCurrent(sf::Time deltaTime);
		void								checkLevelChange();

	private:

	private:
		sf::RenderWindow&					window;
		sf::Text							scoreText;
		sf::Text							levelText;
		sf::Clock							clock;
		sf::Time							timer;
		TheGame::Level						gameLevel;
		bool								levelChanged;
		bool								newLevel;
		int									currentLevel;
		std::string							levelInStringForm;
};
#endif
