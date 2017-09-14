#include "Game.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: sf::RenderWindow																						 *
 * Output: None																									 *
 * Description: The constructor of the game class initializes the render window. It then loads all textures      *
 * soundBuffers, and fonts. Next, it builds the scene graph that will hold all entities that will be rendered    *
 * to the screen. Then, it initializes the enemy generator class and command class. Finally, it will set the     *
 * explosion sound buffer for the game class. The explosion sound buffer is not implemented directly in any of   *
 * the classes enemy or player ship classes because the explosion sound is meant to play when any enemy or player*
 * object is destroyed, therefore it cannot be played within an enemy or player class because it will be		 *
 * destroyed before the sound can be played.																	 *
 ****************************************************************************************************************/
Game::Game(sf::RenderWindow& window) : mWindow(window)
{
	loadTextures();
	loadSoundBuffers();
	loadFonts();
	buildScene();
	mGenerator = std::unique_ptr<EnemyGenerator>(new EnemyGenerator(window, gameResourceHolder));
	mCommand = std::unique_ptr<Command>(new Command(window));
	explosionSound.setBuffer(gameResourceHolder.getSoundBuffers(SoundBuffers::ID::Explosion));
}

/*****************************************************************************************************************
 *										run()   															     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function is used to manage/render all components of the game function while also   *
 * processing any player events and updating any necessary variables within the game. The function encapsualtes  *
 * all of the data of the Space Shooter game by processing all events, updating every object, and rendering  	 *
 * everything to the screen																						 *
 ****************************************************************************************************************/
void Game::run()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;

	while (mWindow.isOpen() && gameStateIsActive)
	{
		deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
	gameLevel.resetLevel();
}

/*****************************************************************************************************************
 *										processEvents()  													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function is used to process any user events that occur within the menu gamestate. This would *
 * incude whether a button is clicked or if the window is closed. The function specifically processes if the     *
 * user clicks any of the directional buttons that would cause the player ship to move or shoot missiles     	 *
 ****************************************************************************************************************/
void Game::processEvents()
{
	gameScene.processEvents();
	mCommand->processKeyBoardEvents();
}

/*****************************************************************************************************************
 *										Update()	     													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function is a general update function that updates any classes within the game     *
 * as necessary. In this case, the game scene calls the update function which will automatically update every    *
 * node within the scene graph. Also, player input is constantly updated through the scene graph's command       *
 * function
 ****************************************************************************************************************/
void Game::update(sf::Time deltaTime)
{
	gameScene.update(deltaTime);
	mGenerator->generateGameEnemies(gameScene);

	gameScene.command(mCommand->giveCommand(), mCommand->isPressed());
	handleCollisions();
}

/*****************************************************************************************************************
 *										render()		  													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function renders all sprites and backgrounds to the screen. The render function 	 *
 * works by traversing through the scene graph and rendering every scene node is drawable.						 *
 ****************************************************************************************************************/
void Game::render()
{
	mWindow.clear();
	gameScene.draw(mWindow);
	mWindow.display();
}

/*****************************************************************************************************************
 *										loadTextures()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's textures into the game's resourceHolder instance for later         *
 * use.																											 *
 ****************************************************************************************************************/
void Game::loadTextures()
{
	// Player Ships
	gameResourceHolder.loadTextures(Textures::ID::Spaceship, "Media/Textures/playerShip.png");

	// Enemy Ships
	gameResourceHolder.loadTextures(Textures::ID::EnemyA, "Media/Textures/EnemyA.png");
	gameResourceHolder.loadTextures(Textures::ID::EnemyB, "Media/Textures/EnemyB.png");
	gameResourceHolder.loadTextures(Textures::ID::EnemyC, "Media/Textures/EnemyC.png");
	gameResourceHolder.loadTextures(Textures::ID::BossA, "Media/Textures/BossA.png");

	// Power Ups
	gameResourceHolder.loadTextures(Textures::ID::PlayerSpeed, "Media/Textures/bolt.png");
	gameResourceHolder.loadTextures(Textures::ID::AddShip, "Media/Textures/AddShip.png");
	gameResourceHolder.loadTextures(Textures::ID::BulletSpeed, "Media/Textures/BulletSpeed.png");

	// Missile
	gameResourceHolder.loadTextures(Textures::ID::Beam, "Media/Textures/beam.png");

	// Scenery
	gameResourceHolder.loadTextures(Textures::ID::Background, "Media/Textures/galaxy_X.png");
	
	// Misc.
	gameResourceHolder.loadTextures(Textures::ID::Wall, "Media/Textures/Wall.png");

}

/*****************************************************************************************************************
 *										loadSoundBuffers()  													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's sound buffers into the game's resourceHolder instance for later    *
 * use.																											 *
 ****************************************************************************************************************/
void Game::loadSoundBuffers()
{
	gameResourceHolder.loadSoundBuffers(SoundBuffers::ID::Missile, "Media/SoundBuffers/laser.wav");
	gameResourceHolder.loadSoundBuffers(SoundBuffers::ID::Explosion, "Media/SoundBuffers/explosion.wav");
	gameResourceHolder.loadSoundBuffers(SoundBuffers::ID::PowerUp, "Media/SoundBuffers/powerUp.wav");
}

