/**
* @file ChoiceManager.h
*/
#ifndef CHOICEMANAGER_H_INCLUDED
#define CHOICEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;


class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �I���V�[���Ǘ��N���X
*/
class ChoiceManager : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ChoiceManager() = default;
	virtual ~ChoiceManager() = default;

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

private:

	/**
	* �I��
	*/
	enum class GameChoice
	{
		// �퓬
		Battle,

		// �I�v�V����
		Option,

		// �Q�[���I��
		Exit,
	};

	GameChoice choice = GameChoice::Battle;
	int choiceNum = 0;

	// �I��F
	Color highlightedColor = Color{ 0.7f, 0.7f, 0.7f , 1 };

	// �{�^���������ꂽ��
	bool isFadeStart = false;

public:

	// �{�^���z��
	std::vector<UI::ImagePtr> imgButtons;

	// �t�F�[�h�R���|�[�l���g
	FadeOutPtr fadeOut;

};

#endif // !CHOICEMANAGER_H_INCLUDED