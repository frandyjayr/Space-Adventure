#include "Enemy.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, enemy position, enemy level, enemy speed								 *
 * Output: None																								     *
 * Description: The following constructor initializes the enemy position, texture, speed, and level				 *
 ****************************************************************************************************************/
Enemy::Enemy(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position, Ship::Level level,
sf::Vector2f speed) : window(window), Entity(speed), resourceHolder(resourceHolder)
{
	type = Node::Type::Enemy;
	initializeEnemy(resourceHolder, position, level);
}

/*****************************************************************************************************************
 *										setForDestruction()										     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: The following function reduces the health of the enemy by one. If the health is less than or     *
 * equal to zero, the function sets the destruction of the object.												 *
 ****************************************************************************************************************/
void Enemy::setForDestruction()
{
	health -= 1;

	if (health <= 0)
	{
		powerUpGenerator.generateEnemyDrops(mParent, window, resourceHolder, this->getPosition(), velocity);
		toBeDestroyed = true;
		if (shipLevel == Ship::BossA)
		{
			gameLevel.changeBossStatus();
		}
	}
}

/*****************************************************************************************************************
 *										hasOneHealth()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the enemy has one health														     *
 * Description: The following function returns true if the enemy ship has one health							 *
 ****************************************************************************************************************/
bool Enemy::hasOneHealth()
{
	if (health == 1)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																								     *
 * Description: Draws the player entity to the screen.															 *
 ****************************************************************************************************************/
void Enemy::drawCurrent(sf::RenderWindow& window)
{
	renderEnemy();
}

/*****************************************************************************************************************
 *										updateCurrent()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Updates the enemy object by updating its movement any missiles that the enemy fires				 *
 ****************************************************************************************************************/
void Enemy::updateCurrent(sf::Time deltaTime)
{
	moveEnemy(deltaTime);
	updateMissile();
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Draws the player entity to the screen.															 *
 ****************************************************************************************************************/
void Enemy::renderEnemy()
{
	window.draw(mEntity);
}

/*****************************************************************************************************************
 *										shootMissile()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Creates a missile object and attaches it to the enemy class. The missile will then be rendered   *
 * because it is now an attached scenenode child of enemy.														 *
 ****************************************************************************************************************/
void Enemy::shootMissile()
{
	std::unique_ptr<SceneNode> missile(new Missile(window, resourceHolder, 
	mEntity.getPosition().x + (mEntity.getGlobalBounds().width / 2),
	mEntity.getPosition().y + mEntity.getGlobalBounds().height,
	Object::Direction::DOWN, Node::Type::EnemyMissile));
	attachChild(missile);
}

/*****************************************************************************************************************
 *										diceRoll()												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: unsigned int																						     *
 * Description: returns a random number of the screen from the range of 0 to missileProbability					 *
 ****************************************************************************************************************/
unsigned int Enemy::diceRoll()
{
	return rand() % missileProbability;
}

/*****************************************************************************************************************
 *										moveEnemy()												     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Moves the enemy based on the velocity and deltaTime												 *
 ****************************************************************************************************************/
void Enemy::moveEnemy(sf::Time deltaTime)
{
	mEntity.move(velocity * deltaTime.asSeconds());
}

/*****************************************************************************************************************
 *										updateMissile()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Updates the missile of the enemy. A random firing system is used for this function. If the       *
 * diceRoll function rolls the target value, a missile will fire, therefore, the smaller the target value, the   *
 * higher probaility that a missile will be fired because the dice will have fewer numbers to roll				 *
 * The target value is arbitrary, however must be between 0 and the target value.							     *
 ****************************************************************************************************************/
void Enemy::updateMissile()
{
	if (diceRoll() == TARGET_VALUE)
	{
		shootMissile();
	}
}

/*****************************************************************************************************************
 *										initializeEnemy()										     			 *
 *****************************************************************************************************************
 * Input: resourceHolder, enemy Position, and Ship level														 *
 * Output: None																								     *
 * Description: initializes the enemy's position, scale, level, and node type. Textures, health, and missile     *
 * probability are based on the level argument that is passed													 *
 ****************************************************************************************************************/
void Enemy::initializeEnemy(ResourceHolder& resourceHolder, sf::Vector2f position, Ship::Level level)
{
	mEntity.setPosition(position);
	mEntity.setScale(0.3, 0.3);
	type = Node::Type::Enemy;
	shipLevel = level;

	if (level == Ship::EasyA)
	{
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::EnemyA));
		health = 0 + gameLevel.healthIncreaseByLevel();
		missileProbability = 2500 + gameLevel.bulletIncreaseByLevel();
	}
	else if (level == Ship::MediumA)
	{
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::EnemyB));
		health = 1 + gameLevel.healthIncreaseByLevel();
		missileProbability = 2100 + gameLevel.bulletIncreaseByLevel();;
	}
	else if (level == Ship::HardA)
	{
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::EnemyC));
		health = 2 + gameLevel.healthIncreaseByLevel();
		missileProbability = 1600 + gameLevel.bulletIncreaseByLevel();;
	}
	else if (level == Ship::BossA)
	{
		mEntity.setTexture(resourceHolder.getTextures(Textures::ID::BossA));
		mEntity.setScale(1.5, 1.5);
		health = (20 * gameLevel.getLevel) + gameLevel.healthIncreaseByLevel();
		missileProbability = 300 + gameLevel.bulletIncreaseByLevel();;
		if (missileProbability <= 0)
		{
			missileProbability = MAX_MISSILE_PROBABILITY;
		}
	}

}
