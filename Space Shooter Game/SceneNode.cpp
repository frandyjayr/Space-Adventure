#include "SceneNode.hpp"


/*****************************************************************************************************************
 *										Constructor													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: sets the toBeDestroyed variable to false to ensure none of the nodes get destroyed to begin with *
 ****************************************************************************************************************/
SceneNode::SceneNode()
{
	toBeDestroyed = false;
}

/*****************************************************************************************************************
 *										attachChild													     		 *
 *****************************************************************************************************************
 * Input: unique_ptr<SceneNode>																					 *
 * Output: None																									 *
 * Description: Attaches a child to the scene node																 *
 ****************************************************************************************************************/
void SceneNode::attachChild(Ptr& child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

/*****************************************************************************************************************
 *										detachChild()												     		 *
 *****************************************************************************************************************
 * Input: SceneNode																								 *
 * Output: SceneNode																							 *
 * Description: Detaches a child from the scene. The scene node that is detached also detaches its children to   *
 * prevent any errors from occuring.																			 *
 ****************************************************************************************************************/
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
	[&](Ptr& p) -> bool {return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result; 

	return 0;
}

/*****************************************************************************************************************
 *										draw()														     		 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and draws the each scene Node							 *
 ****************************************************************************************************************/
void SceneNode::draw(sf::RenderWindow& window)
{
	drawCurrent(window);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->draw(window);
	}
}

/*****************************************************************************************************************
 *										update()													     		 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and updates each scene node								 *
 ****************************************************************************************************************/
void SceneNode::update(sf::Time deltaTime)
{
	updateCurrent(deltaTime);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->update(deltaTime);
	}
	removeDestroyedObjects();
}

/*****************************************************************************************************************
 *										processEvents()												     		 * 
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and processes each scene Node event						 *
 ****************************************************************************************************************/
void SceneNode::processEvents()
{
	processEventsCurrent();

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->processEvents();
	}
}

/*****************************************************************************************************************
 *										powerUp()														   		 *
 *****************************************************************************************************************
 * Input: Power power																							 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and calls the powerUp function for each scene Node       *
 ****************************************************************************************************************/
void SceneNode::powerUp(Power power)
{
	powerUpCurrent(power);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->powerUp(power);
	}
}

/*****************************************************************************************************************
 *										collidesWithObject()										     		 *
 *****************************************************************************************************************
 * Input: SceneNode, SceneNode																					 *
 * Output: bool indicating if the two sceneNode collide															 *
 * Description: checks if two sceneNodes intersect. If so, it returns true										 *
 ****************************************************************************************************************/
bool SceneNode::collidesWithObject(SceneNode& lhs, SceneNode& rhs)
{
	return lhs.getBounds().intersects(rhs.getBounds());
}

/*****************************************************************************************************************
 *										isMarkedForDestruction()									     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if an object is to be destroyed														 *																					 *
 * Description: returns true if an object is to be destroyed													 *
 ****************************************************************************************************************/
bool SceneNode::isMarkedForDestruction()
{
	return toBeDestroyed;
}

/*****************************************************************************************************************
 *										gameIsOver()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Bool	indicating if the game is over																	 *
 * Description: The following function is a virtual function and is meant to be overloaded by the inherited		 *
 * functions																									 *
 ****************************************************************************************************************/
bool SceneNode::gameIsOver()
{
	return 0;
}

/*****************************************************************************************************************
 *										hasOneHealth()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the sceneNode has one health														 *
 * Description: The following function is a virtual function and is meant to be overloaded by the inherited		 *
 * functions																									 *
 ****************************************************************************************************************/
bool SceneNode::hasOneHealth()
{
	return false;
}

/*****************************************************************************************************************
 *										reset()												     				 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and resets each scene Node								 *
 ****************************************************************************************************************/
void SceneNode::reset()
{
	resetCurrent();

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->reset();
	}
}

/*****************************************************************************************************************
 *										getPosition()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::Vector2f																							 *
 * Description: returns the position of the scene Node															 *
 ****************************************************************************************************************/
sf::Vector2f SceneNode::getPosition()
{
	return mEntity.getPosition();
}

/*****************************************************************************************************************
 *										getBounds()													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::FloatRect																						 *
 * Description: returns the gloabl bounds of the scene Node														 *
 ****************************************************************************************************************/
sf::FloatRect SceneNode::getBounds()
{
	return mEntity.getGlobalBounds();
}

