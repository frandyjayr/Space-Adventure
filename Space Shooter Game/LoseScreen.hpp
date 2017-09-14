#ifndef LOSESCREEN_HPP
#define LOSESCREEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.hpp"
#include "ResourceHolder.hpp"

class LoseScreen : public GameState
{
	public:
							LoseScreen(sf::RenderWindow& window);
		void				run();

	private:
		void				renderLoseScreen();
		void				loadTextures();
		void				loadSoundBuffers();
		void				setTextures();
		void				setSoundBuffers();
		bool				inLoseScreen();

	private:
		sf::Clock			clock;
		sf::Time			screenTimer;
		ResourceHolder		LoseScreenResourceHolder;
		sf::RenderWindow&	window;
		sf::Sprite			loseScreen;
		sf::Sound			loseSoundA;
		sf::Sound			loseSoundB;
		bool				inScreen;
		bool				soundPlayed;
};

#endif
