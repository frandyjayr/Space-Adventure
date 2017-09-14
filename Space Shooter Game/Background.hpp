#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "SceneNode.hpp"

struct backgroundTile
{
	sf::Sprite   tile;
	sf::Vector2f position;
};

class Background : public SceneNode
{
	public:
											Background(sf::RenderWindow& window, ResourceHolder& resourceHolder);

	private:
		void								renderBackground();
		void								updateBackground(sf::Time deltaTime);
		void								initializeVector();
		void								changePosition(int position);
		bool								outOfView(int position);
		virtual void						drawCurrent(sf::RenderWindow& target);
		virtual void						updateCurrent(sf::Time deltaTime);

	private:
		sf::RenderWindow&					window;
		sf::Sprite							background;
		std::vector<backgroundTile>			tiles;
		sf::Vector2f						scrollSpeed;;
};
#endif