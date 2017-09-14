#include "Command.hpp"

bool Command::gameIsRunning = true;

/*****************************************************************************************************************
 *										constructor													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: RenderWindow																							 *
 * Description: Initializes the pressed variable to false														 *
 ****************************************************************************************************************/
Command::Command(sf::RenderWindow& window) : window(window)
{
	pressed = false;
}

/*****************************************************************************************************************
 *										giveCommand()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::KeyBoard::Key																					 *
 * Description: returns a keyboard key that the user presses													 *
 ****************************************************************************************************************/
sf::Keyboard::Key Command::giveCommand()
{
	return key;
}

/*****************************************************************************************************************
 *										isPressed()												     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating is a key is pressed																	 *
 * Description: returns true if a key is pressed																 *
 ****************************************************************************************************************/
bool Command::isPressed()
{
	return pressed;
}

/*****************************************************************************************************************
 *										processKeyBoardEvents()									     			 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Process any keyboard events that occur. If a key is pressed, it will update the class to indicate*
 * that a specific key is pressed and will output that key in the give command function							 *
 ****************************************************************************************************************/
void Command::processKeyBoardEvents()
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		// Check for any key presses and processes if they are relevant keys
		switch (event.type)
		{
			case sf::Event::KeyPressed:
			{
				handleKeyBoardInput(event.key.code, true);
				break;
			}
			case sf::Event::KeyReleased:
			{
				handleKeyBoardInput(event.key.code, false);
				break;
			}
			case sf::Event::Closed:
			{
				window.close();
				closeGameWindow();
				break;
			}
		}
	}
}

void Command::closeGameWindow()
{
	gameIsRunning = false;
}

/*****************************************************************************************************************
 *										processKeyBoardEvents()									     			 *
 *****************************************************************************************************************
 * Input: sf::KeyBoard::Key, bool isPressed																	     * 
 * Output: None																									 *
 * Description: The function will check if any key is pressed, if that key is pressed, it will set that key      *
 * to true, indicating that it was pressed. If the key is released, it will set the key press to false,          *
 * indicating that the key is no longer pressed.
 ****************************************************************************************************************/
void Command::handleKeyBoardInput(sf::Keyboard::Key key, bool isPressed)
{

	if (key == sf::Keyboard::Key::Left)
	{
		this->key = key;
		pressed = isPressed;
	}
	if (key == sf::Keyboard::Key::Right)
	{
		this->key = key;
		pressed = isPressed;
	}
	if (key == sf::Keyboard::Key::Up)
	{
		this->key = key;
		pressed = isPressed;
	}
}

bool Command::gameWindowIsOpen()
{
	return gameIsRunning;
}
