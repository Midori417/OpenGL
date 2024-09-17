/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "FadeOut.h"

#include "CameraManager.h"

#include "BaseMs.h"
#include "Gundam.h"

#include "HumanPilot.h"
#include "CpuPilot.h"

#include "../Global.h"

// �X�^�e�B�b�N�ϐ���������
BattleInfoPtr BattleManager::battleInfo = nullptr;

/**
* �������Ɏ��s
*/
void BattleManager::Awake()
{
	// �e�}�l�[�W�����擾
	auto resManager = AssetManager::GetInstance();

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto obj = Instantate(resManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// �o�g�������쐬
	battleInfo = std::make_shared<BattleInfo>();
	{
		// �z���\��
		battleInfo->controlInfo.reserve(playerMax);
		for (int i = 0; i < playerMax; ++i)
		{
			battleInfo->controlInfo.push_back(std::make_shared<ControlInfo>());
		}

		// �e�X�g
		battleInfo->controlInfo[0]->teamId = 1;
		battleInfo->controlInfo[0]->playerId = 0;
		battleInfo->controlInfo[0]->ms = MsList::Gundam;

		battleInfo->controlInfo[1]->teamId = 2;
		battleInfo->controlInfo[1]->playerId = 1;
		battleInfo->controlInfo[1]->ms = MsList::Gundam;

		battleInfo->controlInfo[2]->teamId = 2;
		battleInfo->controlInfo[2]->playerId = 1;
		battleInfo->controlInfo[2]->ms = MsList::Gundam;

		battleInfo->controlInfo[3]->teamId = 1;
		battleInfo->controlInfo[3]->playerId = 1;
		battleInfo->controlInfo[3]->ms = MsList::Gundam;

		// �o�g������ݒ�
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}
	}

	//// �R���g���[���̍쐬
	//int i = 0;
	//for (auto x : battleInfo->controlInfo)
	//{
	//	// �`�[��ID��0�Ȃ�o��Ȃ�
	//	if (x->teamId == 0)
	//	{
	//		i++;
	//		continue;
	//	}
	//	// �v���C���[���쐬
	//	auto player = Instantate(CreateObjectType::Empty);
	//	player->name = "Player" + std::to_string(i);
	//	// �N�����삷�邩��ݒ�
	//	if (x->playerId == 0)
	//	{
	//		auto hyumanControl = player->AddComponent<HumanPilot>();
	//		pilots.push_back(hyumanControl);
	//		// �@�̂�ݒ�
	//		auto ms = Instantate(CreateObjectType::Empty);
	//		ms->name = "MS" + std::to_string(i);
	//		// �Ή�����Ms�R���|�[�l���g��ǉ�
	//		hyumanControl->myMs = SetMs(ms, x->ms);
	//		// �J������ݒ�
	//		auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
	//		camera->name = "PlayerCamera";
	//		hyumanControl->myCamera = camera->AddComponent<CameraManager>();
	//		// �`�[����ݒ�
	//		if (x->teumId == 1)
	//		{
	//			team1Pilots.push_back(hyumanControl);
	//			// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
	//			if (team1Pilots.size() > 1)
	//			{
	//				hyumanControl->myTeamOtherOwner = team1Pilots.begin()->get();
	//				team1Pilots.begin()->get()->myTeamOtherOwner = hyumanControl.get();
	//			}
	//		}
	//		else if (x->teumId == 2)
	//		{
	//			team2Pilots.push_back(hyumanControl);
	//			// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
	//			if (team2Pilots.size() > 1)
	//			{
	//				hyumanControl->myTeamOtherOwner = team2Pilots.begin()->get();
	//				team2Pilots.begin()->get()->myTeamOtherOwner = hyumanControl.get();
	//			}
	//		}
	//	}
	//	else if (x->playerId == 1)
	//	{
	//		auto cpuControl = player->AddComponent<CpuPilot>();
	//		pilots.push_back(cpuControl);
	//		// �@�̂�ݒ�
	//		auto ms = Instantate(CreateObjectType::Empty);
	//		ms->name = "MS" + std::to_string(i);
	//		// �Ή�����Ms�R���|�[�l���g��ǉ�
	//		cpuControl->myMs = SetMs(ms, x->ms);
	//		// ���z�J������ݒ�
	//		auto camera = Instantate(CreateObjectType::Empty);
	//		camera->name = "VitualCaemra";
	//		cpuControl->myCamera = camera->AddComponent<CameraManager>();
	//		// �`�[����ݒ�
	//		if (x->teumId == 1)
	//		{
	//			team1Pilots.push_back(cpuControl);
	//			// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
	//			if (team1Pilots.size() > 1)
	//			{
	//				cpuControl->myTeamOtherOwner = team1Pilots.begin()->get();
	//				team1Pilots.begin()->get()->myTeamOtherOwner = cpuControl.get();
	//			}
	//		}
	//		else if (x->teumId == 2)
	//		{
	//			team2Pilots.push_back(cpuControl);
	//			// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
	//			if (team2Pilots.size() > 1)
	//			{
	//				cpuControl->myTeamOtherOwner = team2Pilots.begin()->get();
	//				team2Pilots.begin()->get()->myTeamOtherOwner = cpuControl.get();
	//			}
	//		}
	//	}
	//	i++;
	//}

	// ����`�[���̃I�[�i��ݒ�
	{
		for (auto teum1 : team1Pilots)
		{
			for (auto teum2 : team2Pilots)
			{
				teum1->otherTeamOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : team2Pilots)
		{
			for (auto teum1 : team1Pilots)
			{
				teum2->otherTeamOwner.push_back(teum1.get());
			}
		}
	}

	// ���`�[���̗͂�ݒ�
	{
		for (auto teum1 : team1Pilots)
		{
			teum1->SetTeamHP(team1Hp.get(), team2Hp.get());
		}
		for (auto teum2 : team2Pilots)
		{
			teum2->SetTeamHP(team2Hp.get(), team1Hp.get());
		}
	}

	// UI
	{
		// STANBAY���쐬
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standby";
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = resManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
		}
		// GO���쐬
		{
			auto go = Instantate(CreateObjectType::Empty);
			go->name = "Go";
			imgGo = go->AddComponent<Image>();
			imgGo->texture = resManager->GetTexture("Go");
			imgGo->SetWindowSize();
		}
	}
}

