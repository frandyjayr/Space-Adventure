#include "LoseScreen.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: sf::RenderWindow																						 *
 * Output: None																									 *
 * Description: The constructor initializes the window variable. It also loads all textures, soundBuffers, and   *
 * any background music. Once initialized, it sets the textures, soundBuffers, and music for the game. Finally,  *
 * it sets up the bools for the menu.																			 *
 ****************************************************************************************************************/
LoseScreen::LoseScreen(sf::RenderWindow& window) : window(window)
{
	loadTextures();
	loadSoundBuffers();
	setTextures();
	setSoundBuffers();
	inScreen = true;
	soundPlayed = false;

}

/*****************************************************************************************************************
*										run()		  															 *
*****************************************************************************************************************
* Input: None																									 *
* Output: None																								     *
* Description: Virtual function that runs the menu gamestate, rendering the images, playing the music, and      *
* stopping the music once the gamestate has ended																 *
****************************************************************************************************************/
void LoseScreen::run()
{
	loseSoundA.play();
	renderLoseScreen();
}

/*****************************************************************************************************************
 *										inLoseScreen()															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the player is still in the Lose screen											 *
 * Description: The bool-returning function will return true if the player is inside the lose gamestate, else    *
 * return false;																								 *
 ****************************************************************************************************************/
bool LoseScreen::inLoseScreen()
{
	return inScreen;
}

void LoseScreen::loadTextures()
{
	LoseScreenResourceHolder.loadTextures(Textures::ID::LoseScreen, "Media/Textures/LoseScreen/LoseScreen.jpg");
}

/*****************************************************************************************************************
 *										loadSoundBuffers()  													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's sound buffers into the menu's resourceHolder instance for later    *
 * use.																											 *
 ****************************************************************************************************************/
void LoseScreen::loadSoundBuffers()
{
	LoseScreenResourceHolder.loadSoundBuffers(SoundBuffers::ID::LoseA, "Media/SoundBuffers/Lose.flac");
	LoseScreenResourceHolder.loadSoundBuffers(SoundBuffers::ID::LoseB, "Media/SoundBuffers/Lose2.wav");
}

/*****************************************************************************************************************
 *										setTextures()  		    												 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's textures into the menu's resourceHolder instance for later         *
 * use.																											 *
 ****************************************************************************************************************/

void LoseScreen::setTextures()
{
	loseScreen.setTexture(LoseScreenResourceHolder.getTextures(Textures::ID::LoseScreen));
}

/*****************************************************************************************************************
 *										setSoundBuffers()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function sets the sound buffer for the game. The soundBuffer for the menu include the hover  *
 * sound that occurs in the menu when the player hovers their mouse over the play or exit buttons                *
 ****************************************************************************************************************/
void LoseScreen::setSoundBuffers()
{
	loseSoundA.setBuffer(LoseScreenResourceHolder.getSoundBuffers(SoundBuffers::ID::LoseA));
	loseSoundB.setBuffer(LoseScreenResourceHolder.getSoundBuffers(SoundBuffers::ID::LoseB));
}

/*****************************************************************************************************************
 *										renderLoseScreen()  													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function renders the lose screen image. It is a single image that says "You Lose". The state *
 * will automatically end after the timer has ended.															 *
 ****************************************************************************************************************/
void LoseScreen::renderLoseScreen()
{

	while (window.isOpen() && inLoseScreen())
	{
		window.clear();
		window.draw(loseScreen);
		window.display();

		screenTimer = clock.getElapsedTime();
		if (screenTimer.asSeconds() > 2 && !soundPlayed)
		{
			soundPlayed = true;
			loseSoundB.play();
		}
		if (screenTimer.asSeconds() > 4)
		{
			inScreen = false;
		}
	}
	window.clear();
}
