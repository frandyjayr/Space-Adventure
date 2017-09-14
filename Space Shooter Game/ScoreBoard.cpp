#include "ScoreBoard.hpp"
#include <iostream>

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: The constructor iniitalizes the scoreBoard's text attributes including the font, size, and       *
 * location on the screen. It also initializes the bool variables levelChanged and newLevel to true				 *
 ****************************************************************************************************************/
ScoreBoard::ScoreBoard(sf::RenderWindow& window, ResourceHolder& resourceHolder) : window(window)
{
	scoreText.setFont(resourceHolder.getFont(Fonts::ID::DigitalTech));
	levelText.setFont(resourceHolder.getFont(Fonts::ID::DigitalTech));

	levelChanged = true;
	newLevel = true;

	currentLevel = 1;
	levelInStringForm = "Level 1";
	scoreText.setString(levelInStringForm);
	levelText.setString(levelInStringForm);
	levelText.setPosition(window.getSize().x / 3, window.getSize().y / 2.5);
	scoreText.setCharacterSize(20);
	levelText.setCharacterSize(80);
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Draws the player entity to the screen.															 *
 ****************************************************************************************************************/
void ScoreBoard::drawCurrent(sf::RenderWindow& window)
{
	window.draw(scoreText);
	if (levelChanged)
	{
		if (newLevel)
		{
			timer = clock.restart();
			newLevel = false;
		}

		timer = clock.getElapsedTime();
		window.draw(levelText);

		if (timer.asSeconds() > 5)
		{
			levelChanged = false;
			timer = clock.restart();
		}
	}
}	

/*****************************************************************************************************************
 *										updateCurrent()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Updates the enemy object by updating its movement any missiles that the enemy fires				 *
 ****************************************************************************************************************/
void ScoreBoard::updateCurrent(sf::Time deltaTime)
{
	checkLevelChange();
}

/*****************************************************************************************************************
 *										checkLevelChange()										     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Checks to see if the level has changed. If so, the text strings are updated to reflect the       *
 * name of the current level																					 *
 ****************************************************************************************************************/
void ScoreBoard::checkLevelChange()
{
	if (currentLevel < gameLevel.getLevel())
	{
		currentLevel++;
		std::string text = std::to_string(gameLevel.getLevel());
		levelInStringForm = "Level " + std::to_string(gameLevel.getLevel());
		levelText.setString(levelInStringForm);
		scoreText.setString(levelInStringForm);
		levelChanged = true;
		newLevel = true;
	}
}
