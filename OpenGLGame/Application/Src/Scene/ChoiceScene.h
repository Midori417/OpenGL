/**
* @file ChoiceScene.h
*/
#ifndef CHOICESCENE_H_INCLUDED
#define CHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* �Q�[���I���V�[��
*/
class ChoiceScene : public Scene
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ChoiceScene() = default;
	virtual ~ChoiceScene() = default;

private:

	/**
	* �Q�[���I���V�[���̏�����
	*/
	virtual bool Initialize() override;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
