#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"

namespace TheGame
{
	class Level
	{
		public:
			static int				getLevel();
			static void				increaseLevel();
			int						healthIncreaseByLevel();
			float					bulletIncreaseByLevel();
			bool					bossDefeated();
			static void				changeBossStatus();
			void					resetLevel();

		private:
			static int				level;
			static bool				bossIsDead;


	};
}
#endif