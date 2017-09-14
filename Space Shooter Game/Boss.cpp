#include "Boss.hpp"

/*****************************************************************************************************************
 *										Constructor													     		 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, Boss Position, Boss Level, Boss Speed									 *
 * Output: None																									 *
 * Description: sets the movement speed of the Boss and initializes the Base Enemy class.						 *
 ****************************************************************************************************************/
Boss::Boss(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position, Ship::Level level, sf::Vector2f speed) :
Enemy(window, resourceHolder, position, level, sf::Vector2f(0, speed.y))
{
	movementSpeedHolder = speed;
	spawnComplete = false;
}

/*****************************************************************************************************************
 *										stopVerticalMovement										     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Stops the vertical movement of the boss when it reaches a specific vertical point of the screen  *
 * This prevents the boss sprite from moving towards the player and allows the player to "battle" the boss       *
 ****************************************************************************************************************/
void Boss::stopVerticalMovement()
{
	if (reachedEndOfLine() && !spawnComplete)
	{
		velocity.y = 0;
		velocity.x = movementSpeedHolder.x;
		spawnComplete = true;
	}
}

/*****************************************************************************************************************
 *										moveHorizontally()										     		     *
 *****************************************************************************************************************
 * Input: None																							         * 
 * Output: None																									 *
 * Description: Moves the boss horizontally in an infinite loop. If the boss collides with the left or right     *
 * side of the screen, it will reverse its velocity and move the opposite direction.							 *
 ****************************************************************************************************************/
void Boss::moveHorizontally()
{
	if (reachedRightSide())
	{
		velocity.x *= -1.0;
	}
	else if (reachedLeftSide())
	{
		velocity.x *= -1.0;
	}
}

/*****************************************************************************************************************
 *										reachedEndOfLine()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the Boss reached the maximum Y coordinate position								 * 																									 
 * Description: returns true if the boss Y coordinate reaches the end of line.									 *
 ****************************************************************************************************************/
bool Boss::reachedEndOfLine()
{
	if (mEntity.getPosition().y > 100)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										reachedLeftSide()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the Boss reached the left side of the window										 *
 * Description: returns true if the boss collides with the left side of the window								 *
 ****************************************************************************************************************/
bool Boss::reachedLeftSide()
{
	if (mEntity.getPosition().x < 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										reachedRightSide()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the Boss reached the right side of the window										 *
 * Description: returns true if the boss collides with the right side of the window								 *
 ****************************************************************************************************************/
bool Boss::reachedRightSide()
{
	if ((mEntity.getPosition().x + mEntity.getGlobalBounds().width) > window.getSize().x)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										reachedLeftSide()											     		 *
 *****************************************************************************************************************
 * Input: sf::Time DeltaTime																					 *
 * Output: None																									 *
 * Description: updates the Boss Missilles, vertical movement, and horizontal movement.							 *
 ****************************************************************************************************************/
void Boss::updateCurrent(sf::Time deltaTime)
{
	updateMissile();
	moveHorizontally();
	moveEnemy(deltaTime);
	stopVerticalMovement();
}

