/**
* @file BattleManger.cpp
*/
#include "BattleManger.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/Math/Quaternion.h"

#include "../BattleSettingInfo.h"
#include "HyumanControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "Gundam.h"

/**
* 生成時に実行
*/
void BattleManager::Awake()
{
	auto assetManager = AssetManager::GetInstance();

	// バトル設定シーンで設定した情報をもとにバトルルールを設定していく
	// まだバトル設定シーンが完成していないので一旦ここに作る
	{
		battleSettingInfo = std::make_shared<BattleSettingInfo>();

		// プレイヤーの数情報作成する
		for (int i = 0; i < playerMax; ++i)
		{
			battleSettingInfo->controlInfo.push_back(std::make_shared<ControlInfo>());
		}

		battleSettingInfo->controlInfo[0]->teumId = 1;
		battleSettingInfo->controlInfo[0]->playerId = 0;
		battleSettingInfo->controlInfo[0]->ms = MsList::Gundam;

		battleSettingInfo->controlInfo[1]->teumId = 2;
		battleSettingInfo->controlInfo[1]->playerId = 1;
		battleSettingInfo->controlInfo[1]->ms = MsList::Gundam;

		battleSettingInfo->controlInfo[2]->teumId = 2;
		battleSettingInfo->controlInfo[2]->playerId = 1;
		battleSettingInfo->controlInfo[2]->ms = MsList::Gundam;

		battleSettingInfo->controlInfo[3]->teumId = 1;
		battleSettingInfo->controlInfo[3]->playerId = 1;
		battleSettingInfo->controlInfo[3]->ms = MsList::Gundam;
	}

	BattleSetting();

	// UIの作成
	{
		// STANBAYを作成
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standbay";

			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = assetManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
			imgStandbay->isActive = false;
		}
		// GOを作成
		{
			auto go = Instantate(CreateObjectType::Empty);
			go->name = "Go";

			imgGo = go->AddComponent<Image>();
			imgGo->texture = assetManager->GetTexture("Go");
			imgGo->SetWindowSize();
			imgGo->isActive = false;
		}
	}
}

/**
* Updateが始まる前に一度実行
*/
void BattleManager::Start()
{
	// MSの初期位置を設定
	for (int i = 0; i < teum1Controls.size(); ++i)
	{
		BaseControlPtr control = teum1Controls[i];

		control->myMs->GetTransform()->position = responPoses[0] + Vector3(10.0f * i, 0, 0);

		Vector3 toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		control->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}
	for (int i = 0; i < teum2Controls.size(); ++i)
	{
		BaseControlPtr control = teum2Controls[i];

		// 機体の初期値
		control->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// 相手の方向に相手を向ける
		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		control->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}

	// コントロールの処理を開始させる
	for (auto teum1 : teum1Controls)
	{
		teum1->StartOk();
	}
	for (auto teum2 : teum2Controls)
	{
		teum2->StartOk();
	}
}

/**
* 毎フレーム実行
*/
void BattleManager::Update()
{
}

/**
* バトルルールを設定する
*/
void BattleManager::BattleSetting()
{
	// チーム体力を設定
	{
		// チーム1の体力を設定
		if (battleSettingInfo->teum1Hp > 0)
		{
			teum1Hp = std::make_shared<int>(battleSettingInfo->teum1Hp);
		}
		// teum1Hpが0以下なら体力をチーム体力を無限にする
		else
		{
			teum1Hp = std::make_shared<int>(teumMaxHp);
			isTeum1HpInfinity = true;
		}

		// チーム2の体力を設定
		if (battleSettingInfo->teum1Hp > 0)
		{
			teum2Hp = std::make_shared<int>(battleSettingInfo->teum2Hp);
		}
		// teum2Hpが0以下なら体力をチーム体力を無限にする
		else
		{
			teum2Hp = std::make_shared<int>(teumMaxHp);
			isTeum2HpInfinity = true;
		}
	}

	// バトル時間を設定
	{
		battleTime = battleSettingInfo->time;
	}

	// コントロールを作成
	{
		auto controllInfos = battleSettingInfo->controlInfo;
		for (int i = 0; i < controllInfos.size(); ++i)
		{
			auto info = controllInfos[i];

			// チームIDが0なら出場しない
			if (info->teumId == 0)
			{
				continue;
			}

			// プレイヤーを作成
			auto player = Instantate(CreateObjectType::Empty);
			player->name = "Player" + std::to_string(i);

			// 人間が操作
			if (info->playerId == 0)
			{
				auto control = player->AddComponent<HyumanControl>();

				// コントロール配列に追加
				controls.push_back(control);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// msにMSListに対応するコンポーネントを追加
				control->myMs = SetMs(ms, info->ms);

				// カメラを取得して設定
				auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				control->myCamera = camera->AddComponent<LookOnCamera>();

				// チームを設定
				SetTeum(control, info->teumId);
			}
			// CPUが操作
			else
			{
				auto control = player->AddComponent<CpuControl>();

				// コントロール配列に追加
				controls.push_back(control);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// msにMSListに対応するコンポーネントを追加
				control->myMs = SetMs(ms, info->ms);

				// 仮想カメラを作成
				auto camera = Instantate(CreateObjectType::Empty);
				control->myCamera = camera->AddComponent<LookOnCamera>();

				// チームを設定
				SetTeum(control, info->teumId);
			}
		}
	}
	// コントロールに相手にチームのコントロールを設定
	{
		for (auto teum1 : teum1Controls)
		{
			for (auto teum2 : teum2Controls)
			{
				teum1->otherTeamControls.push_back(teum2.get());
			}
		}
		for (auto teum2 : teum2Controls)
		{
			for (auto teum1 : teum1Controls)
			{
				teum2->otherTeamControls.push_back(teum1.get());
			}
		}
	}
}

/**
* msに対応するコンポーネントをobjに追加する
*
* @param obj 追加するオブジェクト
* @param ms 追加したいコンポーネントに対応するMsList
*/
BaseMsPtr BattleManager::SetMs(GameObjectPtr& obj, MsList ms)
{
	switch (ms)
	{
	case MsList::None:
		return nullptr;
		break;
	case MsList::Gundam:
		return obj->AddComponent<Gundam>();
		break;
	}

	return nullptr;
}

/**
* チームを設定する
*
* @param control	設定するコントロール
* @param id			チームID
*/
void BattleManager::SetTeum(const BaseControlPtr& control, int id)
{
	if (id == 1)
	{
		// チーム1に登録
		teum1Controls.push_back(control);
		
		// チーム人数が1以上なら自チームのコントロールを設定
		if (teum1Controls.size() > 1)
		{
			control->myTeamOtherControl = teum1Controls.begin()->get();
			teum1Controls.begin()->get()->myTeamOtherControl = control.get();
		}
	}
	else
	{
		// チーム2に登録
		teum2Controls.push_back(control);

		// チーム人数が1以上なら自チームのコントロールを設定
		if (teum2Controls.size() > 1)
		{
			control->myTeamOtherControl = teum2Controls.begin()->get();
			teum2Controls.begin()->get()->myTeamOtherControl = control.get();
		}
	}
}

/**
* リスポーン位置を設定
*
* @param poses 設定したいリスポーン位置配列
*/
void BattleManager::SetResponPos(const std::vector<Vector3>& poses)
{
	responPoses.clear();
	responPoses = poses;
}
