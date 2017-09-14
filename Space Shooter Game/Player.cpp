#include "Player.hpp"

int Player::numberOfShips = STARTING_SHIP_SIZE;
float Player::bulletSpeed = STARTING_BULLET_SPEED;
sf::Vector2f Player::playerSpeed = STARTING_SHIP_SPEED;

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, Player position															 *
 * Output: None																								     *
 * Description: The following constructor initializes the players texture, scale, and position. It then          *
 * initializes the sound buffers for the powerup and missile sounds.										     *
 ****************************************************************************************************************/
Player::Player(sf::RenderWindow& window, ResourceHolder& resourceHolder, sf::Vector2f position) : mWindow(window), resourceHolder(resourceHolder)
{
	mEntity.setTexture(resourceHolder.getTextures(Textures::ID::Spaceship));
	mEntity.setScale(0.130, 0.130);
	mEntity.setPosition(position);

	missileSound.setBuffer(resourceHolder.getSoundBuffers(SoundBuffers::ID::Missile));
	powerUpSound.setBuffer(resourceHolder.getSoundBuffers(SoundBuffers::ID::PowerUp));

	type = Node::Type::Player;
}

/*****************************************************************************************************************
 *										setForDestruction()										     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Virtual function that updates the total numberOFShips. The number of ships variable is static    *
 * therefore gets updated even though the object is set to be destroyed when the function is called				 *
 ****************************************************************************************************************/
void Player::setForDestruction()
{
	numberOfShips--;
	toBeDestroyed = true;
}

/*****************************************************************************************************************
 *										gameIsOver()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Bool that returns true if the number of ships between all ship classes is 0 or less					 *
 * Description: returns true if there are no more ships remaining. It also resets the numberOfShips and bullet	 *
 * speed of the player.																							 *
 ****************************************************************************************************************/
bool Player::gameIsOver()
{
	if (numberOfShips > 0)
	{
		return false;
	}
	numberOfShips = 1;
	bulletSpeed = 2;
	return true;
}

/*****************************************************************************************************************
 *										updateCurrent()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Updates the player by using the playerUpdate function. This will update the players movement     *
 * and also any missiles that are fired																			 *
 ****************************************************************************************************************/
void Player::updateCurrent(sf::Time deltaTime)
{
	updatePlayer(deltaTime);
}

/*****************************************************************************************************************
 *										renderPlayer()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Renders the player onto the screen																 *
 ****************************************************************************************************************/
void Player::renderPlayer()
{
	mWindow.draw(mEntity);
}

/*****************************************************************************************************************
 *										MoveLeft()												     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Moves the player sprite left based on deltaTime and the ship velocity.							 *
 ****************************************************************************************************************/
void Player::moveLeft(sf::Time deltaTime)
{
	// only move if the player is inside the screen bounds
	if (!(mEntity.getPosition().x < 0))
	{
		mEntity.move((playerSpeed.x * deltaTime.asSeconds()) * -1, playerSpeed.y);
	}
}

/*****************************************************************************************************************
 *										MoveRight()												     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Moves the player sprite right based on deltaTime and the ship velocity.							 *
 ****************************************************************************************************************/
void Player::moveRight(sf::Time deltaTime)
{
	// only move if the player is inside the screen bounds
	if (!(mEntity.getPosition().x + mEntity.getGlobalBounds().width > mWindow.getSize().x))
	{
		mEntity.move(playerSpeed * deltaTime.asSeconds());
	}
}

/*****************************************************************************************************************
 *										shootMissile()											     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: When called, this function will create a missile class instance and spawn it above the player    *
 * to make it look like the missile is being fired from the ship. There is a timer, however that only allows     *
 * this function to create missile objects based on the bullet speed. The higher the bullet speed, the higher    *
 * frequency missiles can be created																			 *
 ****************************************************************************************************************/
void Player::shootMissile()
{
	time = clock.getElapsedTime();
	if (time.asSeconds() > (1.0 / bulletSpeed))
	{
		std::unique_ptr<SceneNode> missile(new Missile(mWindow, resourceHolder,
		(mEntity.getPosition().x + (mEntity.getGlobalBounds().width / 2)), 
	 	 mEntity.getPosition().y - (mEntity.getGlobalBounds().height / 2),
		 Object::Direction::UP, Node::Type::PlayerMissile));
		attachChild(missile);
		missileSound.play();
		clock.restart();
	}
	refreshTime();
}

/*****************************************************************************************************************
 *										updatePlayer()											     			 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																								     *
 * Description: Updates the players movements and any missiles that are launched by the player					 *
 ****************************************************************************************************************/
