#include "Level.hpp"

int TheGame::Level::level = 1;
bool TheGame::Level::bossIsDead = false;

/*****************************************************************************************************************
 *										getLevel												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: int																									 *
 * Description: returns the level of the game
 ****************************************************************************************************************/
int TheGame::Level::getLevel()
{
	return level;
}

/*****************************************************************************************************************
 *										increaseLevel()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Increase the level of the game																	 *
 ****************************************************************************************************************/
void TheGame::Level::increaseLevel()
{
	level++;
}

/*****************************************************************************************************************
 *										healthincreaseByLevel()									     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Int																									 *
 * Description: Outputs an int that represents the new health of an enemy. The health that returns is based on   *
 * The current level of the game. Higher levels output higher health increases									 *
 ****************************************************************************************************************/
int TheGame::Level::healthIncreaseByLevel()
{
	return (level * 1.5);
}

/*****************************************************************************************************************
 *										bulletIncreaseByLevel()									     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: float																								 *
 * Description: Outputs a float that represents the new bullet frequency of an enemy. The frequency returns is   *
 * based on the current level of the game. Bullet frequency outputs negative value because it subtracts from the *
 * enemy's roll probability. If the number of values to roll is smaller, the roll probability is higher. This    *
 * explains the negative sign below.																			 *
 ****************************************************************************************************************/
float TheGame::Level::bulletIncreaseByLevel()
{
	return (-1 * level * 100);
}

/*****************************************************************************************************************
 *										bossDefeated()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indcating if the boss has been defeated														     *
 * Description: Returns true if the boss is dead, false otherwise												 *
 ****************************************************************************************************************/
bool TheGame::Level::bossDefeated()
{
	return bossIsDead;
}

/*****************************************************************************************************************
 *										changeBossStatus()										     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Changes the boss status of the Boss. If bossIsDead is true, after calling the function, it will  *
 * change it to false and vice versa.																			 *
 ****************************************************************************************************************/
void TheGame::Level::changeBossStatus()
{
	if (bossIsDead)
	{
		bossIsDead = false;
	}
	else
	{
		bossIsDead = true;
	}

}

/*****************************************************************************************************************
 *										resetLevel()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Resets the level of the game back to level 1													 *
 ****************************************************************************************************************/
void TheGame::Level::resetLevel()
{
	level = 1;
}

