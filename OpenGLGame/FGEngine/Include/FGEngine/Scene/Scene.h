/**
* @file Scene.h
*/
#ifndef FGENGINE_SCENE_H_INCLUDED
#define FGENGINE_SCENE_H_INCLUDED
#include "FGEngine/UsingNames/UsingScene.h"
#include "FGEngine/UsingNames/UsingAsset.h"
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingMath.h"
#include <string>

namespace FGEngine
{
	/**
	* シーンの基底クラス
	*/
	class Scene
	{
		friend class SceneManager;
	public:	// コンストラクタ・デストラクタ

		/**
		* デフォルトコンストラクタ
		*/
		Scene() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~Scene() = default;

	public:	// オブジェクトの生成・破壊

		/**
		* ゲームオブジェクトを作成
		*/
		GameObjectPtr CreateGameObject(const std::string& name);
		GameObjectPtr CreateGameObject(const std::string& name, const TransformPtr transform);
		GameObjectPtr CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* ゲームオブジェクトをクローンする
		* 
		* @param gameObject クローン元のゲームオブジェクト
		* 
		* @return 作成したゲームオブジェクト
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject);

		/**
		* ゲームオブジェクトをクローンする
		*
		* @param gameObject クローン元のゲームオブジェクト
		* @param transform	クローンするトランスフォーム
		*
		* @return 作成したゲームオブジェクト
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject, const TransformPtr& tranform);

		/**
		* ゲームオブジェクトをクローンする
		*
		* @param gameObject クローン元のゲームオブジェクト
		* @param position	クローンした時の位置
		* @param rotation	クローンした時の回転
		*
		* @return 作成したゲームオブジェクト
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation);

		/**
		* 全てのゲームオブジェクトを削除する
		*/
		void AllClearGameObject();

	public:

		/**
		* カメラコンポーネントを取得
		*/
		CameraPtr GetMainCameraInfo() const;

		/**
		* メインカメラを設定
		* 
		* @param camera 設定するカメラ
		*/
		void SetMainCameraInfo(const CameraPtr& camera);

	protected:

		/**
		* シーンの初期化
		*
		* @param engine エンジン
		*
		* @retval true	初期化成功
		* @retval false	初期化失敗
		*/
		virtual bool Initialize()
		{
			return true;
		}

	private:	// シーンのイベント

		/**
		* 生成時の処理
		*/
		void Awake();

		/**
		* 毎フレーム時の処理
		*/
		void Update();

		/**
		* 毎フレーム描画する
		*/
		void Render();

		/**
		* 終了時の処理
		*/
		void Fainalize();

	private:	// ゲームオブジェクトの処理

		/**
		* ゲームイベントの更新
		*/
		void UpdateGameEvent();

		/**
		* Animatorを更新
		*/
		void UpdateAnimator();

		/**
		* AudioSourceを更新
		*/
		void UpdateAudioSource();

		/**
		* トランスフォームを更新
		*/
		void UpdateTransform();

		/**
		* リジッドボディを更新
		*/
		void UpdateRigidbody();

		/**
		* ゲームオブジェクトの衝突処理の準備
		*/
		void CollisionGameObject();

		/**
		* ゲームオブジェクトの描画処理の準備
		*/
		void RendererGameObject();

		/**
		* ゲームオブジェクトのUI描画処理
		*/
		void UIRendererGameObject();

		/**
		* ゲームオブジェクトの削除処理
		*/
		void DestoryGameObject();

	public:

		// シーンの名前
		std::string name = "デフォルトシーン";

		// スカイボックス用のマテリアル
		MaterialPtr skyBoxMaterial;

	private:	// ゲームオブジェクト

		// メインカメラコンポーネント
		CameraPtr mainCamera;
		
		// ゲームオブジェクト配列
		GameObjectList gameObjects;
	};
}
#endif // !SCENEH_INCLUDED
