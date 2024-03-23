/**
* @file MainScene.h
*/
#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* ���C���V�[��
*/
class MainScene : public FGEngine::SceneSystem::Scene
{
public:

	// �R���X�g���N�^
	MainScene() = default;

	// �f�X�g���N�^
	virtual ~MainScene() = default;

private:

	// ���C���V�[���̏�����
	virtual bool Initialize(Engine& engine) override;

	// ���C���V�[���̍X�V
	virtual void Update(Engine& engine) override;

	// ���C���V�[���̏I������
	virtual void Finalize(Engine& engine) override;

private:

	GltfAnimatedMeshRendererPtr animTestRenderer;

};
#endif // !MAINSCENE_H_INCLUDED