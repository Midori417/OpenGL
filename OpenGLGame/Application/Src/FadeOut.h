/**
* @file FadeOut.h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class FadeOut : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	FadeOut() = default;
	virtual ~FadeOut() = default;

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* �X�V
	*/
	virtual void Update() override;

public:

	/**
	* �t�F�[�h�̏󋵂��擾
	* 
	* @retval true	�t�F�[�h�I��
	* @retval false	�I����Ă��Ȃ�
	*/
	bool IsFadeOut() const;

public:

	// �C���[�W�R���|�[�l���g
	ImagePtr image;

	float speed = 1;

	// �t�F�[�h���J�n���邩
	bool isStart = false;

private:

	// �t�F�[�h���I����true : �I����ĂȂ����false
	bool isFadeOut = false;
};


#endif // !FADEOUT_H_INCLUDED
