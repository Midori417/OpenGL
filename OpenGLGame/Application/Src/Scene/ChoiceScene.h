/**
* @file ChoiceScene.h
*/
#ifndef CHOICESCENE_H_INCLUDED
#define CHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* �Q�[���I���V�[��
*/
class ChoiceScene : public Scene
{
public:

	// �R���X�g���N�^
	ChoiceScene() = default;

	// �f�X�g���N�^
	virtual ~ChoiceScene() = default;

private:

	// �Q�[���I���V�[���̏�����
	virtual bool Initialize() override;

	// �Q�[���I���V�[���̍X�V
	virtual void Update() override;

	// �Q�[���I���V�[���̏I������
	virtual void Finalize() override;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
