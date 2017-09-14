#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ResourceHolder.hpp"

namespace Object
{
	enum Direction 
	{
		DOWN = 1, UP = -1
	};
}

class Missile : public Entity
{
	public:
		enum Type
		{
			Enemy,
			Player
		};

	public:
											Missile(sf::RenderWindow& window, ResourceHolder& resourceHolder, 
											float positionX,  float positionY, Object::Direction direction,
											Node::Type type);

	private:
		virtual void						drawCurrent(sf::RenderWindow& target);
		virtual void						updateCurrent(sf::Time deltaTime);
		void								moveMissile(sf::Time deltaTime);
		void								renderMissile();
		bool								outOfWindowRange();
		void								deleteOutOfRangeObjects();

	private:
		float								positionX;
		float								positionY;
		sf::Vector2f						position;
		sf::RenderWindow&					window;

};
#endif
