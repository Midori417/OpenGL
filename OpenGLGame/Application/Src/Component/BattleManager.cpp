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
	auto assetManager = AssetManager::GetInstance();

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto obj = Instantate(assetManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// �o�g�������쐬
	// ��X�o�g���ݒ�V�[���ł���
	battleInfo = std::make_shared<BattleInfo>();
	{
		// �z���\��
		battleInfo->pilotInfos.reserve(playerMax);
		for (int i = 0; i < playerMax; ++i)
		{
			PilotInfo pilotInfo;
			battleInfo->pilotInfos.push_back(pilotInfo);
		}

		// �e�X�g
		battleInfo->pilotInfos[0].teamId = 1;
		battleInfo->pilotInfos[0].playerId = 0;
		battleInfo->pilotInfos[0].ms = MsList::Gundam;

		battleInfo->pilotInfos[1].teamId = 2;
		battleInfo->pilotInfos[1].playerId = 1;
		battleInfo->pilotInfos[1].ms = MsList::Gundam;

		// �o�g������ݒ�

		// �`�[���̗͂�ݒ�
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}

		// ���Ԃ�ݒ�
	}

	BattleSetting();

	// UI
	{
		// STANBAY���쐬
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standby";
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = assetManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
		}
		// GO���쐬
		{
			auto go = Instantate(CreateObjectType::Empty);
			go->name = "Go";
			imgGo = go->AddComponent<Image>();
			imgGo->texture = assetManager->GetTexture("Go");
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
		std::vector<PilotInfo> pilotInfos = battleInfo->pilotInfos;
		for (int i = 0; i < pilotInfos.size(); ++i)
		{
			PilotInfo pilotInfo = pilotInfos[i];

			// �`�[��ID��0�Ȃ�o�ꂵ�Ȃ�
			if (pilotInfo.teamId == 0)
			{
				continue;
			}

			// �p�C���b�g���쐬
			GameObjectPtr pilotObj = Instantate(CreateObjectType::Empty);
			pilotObj->name = "Pilot" + std::to_string(i);

			// �l�Ԃ�����
			if (pilotInfo.playerId == 0)
			{
				BasePilotPtr pilot = pilotObj->AddComponent<HumanPilot>();

				// �R���g���[���z��ɒǉ�
				pilots.push_back(pilot);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);
				// ms�ɑΉ�����@�̃R���|�[�l���g��ǉ����ăp�C���b�g�ɐݒ�
				pilot->myMs = SetMs(ms, pilotInfo.ms);

				// �J�������擾���Đݒ�
				GameObjectPtr camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				camera->name = "Camera";
				pilot->myCamera = camera->AddComponent<CameraManager>();

				// �`�[����ݒ�
				SetTeum(pilot, pilotInfo.teamId);
			}
			// CPU������
			else
			{
				BasePilotPtr pilot = pilotObj->AddComponent<CpuPilot>();

				// �R���g���[���z��ɒǉ�
				pilots.push_back(pilot);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);
				// ms�ɑΉ�����@�̃R���|�[�l���g��ǉ����ăp�C���b�g�ɐݒ�
				pilot->myMs = SetMs(ms, pilotInfo.ms);

				// ���z�J�������쐬
				GameObjectPtr camera = Instantate(CreateObjectType::Empty);
				camera->name = "VirtualCamera";
				pilot->myCamera = camera->AddComponent<CameraManager>();

				// �`�[����ݒ�
				SetTeum(pilot, pilotInfo.teamId);
			}
		}
	}

	// �p�C���b�g�ɑ���`�[���̃p�C���b�g��ݒ�
	{
		for (BasePilotPtr& pilot1 : team1Pilots)
		{
			for (BasePilotPtr& pilot2 : team2Pilots)
			{
				pilot1->SetOtherTeamPilot(pilot2);
			}
		}
		for (BasePilotPtr& pilot2 : team2Pilots)
		{
			for (BasePilotPtr& pilot1 : team2Pilots)
			{
				pilot2->SetOtherTeamPilot(pilot1);
			}
		}
	}

	// ���`�[���̗͂�ݒ�
	{
		for (BasePilotPtr pilot : team1Pilots)
		{
			pilot->SetTeamHP(team1Hp.get(), team2Hp.get());
		}
		for (BasePilotPtr pilot : team1Pilots)
		{
			pilot->SetTeamHP(team2Hp.get(), team1Hp.get());
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


/**
* �`�[����ݒ肷��
*
* @param control	�ݒ肷��R���g���[��
* @param id			�`�[��ID
*/
void BattleManager::SetTeum(const BasePilotPtr& control, int id)
{
	if (id == 1)
	{
		// �`�[��1�ɓo�^
		team1Pilots.push_back(control);

		// �`�[���l����1�ȏ�Ȃ玩�`�[���̃R���g���[����ݒ�
		if (team1Pilots.size() > 1)
		{
			control->SetPartnerPilot(team1Pilots[0]);
			team1Pilots[0]->SetPartnerPilot(control);
		}
	}
	else
	{
		// �`�[��2�ɓo�^
		team2Pilots.push_back(control);

		// �`�[���l����1�ȏ�Ȃ玩�`�[���̃R���g���[����ݒ�
		if (team2Pilots.size() > 1)
		{
			control->SetPartnerPilot(team2Pilots[0]);
			team2Pilots[0]->SetPartnerPilot(control);
		}
	}
}