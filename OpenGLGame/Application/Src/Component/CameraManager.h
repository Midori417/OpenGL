/**
* @file CameraManager.h
*/
#ifndef CAMERAMANAGER_H_INCLUDED
#define CAMERAMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// ��s�錾
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* �J�����Ǘ��}�l�[�W���[
*/
class CameraManager : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CameraManager() = default;

private:

	virtual void Awake() override;

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void LateUpdate() override;

	/**
	* �R���|�[�l���g���N���[������
	*/
	virtual ComponentPtr Clone() const override;

public:

	/**
	* ���g�̋@�̂�ݒ�
	*/
	void SetMyMs(const TransformPtr& myMs);

	/**
	* �^�[�Q�b�g�@�̂�ݒ�
	*/
	void SetTarget(const TransformPtr& target);

private:

	// ���g�̋@��
	Transform* trsMyMs = nullptr;

	// �^�[�Q�b�g�̃g�����X�t�H�[��
	Transform* trsTarget = nullptr;

	// ���b�N�I���J�����R���|�[�l���g
	LookOnCameraPtr lookOnCamera = nullptr;
};

#endif // !CAMERAMANAGER_H_INCLUDED