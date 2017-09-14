#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <assert.h>
#include <functional>
#include <SFML/Graphics.hpp>
#include <memory>

#include "ResourceHolder.hpp"

namespace Node 
{
	enum Type { Enemy, PlayerMissile, EnemyMissile, Player, PowerUpShip, PowerUpBullet, PowerUpPlayerSpeed, Wall};
}

enum Power
{
	AddShip, BulletSpeed, PlayerSpeed
};

class SceneNode : public sf::Transformable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
		typedef std::pair<SceneNode*, SceneNode*> SceneNode::Pair;

	public:
								SceneNode();
		virtual void			attachChild(Ptr& child);
		Ptr						detachChild(const SceneNode& node);
		virtual void			draw(sf::RenderWindow& window);
		virtual void			update(sf::Time deltaTime);
		virtual void			processEvents();
		virtual void			powerUp(Power power);
		virtual void			command(sf::Keyboard::Key key, bool isPressed);
		virtual bool			collidesWithObject(SceneNode& lhs, SceneNode& rhs);
		virtual bool			isMarkedForDestruction();
		virtual bool			gameIsOver();
		virtual bool			hasOneHealth();
		virtual void			reset();
		virtual sf::Vector2f	getPosition();
		virtual sf::FloatRect	getBounds();
		sf::Vector2f			getLastChildPosition();
		virtual void			setForDestruction();
		void					removeDestroyedObjects();
		void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		Node::Type				getType();

	protected:
		std::vector<Ptr>		mChildren;
		SceneNode*				mParent;
		bool					toBeDestroyed;
		sf::Sprite				mEntity;
		Node::Type				type;

	private:
		void					checkNodeCollisions(SceneNode& node, std::set<Pair>& collisionPairs);
		virtual void			drawCurrent(sf::RenderWindow& target);
		virtual void			updateCurrent(sf::Time deltaTime);
		virtual void			powerUpCurrent(Power power);
		virtual void			processEventsCurrent();
		virtual void			resetCurrent();

		virtual void			commandCurrent(sf::Keyboard::Key key, bool isPressed);

};
#endif