void Player::updatePlayer(sf::Time deltaTime)
{
	if (mMove.getMovement(Left))
	{
		moveLeft(deltaTime);
	}
	if (mMove.getMovement(Right))
	{
		moveRight(deltaTime);
	}
	if (mMove.getMovement(Up))
	{
		shootMissile();
	}
}

/*****************************************************************************************************************
 *										drawCurrent()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																								     *
 * Description: Draws the player entity to the screen.															 *
 ****************************************************************************************************************/
void Player::drawCurrent(sf::RenderWindow & window)
{
	renderPlayer();
}

/*****************************************************************************************************************
 *										powerUpCurrent()										     			 *
 *****************************************************************************************************************
 * Input: Power power																							 *
 * Output: None																								     *
 * Description: Applies the specific powerUp to the ship based on the power argument							 *
 ****************************************************************************************************************/
void Player::powerUpCurrent(Power power)
{
	if (power == AddShip && numberOfShips < 2)
	{
		std::unique_ptr<SceneNode> extraShip(new Player(mWindow, resourceHolder,
		sf::Vector2f((mParent->getLastChildPosition().x + mEntity.getGlobalBounds().width),
		mParent->getLastChildPosition().y)));
		mParent->attachChild(extraShip);
		numberOfShips++;

	}
	if (power == BulletSpeed)
	{
		increaseBulletSpeed();
	}
	if (power == PlayerSpeed)
	{
		increasePlayerSpeed();
	}
	powerUpSound.play();
}

/*****************************************************************************************************************
 *										handlePlayerInput										     			 *
 *****************************************************************************************************************
 * Input: sf::KeyBoard::Key, bool isPressed																		 *
 * Output: None																								     *
 * Description: Sets if a key is pressed based on the key and bool argument that is passed						 *
 ****************************************************************************************************************/
void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

	if (key == sf::Keyboard::Key::Left)
	{
		mMove.setMovement(Left, isPressed);
	}
	if (key == sf::Keyboard::Key::Right)
	{
		mMove.setMovement(Right, isPressed);
	}
	if (key == sf::Keyboard::Key::Up)
	{
		mMove.setMovement(Up, isPressed);
	}
}

/*****************************************************************************************************************
 *										refreshTime()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: resets the clock timer if the timer is creater than 10 seconds. The purpose of this timer is     *
 * to ensure that the timer does not go to run forever and contains an overflow value that could crash the       *
 * program. The number 10 is an arbitrary number.															     *
 ****************************************************************************************************************/
void Player::refreshTime()
{
	if (time.asSeconds() > 10)
	{
		clock.restart();
	}
}

/*****************************************************************************************************************
 *										increaseBulletSpeed										     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Increases the bulletspeed of the player															 *
 ****************************************************************************************************************/
void Player::increaseBulletSpeed()
{
	if (bulletSpeed < MAX_BULLET_SPEED)
	{
		bulletSpeed += BULLET_BOOST_VALUE;
	}
}

/*****************************************************************************************************************
*										increasePlayerSpeed										     			 *
*****************************************************************************************************************
* Input: None																									 *
* Output: None																								     *
* Description: Increases the playerSpeed of the player															 *
****************************************************************************************************************/
void Player::increasePlayerSpeed()
{
	if (playerSpeed.x < MAX_SHIP_SPEED)
	{
		playerSpeed.x += PLAYER_BOOST_VALUE;
	}
}
/*****************************************************************************************************************
 *										commandCurrent()										     			 *
 *****************************************************************************************************************
 * Input: sf::KeyBoard key, bool isPressed																		 *
 * Output: None																								     *
 * Description: This function is used to control the player entity. It allows an external object to move the     *
 * player left, right, and to fire missiles																		 *
 ****************************************************************************************************************/
void Player::commandCurrent(sf::Keyboard::Key key, bool isPressed)
{
	handlePlayerInput(key, isPressed);
}

/*****************************************************************************************************************
 *										resetCurrent()											     			 *
 *****************************************************************************************************************
 * Input: None																									 * 
 * Output: None																								     *
 * Description: The function is used to reset the numberOFShips, bulletSpeed, and playerSpeed when called to     *
 * their starting values. This function is to be used when the game restarts									 *
 ****************************************************************************************************************/
void Player::resetCurrent()
{
	numberOfShips = STARTING_SHIP_SIZE;
	bulletSpeed = STARTING_BULLET_SPEED;
	playerSpeed = STARTING_SHIP_SPEED;
}


