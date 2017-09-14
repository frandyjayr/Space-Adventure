#include "PowerUpGenerator.hpp"

int PowerUpGenerator::enemiesDestroyed = 0;

/*****************************************************************************************************************
 *										generateEnemyDrops()										     		 *
 *****************************************************************************************************************
 * Input: SceneNode, RenderWindow, resourceHolder, position, velocity											 *
 * Output: None																									 *
 * Description: The following function is used to drop power up items in the game. It should be called whenever  *
 * an enemy entity is destroyed. The function ensures that power up drops are only generated based on the number *
 * of enemies that are killed. Once that threshold has been met, the counter resets and starts again.			 *
 ****************************************************************************************************************/
void PowerUpGenerator::generateEnemyDrops(SceneNode* node, sf::RenderWindow& window, ResourceHolder& resourceHolder, 
	sf::Vector2f position, sf::Vector2f velocity)
{
	enemyDestroyed();
	if (readyToSpawn())
	{
		std::unique_ptr<SceneNode> enemyDrop(new PowerUp(window, resourceHolder,
		position, velocity, randomizePower()));
		node->attachChild(enemyDrop);
	}
}

/*****************************************************************************************************************
 *										randomizePower()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Power																								 *
 * Description: Returns a random powerup in the game. Each power up has an equal opportunity of being created.   *
 * The function uses the rand() function to generate powerups.													 *
 ****************************************************************************************************************/
Power PowerUpGenerator::randomizePower()
{
	int value = rand() % 3 + 1;
	if (value == 1)
	{
		return BulletSpeed;
	}
	else if (value == 2)
	{
		return PlayerSpeed;
	}
	else if (value == 3)
	{
		return AddShip;
	}
}

/*****************************************************************************************************************
 *										readyToSpawn()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool																									 *
 * Description: The function checks to see if a new power up is ready to spawn. This is determined by the number *
 * of enemies that have been destroyed. If the player reaches the REQUIRED_NUMBER_TO_KILL parameter, this        *
 * function will return true																					 *
 ****************************************************************************************************************/
bool PowerUpGenerator::readyToSpawn()
{
	if (enemiesDestroyed >= REQUIRED_NUMBER_TO_KILL)
	{
		resetPowerUpGenerator();
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										resetPowerUpGenerator()										     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Resets the number of enemies destroyed. When the enemiesDestroyed reaches a certain threshold,   *
 * the value is reset to zero so powerups are generated only once every X number of enemies destroyed			 *
 ****************************************************************************************************************/
void PowerUpGenerator::resetPowerUpGenerator()
{
	enemiesDestroyed = 0;
}

/*****************************************************************************************************************
 *										enemyDestroyed()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Increases the number of enemies Destroyed														 *
 ****************************************************************************************************************/
void PowerUpGenerator::enemyDestroyed()
{
	enemiesDestroyed++;
}


