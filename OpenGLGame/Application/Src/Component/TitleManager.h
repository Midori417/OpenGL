/**
* @file TitleManager.h
*/
#ifndef TITLEMANAGER_H_INCLUDED
#define TITLEMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �^�C�g���V�[���̊Ǘ��R���|�[�l���g
*/
class TitleManager : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleManager() = default;

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

	// �V�[���؂�ւ����̃t�F�[�h�A�E�g�R���|�[�l���g
	FadeOutPtr fadeOut = nullptr;

	// ���艹��炷���߂̃R���|�[�l���g
	AudioSourcePtr audioSource = nullptr;
};

#endif // !TITLEMANAGER_H_INCLUDED
