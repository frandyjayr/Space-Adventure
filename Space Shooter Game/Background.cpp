#include "Background.hpp"
#include <iostream>

/*****************************************************************************************************************
 *										Constructor													     		 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder																			 *
 * Output: None																									 *
 * Description: The constructor initializes the background texture, scroll speed, and the vector in which the    *
 * background sprites will be placed in. The background is put in a vector to allow it to be used in such a way  *
 * that gives it a continuous, scrolling animation.																 *
 ****************************************************************************************************************/
Background::Background(sf::RenderWindow& window, ResourceHolder& resourceHolder) : window(window)
{
	background.setTexture(resourceHolder.getTextures(Textures::ID::Background));
	scrollSpeed = sf::Vector2f(0, 150);
	initializeVector();
}

/*****************************************************************************************************************
 *										renderBackground()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Renders the background in a continous, scrolling animation form by using the vector the was      *
 * created in the constructor																					 *
 ****************************************************************************************************************/
void Background::renderBackground()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		window.draw(tiles[i].tile);
	}
}

/*****************************************************************************************************************
 *										updateBackground()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Updates the	background movement based on deltaTime. The scroll speed has a direct influence on   *
 * the scroll speed of the background.																			 *
 ****************************************************************************************************************/
void Background::updateBackground(sf::Time deltaTime)
{
	sf::Vector2f change = scrollSpeed * deltaTime.asSeconds();
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].tile.move(change);
		tiles[i].position.x += change.x;
		tiles[i].position.y += change.y;
		if (outOfView(i))
		{
			changePosition(i);
		}
	}
}

/*****************************************************************************************************************
 *										initializeVector()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Initializes the vector in which the background sprite will be contained in						 *
 ****************************************************************************************************************/
void Background::initializeVector()
{
	backgroundTile newTile;
	newTile.tile = background;
	newTile.position = sf::Vector2f(0, 0);
	newTile.tile.setPosition(newTile.position);
	tiles.push_back(newTile);


	newTile.position = sf::Vector2f(0, (window.getSize().y) * -1.0);
	newTile.tile.setPosition(newTile.position);
	tiles.push_back(newTile);
}


/*****************************************************************************************************************
 *										changePosition()											     		 *
 *****************************************************************************************************************
 * Input: int posiiton																							 *
 * Output: None																									 *
 * Description: Helper function that moves resets the background iamge within the vector to start at the top of  *
 * the window in order to allow for continous scrolling of the background iamge									 *
 ****************************************************************************************************************/
void Background::changePosition(int position)
{
	tiles[position].position = sf::Vector2f(0, (window.getSize().y) * -1.0);
	tiles[position].tile.setPosition(tiles[position].position);
}


/*****************************************************************************************************************
 *										outOfView()													     		 *
 *****************************************************************************************************************
 * Input: int Position																							 *
 * Output: bool indicating if a sprite is out of the user's view based on window size						     *
 * Description: Returns true if a sprite is out of view based on the window size								 *
 ****************************************************************************************************************/
bool Background::outOfView(int position)
{
	if (tiles[position].position.y > window.getSize().y)
	{
		return true;
	}
	return false;
}


/*****************************************************************************************************************
 *										updateBackground()											     		 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																									 *
 * Description: Renders the background on the game screen														 *
 ****************************************************************************************************************/
void Background::drawCurrent(sf::RenderWindow & target)
{
	renderBackground();
}

/*****************************************************************************************************************
 *										updateCurrent()												     		 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																									 *
 * Description: Updates the background Nodd within the scene graph. This update function specifically will       *
 * update the background position, giving the background scrolling animation look.								 *
 ****************************************************************************************************************/
void Background::updateCurrent(sf::Time deltaTime)
{
	updateBackground(deltaTime);
}
