/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "PlayerControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
#include "Global.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::SceneSystem;

/**
* �������Ɏ��s
*/
void BattleManager::Awake()
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
			{
				auto camera = Instantate("virtualCamera");
				cpuControl->lookOnCamera = camera->AddComponent<LookOnCamera>();
			}
		}
	}

	// �`�[��Hp��ݒ�
	{
		teum1Hp = std::make_shared<int>(teumMaxHp);
		teum2Hp = std::make_shared<int>(teumMaxHp);

		playerControl->SetTeumHP(teum1Hp.get());
		cpuControl->SetTeumHP(teum2Hp.get());
	}

	// ���݂��̃R���g���[���[�̏���ݒ�
	playerControl->otherOwner = cpuControl.get();
	cpuControl->otherOwner = playerControl.get();
}

/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{

	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// UI
	{
		// STANBAY���쐬
		{
			auto standbay = Instantate("Standbay");
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = resManager->GetTexture("STANDBAY");
			imgStandbay->size = winManager->GetWindowSize();
		}
		// GO�̔w�i���쐬
		{
			auto goBack = Instantate("GoBack");
			imgGoBack = goBack->AddComponent<Image>();
			imgGoBack->texture = resManager->GetTexture("GoBack");
			imgGoBack->size = winManager->GetWindowSize();
		}
		// GO���쐬
		{
			auto go = Instantate("Go");
			imgGo = go->AddComponent<Image>();
			imgGo->texture = resManager->GetTexture("GO");
			imgGo->size = winManager->GetWindowSize() * 0.9f;
		}
		// WIN���쐬
		{
			auto win = Instantate("Win");
			imgWin = win->AddComponent<Image>();
			imgWin->texture = resManager->GetTexture("Win");
			imgWin->size = winManager->GetWindowSize();
		}
		// Lose���쐬
		{
			auto lose = Instantate("Lose");
			imgLose = lose->AddComponent<Image>();
			imgLose->texture = resManager->GetTexture("Lose");
			imgLose->size = winManager->GetWindowSize();
		}

	}
	// UI���\��
	imgStandbay->SetEnable(false);
	imgGoBack->SetEnable(false);
	imgGo->SetEnable(false);
	imgWin->SetEnable(false);
	imgLose->SetEnable(false);


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

		if (*teum1Hp <= 0)
		{
			imgLose->SetEnable(true);
			state = GameState::Victory;
		}
		else if(*teum2Hp <= 0)
		{
			imgWin->SetEnable(true);
			state = GameState::Victory;
		}
		break;
	case BattleManager::GameState::Victory:

		playerControl->Finish();
		cpuControl->Finish();
		playerControl->SetEnable(false);
		cpuControl->SetEnable(false);

		if (InputKey::GetKey(KeyCode::Enter))
		{
			SceneManager::LoadScene("�^�C�g���V�[��");
		}


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
