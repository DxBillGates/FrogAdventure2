#pragma once
#include "Header/GameFramework/Collision/ICollider.h"
#include "Header/GameFramework/GameObject/GameObject.h"

#include <map>

enum class GameObjectCollisionType
{
	PLAYER,
	STAGE_OBJECT,
	STAGE_CLEAR,
	BLOCK,
	ADD_VELOCITY,
};

class GameObjectCollisionManager
{
private:
	std::map<GE::GameObject*, GE::ICollider*> playerColliders;
	std::map<GE::GameObject*, GE::ICollider*> otherColliders;
public:
	void AddCollider(GE::GameObject* gameObject, GE::ICollider* collider, GameObjectCollisionType type);
	void CollisionCheckPlayerTo();
	void Update();
};

