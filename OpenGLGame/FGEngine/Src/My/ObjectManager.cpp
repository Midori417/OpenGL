/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "RenderingEngine.h"
#include "ResouceManager.h"
#include "WindowManager.h"
#include "ShaderObject.h"
#include "Time.h"
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
			if (prog.second->isShadow)
			{
				continue;
			}
			programs.push_back(prog.second->GetProgId());
		}

		// カメラのパラメータを設定
		for (auto prog : programs)
		{
			if (mainCamera)
			{
				// アスペクト比と視野角を設定
				float fovScale = mainCamera->camera->GetFovScale();
				float aspectRatio = mainCamera->camera->aspect;
				glProgramUniform2f(prog, RenderingSystem::locAspectRatioAndScaleFov, fovScale / aspectRatio, fovScale);

				// 位置と回転を設定
				Vector3 pos;
				Vector3 scale;
				Matrix3x3 rot;
				Matrix4x4::Decompose(mainCamera->transform->worldToLocalMatrix, pos, scale, rot);
				Quaternion q = Quaternion::RotationMatrixToQuaternion(rot);
				rot = Quaternion::QuaternionToRotationMatrix3x3(Quaternion(q.x, q.y, q.z, -q.w));
				glProgramUniform3fv(prog, RenderingSystem::locCameraPos, 1, &pos.x);
				glProgramUniformMatrix3fv(prog, RenderingSystem::locCameraRotationMatrix, 1, GL_FALSE, &rot.data[0].x);
			}
		}

		// オブジェクトに描画コンポーネントの有無で分ける
		auto iter = std::stable_partition(gameObjects.begin(), gameObjects.end(),
			[](const auto& a) {
				return !a->renderer; });

		GameObjectList drawList(iter, gameObjects.end());
		std::vector<RendererPtr> rendererList;
		rendererList.reserve(gameObjects.size());

		// オブジェクトのrendererを取得
		for (auto i = iter; i < gameObjects.end(); ++i)
		{
			// イテレータから要素番号を取得
			auto index = std::distance(gameObjects.begin(), i);

			// 要素番号のRendererコンポーネントをRenderer配列に追加
			rendererList.push_back(gameObjects[index]->renderer);
		}
		RenderingSystem::RenderingEngine::GetInstance()->DrawGameObject(rendererList);

	}

	void ObjectManager::UpdateGameObject()
	{
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
		auto obj = CreateObject<GameObject>(name);

		// Transformを追加
		obj->AddComponent<Transform>();
		obj->AddComponent<Renderer>();

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