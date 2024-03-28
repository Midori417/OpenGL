/**
* @file GameObject.h
*/
#pragma once
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"

namespace FGEngine
{
	/**
	* ゲームに登場する様々なオブジェクトの基本クラス
	*/
	class GameObject : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		GameObject() = default;
		virtual ~GameObject() = default;

		// コピーと代入を禁止
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;

		// ゲームオブジェクトにコンポーネントを追加する
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// コンポーネントが基底クラスじゃなければnullptrを返す
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// コンポーネントを作成
			auto p = std::make_shared<T>;

			// Colliderが基底クラスの場合
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// MonoBehaviourが基底クラスの場合
			if constexpr (std::is_base_of_v<MonoBehaviour, T>)
			{
				monoBehaviours.push_back(p);
				p->Awake();
			}

			// Transformが基底クラスの場合
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
			}

			// Rendererが基底クラスの場合
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				renderer = p;
			}
			// Rigidbodyが基底クラスの場合
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				rigidbody = p;
			}

			p->SetName(ToString());
			// コンポーネント配列に登録
			components.push_back(p);
		}

		// コンポーネントを検索する
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			for (auto& e : components)
			{
				// T型にアップキャストしている場合取得する
				auto p = std::dynamic_pointer_cast<T>(e);
				if (p)
				{
					// 見つかったコンポーネント
					return p;
				}
			}
			// 見つかなかった
			return nullptr;
		}

		// Transformを取得
		TransformPtr GetTransform() const
		{
			return transform;
		}

	public:

		std::string tag = "Untagged";		// タグ
		bool isActive = true;				// オブジェクトが有効かどうか

	private:

		std::vector<ComponentPtr> components;			// コンポーネント配列
		std::vector<ColliderPtr> colliders;				// コライダー配列
		std::vector<MonoBehaviourPtr> monoBehaviours;	// 	アプリケーションコンポーネント配列
		TransformPtr transform;			// トランスフォームコンポーネントポインター
		RendererPtr renderer;			// 描画コンポーネントポインター
		RigidbodyPtr rigidbody;			// 物理コンポーネントポインター

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}