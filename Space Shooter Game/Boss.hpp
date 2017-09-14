#ifndef BOSS_HPP
#define BOSS_HPP

#include "Enemy.hpp"

class Boss : public Enemy
{
	public:
		Boss(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position,
			Ship::Level level, sf::Vector2f speed);

	private:	
		void			stopVerticalMovement();
		void			moveHorizontally();
		bool			reachedEndOfLine();
		bool			reachedLeftSide();
		bool			reachedRightSide();
		virtual void	updateCurrent(sf::Time deltaTime);

	private:
		sf::Vector2f	movementSpeedHolder;
		bool			spawnComplete;
};
#endif