/**
* @file MainScene.h
*/
#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* ���C���V�[��
*/
class MainScene : public Scene
{
public:

	// �R���X�g���N�^
	MainScene() = default;

	// �f�X�g���N�^
	virtual ~MainScene() = default;

private:

	// ���C���V�[���̏�����
	virtual bool Initialize() override;

	// ���C���V�[���̍X�V
	virtual void Update() override;

	// ���C���V�[���̏I������
	virtual void Finalize() override;

};
#endif // !MAINSCENE_H_INCLUDED