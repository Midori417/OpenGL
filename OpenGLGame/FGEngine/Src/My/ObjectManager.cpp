/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "ResouceManager.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Time.h"
#include "WorldCollider.h"
#include "ShaderLocationNum.h"
#include <algorithm>

namespace FGEngine::ObjectSystem
{
	/**
	* オブジェクトマネージャーを初期化
	*
	* @retval 0		正常に初期化
	* @retval 0以外 初期化失敗
	*/
	int ObjectManager::Initialize()
	{
		// ゲームオブジェクト配列の容量をを予約
		gameObjects.reserve(1000);

		return 0;
	}

	/**
	* オブジェクトマネージャーを更新
	*/
	void ObjectManager::Update()
	{
		// ゲームオブジェクト配列が空のため何もしない
		if (gameObjects.empty())
		{
			return;
		}

		// ゲームオブジェクトのイベント処理
		UpdateMonoBehaviour();

		// オブジェクト座標処理
		UpdateTransform();

		// 衝突処理
		CollisionGameObject();

		// 物理処理
		UpdateRigidbody();

		// オブジェクトの破壊処理
		DestoryGameObject();

		// UIの描画処理
		UIRendererGameObject();

		// オブジェクトの描画処理
		RendererGameObject();

	}

	/**
	* ゲームオブジェクトを描画
	*/
	void ObjectManager::RendererGameObject()
	{
		// シェーダの仕分け
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		std::vector<GLuint> programs;
		for (auto prog : *resouceManager->GetShaderList())
		{
			// 影用のシェーダの場合除外
			if (prog.second->isNormal)
			{
				programs.push_back(prog.second->GetProgId());
			}
		}

		// カメラのパラメータを設定
		for (auto prog : programs)
		{
			if (mainCamera)
			{
				// アスペクト比と視野角を設定
				float fovScale = mainCamera->camera->GetFovScale();
				float aspectRatio = mainCamera->camera->aspect;
				glProgramUniform2f(prog, RenderingSystem::locAspectRatioAndScaleFov, 1 / aspectRatio, fovScale);

				// カメラの位置と回転とスケールの格納先
				Vector3 pos;
				Vector3 scale;
				Matrix3x3 rot;

				// カメラの座標変換行列を分解
				Matrix4x4::Decompose(mainCamera->transform->transformMatrix, pos, scale, rot);

				// クォータニオンに一度変換
				Quaternion q = Quaternion::RotationMatrixToQuaternion(rot);
				// カメラは逆回転にするため逆数にする
				rot = Quaternion::QuaternionToRotationMatrix3x3(Quaternion(q.x, q.y, q.z, -q.w));

				// GPUに情報を伝える
				glProgramUniform3fv(prog, RenderingSystem::locCameraPos, 1, &pos.x);
				glProgramUniformMatrix3fv(prog, RenderingSystem::locCameraRotationMatrix, 1, GL_FALSE, &rot.data[0].x);
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
		RenderingSystem::RenderingEngine::GetInstance()->DrawGameObject(rendererList);
	}

	/**
	* ゲームオブジェクトのUI描画処理
	*/
	void ObjectManager::UIRendererGameObject()
	{
		// UI描画コンポーネントの有無で仕分する
		std::vector<UI::ImGuiLayoutPtr> imguiList;
		imguiList.reserve(gameObjects.size());

		for (auto x : gameObjects)
		{
			if (x->imGuiLayout)
			{
				imguiList.push_back(x->imGuiLayout);
			}
		}

		// UIがないため処理を終わる
		if (imguiList.empty())
		{
			return;
		}

		// レイヤー順に並び替える
		std::stable_sort(imguiList.begin(), imguiList.end(),
			[](const UI::ImGuiLayoutPtr& a, const UI::ImGuiLayoutPtr& b) {
				return a->layer < b->layer; });

		for (auto x : gameObjects)
		{
			if (x->imGuiLayout)
			{
				x->imGuiLayout->UIUpdate();
			}
		}
	}

	/**
	* ゲームオブジェクトの衝突処理の準備
	*/
	void ObjectManager::CollisionGameObject()
	{
		// ワールド座標系の衝突判定を作成
		std::vector<PhysicsSystem::WorldColliderList> colliders;
		colliders.reserve(gameObjects.size());
		for (const auto& e : gameObjects)
		{
			if (e->colliders.empty()) 
			{
				continue; // コライダーを持っていなかったら何もしない
			}

			// 衝突判定を作成
			PhysicsSystem::WorldColliderList list(e->colliders.size());
			for (int i = 0; i < e->colliders.size(); ++i)
			{
				// オリジナルのコライダーをコピー
				list[i].origin = e->colliders[i];

				//コライダーの座標をワールド座標に変換
				list[i].world = e->colliders[i]->GetTransformedCollider(e->transform->GetTransformMatrix());
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
				if (goA->IsDestroyed())
				{
					continue;	// 削除済みなので飛ばす
				}
				for (auto b = a + 1; b != colliders.end(); ++b)
				{
					const GameObjectPtr goB = b->at(0).origin->OwnerObject();
					if (goB->IsDestroyed())
					{
						continue;	// 削除済みなので飛ばす
					}
					PhysicsSystem::PhysicsEngine::GetInstance()->HandleWorldColliderCollision(&*a, &*b); // コライダー単位の衝突判定
				}
			}
		}

	}

	/**
	* Transformを更新
	*/
	void ObjectManager::UpdateTransform()
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
				Matrix4x4 m = e->GetTransformMatrix();
				Matrix3x3 n = e->GetNormalMatrix();
				for (e = e->GetParent(); e; e = e->GetParent())
				{
					m = e->GetTransformMatrix() * m;
					n = e->GetNormalMatrix() * n;
				}
				worldTransforms[i] = m;
				worldNormals[i] = n;
			}
		}

