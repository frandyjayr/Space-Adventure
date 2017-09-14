#include "PowerUp.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, PowerUp Position, PowerUp Velocity, PowerUp Type						 *
 * Output: None																								     *
 * Description: Constructor uses the createPowerUp helper function to create the power up by settings its power, *
 * position, and initializing the velocity.																		 *
 ****************************************************************************************************************/
PowerUp::PowerUp(sf::RenderWindow & window, ResourceHolder & resourceHolder, sf::Vector2f position, sf::Vector2f velocity, Power power) :
Entity(sf::Vector2f(0, 300)), window(window) 
{
	createPowerUp(power, position, resourceHolder);
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																								     *
 * Description: Draws the PowerUp to the window																	 *
 ****************************************************************************************************************/
void PowerUp::drawCurrent(sf::RenderWindow& target)
{
	window.draw(mEntity);
}

/*****************************************************************************************************************
 *										UpdateCurrent()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Updates the PowerUp per iteration. Every iteteration, the rotation is updated and the object is  *
 * checked if it is out of range. If so, it is deleted.															 *
 ****************************************************************************************************************/
void PowerUp::updateCurrent(sf::Time deltaTime)
{
	rotate(deltaTime);
	deleteOutOfRangeObjects();
}

/*****************************************************************************************************************
 *										rotate()												     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Rotates the sprite in a counter clockwise motion per iteration									 *
 ****************************************************************************************************************/
void PowerUp::rotate(sf::Time deltaTime)
{
	mEntity.move(velocity * deltaTime.asSeconds());
	mEntity.rotate(200 * deltaTime.asSeconds());
}

/*****************************************************************************************************************
 *										deleteOutOfRangeObjects()								     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Checks if the object is out of the window's view. If so, it is deleted. This is important for    *
 * memory management.																							 *
 ****************************************************************************************************************/
void PowerUp::deleteOutOfRangeObjects()
{
	if (outOfRange())
	{
		toBeDestroyed = true;
	}
}

/*****************************************************************************************************************
 *										createPowerUp											     			 *
 *****************************************************************************************************************
 * Input: Power, PowerUp position, resourceHolder																 *
 * Output: None																								     *
 * Description: The following helper function creates a powerup based on its Power type.
 ****************************************************************************************************************/
void PowerUp::createPowerUp(Power power, sf::Vector2f position, ResourceHolder& resourceHolder)
{
	this->power = power;
	mEntity.setOrigin(mEntity.getLocalBounds().width / 2, mEntity.getLocalBounds().height / 2);

	if (power == AddShip)
	{
		type = Node::PowerUpShip;
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::AddShip));
		mEntity.setPosition(position);
		mEntity.setScale(0.09, 0.09);
	}
	if (power == BulletSpeed)
	{
		type = Node::PowerUpBullet;
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::BulletSpeed));
		mEntity.setPosition(position);
	}
	if (power == PlayerSpeed)
	{
		type = Node::PowerUpPlayerSpeed;
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::PlayerSpeed));
		mEntity.setPosition(position);
	}
}

/*****************************************************************************************************************
 *										OutOfRange												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the PowerUp is out of the windows view										     *
 * Description: The following function checks if the object is out of the range of the game window. If so, it    *
 * returns true. Else it will return false																		 *
 ****************************************************************************************************************/
bool PowerUp::outOfRange()
{
	if (mEntity.getPosition().y > window.getSize().y)
	{
		return true;
	}
	return false;
}
