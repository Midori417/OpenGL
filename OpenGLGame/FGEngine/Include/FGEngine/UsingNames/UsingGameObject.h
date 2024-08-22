/**
* @file UsinGameObject.h
*/
#ifndef FGENGINE_USINGGAMEOBJECT_H_INCLUDED
#define FGENGINE_USINGGAMEOBJECT_H_INCLUDED
#include <memory>
#include <vector>

namespace FGEngine
{
	// ゲームオブジェクト
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using GameObjectList = std::vector<GameObjectPtr>;
}

#endif // !FGENGINE_USINGGAMEOBJECT_H_INCLUDED