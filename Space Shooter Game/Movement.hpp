#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP


enum Direction { Up, Left, Down, Right };


class Movement
{
	private:

		bool	mIsMovingUp;
		bool	mIsMovingDown;
		bool	mIsMovingLeft;
		bool	mIsMovingRight;

	public:
				Movement();
		void	setMovement(Direction direction, bool isPressed);
		bool	getMovement(Direction direction);
};
#endif