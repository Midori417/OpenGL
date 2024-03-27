/**
* @file GameObject.h
*/
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Object.h"

#include <string>
#include <vector>
#include <memory>
#include <type_traits>

namespace FGEngine
{

	// 先行宣言
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;
	class Renderer;
	using RendererPtr = std::shared_ptr<Renderer>;
	class MonoBehaviour;
	using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;

	/**
	* ゲームに登場する様々なオブジェクトの基本クラス
	*/
	class GameObject : public Object
	{
		friend ObjectManager;
	public:

		GameObject() = default;
		virtual ~GameObject() = default;

		// コピーと代入を禁止
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;



		// ゲームオブジェクトにコンポーネントを追加する
		template<class T>
		std::shared_ptr<T> AddComponent();

		// コンポーネントを検索する
		template<class T>
		std::shared_ptr<T> GetComponent() const;


	

	public:

		std::string tag = "Untagged";			// タグ
		TransformPtr transform;
		RendererPtr renderer;

	private:

		bool isActive = true;
		std::vector<ComponentPtr> components;	// コンポーネント配列
		std::vector<MonoBehaviourPtr> monoBehabiours;	
		std::vector<ColliderPtr> colliders;	// コライダー配列

	public:

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}
#endif // !GAMEOBJECT_H_INCLUDED
