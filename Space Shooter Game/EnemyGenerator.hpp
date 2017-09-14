#ifndef ENEMYGENERATOR_HPP
#define ENEMYGENERATOR_HPP

#include "SceneNode.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"

const int SPAWN_FREQUENCY = 3;
const int LEVEL_FREQUENCY = 21;

class EnemyGenerator
{
	public:
							EnemyGenerator(sf::RenderWindow& window, ResourceHolder& resourceHolder);
		void				generateGameEnemies(SceneNode& node);

	private:
		void				updateLevel();
		sf::Vector2f		generateRandomLocation();
		bool				readyToSpawn();
		Ship::Level			levelIncrease();

	private:
		sf::RenderWindow&	window;
		ResourceHolder&		resourceHolder;
		sf::Time			spawnTimer;
		sf::Time			levelTimer;
		sf::Clock			levelClock;
		sf::Clock			spawnClock;
		Ship::Level			level;
		TheGame::Level		gameLevel;
		unsigned int		spawnFrequency;
		unsigned int		levelFrequency;
		bool				bossASpawned;
	private:
};
#endif
