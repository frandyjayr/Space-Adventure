#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Missile.hpp"
#include "Movement.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"

const int STARTING_SHIP_SIZE = 1;
const float STARTING_BULLET_SPEED = 2;
const sf::Vector2f STARTING_SHIP_SPEED = sf::Vector2f(400, 0);
const int MAX_SHIP_SPEED = 800;
const int MAX_BULLET_SPEED = 5;
const int PLAYER_BOOST_VALUE = 40;
const float BULLET_BOOST_VALUE = 0.5;

class Player : public SceneNode
{
	public:
								Player(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position);
		virtual void			setForDestruction();
		virtual bool			gameIsOver();

	private:
		virtual void			updateCurrent(sf::Time deltaTime);
		virtual void			drawCurrent(sf::RenderWindow& window);
		virtual void			powerUpCurrent(Power power);
		virtual void			commandCurrent(sf::Keyboard::Key key, bool isPressed);
		virtual void			resetCurrent();
		static void				increaseBulletSpeed();
		static void				increasePlayerSpeed();
		void					updatePlayer(sf::Time deltaTime);
		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void					shootMissile();
		void					moveLeft(sf::Time deltaTime);
		void					moveRight(sf::Time deltaTime);
		void					renderPlayer();
		void					refreshTime();

	private:
		sf::Time				time;
		sf::Clock				clock;
		sf::RenderWindow&		mWindow;
		sf::Sound				missileSound;
		sf::Sound				powerUpSound;
		ResourceHolder&			resourceHolder;
		Movement				mMove;
	
	private:
		static int				numberOfShips;
		static float			bulletSpeed;
		static sf::Vector2f		playerSpeed;
};
#endif
