#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Entity.hpp"
#include "SceneNode.hpp"

class PowerUp : public Entity
{
	public:
								PowerUp(sf::RenderWindow& window, ResourceHolder& resourceHolder, 
								sf::Vector2f position, sf::Vector2f velocity, Power power);
	private:
		virtual void			drawCurrent(sf::RenderWindow& target);
		virtual void			updateCurrent(sf::Time deltaTime);
		void					rotate(sf::Time deltaTime);
		void					deleteOutOfRangeObjects();
		void					createPowerUp(Power power, sf::Vector2f position, ResourceHolder& resourceHolder);
		bool					outOfRange();

	private:
		sf::RenderWindow&		window;
		Power					power;
};
#endif
