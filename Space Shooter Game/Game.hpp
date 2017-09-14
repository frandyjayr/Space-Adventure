#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <memory>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "Background.hpp"
#include "Command.hpp"
#include "Enemy.hpp"
#include "EnemyGenerator.hpp"
#include "GameState.hpp"
#include "Movement.hpp"
#include "Player.hpp"
#include "PowerUpGenerator.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "ScoreBoard.hpp"
#include "Wall.hpp"

class Game : public GameState
{
	public:
											Game(sf::RenderWindow& window);
		void								run();

	private:
		void								processEvents();
		void								update(sf::Time deltaTime);
		void								render();
		void								loadTextures();
		void								loadSoundBuffers();
		void								loadFonts();
		void								handleCollisions();
		void								buildScene();
		bool								matchesCategories(SceneNode::Pair& colliders, Node::Type typeA, Node::Type typeB);

	private:
		sf::Time							time;
		sf::Clock							clock;
		sf::RenderWindow&					mWindow;
		std::unique_ptr<SceneNode>			mPlayer;
		std::unique_ptr<SceneNode>			mEnemy;
		std::unique_ptr<SceneNode>			mBackground;
		std::unique_ptr<SceneNode>			mScoreBoard;
		std::unique_ptr<EnemyGenerator>		mGenerator;
		std::unique_ptr<Command>			mCommand;
		ResourceHolder						gameResourceHolder;
		SceneNode							gameScene; 
		PowerUpGenerator					powerUpGenerator;
		TheGame::Level						gameLevel;
		sf::Sound							explosionSound;
		
};
#endif

