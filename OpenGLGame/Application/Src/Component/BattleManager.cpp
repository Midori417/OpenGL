/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "FadeOut.h"

#include "CameraManager.h"

#include "BaseMs.h"
#include "Ms/Gundam.h"

#include "HumanPilot.h"
#include "CpuPilot.h"

#include "../Global.h"
#include "../GameSoundName.h"

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

		//battleInfo->pilotInfos[2].teamId = 2;
		//battleInfo->pilotInfos[2].playerId = 1;
		//battleInfo->pilotInfos[2].ms = MsList::Gundam;

		//battleInfo->pilotInfos[3].teamId = 1;
		//battleInfo->pilotInfos[3].playerId = 1;
		//battleInfo->pilotInfos[3].ms = MsList::Gundam;

		battleInfo->team1Hp = teamMaxHp;
		battleInfo->team2Hp = teamMaxHp;
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

	//audioBGM = OwnerObject()->AddComponent<AudioSource>();
	//audioBGM->SetSoundFilename(GameSound::BGM::battle01);
	//audioBGM->isLooop = true;
	//audioBGM->Play();
}

/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{
	SetBattlePosition(team1Pilots, 0);
	SetBattlePosition(team2Pilots, 1);

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
	{
	}

	break;
	case BattleManager::BattleState::Standbay:
	{
	}
	break;
	case BattleManager::BattleState::GO:
	{
	}
	break;
	case BattleManager::BattleState::Battle:
	{

	}
	break;
	case BattleManager::BattleState::Victory:
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
			team1Hp = battleInfo->team1Hp;
		}

		// �`�[��2�̗̑͂�ݒ�
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = battleInfo->team2Hp;
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
				pilot->myMs = CreateMs(pilotInfo.ms);

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
				pilot->myMs = CreateMs(pilotInfo.ms);

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
	}
}

/**
* �I�u�W�F�N�g�𐶐���ms�ɑΉ������R���|�[�l���g��ǉ�����
*
* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
*/
BaseMsPtr BattleManager::CreateMs(MsList ms)
{
	// �@�̂𐶐�
	GameObjectPtr obj = Instantate(CreateObjectType::Empty);
	obj->tag = "Ms";

	// ms�ɑΉ������R���|�[�l���g��ǉ�����
	switch (ms)
	{
	case MsList::Gundam:
		return obj->AddComponent<Gundam>();
		break;
	}

	// �Ή������R���|�[�l���g���Ȃ��̂ŃI�u�W�F�N�g��j�󂷂�
	obj->Destroy();
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

/**
* �o�g���X�^�[�g�ʒu��ݒ肷��
*
* @param pilots	�z�u����p�C���b�g
* @param id		�`�[��ID
*/
void BattleManager::SetBattlePosition(const std::vector<BasePilotPtr>& pilots, int id)
{
	// ���X�|�[���ʒu���Q�ȏ�Ȃ���Ή������Ȃ�
	if (responPoses.size() < 2)
	{
		return;
	}

	// MS�̏o���ʒu��ݒ�
	for (int i = 0; i < pilots.size(); ++i)
	{
		BasePilotPtr pilot = pilots[i];

		pilot->myMs->GetTransform()->position = responPoses[id] + Vector3(10.0f * i, 0, 0);

		// ���X�|�[���ʒu��ݒ�
		pilot->responPoss = responPoses;

		Vector3 toTargetVector;
		if (id == 0)
		{
			toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		}
		else
		{
			toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		}
		pilot->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector);
	}
}
