/**
* @file TitleManager.h
*/
#ifndef TITLEMANAGER_H_INCLUDED
#define TITLEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// ��s�錾
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �^�C�g���Ǘ��R���|�[�l���g
*/
class TitleManager : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	TitleManager() = default;
	virtual ~TitleManager() = default;

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

	// �t�F�[�h�A�E�g
	FadeOutPtr fadeOut;
};


#endif // !TITLEMANAGER_H_INCLUDED
