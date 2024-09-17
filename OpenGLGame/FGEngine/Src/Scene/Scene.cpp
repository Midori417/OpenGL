/**
* @file Scene.cpp
*/
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/Debug.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/MainSystem/PhysicsEngine.h"
#include "FGEngine/MainSystem/RenderingEngine.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Shader.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* ゲームオブジェクトを作成
	*
	* @param name オブジェクトの名前
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Scene::CreateGameObject(const std::string& name)
	{
		auto obj = GameObject::Create(name);

		obj->ownerScene = this;

		// ゲームオブジェクト配列に登録
		gameObjects.push_back(obj);

		// 作成したゲームオブジェクト
		return obj;
	}

	/**
	* typeにあったオブジェクトを生成する
	*
	* @param type 生成したいオブジェクトの名前
	* namespace CreateObjectから選択推奨
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Scene::Instantate(const std::string& type)
	{
		if (type == CreateObjectType::Empty)
		{
			return CreateGameObject("GameObject");
		}
		else if (type == CreateObjectType::Camera)
		{
			GameObjectPtr p = CreateGameObject("Camera");
			CameraPtr camera = p->AddComponent<Camera>();

			// メインカメラが存在しない場合設定する
			SetMainCameraInfo(camera);

			return p;
		}
		else if (type == CreateObjectType::GameObject3D::Cube)
		{
			GameObjectPtr p = CreateGameObject("Cube");
			p->AddComponent<AabbCollider>();
			MeshRendererPtr mesh = p->AddComponent<MeshRenderer>();

			// メッシュを設定する
			auto assetManger = AssetManager::GetInstance();
			mesh->mesh = assetManger->GetStaticMesh("Cube");
			mesh->shader = assetManger->GetShader(DefalutShader::Unlit);

			return p;
		}
		else if (type == CreateObjectType::GameObject3D::Sphere)
		{
			GameObjectPtr p = CreateGameObject("Sphere");
			MeshRendererPtr mesh = p->AddComponent<MeshRenderer>();

			// メッシュを生成
			auto assetManger = AssetManager::GetInstance();
			mesh->mesh = assetManger->GetStaticMesh("Sphere");
			mesh->shader = assetManger->GetShader(DefalutShader::Unlit);

			return p;
		}

		LOG_ERROR("(%s)このタイプのオブジェクトは存在しません", type);
		return nullptr;
	}

	/**
	* ゲームオブジェクトをクローンする
	*
	* @param gameObject クローン元のゲームオブジェクト
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Scene::Instantate(const GameObjectPtr& gameObject)
	{
		GameObjectPtr p = GameObject::Clone(gameObject);

		// シーンを設定する
		p->ownerScene = this;

		// 自身を持たせる
		p->gameObject = p;

		// 配列に追加
		gameObjects.push_back(p);

		return p;
	}

	/**
	* ゲームオブジェクトをクローンする
	*
	* @param gameObject クローン元のゲームオブジェクト
	* @param transform	クローンするトランスフォーム
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Scene::Instantate(const GameObjectPtr& gameObject, const TransformPtr& tranform)
	{
		GameObjectPtr p = GameObject::Clone(gameObject, tranform);

		// シーンを設定する
		p->ownerScene = this;

		// 自身を持たせる
		p->gameObject = p;

		// 配列に追加
		gameObjects.push_back(p);

		return p;
	}

	/**
	* ゲームオブジェクトをクローンする
	*
	* @param gameObject クローン元のゲームオブジェクト
	* @param position	クローンした時の位置
	* @param rotation	クローンした時の回転
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Scene::Instantate(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation)
	{
		GameObjectPtr p = Instantate(gameObject);

		// 位置と回転を設定
		TransformPtr transform = p->GetTransform();
		transform->position = position;
		transform->rotation = rotation;

		// 配列に追加
		gameObjects.push_back(p);

		return p;
	}

	/**
	* 全てのゲームオブジェクトを削除する
	*/
	void Scene::AllClearGameObject()
	{
		gameObjects.clear();
	}

	/**
	* カメラコンポーネントを取得
	*/
	CameraPtr Scene::GetMainCameraInfo() const
	{
		return mainCamera;
	}

	/**
	* メインカメラを設定
	*
	* @param camera 設定するカメラ
	*/
	void Scene::SetMainCameraInfo(const CameraPtr& camera)
	{
		mainCamera = camera;
	}

	/**
	* 生成時の処理
	*/
	void Scene::Awake()
	{
		// ゲームオブジェクト配列を予約
		gameObjects.reserve(1000);
	}

	/**
	* 毎フレーム時の処理
	*/
	void Scene::Update()
	{
		if (!gameObjects.empty())
		{
			UpdateGameEvent();
			UpdateTransform();
			UpdateAudioSource();
			CollisionGameObject();
			UpdateRigidbody();
			UpdateAnimator();

			DestoryGameObject();
		}
	}

	/**
	* 毎フレーム描画する
	*/
	void Scene::Render()
	{
		UIRendererGameObject();
		RendererGameObject();
	}

	/**
	* 終了時の処理
	*/
	void Scene::Fainalize()
	{
		AllClearGameObject();
	}


	/**
	* ゲームイベントの更新
	*/
	void Scene::UpdateGameEvent()
	{
		// Startイベント
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// イベントがなければ何もスキップする
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (int i = 0; i < x->gameEvents.size(); ++i)
				{
					auto event = x->gameEvents[i];
					if (event->isActive && !event->isStart)
					{
						event->Start();
						event->isStart = true;
					}
				}
			}
		}

		// Updateイベント
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// イベントがなければ何もスキップする
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (int i = 0; i < x->gameEvents.size(); ++i)
				{
					auto event = x->gameEvents[i];
					if (event->isActive && event->isStart)
					{
						event->Update();
					}
				}
			}
		}

		// LateUpdateイベント
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// イベントがなければ何もスキップする
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (int i = 0; i < x->gameEvents.size(); ++i)
				{
					auto event = x->gameEvents[i];
					if (event->isActive && event->isStart)
					{
						event->LateUpdate();
					}
				}
			}
		}
	}

	/**
	* Animatorを更新
	*/
	void Scene::UpdateAnimator()
	{
		for (auto& x : gameObjects)
		{
			auto e = x->animator;
			if (e)
			{
				e->Update();
			}
		}
	}

	/**
	* AudioSourceを更新
	*/
	void Scene::UpdateAudioSource()
	{
		for (auto x : gameObjects)
		{
			// 持っていなければ何もしない
			if (x->audioSources.empty())
			{
				continue;
			}
			for (auto audio : x->audioSources)
			{
				audio->Set3DSoundPos();
			}
		}
	}

	/**
	* トランスフォームを更新
	*/
	void Scene::UpdateTransform()
	{
		// ローカル座標変換行列を更新
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			GameObjectPtr e = gameObjects[i];
			if (e->transform != nullptr)
			{
				e->transform->LocalTransformUpdate();
			}
		}

		// ワールド座標変換行列を計算
		std::vector<Matrix4x4> worldTransforms(gameObjects.size());
		std::vector<Matrix3x3> worldNormals(gameObjects.size());
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			TransformPtr e = gameObjects[i]->transform;
			if (e != nullptr)
			{
				Matrix4x4 m = e->GetLocalTransformMatrix();
				Matrix3x3 n = e->GetNormalMatrix();
				for (e = e->GetParent(); e; e = e->GetParent())
				{
					m = e->GetLocalTransformMatrix() * m;
					n = e->GetNormalMatrix() * n;
				}
				worldTransforms[i] = m;
				worldNormals[i] = n;
			}
		}

		// ワールド座標変換行列をゲームオブジェクトに設定
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			gameObjects[i]->transform->worldTransformMatrix = worldTransforms[i];
			gameObjects[i]->transform->normalMatrix = worldNormals[i];
		}
	}

	/**
	* リジッドボディを更新
	*/
	void Scene::UpdateRigidbody()
	{
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				auto e = x->rigidbody;
				if (e)
				{
					e->GravityUpdate();
				}
			}
		}
	}

	/**
	* ゲームオブジェクトの衝突処理の準備
	*/
	void Scene::CollisionGameObject()
	{
		// ワールド座標系の衝突判定を作成
		std::vector<WorldColliderList> colliders;
		colliders.reserve(gameObjects.size());
		for (const auto& e : gameObjects)
		{
			if (e->colliders.empty())
			{
				continue; // コライダーを持っていなかったら何もしない
			}

			if (e->rigidbody)
			{
				e->rigidbody->isGrounded = false;
			}

			// 衝突判定を作成
			WorldColliderList list(e->colliders.size());
			for (int i = 0; i < e->colliders.size(); ++i)
			{
				// オリジナルのコライダーをコピー
				list[i].origin = e->colliders[i];

				//コライダーの座標をワールド座標に変換
				list[i].world = e->colliders[i]->GetTransformedCollider(e->transform->GetWorldTransformMatrix());
			}
			colliders.push_back(list);
		}

		// 衝突処理はコリジョンのついたゲームオブジェクトが二個以上
		if (colliders.size() >= 2)
		{
			// ゲームオブジェクト単位の衝突判定
			for (auto a = colliders.begin(); a != colliders.end() - 1; ++a)
			{
				const GameObjectPtr goA = a->at(0).origin->OwnerObject();
				if (goA->GetState() == GameObjectState::Destroyed)
				{
					continue;	// 削除済みなので飛ばす
				}
				for (auto b = a + 1; b != colliders.end(); ++b)
				{
					const GameObjectPtr goB = b->at(0).origin->OwnerObject();
					if (goB->GetState() == GameObjectState::Destroyed)
					{
						continue;	// 削除済みなので飛ばす
					}
					// コライダー単位の衝突判定
					PhysicsEngine::GetInstance()->HandleWorldColliderCollision(&*a, &*b);
				}
			}
		}
	}

	/**
	* ゲームオブジェクトの描画処理の準備
	*/
	void Scene::RendererGameObject()
	{
		// シェーダの仕分け
		auto resouceManager = AssetManager::GetInstance();
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Unlit));
		programs.push_back(resouceManager->GetShader(DefalutShader::Particle));

		// カメラのパラメータを設定
		for (auto prog : programs)
		{
			if (mainCamera)
			{
				// アスペクト比と視野角を設定
				float fovScale = mainCamera->GetFovScale();
				float aspectRatio = mainCamera->aspect;
				prog->SetFloat4("aspectRatioAndScaleFov", 1 / aspectRatio, fovScale, mainCamera->near, mainCamera->far);

				// カメラの位置と回転とスケールの格納先
				Vector3 pos;
				Vector3 scale;
				Matrix3x3 rot;

				// カメラの座標変換行列を分解
				Matrix4x4::Decompose(mainCamera->GetTransform()->GetWorldTransformMatrix(), pos, scale, rot);

				// クォータニオンに一度変換
				Quaternion q = Quaternion::RotationMatrixToQuaternion(rot);
				// カメラは逆回転にするため逆数にする
				rot = Quaternion::QuaternionToRotationMatrix(Quaternion(q.x, q.y, q.z, -q.w));

				// GPUに情報を伝える
				prog->SetVector3("cameraPosition", pos);
				prog->SetMatrix3x3("cameraRotationMatrix", rot);
			}
		}

		// 描画コンポーネントの有無で仕分けする
		std::vector<RendererPtr> rendererList;
		rendererList.reserve(gameObjects.size());
		for (auto x : gameObjects)
		{
			if (x->renderer)
			{
				rendererList.push_back(x->renderer);
			}
		}

		// レンダリングエンジンに描画してもらう
		RenderingEngine::GetInstance()->DrawGameObject(rendererList, mainCamera);
	}

	/**
	* ゲームオブジェクトのUI描画処理
	*/
	void Scene::UIRendererGameObject()
	{
		for (auto& x : gameObjects)
		{
			if (!x->isActive)
			{
				// ゲームオブジェクトが非アクティブのため飛ばす
				continue;
			}
			if (!x->imGuiLayout)
			{
				// ImGUIコンポーネントを所持していないため飛ばす
				continue;
			}
			if (!x->imGuiLayout->isActive)
			{
				// IMGUIコンポーネントが非アクティブのため飛ばす
				continue;
			}		
			// UIの更新
			x->imGuiLayout->UIUpdate();
		}
	}

	/**
	* ゲームオブジェクトの破棄処理
	*/
	void Scene::DestoryGameObject()
	{
		// 破棄予定のコンポーネントを削除
		for (auto& x : gameObjects)
		{
			x->DestroyComponent();
		}

		// 破棄状態の更新
		for (auto& x : gameObjects)
		{
			x->UpdateDestroyTime();
		}

		// 破棄予定でゲームオブジェクトを分ける
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) {
				return p->GetState() != GameObjectState::Destroyed;
			});

		// 破棄のゲームオブジェクト
		GameObjectList destroyList(
			std::move_iterator(iter),
			std::move_iterator(gameObjects.end()));

		// 配列から移動済みのゲームオブジェクトを削除
		gameObjects.erase(iter, gameObjects.end());

		// 削除イベント
		for (auto& x : destroyList)
		{
			if (x->gameEvents.empty())
			{
				continue;
			}
			for (auto& event : x->gameEvents)
			{
				event->OnDestroy();
			}
		}
	}
}