/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{
	// MS�̏o���ʒu��ݒ�
	for (int i = 0; i < team1Pilots.size(); ++i)
	{
		auto teum1 = team1Pilots[i];

		teum1->myMs->GetTransform()->position = responPoses[0] + Vector3(10.0f * i, 0, 0);
		teum1->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		teum1->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}
	for (int i = 0; i < team2Pilots.size(); ++i)
	{
		auto teum2 = team2Pilots[i];

		teum2->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// ���X�|�[���ʒu��ݒ�
		teum2->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		teum2->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}

	// UI���\��
	imgStandbay->isActive = false;
	imgGo->isActive = false;
}

/**
* ���t���[�����s
*/
void BattleManager::Update()
{
	// �o�g�����
	switch (battleState)
	{
	case BattleManager::BattleState::Ready:

		// ����
	{
		// �^�C�}�[��i�߂�
		timer += Time::DeltaTime();
		if (timer > readyTime)
		{
			// �o�g����Ԃ��X�^���o�C��
			battleState = BattleState::Standbay;

			// Stanbay��\��
			imgStandbay->isActive = true;

			// �^�C�}�[��0�ɂ���
			timer = 0;
		}
	}

	break;
	case BattleManager::BattleState::Standbay:

		// �X�^���o�C
	{
		// �^�C�}�[��i�߂�
		timer += Time::DeltaTime();
		if (timer > standbayTime)
		{
			// �o�g����Ԃ��S�[��
			battleState = BattleState::GO;

			// Stanbay���\����
			imgStandbay->isActive = false;
			// GO��\��
			imgGo->isActive = true;

			// �^�C�}�[��0�ɂ���
			timer = 0;
		}
	}
	break;
	case BattleManager::BattleState::GO:
		// �S�[
	{
		// �^�C�}�[��i�߂�
		timer += Time::DeltaTime();
		if (timer > goTime)
		{
			// �o�g����Ԃ��o�g����
			battleState = BattleState::Battle;

			// GO���\����
			imgGo->isActive = false;

			// �R���g���[���̏������J�n������
			for (auto teum1 : team1Pilots)
			{
				teum1->ControlStart();
			}
			for (auto teum2 : team2Pilots)
			{
				teum2->ControlStart();
			}
		}
	}
	break;
	case BattleManager::BattleState::Battle:
		// �o�g����
	{
		if (*team1Hp <= 0 || *team2Hp <= 0)
		{
			VictoryState teum1Victory = VictoryState::None;
			VictoryState teum2Victory = VictoryState::None;
			// �ǂ���̃`�[��Hp��0�Ȃ�Έ�������
			if (*team1Hp <= 0 && *team2Hp <= 0)
			{
				teum1Victory = VictoryState::Drow;
				teum2Victory = VictoryState::Drow;
			}
			else if (*team1Hp <= 0)
			{
				teum1Victory = VictoryState::Lose;
				teum2Victory = VictoryState::Win;
			}
			else if (*team2Hp <= 0)
			{
				teum1Victory = VictoryState::Win;
				teum2Victory = VictoryState::Lose;
			}

			// �I������������
			for (auto teum1 : team1Pilots)
			{
				teum1->Finish(teum1Victory);
				teum1->isActive = false;
			}
			for (auto teum2 : team2Pilots)
			{
				teum2->Finish(teum2Victory);
				teum2->isActive = false;
			}
			battleState = BattleState::Victory;
		}
	}
	break;
	case BattleManager::BattleState::Victory:

		// ���s
	{
		if (InputKey::GetKey(KeyCode::Enter))
		{
			fadeOut->FadeStart();
		}

		// �t�F�[�h���I��������V�[�����ړ�����
		if (fadeOut->IsFadeOut())
		{
			SceneManager::LoadScene("BattleSettingScene");
		}
	}

	break;
	}
}

