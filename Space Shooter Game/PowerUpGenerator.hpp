#ifndef POWERUPGENERATOR_HPP
#define POWERUPGENERATOR_HPP

#include "PowerUp.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"

const int REQUIRED_NUMBER_TO_KILL = 7;

class PowerUpGenerator
{
	public:
		void			generateEnemyDrops(SceneNode* node, sf::RenderWindow& window, ResourceHolder& resourceHolder, 
						sf::Vector2f position, sf::Vector2f velocity);
		static void		resetPowerUpGenerator();

	private:
		static int		enemiesDestroyed;

	private:
		Power			randomizePower();
		bool			readyToSpawn();
		static void		enemyDestroyed();
};
#endif