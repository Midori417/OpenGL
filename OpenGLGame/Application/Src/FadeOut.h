/**
* @file FadeOut.h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

/**
* �t�F�[�h�A�E�g�R���|�[�l���g
*/
class FadeOut : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	FadeOut() = default;
	virtual ~FadeOut() = default;

	/**
	* �t�F�[�h���J�n����
	*/
	void FadeStart();

	/**
	* �t�F�[�h���n�܂��Ă��邩���擾
	* 
	* @retval true �n�܂��Ă���
	* @retval false �n�܂��Ă��Ȃ�
	*/
	bool IsFadeStart() const;

	/**
	* �t�F�[�h�̏󋵂��擾
	*
	* @retval true	�t�F�[�h�I��
	* @retval false	�I����Ă��Ȃ�
	*/
	bool IsFadeOut() const;

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

public:

	// �C���[�W�R���|�[�l���g
	ImagePtr image;

	// �t�F�[�h���x
	float speed = 1;

private:

	// �t�F�[�h���J�n���邩
	bool isStart = false;

	// �t�F�[�h���I����true : �I����ĂȂ����false
	bool isFadeOut = false;
};


#endif // !FADEOUT_H_INCLUDED
