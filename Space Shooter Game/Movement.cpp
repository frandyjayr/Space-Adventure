#include "Movement.hpp"

/*****************************************************************************************************************
 *										Constructor												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Initializes the moving variables to false to indicate that there is no movement					 *
 ****************************************************************************************************************/
Movement::Movement()
{
	mIsMovingUp = false;
	mIsMovingDown = false;
	mIsMovingLeft = false;
	mIsMovingRight = false;
}

/*****************************************************************************************************************
 *										setMovement()											     			 *
 *****************************************************************************************************************
 * Input: Direction, bool isPressed																				 *
 * Output: None																								     *
 * Description: sets the private variables movement to true or false based on the argument input			     *
 ****************************************************************************************************************/
void Movement::setMovement(Direction direction, bool isPressed)
{
	switch (direction)
	{
		case (Up):
		{
			mIsMovingUp = isPressed;
			break;
		}
		case (Down):
		{
			mIsMovingDown = isPressed;
			break;
		}
		case (Left):
		{
			mIsMovingLeft = isPressed;
			break;
		}
		case (Right):
		{
			mIsMovingRight = isPressed;
			break;
		}
	}
}

/*****************************************************************************************************************
 *										getMovement()											     			 *
 *****************************************************************************************************************
 * Input: RenderWindow, ResourceHolder, PowerUp Position, PowerUp Velocity, PowerUp Type						 *
 * Output: bool indicating if the direction argument is moving												     *
 * Description: Accessor function that returns a bool indicating if the direction argument is moving or not      *
 ****************************************************************************************************************/
bool Movement::getMovement(Direction direction)
{
	switch (direction)
	{
		case (Up):
		{
			return mIsMovingUp;
		}
		case (Down):
		{
			return mIsMovingDown;
		}
		case (Left):
		{
			return mIsMovingLeft;
		}
		case (Right):
		{
			return mIsMovingRight;
		}
	}
}