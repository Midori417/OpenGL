/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* �^�C�g���V�[��
*/
class TitleScene : public FGEngine::SceneSystem::Scene
{
public:

	// �R���X�g���N�^
	TitleScene() = default;

	// �f�X�g���N�^
	virtual ~TitleScene() = default;

private:

	// �^�C�g���V�[���̏�����
	virtual bool Initialize() override;

	// �^�C�g���V�[���̍X�V
	virtual void Update() override;

	// �^�C�g���V�[���̏I��
	virtual void Finalize() override;

private:

	float rotY = 0;
	float rotX = 0;
};
#endif // !TITLESCENE_H_INCLUDED
