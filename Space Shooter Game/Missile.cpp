#include "Missile.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, missile positionx, missile positiony, missile direction, and node type	 *
 * Output: None																								     *
 * Description: The following constructor initializes the position of the missile and sets it texture and        *
 * node type																									 *
 ****************************************************************************************************************/
Missile::Missile(sf::RenderWindow& window, ResourceHolder& resourceHolder,
	float positionX, float positionY, Object::Direction direction, Node::Type type) :
	Entity(sf::Vector2f(0, 600 * direction)), window(window)
{
	this->positionX = positionX;
	this->positionY = positionY;
	mEntity.setTexture(resourceHolder.getTextures(Textures::ID::Beam));
	mEntity.setPosition(positionX, positionY);

	this->type = type;
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																								     *
 * Description: Renders the missile to the screen
 ****************************************************************************************************************/
void Missile::drawCurrent(sf::RenderWindow& target)
{
	renderMissile();
}

/*****************************************************************************************************************
 *										updateCurrent()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: updates the missles posiiton on the window and destroys the missle if it is out of range.        *
 ****************************************************************************************************************/
void Missile::updateCurrent(sf::Time deltaTime)
{
	moveMissile(deltaTime);
	deleteOutOfRangeObjects();
}

/*****************************************************************************************************************
 *										moveMissile()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Moves the missile sprite based on the velocity													 *
 ****************************************************************************************************************/
void Missile::moveMissile(sf::Time deltaTime)
{
	positionX += (velocity.x * deltaTime.asSeconds());
	positionY += (velocity.y * deltaTime.asSeconds());
	mEntity.setPosition(positionX, positionY);
}

/*****************************************************************************************************************
 *										renderMissile()											     			 *
 ***************************************************************************************************************** 
 * Input: None																									 *
 * Output: None																								     *
 * Description: Renders the Missile entity to the window														 *
 ****************************************************************************************************************/
void Missile::renderMissile()
{
	window.draw(mEntity);
}

/*****************************************************************************************************************
 *										OutOfRange()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating whether the object is out of the window range										 *
 * Description: Checks if the missile object is out of the window viewing range. If so, it returns true          *
 ****************************************************************************************************************/
bool Missile::outOfWindowRange()
{
	if ((positionY + mEntity.getGlobalBounds().height < 0) ||
		(positionY > window.getSize().y))
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
*										deleteOutOfRangeObjects()								     			 *
*****************************************************************************************************************
* Input: None																									 *
* Output: None																								     *
* Description: Checks if the object is out of the window's view. If so, it is deleted. This is important for    *
* memory management.																							 *
****************************************************************************************************************/
void Missile::deleteOutOfRangeObjects()
{
	if (outOfWindowRange())
	{
		toBeDestroyed = true;
	}
}