/**
* �o�g������ݒ�
*/
void BattleManager::SetBattleInfo(BattleInfoPtr _battleInfo)
{
	battleInfo.swap(_battleInfo);
}

/**
* ���X�|�[���ʒu��ݒ�
*
* @param posed ���X�|�[���ʒu�z��
*/
void BattleManager::SetResponPos(const std::vector<Vector3>& poses)
{
	responPoses.clear();
	responPoses = poses;
}

/**
* �o�g���ݒ������
*/
void BattleManager::BattleSetting()
{
	// �`�[���̗͂�ݒ�
	{
		// �`�[��1�̗̑͂�ݒ�
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		// teum1Hp��0�ȉ��Ȃ�̗͂��`�[���̗͂𖳌��ɂ���
		else
		{
			team1Hp = std::make_shared<int>(teamMaxHp);
			//isTeum1HpInfinity = true;
		}

		// �`�[��2�̗̑͂�ݒ�
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}
		// teum2Hp��0�ȉ��Ȃ�̗͂��`�[���̗͂𖳌��ɂ���
		else
		{
			team2Hp = std::make_shared<int>(teamMaxHp);
			//isTeum2HpInfinity = true;
		}
	}

	// �o�g�����Ԃ�ݒ�
	{
	}

	// �R���g���[�����쐬
	{
		auto controllInfos = battleInfo->controlInfo;
		for (int i = 0; i < controllInfos.size(); ++i)
		{
			auto info = controllInfos[i];

			// �`�[��ID��0�Ȃ�o�ꂵ�Ȃ�
			if (info->teamId == 0)
			{
				continue;
			}

			// �v���C���[���쐬
			auto player = Instantate(CreateObjectType::Empty);
			player->name = "Player" + std::to_string(i);

			// �l�Ԃ�����
			if (info->playerId == 0)
			{
				auto control = player->AddComponent<HumanPilot>();

				// �R���g���[���z��ɒǉ�
				pilots.push_back(control);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// ms��MSList�ɑΉ�����R���|�[�l���g��ǉ�
				control->myMs = SetMs(ms, info->ms);

				// �J�������擾���Đݒ�
				auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				control->myCamera = camera->AddComponent<CameraManager>();

				// �`�[����ݒ�
				//SetTeum(control, info->teamId);
			}
			// CPU������
			else
			{
				auto control = player->AddComponent<CpuPilot>();

				// �R���g���[���z��ɒǉ�
				pilots.push_back(control);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// ms��MSList�ɑΉ�����R���|�[�l���g��ǉ�
				control->myMs = SetMs(ms, info->ms);

				// ���z�J�������쐬
				auto camera = Instantate(CreateObjectType::Empty);
				control->myCamera = camera->AddComponent<CameraManager>();

				// �`�[����ݒ�
				//SetTeum(control, info->teamId);
			}
		}
	}
	// �R���g���[���ɑ���Ƀ`�[���̃R���g���[����ݒ�
	{
		for (auto teum1 : team1Pilots)
		{
			for (auto teum2 : team2Pilots)
			{
				//teum1->otherTeamControls.push_back(teum2.get());
			}
		}
		for (auto teum2 : team2Pilots)
		{
			for (auto teum1 : team2Pilots)
			{
				//teum2->otherTeamControls.push_back(teum1.get());
			}
		}
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
