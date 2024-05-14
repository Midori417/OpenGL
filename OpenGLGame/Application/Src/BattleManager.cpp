/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "PlayerControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;


/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{
	// �v���C���[���쐬
	{
		auto playerObj = Instantate("Player");
		playerControl = playerObj->AddComponent<PlayerControl>();

		// �e�X�g(��őI���ł���悤�ɂ���)
		playerControl->ms = MsList::Gundam;

		// �v���C���[�̋@�̂��쐬
		{
			auto playerMs = Instantate("MyMs", Vector3(0, 6, 50), Quaternion::AngleAxis(180, Vector3::up));;
			// �Ή�����R���|�[�l���g��ǉ�
			playerControl->myMs = SetMs(playerMs, playerControl->ms);
		}
		// �J���������b�N�I���J�����ɕύX
		{
			auto camera = ObjectManager::GetInstance()->GetMainCamera();
			playerControl->lookOnCamera = camera->AddComponent<LookOnCamera>();
		}
	}
	// CPU���쐬
	{
		auto cpuObj = Instantate("CPU");
		cpuControl = cpuObj->AddComponent<CpuControl>();
		cpuControl->ms = MsList::Gundam;
		// CPU�̋@�̂��쐬
		{
			auto cpuMs = Instantate("CpuMs", Vector3(0, 6, -50));
			cpuControl->myMs = SetMs(cpuMs, cpuControl->ms);
		}
	}

	// ���݂��̃R���g���[���[�̏���ݒ�
	playerControl->otherOwner = cpuControl.get();
	cpuControl->otherOwner = playerControl.get();

	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();
	// StadByUI
	{
		auto standbay = Instantate("Standbay");
		imgStandbay = standbay->AddComponent<Image>();
		imgStandbay->texture = resManager->GetTexture("STANDBAY");
		imgStandbay->size = winManager->GetWindowSize();
	}
	{
		auto goBack = Instantate("GoBack");
		imgGoBack = goBack->AddComponent<Image>();
		imgGoBack->texture = resManager->GetTexture("GoBack");
		imgGoBack->size = winManager->GetWindowSize();
	}
	{
		auto go = Instantate("Go");
		imgGo = go->AddComponent<Image>();
		imgGo->texture = resManager->GetTexture("GO");
		imgGo->size = winManager->GetWindowSize() * 0.9f;
	}

	// UI���\��
	imgStandbay->SetEnable(false);
	imgGoBack->SetEnable(false);
	imgGo->SetEnable(false);
}

/**
* ���t���[�����s
*/
void BattleManager::Update()
{
	switch (state)
	{
	case BattleManager::GameState::Ready:
		timer += Time::DeltaTime();
		if (timer > readyTime)
		{
			imgStandbay->SetEnable(true);
			state = GameState::Standbay;
			timer = 0;
		}
		break;
	case BattleManager::GameState::Standbay:

	{
		timer += Time::DeltaTime();
		if (timer > standbayTime)
		{
			imgStandbay->SetEnable(false);
			imgGoBack->SetEnable(true);
			imgGo->SetEnable(true);
			state = GameState::GO;
			timer = 0;
		}
	}

		break;
	case BattleManager::GameState::GO:
	{
		timer += Time::DeltaTime();;
		imgGo->size += 10000 * Time::DeltaTime();
		if (timer > goTime)
		{
			imgGo->SetEnable(false);
			imgGoBack->SetEnable(false);

			playerControl->isStart = true;
			cpuControl->isStart = true;

			state = GameState::Battle;
		}
	}
		break;
	case BattleManager::GameState::Battle:
		break;
	default:
		break;
	}
}

/**
* ms�ɑΉ�����R���|�[�l���g��obj�ɒǉ�����
* 
* @param obj �ǉ�����I�u�W�F�N�g
* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
*/
BaseMsPtr BattleManager::SetMs(GameObjectPtr obj, MsList ms)
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
