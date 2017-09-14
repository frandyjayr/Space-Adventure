#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Level.hpp"
#include "Missile.hpp"
#include "PowerUp.hpp"
#include "PowerUpGenerator.hpp"
#include "ResourceHolder.hpp"

const unsigned int TARGET_VALUE = 2;
const int MAX_MISSILE_PROBABILITY = 20;

namespace Ship
{
	enum Level { EasyA, MediumA, HardA, BossA };
}


class Enemy : public Entity
{
	public:
											Enemy(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position = sf::Vector2f(0,0),
											Ship::Level level = Ship::Level::EasyA, sf::Vector2f speed = sf::Vector2f(0,0));
		virtual void						setForDestruction();
		virtual bool						hasOneHealth();

	protected:
		virtual void						drawCurrent(sf::RenderWindow& window);
		virtual void						updateCurrent(sf::Time deltaTime);
		void								moveEnemy(sf::Time deltaTime);
		void								updateMissile();

	protected:
		sf::RenderWindow&					window;
		ResourceHolder&						resourceHolder;
		TheGame::Level						gameLevel;
		Ship::Level							shipLevel;
		PowerUpGenerator					powerUpGenerator;
		int									missileProbability;
		unsigned int						health;

	private:
		void								renderEnemy();
		void								shootMissile();
		unsigned int						diceRoll();
		void								initializeEnemy(ResourceHolder& resourceHolder, sf::Vector2f position, Ship::Level level);
};
#endif
