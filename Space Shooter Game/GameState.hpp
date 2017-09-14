#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameState
{
	public:
						GameState();
		void virtual	run() = 0;

	protected:
		bool			gameStateIsActive;
};
#endif