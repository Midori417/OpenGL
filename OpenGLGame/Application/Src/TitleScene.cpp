/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;

/**
* �^�C�g���V�[���̏�����
* 
* @param engine �G���W��
*/
bool TitleScene::Initialize()
{

	return true;
}

/**
* �^�C�g���V�[���̍X�V
* 
* @param engine		�G���W��
* @param deltaTime	�O��̍X�V����̌o�ߎ���
*/
void TitleScene::Update()
{
	if (Input::GetKeyDown(KeyCode::Enter))
	{
		SceneManager::LoadScene("���C���V�[��");
	}
}

/**
* �^�C�g���V�[���̏I��
* 
* @param engine �G���W��
*/
void TitleScene::Finalize()
{
}
