/**
* @file BattleSettingManager.cpp
*/
#include "BattleSettingManager.h"
#include "FadeOut.h"
using namespace FGEngine::UI;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;

/**
* �������Ɏ��s
*/
void BattleSettingManager::Awake()
{
	// �}�l�[�W�����擾
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �o�g���ݒ��ʂ��쐬
	{
		auto battleSetting = Instantate("BattleSetting");
		auto image = battleSetting->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleSetting");
		image->size = winManager->GetWindowSize();
	}

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = Instantate("FadeObjectB");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}
}

/**
* ���t���[�����s
*/
void BattleSettingManager::Update()
{
	// �t�F�[�h�A�E�g���I�������
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("�o�g���}�b�v01�V�[��");
	}

	/**
	* �t�F�[�h���J�n�����牽�����Ȃ�
	*/
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Eneter(����{�^��)���t�F�[�h�J�n
	if (InputKey::GetKey(KeyCode::Enter))
	{
		fadeOut->FadeStart();
	}
}
