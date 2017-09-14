#include "Wall.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder																			 *
 * Output: None																								     *
 * Description: Sets the transparent texture of the wall sprite. The wall acts as an invisible barrier that the  *
 * Enemy ships can collide wtih. The constructor sets the position of the wall to be below the player ship at    *
 * the bottom of the window.																					 *
 ****************************************************************************************************************/
Wall::Wall(sf::RenderWindow& window, ResourceHolder& resourceHolder) : Entity(sf::Vector2f(0,0)), 
window(window)
{
	mEntity.setTexture(resourceHolder.getTextures(Textures::ID::Wall));
	mEntity.setPosition(sf::Vector2f(0, window.getSize().y));
	type = Node::Type::Wall;
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																								     *
 * Description: Although the wall is transparent, it's sprite is still drawn on the screen to give it a position *
 * that the enemy ships can collide with. If the enemy ships collide with the wall, the game resets.             *
 ****************************************************************************************************************/
void Wall::drawCurrent(sf::RenderWindow & window)
{
	window.draw(mEntity);
}
