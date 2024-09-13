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
* �������Ɏ��s
*/
void BattleManager::Awake()
{
	auto assetManager = AssetManager::GetInstance();

	// �o�g���ݒ�V�[���Őݒ肵���������ƂɃo�g�����[����ݒ肵�Ă���
	// �܂��o�g���ݒ�V�[�����������Ă��Ȃ��̂ň�U�����ɍ��
	{
		battleSettingInfo = std::make_shared<BattleSettingInfo>();

		// �v���C���[�̐����쐬����
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

	// UI�̍쐬
	{
		// STANBAY���쐬
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standbay";

			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = assetManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
			imgStandbay->isActive = false;
		}
		// GO���쐬
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
* Update���n�܂�O�Ɉ�x���s
*/
void BattleManager::Start()
{
	// MS�̏����ʒu��ݒ�
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

		// �@�̂̏����l
		control->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// ����̕����ɑ����������
		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		control->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}

	// �R���g���[���̏������J�n������
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
* ���t���[�����s
*/
void BattleManager::Update()
{
}

/**
* �o�g�����[����ݒ肷��
*/
void BattleManager::BattleSetting()
{
	// �`�[���̗͂�ݒ�
	{
		// �`�[��1�̗̑͂�ݒ�
		if (battleSettingInfo->teum1Hp > 0)
		{
			teum1Hp = std::make_shared<int>(battleSettingInfo->teum1Hp);
		}
		// teum1Hp��0�ȉ��Ȃ�̗͂��`�[���̗͂𖳌��ɂ���
		else
		{
			teum1Hp = std::make_shared<int>(teumMaxHp);
			isTeum1HpInfinity = true;
		}

		// �`�[��2�̗̑͂�ݒ�
		if (battleSettingInfo->teum1Hp > 0)
		{
			teum2Hp = std::make_shared<int>(battleSettingInfo->teum2Hp);
		}
		// teum2Hp��0�ȉ��Ȃ�̗͂��`�[���̗͂𖳌��ɂ���
		else
		{
			teum2Hp = std::make_shared<int>(teumMaxHp);
			isTeum2HpInfinity = true;
		}
	}

	// �o�g�����Ԃ�ݒ�
	{
		battleTime = battleSettingInfo->time;
	}

	// �R���g���[�����쐬
	{
		auto controllInfos = battleSettingInfo->controlInfo;
		for (int i = 0; i < controllInfos.size(); ++i)
		{
			auto info = controllInfos[i];

			// �`�[��ID��0�Ȃ�o�ꂵ�Ȃ�
			if (info->teumId == 0)
			{
				continue;
			}

			// �v���C���[���쐬
			auto player = Instantate(CreateObjectType::Empty);
			player->name = "Player" + std::to_string(i);

			// �l�Ԃ�����
			if (info->playerId == 0)
			{
				auto control = player->AddComponent<HyumanControl>();

				// �R���g���[���z��ɒǉ�
				controls.push_back(control);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// ms��MSList�ɑΉ�����R���|�[�l���g��ǉ�
				control->myMs = SetMs(ms, info->ms);

				// �J�������擾���Đݒ�
				auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				control->myCamera = camera->AddComponent<LookOnCamera>();

				// �`�[����ݒ�
				SetTeum(control, info->teumId);
			}
			// CPU������
			else
			{
				auto control = player->AddComponent<CpuControl>();

				// �R���g���[���z��ɒǉ�
				controls.push_back(control);

				// �@�̂��쐬
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// ms��MSList�ɑΉ�����R���|�[�l���g��ǉ�
				control->myMs = SetMs(ms, info->ms);

				// ���z�J�������쐬
				auto camera = Instantate(CreateObjectType::Empty);
				control->myCamera = camera->AddComponent<LookOnCamera>();

				// �`�[����ݒ�
				SetTeum(control, info->teumId);
			}
		}
	}
	// �R���g���[���ɑ���Ƀ`�[���̃R���g���[����ݒ�
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
* ms�ɑΉ�����R���|�[�l���g��obj�ɒǉ�����
*
* @param obj �ǉ�����I�u�W�F�N�g
* @param ms �ǉ��������R���|�[�l���g�ɑΉ�����MsList
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
* �`�[����ݒ肷��
*
* @param control	�ݒ肷��R���g���[��
* @param id			�`�[��ID
*/
void BattleManager::SetTeum(const BaseControlPtr& control, int id)
{
	if (id == 1)
	{
		// �`�[��1�ɓo�^
		teum1Controls.push_back(control);
		
		// �`�[���l����1�ȏ�Ȃ玩�`�[���̃R���g���[����ݒ�
		if (teum1Controls.size() > 1)
		{
			control->myTeamOtherControl = teum1Controls.begin()->get();
			teum1Controls.begin()->get()->myTeamOtherControl = control.get();
		}
	}
	else
	{
		// �`�[��2�ɓo�^
		teum2Controls.push_back(control);

		// �`�[���l����1�ȏ�Ȃ玩�`�[���̃R���g���[����ݒ�
		if (teum2Controls.size() > 1)
		{
			control->myTeamOtherControl = teum2Controls.begin()->get();
			teum2Controls.begin()->get()->myTeamOtherControl = control.get();
		}
	}
}

/**
* ���X�|�[���ʒu��ݒ�
*
* @param poses �ݒ肵�������X�|�[���ʒu�z��
*/
void BattleManager::SetResponPos(const std::vector<Vector3>& poses)
{
	responPoses.clear();
	responPoses = poses;
}
