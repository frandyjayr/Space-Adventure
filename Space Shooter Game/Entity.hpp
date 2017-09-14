#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"

class Entity : public SceneNode
{
	public:
									Entity(sf::Vector2f velocity);

	protected:
		sf::Vector2f				velocity;
};
#endif