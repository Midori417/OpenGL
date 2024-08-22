/**
* @file ChoiceManager.cpp
*/
#include "ChoiceManager.h"
#include "FadeOut.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;

/**
* �ŏ��Ɏ��s
*/
void ChoiceManager::Start()
{
	// ���\�[�X�V�X�e�����擾
	auto resManager = AssetManager::GetInstance();

	float baseX = -570;
	float spaceX = 100;

	// �o�g���{�^�����쐬
	{
		auto battleButton = Instantate("BattleButton", Vector3(baseX, -200, 0), Quaternion::identity);
		auto image = battleButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// �I�v�V�����{�^�����쐬
	{
		auto optionButton = Instantate("OptionButton", Vector3(baseX + spaceX, 0, 0), Quaternion::identity);
		auto image = optionButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("OptionButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// ��߂�{�^�����쐬
	{
		auto exitButton = Instantate("ExitButton", Vector3(baseX + spaceX * 2, 200, 0), Quaternion::identity);
		auto image = exitButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = Instantate("FadeObjectA");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}
}

/**
* ���t���[�����s
*/
void ChoiceManager::Update()
{

	// �t�F�[�h�A�E�g���ݒ肳��Ă��Ȃ���Ή������Ȃ�
	if (!fadeOut)
	{
		return;
	}

	// �t�F�[�h�A�E�g���I�������
	if (fadeOut->IsFadeOut())
	{
		switch (choiceNum)
		{
		case (int)ChoiceManager::GameChoice::Battle:
			SceneManager::LoadScene("�o�g���ݒ�V�[��");
			break;
		case (int)ChoiceManager::GameChoice::Option:
			break;
		}
	}

	/**
	* �t�F�[�h���J�n�����牽�����Ȃ�
	*/
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	/**
	* Eneter����������I��������
	*/
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		if (choiceNum == (int)ChoiceManager::GameChoice::Exit)
		{
			// �E�B���h�E�����
			WindowManager::GetInstance()->WindowClose();
		}
		else
		{
			// ����ȊO�Ȃ�t�F�[�h�A�E�g���J�n����
			fadeOut->FadeStart();
		}
	}


	// �I�����ړ�
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		choiceNum++;
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		choiceNum--;
	}
	choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);

	for (int i = 0; i < imgButtons.size(); ++i)
	{
		// �I�����ꂽ��ʏ�F
		if (i == choiceNum)
		{
			imgButtons[i]->color = Color::white;
		}
		else
		{
			// �I������Ă��Ȃ���ΐF����������
			imgButtons[i]->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}
}
