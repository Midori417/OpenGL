/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "HumanControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
#include "Global.h"
#include "BgmList.h"
using namespace FGEngine::SoundSystem;

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
* ���X�|�[���ʒu��ݒ�
*
* @param pos ���X�|�[���ʒu
*/
void BattleManager::SetResponPos(const Vector3& pos)
{
	responPoses.push_back(pos);
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
* �������Ɏ��s
*/
void BattleManager::Awake()
{
	// �e�}�l�[�W�����擾
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �o�g������ݒ�
	if (battleInfo->teum1Hp > 0)
	{
		teum1Hp = std::make_shared<int>(battleInfo->teum1Hp);
	}
	if (battleInfo->teum1Hp > 0)
	{
		teum2Hp = std::make_shared<int>(battleInfo->teum2Hp);
	}

	battleTimer = battleInfo->time;

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
			auto hyumanControl = player->AddComponent<HumanControl>();
			controlOwners.push_back(hyumanControl);

			// �@�̂�ݒ�
			auto ms = Instantate("MS" + std::to_string(i));

			// �Ή�����Ms�R���|�[�l���g��ǉ�
			hyumanControl->myMs = SetMs(ms, x->ms);

			// �J������ݒ�
			auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
			hyumanControl->myCamera = camera->AddComponent<LookOnCamera>();
			auto linstner = camera->AddComponent<AudioListner>();
			SoundManager::GetInstance()->SetListner(linstner);
			// �`�[����ݒ�
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(hyumanControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum1ControlOwners.size() > 1)
				{
					hyumanControl->myTeamOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeamOtherOwner = hyumanControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(hyumanControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum2ControlOwners.size() > 1)
				{
					hyumanControl->myTeamOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeamOtherOwner = hyumanControl.get();
				}
			}
		}
		else if (x->playerId == 1)
		{
			auto cpuControl = player->AddComponent<CpuControl>();
			controlOwners.push_back(cpuControl);

			// �@�̂�ݒ�
			auto ms = Instantate("MS" + std::to_string(i));

			// �Ή�����Ms�R���|�[�l���g��ǉ�
			cpuControl->myMs = SetMs(ms, x->ms);

			// ���z�J������ݒ�
			auto camera = Instantate("virtualCamera");
			cpuControl->myCamera = camera->AddComponent<LookOnCamera>();

			// �`�[����ݒ�
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(cpuControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum1ControlOwners.size() > 1)
				{
					cpuControl->myTeamOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeamOtherOwner = cpuControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(cpuControl);
				// �`�[���l����1�ȏ�Ȃ玩�`�[���̃I�[�i��ݒ�
				if (teum2ControlOwners.size() > 1)
				{
					cpuControl->myTeamOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeamOtherOwner = cpuControl.get();
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
				teum1->otherTeamOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : teum2ControlOwners)
		{
			for (auto teum1 : teum1ControlOwners)
			{
				teum2->otherTeamOwner.push_back(teum1.get());
			}
		}
	}

	// ���`�[���̗͂�ݒ�
	{
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->SetTeamHP(teum1Hp.get(), teum2Hp.get());
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->SetTeamHP(teum2Hp.get(), teum1Hp.get());
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
	}

	audioSource = OwnerObject()->AddComponent<AudioSource>();
	audioSource->SetSoundFilename(BGM::bgm01);
	audioSource->SetVolume(0.05f);
	audioSource->isLooop = true;
}

/**
* �ŏ��Ɏ��s
*/
void BattleManager::Start()
{
	// MS�̏o���ʒu��ݒ�
	for (int i = 0; i < teum1ControlOwners.size(); ++i)
	{
		auto teum1 = teum1ControlOwners[i];

		teum1->myMs->GetTransform()->position = responPoses[0] + Vector3(10.0f * i, 0, 0);
		teum1->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		teum1->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}
	for (int i = 0; i < teum2ControlOwners.size(); ++i)
	{
		auto teum2 = teum2ControlOwners[i];

		teum2->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// ���X�|�[���ʒu��ݒ�
		teum2->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		teum2->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
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
			imgStandbay->SetEnable(true);

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
			imgStandbay->SetEnable(false);
			// GO��\��
			imgGo->SetEnable(true);

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

			audioSource->Play();

			// GO���\����
			imgGo->SetEnable(false);

			// �R���g���[���̏������J�n������
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->ControlStart();
			}
			for (auto teum2 : teum2ControlOwners)
			{
				teum2->ControlStart();
			}
		}
	}
	break;
	case BattleManager::BattleState::Battle:

		// �o�g����
	{
		// �o�g�����Ԃ����炷
		battleTimer -= Time::DeltaTime();

		if (*teum1Hp <= 0 || *teum2Hp <= 0)
		{
			audioSource->Stop();
			VictoryState teum1Victory = VictoryState::None;
			VictoryState teum2Victory = VictoryState::None;
			// �ǂ���̃`�[��Hp��0�Ȃ�Έ�������
			if (*teum1Hp <= 0 && *teum2Hp <= 0)
			{
				teum1Victory = VictoryState::Drow;
				teum2Victory = VictoryState::Drow;
			}
			else if (*teum1Hp <= 0)
			{
				teum1Victory = VictoryState::Lose;
				teum2Victory = VictoryState::Win;
			}
			else if (*teum2Hp <= 0)
			{
				teum1Victory = VictoryState::Win;
				teum2Victory = VictoryState::Lose;
			}

			// �I������������
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->Finish(teum1Victory);
				teum1->isActive = false;
			}
			for (auto teum2 : teum2ControlOwners)
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
			SceneManager::LoadScene("�o�g���ݒ�V�[��");
		}
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
