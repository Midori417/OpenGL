/**
* @file BasePilot.h
*/
#ifndef BASEPILOT_H_INCLUDED
#define BASEPILOT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

#include "../GameInput.h"

// ��s�錾
class BasePilot;
using BasePilotPtr = std::shared_ptr<BasePilot>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class CameraManager;
using CameraManagerPtr = std::shared_ptr<CameraManager>;

/**
* �p�C���b�g�̊��R���|�[�l���g
*/
class BasePilot : public GameEvent
{
protected: // �h����Ő�������

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BasePilot() = default;

private: // �C�x���g

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

protected:

	/**
	* ������
	*/
	void Initialize();

public: // �Z�b�^�[

	/**
	* �p�[�g�i�[�p�C���b�g��ݒ�
	* 
	* @param �ݒ肷��p�[�g�i�[�p�C���b�g
	*/
	void SetPartnerPilot(const BasePilotPtr& pilot);

	/**
	* ����`�[���̃p�C���b�g��ݒ�
	* 
	* @param �ݒ肷�鑊��`�[���̃p�C���b�g
	*/
	void SetOtherTeamPilot(const BasePilotPtr& pilot);

protected: // �p�[�g�i�[�֌W

	/**
	* �p�[�g�i�[�p�C���b�g���擾
	*/
	BasePilot* GetPartnerPilot() const;

	/**
	* �p�[�g�i�[�̋@�̂��擾
	*/
	BaseMsPtr GetPartnerMs() const;

protected: // ����`�[���֌W

	/**
	* ����`�[���̃p�C���b�g���擾
	* 
	* @param index �p�C���b�g�ԍ�
	*/
	BasePilot* GetOtherTeamPilot(size_t index) const;

	/**
	* ����`�[���̋@�̂��擾
	*
	* @param index �p�C���b�g�ԍ�
	*/
	BaseMsPtr GetOtherTeamMs(size_t index) const;

	/**
	* ����`�[���̃p�C���b�g�̐����擾
	*/
	size_t GetOtherTeamPilotSize() const;

protected: // �^�[�Q�b�g�֌W

	/**
	* �^�[�Q�b�g�p�C���b�g���擾
	*/
	BasePilot* GetTargetPilot() const;

	/**
	* �^�[�Q�b�g�@�̂��擾
	*/
	BaseMsPtr GetTargetMs() const;

public:

	// �J�����Ǘ��}�l�[�W���[
	CameraManagerPtr myCamera = nullptr;

	// �����̋@��
	BaseMsPtr myMs = nullptr;

	// �����ʒu�z��
	std::vector<Vector3> responPoss;

protected:

	// �Q�[������
	GameInputPtr gameInput;

private:

	// ���݂̃^�[�Q�b�g�p�C���b�g
	BasePilot* targetPilot = nullptr;

	// �p�[�g�i�[�p�C���b�g
	BasePilot* partnerPilot = nullptr;

	// ����`�[���p�C���b�g�z��
	std::vector<BasePilot*> otherTeamPilots;
};

#endif // !BASEPILOT_H_INCLUDED
