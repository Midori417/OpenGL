/**
* @file ObjectManager.h
*/
#ifndef FGENGINE_OBJECTMANAGER_H_INCLUDED
#define FGENGINE_OBJECTMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Object.h"
#include "GameObject.h"
#include "Particle.h"

namespace FGEngine::ObjectSystem
{
	/**
	* オブジェクト管理クラス
	*/
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:

		friend Singleton<ObjectManager>;
		friend MainSystem::EngineCore;

		// コンストラクタ
		ObjectManager() = default;

		/**
		* オブジェクトマネージャーを初期化
		*
		* @retval 0		正常に初期化
		* @retval 0以外 初期化失敗
		*/
		int Initialize();

		/**
		* オブジェクトマネージャーを更新
		*/
		void Update();

		/**
		* ゲームオブジェクトの削除処理
		*/
		void DestoryGameObject();

		/**
		* ゲームオブジェクトの描画処理の準備
		*/
		void RendererGameObject();

		/**
		* ゲームオブジェクトのUI描画処理
		*/
		void UIRendererGameObject();

		/**
		* ゲームオブジェクトの衝突処理の準備
		*/
		void CollisionGameObject();

		/**
		* Transformを更新
		*/
		void UpdateTransform();

		/**
		* MonoBehaviourを更新
		*/
		void UpdateMonoBehaviour();

		/**
		* パーティクルシステムの更新
		*/
		void UpdateParticleSystem();

		/**
		* Rigidbodyを更新
		*/
		void UpdateRigidbody();

		/**
		* Animatorを更新
		*/
		void UpdateAnimator();

		/**
		* AudioSourceを更新
		*/
		void UpdateAudioSource();


		/**
		* ゲームオブジェクトを取得
		*/
		GameObjectList& GetGameObjects()
		{
			return gameObjects;
		}


	public:

		/**
		* ゲームオブジェクトを作成
		*/
		GameObjectPtr CreateGameObject(const std::string& name);
		GameObjectPtr CreateGameObject(const std::string& name, const TransformPtr transform);
		GameObjectPtr CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation = Quaternion::identity);

		/**
		* メインカメラを取得
		*/
		GameObjectPtr GetMainCamera() const
		{
			return mainCamera;
		}

		/**
		* メインカメラを設定
		*/
		void SetMainCamera(GameObjectPtr camera)
		{
			mainCamera = camera;
		}

		/**
		* 全てのゲームオブジェクトを削除
		*/
		void AllClearGameObject()
		{
			gameObjects.clear();
		}

		// パーティクルエミッタの操作
		ParticleEmitterPtr AddParticleEmitter(const ParticleEmitterParameter& ep, const ParticleParameter& pp);
		ParticleEmitterPtr FindParticleEmitter(const std::string& name) const;
		void RemoveParticleEmitter(const ParticleEmitterPtr&);
		void RemoveParticleEmitterAll();

	private:

		// ゲームオブジェクト配列
		std::vector<GameObjectPtr> gameObjects;

		// メインカメラオブジェクト
		GameObjectPtr mainCamera;

		// 破壊オブジェクトが存在するかどうか
		bool isDestoryObject = false;

		// パーティクル管理
		ParticleManagerPtr particleManager;
	};
}

#endif // !OBJECTMANAGER_H_INCLUDED
