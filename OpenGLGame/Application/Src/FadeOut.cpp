/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"

/**
* �ŏ��Ɏ��s
*/
void FadeOut::Start()
{
	// �R���|�[�l���g���擾
	image = OwnerObject()->GetComponent<Image>();

	// �C���[�W���Ȃ���Ή������Ȃ�
	if (!image)
	{
		return;
	}

	image->color.a = 0;
}

/**
* �X�V
*/
void FadeOut::Update()
{
	// �C���[�W���Ȃ���Ή������Ȃ�
	if (!image || isFadeOut || !isStart)
	{
		return;
	}

	// �A���t�@�l�𑝉�
	image->color.a += speed * Time::DeltaTime();
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true; // �t�F�[�h�I��
	}
}

/**
* �t�F�[�h�̏󋵂��擾
*
* @retval true	�t�F�[�h�I��
* @retval false	�I����Ă��Ȃ�
*/
bool FadeOut::IsFadeOut() const
{
	return isFadeOut;
}
