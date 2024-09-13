/**
* @file FadeOut,h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

/**
* �t�F�[�h�A�E�g�I�u�W�F�N�g�R���|�[�l���g
*/
class FadeOut : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	FadeOut() = default;

public:

	/**
	* �t�F�[�h���J�n����
	*/
	void FadeStart();

	/**
	* �t�F�[�h���J�n���Ă��邩�擾
	* 
	* @retval true	�n�߂��Ă���
	* @retval false �n�܂��Ă��Ȃ�
	*/
	bool IsFadeStart() const;

	/**
	* �t�F�[�h�̏󋵂��擾
	* 
	* @retval true	�t�F�[�h�A�E�g����
	* @retval false	�t�F�[�h���܂��̓t�F�[�h�J�n���Ă��Ȃ�
	*/
	bool IsFadeOut() const;

private:

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �t�F�[�h�A�E�g�R���|�[�l���g���N���[������
	* 
	* @return �N���[�������t�F�[�h�A�E�g�R���|�[�l���g
	*/
	virtual ComponentPtr Clone() const override;

public:

	// �t�F�[�h�A�E�g���鑬�x
	float speed = 1;

private:

	// �C���[�W�R���|�[�l���g
	ImagePtr image = nullptr;

	// true�Ȃ�t�F�[�h���J�n����
	bool isStart = false;

	// �t�F�[�h������������true
	bool isFadeOut = false;

};
using FadeOutPtr = std::shared_ptr<FadeOut>;

#endif // !FADEOUT_H_INCLUDED
