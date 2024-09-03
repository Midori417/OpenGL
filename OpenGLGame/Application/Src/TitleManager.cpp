/**
* @file TitleManager.cpp
*/
#include "TitleManager.h"
#include "FadeOut.h"

/**
* �ŏ��Ɏ��s
*/
void TitleManager::Start()
{
	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = Instantate("FadeObject");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}

}

/**
* ���t���[�����s
*/
void TitleManager::Update()
{
	// �t�F�[�h���I��������V�[���ړ�
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("�Q�[���I���V�[��");
	}

	// ��������̓��͂�����΃t�F�[�h���J�n������
	if (InputKey::AnyKey() && !fadeOut->IsFadeStart())
	{
		fadeOut->FadeStart();
	}

}
