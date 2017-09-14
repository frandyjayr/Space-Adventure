#include "Entity.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: sf::Vector2f velocity																					 *
 * Output: None																									 *
 * Description: Initializes the velocity of the entity.															 *
 ****************************************************************************************************************/
Entity::Entity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