		// ワールド座標変換行列をゲームオブジェクトに設定
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			gameObjects[i]->transform->transformMatrix = worldTransforms[i];
			gameObjects[i]->transform->normalMatrix = worldNormals[i];
		}

	}

	/**
	* MonoBehaviourの更新
	*/
	void ObjectManager::UpdateMonoBehaviour()
	{
		// スタート処理
		for (auto x : gameObjects)
		{
			// 持っていなければ何もしない
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (!mono->isStart && mono->enabled)
				{
					mono->Start();
					mono->isStart = true;
				}
			}
		}

		// 更新処理
		for (auto x : gameObjects)
		{
			// 持っていなければ何もしない
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (mono->enabled)
				{
					mono->Update();
				}
			}
		}

		// 更新処理2
		for (auto x : gameObjects)
		{
			// 持っていなければ何もしない
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (mono->enabled)
				{
					mono->LateUpdate();
				}
			}
		}


	}

	/**
	* Rigidbodyを更新
	*/
	void ObjectManager::UpdateRigidbody()
	{
		for (auto x : gameObjects)
		{
			if (x->rigidbody)
			{
				x->rigidbody->GravityUpdate();
			}
		}
	}

	/**
	* ゲームオブジェクトの削除処理
	*/
	void ObjectManager::DestoryGameObject()
	{
		// オブジェクト配列がからなら何もしない
		if (gameObjects.empty())
		{
			return;
		}

		// 破棄予定濃霧でゲームオブジェクトを分ける
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return !p->IsDestroyed(); });

		// 破棄予定の破壊時間が0以上ならタイマーを減らす
		// 0以下なら破棄状態にする
		for (auto i = iter; i < gameObjects.end(); ++i)
		{
			if (i->get()->destroyTime > 0)
			{
				i->get()->destroyTime -= Time::DeltaTime();
				if (i->get()->destroyTime <= 0)
				{
					i->get()->hideFlag = Object::HideFlag::Destory;
					isDestoryObject = true;
				}
			}
		}

		// 破棄状態のオブジェクトがなければ何もしない
		if (!isDestoryObject)
		{
			return;
		}

		// 破棄状態の有無でオブジェクトを分ける
		auto iter2 = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return p->GetHideFlag() == Object::HideFlag::Destory; });

		// 破棄状態のゲームオブジェクトを別の配列に移動
		GameObjectList destroyList(
			std::move_iterator(iter2),
			std::move_iterator(gameObjects.end()));

		// 配列から移動済みのゲームオブジェクトを削除
		gameObjects.erase(iter2, gameObjects.end());

		for (auto& e : destroyList)
		{
			// 自身のもつゲームオブジェクト破棄
			e->gameObject = nullptr;

			// 破棄状態のゲームオブジェクトのOnDestoryを実行
			for (auto x : e->monoBehaviours)
			{
				x->OnDestory();
			}
		}

		// 破壊オブジェクトがないにする
		isDestoryObject = false;
	}

	/**
	* ゲームオブジェクトを作成
	*
	* @param name オブジェクトの名前
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name)
	{
		auto obj = std::make_shared<GameObject>();

		// 名前を設定
		obj->SetName(name);

		// Transformを追加
		obj->AddComponent<Transform>();

		obj->gameObject = obj;

		// ゲームオブジェクト配列に登録
		gameObjects.push_back(obj);

		// 作成したゲームオブジェクト
		return obj;
	}

	/**
	* ゲームオブジェクトを作成
	*
	* @param name		オブジェクトの名前
	* @param transform	オブジェクトのTransfrom
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Transform& transform)
	{
		// ゲームオブジェクトを作成
		auto obj = CreateGameObject(name);

		// Tranformを設定

		// 位置
		obj->GetTransform()->position = transform.position;

		// 回転
		obj->GetTransform()->rotation = transform.rotation;

		// 拡大縮小
		obj->GetTransform()->scale = transform.scale;

		// 作成したゲームオブジェクト
		return obj;
	}

	/**
	* ゲームオブジェクトを作成
	*
	* @param name オブジェクトの名前
	* @param
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		// ゲームオブジェクトを作成
		auto obj = CreateGameObject(name);

		// 位置
		obj->GetTransform()->position = position;

		// 回転
		obj->GetTransform()->rotation = rotation;

		// 作成したゲームオブジェクト
		return obj;
	}
}