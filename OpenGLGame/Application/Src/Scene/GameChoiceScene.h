/**
* @file GameChoiceScene.h
*/
#ifndef GAMECHOICESCENE_H_INCLUDED
#define GAMECHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* �Q�[���I���V�[��
*/
class GameChiecScene : public Scene
{
public:

	// �R���X�g���N�^
	GameChiecScene() = default;

	// �f�X�g���N�^
	virtual ~GameChiecScene() = default;

private:

	// �Q�[���I���V�[���̏�����
	virtual bool Initialize() override;

	// �Q�[���I���V�[���̍X�V
	virtual void Update() override;

	// �Q�[���I���V�[���̏I������
	virtual void Finalize() override;

private:

	/**
	* �I��
	*/
	enum class Choice
	{
		// �퓬
		Battle,

		// �I�v�V����
		Option,

		// �Q�[���I��
		Exit,
	};

	Choice choice = Choice::Battle;
	int choiceNum = 0;

	Color highlightedColor = Color{ 1.3f, 1.3f, 1.3f , 1};		// �I��F
	Color pressedColor = Color{ 0.7f, 0.7f, 0.7f , 1};		// �����F

	// �{�^���z��
	std::vector<UI::ImagePtr> imgButtons;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
