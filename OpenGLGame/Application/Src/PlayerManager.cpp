/**
* @file PlayerManager.cpp
*/
#include "PlayerManager.h"
#include "CameraMove.h"
#include "EnemyMs.h"
#include "Gundam.h"

void PlayerManager::Awake()
{
	// カメラを生成
	auto engine = GetGameObject()->GetEngine();
	auto camera = engine->GetMainCamera();
	cameraMove = camera->AddComponent<CameraMove>();

	// ガンダムを生成
	auto gundam = engine->Create<GameObject>("gundam", Vector3(0, 4.5, 0));
	myMs = gundam->AddComponent<Gundam>();
	myMs->SetPlayerManager(this);

	// UI生成
	// boostGage
	auto boostbarBack = engine->Create<GameObject>("BoostbarBack", Vector3(1000,950,0));
	{
		imgBoostbarBack = boostbarBack->AddComponent<Image>();
		imgBoostbarBack->filename = "Res/UI/Battle/BoostbarBack.tga";
		imgBoostbarBack->size.x = 400;
		imgBoostbarBack->size.y = 100;
	}
	auto boostbar = engine->Create<GameObject>("Boostbar", Vector3(1020, 950,0));
	{
		imgBoostbar = boostbar->AddComponent<Image>();
		imgBoostbar->filename = "Res/UI/Battle/Boostbar2.tga";
		imgBoostbar->size.x = 360;
		imgBoostbar->size.y = 100;
	}

	// HP
	auto hpBack = engine->Create<GameObject>("HpBack", Vector3(-10, 700, 0));
	imgHpBack = hpBack->AddComponent<Image>();
	imgHpBack->filename = "Res/UI/Battle/HPBack.tga";
	imgHpBack->size.x = 400;
	imgHpBack->size.y = 300;
	auto hp = engine->Create<GameObject>("Hp", Vector3(80, 710, 0));
	txtHp = hp->AddComponent<Text>();
	txtHp->text = "888";
	txtHp->index = 1;

	// ターゲットカーソル
	Vector2 pos = engine->GetFramebufferSize();
	auto targetMark = engine->Create<GameObject>("TargetMark", Vector3((pos.x / 2)- (150 /2), (pos.y / 2) - (150 / 2), 0));
	imgTargetMark = targetMark->AddComponent<Image>();
	imgTargetMark->filename = "Res/UI/Battle/TargetMark01.tga";
	imgTargetMark->size = Vector2(150);
	auto targetMsInfo = engine->Create<GameObject>("TargetMsInfo", Vector3((pos.x / 2) +20, (pos.y / 2) - 100, 0));
	imgTargetMsInfo = targetMsInfo->AddComponent<Image>();
	imgTargetMsInfo->filename = "Res/UI/Battle/TargetMsInfo.tga";
	imgTargetMsInfo->size = Vector2(250, 100);
	Vector2 msInfoPos(targetMsInfo->transform->position);
	auto targetMsHpBar = engine->Create<GameObject>("TargetMsHpBar", Vector3(msInfoPos.x + 126, msInfoPos.y +30, 0));
	imgTargetMSHpBar = targetMsHpBar->AddComponent<Image>();
	imgTargetMSHpBar->filename = "Res/UI/Battle/TargetMsHpBar.tga";
	imgTargetMSHpBar->size = Vector2(115, 15);


	// 武器
	imgWeaponBacks.resize(myMs->GetParameter().weaponMax);
	for (int i = 0; i < imgWeaponBacks.size(); ++i)
	{
		auto weaponBack = engine->Create<GameObject>("WeaponBack", Vector3(1400, 800, 0));
		imgWeaponBacks[i] = weaponBack->AddComponent<Image>();
		imgWeaponBacks[i]->filename = "Res/UI/Battle/WeaponBack.tga";
		imgWeaponBacks[i]->size.x = 512;
		imgWeaponBacks[i]->size.y = 128;
	}
	imgWeaponIcons.resize(myMs->GetParameter().weaponMax);
	for (int i = 0; i < imgWeaponIcons.size(); ++i)
	{
		auto weaponIcon = engine->Create<GameObject>("WeaponIcon", Vector3(1400, 800, 0));
		imgWeaponIcons[i] = weaponIcon->AddComponent<Image>();
	}
	txtWeapons.resize(myMs->GetParameter().weaponMax);
	for (int i = 0; i < imgWeaponBacks.size(); ++i)
	{
		auto numWeapon = engine->Create<GameObject>("numWeapon", Vector3(1500, 800, 0));
		txtWeapons[i] = numWeapon->AddComponent<Text>();
		txtWeapons[i]->text = "88";
	}
}

/**
* 敵MSとMYMSのきゅりを求める
*/
float PlayerManager::GetDistance() const
{
	return Vector3::Distance(myMs->transform->position, enemyMs->transform->position);
}

void PlayerManager::Start()
{
	auto target = GetGameObject()->GetEngine()->Create<GameObject>("target", Vector3(0, 7, -10));
	enemyMs = target->AddComponent<EnemyMs>();

	// カメラの設定
	cameraMove->myMsTrs = myMs->transform;
	cameraMove->targetTrs = target->transform.get();

	// プレイヤーの設定
	myMs->SetCameraTrs(cameraMove->transform);
	for (int i = 0; i < imgWeaponIcons.size(); ++i)
	{
		imgWeaponIcons[i]->filename = myMs->GetNumArmer(i)->iconfileName;
		imgWeaponIcons[i]->size = Vector2(512, 128);
		txtWeapons[i]->text = std::to_string(static_cast<int>(myMs->GetNumArmer(i)->amo));
	}
	txtHp->text = std::to_string(static_cast<int>(myMs->GetParameter().hpMax));

	
}

void PlayerManager::Update()
{
	auto engine = GetGameObject()->GetEngine();
	// BoostBar
	{
		auto power = Mathf::Clamp01((myMs->GetParameter().boostPowerMax - myMs->GetParameter().boostPower) / myMs->GetParameter().boostPowerMax);
		imgBoostbar->fillAmout = power;
	}

	// TargetMark
	{
		imgTargetMark->size = Vector2(Mathf::Clamp(GetDistance(), 100.0f, 200.0f));
		Vector2 pos = engine->GetFramebufferSize();
		Vector2 size = imgTargetMark->size;
		imgTargetMark->transform->position = Vector3((pos.x / 2) - (size.x / 2), (pos.y / 2) - (size.y / 2), 0);
		if (GetDistance() <= myMs->AttackDistance().clossRangeDistance)
		{
			imgTargetMark->color = Color::red;
			imgTargetMark->filename = "Res/UI/Battle/TargetMark03.tga";
		}
		else if (GetDistance() <= myMs->AttackDistance().shotDistance)
		{
			imgTargetMark->color = Color::red;
			imgTargetMark->filename = "Res/UI/Battle/TargetMark02.tga";
		}
		else if (GetDistance() > myMs->AttackDistance().shotDistance)
		{
			imgTargetMark->color = Color::green;
			imgTargetMark->filename = "Res/UI/Battle/TargetMark01.tga";
		}
	}
	// MyMSの弾の数を反映
	{
		for (int i = 0; i < txtWeapons.size(); ++i)
		{
			txtWeapons[i]->text = std::to_string(static_cast<int>(myMs->GetNumArmer(i)->amo));
		}

	}
	// MyMSのHpを反映
	{
		txtHp->text = std::to_string(static_cast<int>(myMs->GetParameter().hp));
	}

	{
		imgTargetMSHpBar->fillAmout = enemyMs->GetParameter().hp / enemyMs->GetParameter().hpMax;
	}
}