/*****************************************************************************************************************
 *										loadFonts													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's fonts into the menu's resourceHolder instance for later use	     *
 ****************************************************************************************************************/
void Game::loadFonts()
{
	gameResourceHolder.loadFonts(Fonts::ID::DigitalTech, "Media/Fonts/Digital_tech.otf");
}

/*****************************************************************************************************************
 *										handleCollisions											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function manages collisions that occur between nodes within the SceneGraph. It uses a helper *
 * function, matchesCategories(), to see if specific nodes collide. Specific scenario collisions are input below *
 * and their respective actions are set here. For example, if an enemy missile collides with a player, both      *
 * objects will be destroyed.																				     *
 ****************************************************************************************************************/
void Game::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	gameScene.checkSceneCollision(gameScene, collisionPairs);
	
	for (SceneNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, Node::Type::Enemy, Node::Type::PlayerMissile))
		{
			if (pair.first->hasOneHealth())
			{
				explosionSound.play();
			}
			pair.first->setForDestruction();
			pair.second->setForDestruction();
		}
		else if (matchesCategories(pair, Node::Type::Player, Node::Type::EnemyMissile))
		{
			pair.first->setForDestruction();
			pair.second->setForDestruction();
			powerUpGenerator.resetPowerUpGenerator();
			if (pair.first->gameIsOver())
			{
				gameStateIsActive = false;
			}
		}
		else if (matchesCategories(pair, Node::Type::Player, Node::Type::PowerUpShip))
		{
			pair.first->powerUp(AddShip);
			pair.second->setForDestruction();
		}
		else if (matchesCategories(pair, Node::Type::Player, Node::Type::PowerUpBullet))
		{
			pair.first->powerUp(BulletSpeed);
			pair.second->setForDestruction();
		}
		else if (matchesCategories(pair, Node::Type::Player, Node::Type::PowerUpPlayerSpeed))
		{
			pair.first->powerUp(PlayerSpeed);
			pair.second->setForDestruction();
		}
		else if (matchesCategories(pair, Node::Type::Player, Node::Type::Enemy))
		{
			pair.first->setForDestruction();
			pair.second->setForDestruction();
			gameScene.reset();
			powerUpGenerator.resetPowerUpGenerator();
			if (pair.first->gameIsOver())
			{
				gameStateIsActive = false;
			}
		}
		else if (matchesCategories(pair, Node::Type::Enemy, Node::Type::Wall))
		{
			pair.first->setForDestruction();
			pair.second->setForDestruction();
			gameScene.reset();
			powerUpGenerator.resetPowerUpGenerator();
			gameStateIsActive = false;
		}
	}
}

/*****************************************************************************************************************
 *										buildScene													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: This function builds the scene graph that all the drawable entities will be contained within.    *
 * A scene graph is built in order to allow easy addition and removals of children throughout the game. Because  *
 * Everything that is rendered on the screen is part of the scene graph, additions and removals occur very       *
 * frequently (such as missile, ships, etc.), therefore using a scenengraph was an efficient choice in terms of  *
 * game run time																								 *
 ****************************************************************************************************************/
void Game::buildScene()
{

	mBackground = std::unique_ptr<SceneNode>(new Background(mWindow, gameResourceHolder));
	mPlayer = std::unique_ptr<SceneNode>(new Player(mWindow, gameResourceHolder, sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / 1.1)));

	// Player Layer
	std::unique_ptr<SceneNode> playerLayer(new SceneNode());
	playerLayer->attachChild(mPlayer);

	// Background Layer
	std::unique_ptr<SceneNode> backgroundLayer(new SceneNode());
	backgroundLayer->attachChild(mBackground);

	// Enemy Layer
	std::unique_ptr<SceneNode> enemyLayer(new SceneNode());

	// Wall Layer
	std::unique_ptr<SceneNode> wallLayer(new Wall(mWindow, gameResourceHolder));

	// ScoreBoard Layer
	std::unique_ptr<SceneNode> mScoreBoard(new ScoreBoard(mWindow, gameResourceHolder));

	gameScene.attachChild(backgroundLayer);
	gameScene.attachChild(playerLayer);
	gameScene.attachChild(enemyLayer);
	gameScene.attachChild(wallLayer);
	gameScene.attachChild(mScoreBoard);
}

/*****************************************************************************************************************
 *										matchesCategories											     		 *
 *****************************************************************************************************************
 * Input: SceneNode::Pair, Node::Type, Node::Type																 *
 * Output: bool indicating if the two nodes collide																 *
 * Description: The following is an internal helper function that checks if two nodes within the scene graph     *
 * collide.
 ****************************************************************************************************************/
bool Game::matchesCategories(SceneNode::Pair& colliders, Node::Type typeA, Node::Type typeB)
{
	if (colliders.first->getType() == typeA && colliders.second->getType() == typeB)
	{
		return true;
	}
	else if (colliders.first->getType() == typeB && colliders.second->getType() == typeA)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	return false;
}




