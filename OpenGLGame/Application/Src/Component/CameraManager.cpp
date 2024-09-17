/**
* @file CameraManager.cpp
*/
#include "CameraManager.h"
#include "FGEngine/GameObject.h"

#include "LookOnCamera.h"

void CameraManager::Awake()
{
}

/**
* Update���n�܂�O�Ɉ�x���s
*/
void CameraManager::Start()
{
	// ���b�N�I���J������ݒ肷��
	lookOnCamera = OwnerObject()->AddComponent<LookOnCamera>();
}

/**
* ���t���[�����s
*/
void CameraManager::LateUpdate()
{
	// �^�[�Q�b�g�Ǝ��g�̋@�̂����Ȃ��ꍇ�������Ȃ�
	if (!trsTarget || !trsMyMs)
	{
		return;
	}

	// ���b�N�I���J����
	if (lookOnCamera)
	{
		lookOnCamera->LookCamera(trsTarget, trsMyMs);
	}
}

/**
* �R���|�[�l���g���N���[������
*/
ComponentPtr CameraManager::Clone() const
{
	return ComponentPtr();
}

/**
* ���g�̋@�̂�ݒ�
*/
void CameraManager::SetMyMs(const TransformPtr& myMs)
{
	this->trsMyMs = myMs.get();
}

/**
* �^�[�Q�b�g�@�̂�ݒ�
*/
void CameraManager::SetTarget(const TransformPtr& target)
{
	this->trsTarget = target.get();
}