/*****************************************************************************************************************
 *										getLastChildPosition()										     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::Vector2f																							 *
 * Description: returns the position of the last Child in the scene Node										 *
 ****************************************************************************************************************/
sf::Vector2f SceneNode::getLastChildPosition()
{
	return mChildren.back()->getPosition();
}

/*****************************************************************************************************************
 *										setForDestruction()											     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: If called, the toBeDestroyed bool is set to true, destroying the current Scene Node				 *
 ****************************************************************************************************************/
void SceneNode::setForDestruction()
{
	toBeDestroyed = true;
}

/*****************************************************************************************************************
 *										removeDestroyedObjects()									     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: destroys all objects within the scene node whose toBeDestroyed bool value is set to true		 *
 ****************************************************************************************************************/
void SceneNode::removeDestroyedObjects()
{
	auto wreckFieldBegin = std::remove_if(mChildren.begin(), mChildren.end(),
	std::mem_fn(&SceneNode::isMarkedForDestruction));
	mChildren.erase(wreckFieldBegin, mChildren.end());

	std::for_each(mChildren.begin(), mChildren.end(),
	std::mem_fn(&SceneNode::removeDestroyedObjects));
}

/*****************************************************************************************************************
 *										checkNodeCollisions()										     		 *
 *****************************************************************************************************************
 * Input: SceneNode, std::set<Pair>																				 *
 * Output: None																									 *
 * Description: The following functions traverses through the entire scene graph and checks if each node         *
 * collides wtih any other node in the graph other than itself. If so, it inserts the node pairs within a		 *
 * std::set<Pair> that will later be used																		 *
 ****************************************************************************************************************/
void SceneNode::checkNodeCollisions(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collidesWithObject(*this, node)
	&& !isMarkedForDestruction() && !node.isMarkedForDestruction())
	{
		collisionPairs.insert(std::minmax(this, &node));
	}

	for (Ptr& child : mChildren)
	{
		child->checkNodeCollisions(node, collisionPairs);
	}
}

/*****************************************************************************************************************
 *										checkSceneCollision											     		 *
 *****************************************************************************************************************
 * Input: SceneNode, std::set<Pair>																				 *
 * Output: None																									 *
 * Description: Traverses the entire scenegraph to check if each node collides with any other node within the    *
 * Scene graph.																									 *
 ****************************************************************************************************************/
void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollisions(sceneGraph, collisionPairs);

	for (Ptr& child : sceneGraph.mChildren)
	{
		checkSceneCollision(*child, collisionPairs);
	}
}

/*****************************************************************************************************************
 *										getType()													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Node::Type																							 *
 * Description: accessor function that returns the type of the current Node										 *
 ****************************************************************************************************************/
Node::Type SceneNode::getType()
{
	return type;
}

/*****************************************************************************************************************
 *										command()													     		 *
 *****************************************************************************************************************
 * Input: sf::KeyBoard, bool isPressed																			 *
 * Output: None																									 *
 * Description: Traverses through the entire sceneGraph and processes each commandCurrent function				 *
 ****************************************************************************************************************/
void SceneNode::command(sf::Keyboard::Key key, bool isPressed)
{
	commandCurrent(key, isPressed);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++)
	{
		(*itr)->command(key, isPressed);
	}
}

/*****************************************************************************************************************
 *										drawCurrent()												     		 *
 *****************************************************************************************************************
 * Input: RenderWindow																							 *
 * Output: None																									 *
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::drawCurrent(sf::RenderWindow& target)
{
}

/*****************************************************************************************************************
 *										updateCurrent()												     		 *
 *****************************************************************************************************************
 * Input: sf::Time deltaTime																					 *
 * Output: None																									 *
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::updateCurrent(sf::Time deltaTime)
{
}

/*****************************************************************************************************************
 *										powerUpCurrent()											     		 *
 *****************************************************************************************************************
 * Input: Power power																							 *
 * Output: None																									 *
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::powerUpCurrent(Power power)
{
}

/*****************************************************************************************************************
 *										processEventsCurrent()												     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::processEventsCurrent()
{
}

/*****************************************************************************************************************
 *										resetCurrent()												     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::resetCurrent()
{
}

/*****************************************************************************************************************
 *										commandCurrent()												     	 *
 *****************************************************************************************************************
 * Input: sf::KeyBoard::Key, bool isPressed																		 *
 * Output: None																									 * 
 * Description: Virtual function that is to be overloaded by its inherited classes								 *
 ****************************************************************************************************************/
void SceneNode::commandCurrent(sf::Keyboard::Key key, bool isPressed)
{
}

