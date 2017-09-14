#ifndef WALL_HPP
#define WALL_HPP

#include "Entity.hpp"
#include "ResourceHolder.hpp"

class Wall : public Entity
{
	public:
											Wall(sf::RenderWindow& window, ResourceHolder& resourceHolder);
	private:
		virtual void						drawCurrent(sf::RenderWindow& window);

	private:
		sf::RenderWindow&					window;
};
#endif
