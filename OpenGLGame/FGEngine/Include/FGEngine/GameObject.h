/**
* @file GameObject.h
*/
#ifndef FGENGINE_GAMEOBJECT_H_INCLUDED
#define FGENGINE_GAMEOBJECT_H_INCLUDED
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingScene.h"
#include "FGEngine/Component/Component.h"
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Component/ImGuiLayout.h"
#include <string>

namespace FGEngine
{
	/**
	* ゲームオブジェクトの状態
	*/
	enum GameObjectState
	{
		// 通常
		None,

		// 破棄時間
		DestroyTime,

		// 破棄予定
		Destroyed,
	};

	/**
	* ゲームオブジェクト
	*/
	class GameObject 
	{
		friend Scene;
		friend class RenderingEngine;
		friend class PhysicsEngine;
	public:	// コンストラクタ・デストラクタ
		
		/**
		* デフォルトコンストラクタ
		*/
		GameObject() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~GameObject() = default;
						
	public:	// 禁止事項

		// コピーを禁止
		GameObject(GameObject&) = delete;

		// 代入を禁止
		GameObject& operator=(GameObject&) = delete;

	public:

		/**
		* ゲームオブジェクトを生成
		*
		* @param name ゲームオブジェクトの名前
		*/
		static GameObjectPtr Create(const std::string& name);

	public:	// コンポーネントの操作

		/**
		* T型のコンポーネントをゲームオブジェクトに追加
		*/
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// Tがコンポーネントの基底クラスじゃなければ何もしない
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// コンポーネントを作成
			auto p = std::make_shared<T>();

			// コンポーネントの所有者を設定
			p->ownerObject = gameObject;

			// Tがトランスフォームの基底クラスの場合
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
			}

			// Tがレンダラーコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				renderer = p;
			}

			// Tがリジッドボディコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				rigidbody = p;
			}

			// Tがカメラコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				camera = p;
			}

			// Tがアニメータコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				animator = p;
			}

			// TがimGUIコンポーネントの基底クラス
			if constexpr (std::is_base_of_v<ImGuiLayout, T>)
			{
				imGuiLayout = p;
			}

			// Tがコライダーコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// Tがゲームイベントの基底クラスの場合
			if constexpr (std::is_base_of_v<GameEvent, T>)
			{
				gameEvents.push_back(p);
				// 生成イベント実行
				gameEvents.back()->Awake();
			}

			// Tがオウディオコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<AudioSource, T>)
			{
				audioSources.push_back(p);
			}

			// 作成したコンポーネントを追加
			return p;
		}

		/**
		* T型のコンポーネントを取得
		*/
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			// Tがコンポーネントの基底クラスじゃなければ何もしない
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// Tがトランスフォームの基底クラスの場合
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				return std::dynamic_pointer_cast<T>(transform);
			}

			// Tがレンダラーコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				return std::dynamic_pointer_cast<T>(renderer);
			}

			// Tがリジッドボディコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				return std::dynamic_pointer_cast<T>(rigidbody);
			}

			// Tがカメラコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				return std::dynamic_pointer_cast<T>(camera);
			}

			// Tがアニメータコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				return std::dynamic_pointer_cast<T>(animator);
			}

			// TがimGUIコンポーネントの基底クラス
			if constexpr (std::is_base_of_v<ImGuiLayout, T>)
			{
				return std::dynamic_pointer_cast<T>(imGuiLayout);
			}

			// Tがコライダーコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				for (auto& x : colliders)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// Tがゲームイベントコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<GameEvent, T>)
			{
				for (auto& x : gameEvents)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// Tがオウディオコンポーネントの基底クラスの場合
			if constexpr (std::is_base_of_v<AudioSource, T>)
			{
				for (auto& x : audioSources)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// コンポーネントが見つからなかった
			return nullptr;
		}

		/**
		* T型のコンポーネントを削除する 
		*/
		template<class T>
		void RemoveComponent() const
		{
			auto p = GetComponent<T>();

			// 取得したコンポーネントを破棄予定にする
			if (p)
			{
				p->isDestroyed = true;
			}
		}

	public:

		/**
		* ゲームオブジェクトの状態を取得
		*/
		GameObjectState GetState() const;

		/**
		* シーンを取得
		*/
		Scene* GetScene() const;

		/**
		* トランスフォームコンポーネントを取得
		*/
		TransformPtr GetTransform() const;

		/**
		* ゲームオブジェクトを破棄する
		* 
		* @param destroyTime 破棄までの時間
		*/
		void Destroy(float destroyTime = 0);

	public:

		/**
		* クローンしたゲームオブジェクトを取得する
		* 
		* @param object クローンもとのオブジェクト
		* @oaram trasnform クローンするトランスフォーム
		* 
		* @return クローンしたゲームオブジェクト
		*/
		static GameObjectPtr Clone(const GameObjectPtr& object, const TransformPtr& transform = nullptr);

	private:

		/**
		* 状態が破棄待ちなら破棄時間を更新
		*/
		void UpdateDestroyTime();

		/**
		* 削除予定のコンポーネントを削除
		*/
		void DestroyComponent();

	public:

		// オブジェクトの名前
		std::string name = "GameObject";

		// オブジェクトが有効かどうか
		bool isActive = true;

		// タグ
		std::string tag = "None";

	private:

		// 自身を管理するポインター
		std::weak_ptr<GameObject> gameObject;

		// 自身を管理するシーン
		Scene* ownerScene;

		// 状態
		GameObjectState state = GameObjectState::None;

		// 破棄までの時間
		float destroyTime = 0;

	private:	// コンポーネント変数

		// トランスフォームコンポーネントポインター
		TransformPtr transform;

		// 描画コンポーネントポインター
		RendererPtr renderer;	

		// 物理コンポーネントポインター
		RigidbodyPtr rigidbody;

		// アニメータコンポーネントポインター
		AnimatorPtr animator;

		// カメラコンポーネントポインター
		CameraPtr camera;

		// UIレイアウトコンポーネントポインター
		ImGuiLayoutPtr imGuiLayout;

		// コライダー配列
		std::vector<ColliderPtr> colliders;

		// 	ゲームイベント配列
		std::vector<GameEventPtr> gameEvents;

		// AudioSourceコンポーネント配列
		std::vector<AudioSourcePtr> audioSources;
	};
}
#endif // !FGENGINE_GAMOBJECYT_H_INCLUDED
