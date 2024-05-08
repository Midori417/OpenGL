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
			auto playerMs = Instantate("MyMs", Vector3(0, 10, 50), Quaternion::AngleAxis(180, Vector3::up));;
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
			auto cpuMs = Instantate("CpuMs", Vector3(0, 10, -50));
			cpuControl->myMs = SetMs(cpuMs, cpuControl->ms);
		}
	}

	// ���݂��̃R���g���[���[�̏���ݒ�
	playerControl->otherOwner = cpuControl.get();
	cpuControl->otherOwner = playerControl.get();
}

/**
* ���t���[�����s
*/
void BattleManager::Update()
{
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
