/**
* @file GameObject.h
*/
#ifndef FGENGINE_GAMEOBJECT_H_INCLUDED
#define FGENGINE_GAMEOBJECT_H_INCLUDED
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Camera.h"
#include "ImGuiLayout.h"

namespace FGEngine
{
	/**
	* ゲームに登場する様々なオブジェクトの基本クラス
	*/
	class GameObject : public Object
	{
	public:
		
		friend ObjectSystem::ObjectManager;
		friend RenderingSystem::RenderingEngine;
		friend PhysicsSystem::PhysicsEngine;
		friend Collider;

		// コンストラクタ・デストラクタ
		GameObject() = default;
		virtual ~GameObject() = default;

		// コピーと代入を禁止
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;

		/**
		* T型のコンポーネントをゲームオブジェクトに追加
		*/
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// コンポーネントが基底クラスじゃなければnullptrを返す
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// コンポーネントを作成
			auto p = std::make_shared<T>();

			// 親オブジェクトを設定
			p->ownerObject = gameObject;

			// 名前を設定
			p->SetName(ToString());

			// Transformが基底クラスの場合
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
			}

			// Colliderが基底クラスの場合
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// MonoBehaviourが基底クラスの場合
			if constexpr (std::is_base_of_v<MonoBehaviour, T>)
			{
				monoBehaviours.push_back(p);
				// 生成処理を実行
				monoBehaviours.back()->Awake();
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
			// Cameraが基底クラスの場合
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				camera = p;
			}
			// Animatorが基底クラスの場合
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				animator = p;
			}

			// ImGuiLayoutが基底クレスの場合
			if constexpr (std::is_base_of_v<UI::ImGuiLayout, T>)
			{
				imGuiLayout = p;
			}

			// コンポーネント配列に登録
			components.push_back(p);

			return p;
		}

		/**
		* T型のコンポーネントを取得
		*/
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			// コンポーネントが基底クラスじゃなければnullptrを返す
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}
			// Transformが基底クラスの場合
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				return transform;
			}
			// Rendererが基底クラスの場合
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				return renderer;
			}

			// Rigidbodyが基底クラスの場合
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				return rigidbody;
			}
			// Cameraが基底クラスの場合
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				return camera;
			}
			// Animatorが基底クラスの場合
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				return animator;
			}

			// ImGuiLayoutが基底クレスの場合
			if constexpr (std::is_base_of_v<UI::ImGuiLayout, T>)
			{
				return imGuiLayout;
			}


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

		/**
		* T型のコンポーネントを削除する 
		*/
		template<class T>
		void RemoveComponent() const
		{
			// コンポーネントが基底クラスじゃなければnullptrを返す
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}


			// コンポーネントを取得
			auto com = GetComponent<T>();

			// 破棄予定にする
			Destory(com);
		}

		/**
		* トランスフォームコンポーネントを取得
		*/
		TransformPtr GetTransform() const
		{
			return transform;
		}

	private:

		/**
		* 削除予定のコンポーネントを削除
		*/
		void DestroyComponent();

	public:

		// オブジェクトが有効かどうか
		bool isActive = true;

		// タグ
		std::string tag = "Untagged";


	private:

		// 自身を管理するポインター
		GameObjectPtr gameObject;

		// コンポーネント配列
		std::vector<ComponentPtr> components;

		// コライダー配列
		std::vector<ColliderPtr> colliders;

		// 	モノビヘイビア配列
		std::vector<MonoBehaviourPtr> monoBehaviours;

		// トランスフォームコンポーネントポインター
		TransformPtr transform;

		// 描画コンポーネントポインター
		RendererPtr renderer;	

		// 物理コンポーネントポインター
		RigidbodyPtr rigidbody;

		// カメラコンポーネントポインター
		CameraPtr camera;

		// アニメータコンポーネントポインター
		AnimatorPtr animator;

		// UIレイアウトコンポーネントポインター
		UI::ImGuiLayoutPtr imGuiLayout;

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}
#endif // !FGENGINE_GAMOBJECYT_H_INCLUDED
