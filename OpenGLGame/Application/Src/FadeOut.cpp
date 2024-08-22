/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"
using namespace FGEngine::WindowSystem;

/**
* �t�F�[�h���J�n����
*/
void FadeOut::FadeStart()
{
	image->SetEnable(true);
	isStart = true;
}

/**
* �t�F�[�h���n�܂��Ă��邩���擾
*
* @retval true �n�܂��Ă���
* @retval false �n�܂��Ă��Ȃ�
*/
bool FadeOut::IsFadeStart() const
{
	return isStart;
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


/**
* �ŏ��Ɏ��s
*/
void FadeOut::Start()
{
	// �C���[�W�R���|�[�l���g��ǉ�
	image = OwnerObject()->AddComponent<Image>();
	image->texture = AssetManager::GetInstance()->GetTexture("white");
	image->color = Color::black;
	image->size = WindowManager::GetInstance()->GetWindowSize();

	// �A���t�@���[���ɂ���
	image->color.a = 0;
	image->SetEnable(false);
}

/**
* ���t���[�����s
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

	// �A���t�@�l��1�ȏ�ɂȂ�΃t�F�[�h���I������
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true; // �t�F�[�h�I��
	}
}