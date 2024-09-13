/**
* @file SelectManger.h
*/
#ifndef SELECTMANGER_H_INCLUDED
#define SELECTMANGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Color.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �I���V�[���̊Ǘ��R���|�[�l���g
*/
class SelectManager : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SelectManager() = default;

private:

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	/**
	* �I������
	*/
	enum Select
	{
		// �o�g����ʂɈړ�
		Battle,

		// �Q�[�����I��
		Exit,
	};
	// ���ݑI�����Ă��鍀�ڔԍ�
	int selectNum = 0;

	// ���I�����̐F
	Color noSelectColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

	// �I���{�^���C���[�W�R���|�[�l���g�z��
	std::vector<ImagePtr> imgButtons;

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSource = nullptr;
};

#endif // !SELECTMANGER_H_INCLUDED
