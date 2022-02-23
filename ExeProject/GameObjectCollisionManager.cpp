#include "GameObjectCollisionManager.h"
#include "Header/GameFramework/Collision/CollisionManager.h"

void GameObjectCollisionManager::AddCollider(GE::GameObject* gameObject, GE::ICollider* collider, GameObjectCollisionType type)
{
	switch (type)
	{
	case GameObjectCollisionType::PLAYER:
		playerColliders.insert(std::make_pair(gameObject,collider));
		break;
	case GameObjectCollisionType::STAGE_OBJECT:
		otherColliders.insert(std::make_pair(gameObject, collider));
		break;
	case GameObjectCollisionType::STAGE_CLEAR:
		otherColliders.insert(std::make_pair(gameObject, collider));
		break;
	case GameObjectCollisionType::BLOCK:
		otherColliders.insert(std::make_pair(gameObject, collider));
		break;
	case GameObjectCollisionType::ADD_VELOCITY:
		otherColliders.insert(std::make_pair(gameObject, collider));
		break;
	default:
		break;
	}
}

void GameObjectCollisionManager::CollisionCheckPlayerTo()
{
	for (auto& player : playerColliders)
	{
		for (auto& other : otherColliders)
		{
			if (GE::CollisionManager::CheckHit(player.second, other.second))
			{
				player.second->Hit(other.second, other.first);
				other.second->Hit(player.second, player.first);
			}
		}
	}
}

void GameObjectCollisionManager::Update()
{
	CollisionCheckPlayerTo();
}
