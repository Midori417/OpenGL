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
bool TitleScene::Initialize(FGEngine::Engine& engine)
{
	engine.CreateCameraObject("camera");
	auto title = engine.Create<GameObject>("Title");
	{
		auto image = title->AddComponent<Image>();
		image->filename = "Application/Res/UI/Title/Title.tga";
		image->size = engine.GetFramebufferSize();
	}
	auto pos = engine.GetFramebufferSize() / 2;
	auto titleLogo = engine.Create<GameObject>("TitleLogo", Vector3(pos.x - 1000 /2, pos.y - 400 / 2, 0));
	{ 
		auto image = titleLogo->AddComponent<Image>();
		image->filename = "Application/Res/UI/Title/TitleLogo.tga";
		image->size = Vector2(1000, 400);
	}

	return true;
}

/**
* �^�C�g���V�[���̍X�V
* 
* @param engine		�G���W��
* @param deltaTime	�O��̍X�V����̌o�ߎ���
*/
void TitleScene::Update(FGEngine::Engine& engine)
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
void TitleScene::Finalize(FGEngine::Engine& engine)
{
	engine.AllClearGameObject();
}
