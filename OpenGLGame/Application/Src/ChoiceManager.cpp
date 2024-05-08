/**
* @file ChoiceManager.cpp
*/
#include "ChoiceManager.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::SceneSystem;
#include "FadeOut.h"

/**
* �ŏ��Ɏ��s
*/
void ChoiceManager::Start()
{

}

/**
* ���t���[�����s
*/
void ChoiceManager::Update()
{

	if (fadeOut)
	{
		if (fadeOut->IsFadeOut())
		{
			SceneManager::LoadScene("�o�g���}�b�v01�V�[��");
		}
	}

	/**
	* �t�F�[�h���J�n�����牽�����Ȃ�
	*/
	if (isFadeStart)
	{
		return;
	}

	// �I�����ړ�
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		choiceNum++;
		choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		choiceNum--;
		choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);
	}

	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		switch (choiceNum)
		{
		case (int)ChoiceManager::GameChoice::Battle:
			isFadeStart = true;
			if (fadeOut)
			{
				fadeOut->isStart = true;
			}
			break;
		case (int)ChoiceManager::GameChoice::Option:
			break;
		case (int)ChoiceManager::GameChoice::Exit:
			// �E�B���h�E�����
			WindowManager::GetInstance()->WindowClose();
			break;
		}
	}
	

	for (int i = 0; i < imgButtons.size(); ++i)
	{
		// �I������Ă���F���Â�����
		if (i == choiceNum)
		{
			imgButtons[i]->color = Color::white;
		}
		else
		{
			imgButtons[i]->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}
}
