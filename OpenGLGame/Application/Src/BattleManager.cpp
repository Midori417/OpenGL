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

// �X�^�e�B�b�N�ϐ���������
BattleInfoPtr BattleManager::battleInfo = nullptr;

/**
* �o�g������ݒ�
*/
void BattleManager::SetBattleInfo(BattleInfoPtr _battleInfo)
{
	battleInfo.swap(_battleInfo);
}

/**
* �������Ɏ��s
*/
void BattleManager::Awake()
{
	// �e�}�l�[�W�����擾
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �o�g������ݒ�
	teum1Hp = std::make_shared<int>(battleInfo->teum1Hp);
	teum2Hp = std::make_shared<int>(battleInfo->teum2Hp);
	battleTime = battleInfo->time;

	// �R���g���[���̍쐬
	int i = 0;
	for (auto x : battleInfo->controlInfo)
	{
		// �`�[��ID��0�Ȃ�o��Ȃ�
		if (x->teumId == 0)
		{
			i++;
			continue;
		}
		// �v���C���[���쐬
		auto player = Instantate("Player" + std::to_string(i));

		// �N�����삷�邩��ݒ�
		if (x->playerId == 0)
		{
			auto hyumanControl = player->AddComponent<PlayerControl>();

			// �@�̂�ݒ�
			auto ms = Instantate("MS" + std::to_string(i), Vector3(0, 6, 50));

			// �Ή�����Ms�R���|�[�l���g��ǉ�
			hyumanControl->myMs = SetMs(ms, x->ms);

			// �J������ݒ�
			auto camera = ObjectManager::GetInstance()->GetMainCamera();
			hyumanControl->lookOnCamera = camera->AddComponent<LookOnCamera>();

			// �`�[����ݒ�
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(hyumanControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum1ControlOwners.size() > 1)
				{
					hyumanControl->myTeumOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeumOtherOwner = hyumanControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(hyumanControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum2ControlOwners.size() > 1)
				{
					hyumanControl->myTeumOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeumOtherOwner = hyumanControl.get();
				}
			}
		}
		else if (x->playerId == 1)
		{
			auto cpuControl = player->AddComponent<CpuControl>();

			// �@�̂�ݒ�
			auto ms = Instantate("MS" + std::to_string(i), Vector3(0, 6, -50));

			// �Ή�����Ms�R���|�[�l���g��ǉ�
			cpuControl->myMs = SetMs(ms, x->ms);

			// ���z�J������ݒ�
			auto camera = Instantate("virtualCamera");
			cpuControl->lookOnCamera = camera->AddComponent<LookOnCamera>();

			// �`�[����ݒ�
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(cpuControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum1ControlOwners.size() > 1)
				{
					cpuControl->myTeumOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeumOtherOwner = cpuControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(cpuControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum2ControlOwners.size() > 1)
				{
					cpuControl->myTeumOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeumOtherOwner = cpuControl.get();
				}
			}
		}

		i++;
	}

	// ����`�[���̃I�[�i��ݒ�
	{
		for (auto teum1 : teum1ControlOwners)
		{
			for (auto teum2 : teum2ControlOwners)
			{
				teum1->otherTeumOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : teum2ControlOwners)
		{
			for (auto teum1 : teum1ControlOwners)
			{
				teum2->otherTeumOwner.push_back(teum1.get());
			}
		}}

	// ���`�[���̗͂�ݒ�
	{
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->SetMyTeumHP(teum1Hp.get());
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->SetMyTeumHP(teum2Hp.get());
		}
	}

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
}

/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{
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

			// �I�[�i�ɃX�^�[�g��`����
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->isStart = true;
			}
			for (auto teum2 : teum2ControlOwners)
			{
				teum2->isStart = true;
			}

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
		else if (*teum2Hp <= 0)
		{
			imgWin->SetEnable(true);
			state = GameState::Victory;
		}
		break;
	case BattleManager::GameState::Victory:

		// �I�[�i�ɏI��������������
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->Finish();
			teum1->SetEnable(false);
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->Finish();
			teum2->SetEnable(false);
		}

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
