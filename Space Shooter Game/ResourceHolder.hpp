#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <iostream>
#include <list>
#include <map>
#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID {
		Background, Beam, EnemyA, EnemyB, EnemyC, Spaceship, Wall,

		/* Power Ups */
		AddShip, BulletSpeed, PlayerSpeed,

		/* Bosses */
		BossA,

		/* Menu & LoseScreen */
		LoseScreen, MenuNeutral, MenuPlay, MenuExit};
}

namespace SoundBuffers
{
	enum ID {Explosion, LoseA, LoseB, Missile, PowerUp, Hover};
}

namespace Music
{
	enum ID {Game, Menu};
}

namespace Fonts
{
	enum ID {DigitalTech};
}

class ResourceHolder : public sf::NonCopyable
{
	public:
		void				loadTextures(Textures::ID id, const std::string& filename);
		void				loadSoundBuffers(SoundBuffers::ID id, const std::string& filename);
		void				loadMusic(Music::ID id, const std::string& filename);
		void				loadFonts(Fonts::ID id, const std::string& filename);
		sf::Texture&		getTextures(Textures::ID id);
		sf::SoundBuffer&	getSoundBuffers(SoundBuffers::ID id);
		sf::Music&			getMusic(Music::ID id);
		sf::Font&			getFont(Fonts::ID id);

	private:
		std::map<Textures::ID, std::unique_ptr<sf::Texture>>			mTextureMap;
		std::map<SoundBuffers::ID, std::unique_ptr<sf::SoundBuffer>>	mSoundBufferMap;
		std::map<Music::ID, std::unique_ptr<sf::Music>>					mMusicMap;
		std::map<Fonts::ID, std::unique_ptr<sf::Font>>					mFontMap;
};
#endif