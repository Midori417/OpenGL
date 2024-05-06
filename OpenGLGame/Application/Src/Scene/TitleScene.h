/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* �^�C�g���V�[��
*/
class TitleScene : public Scene
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

	// �t�F�[�h�R���|�[�l���g
	FadeOutPtr fadeOut;

	// �{�^���������ꂽ��
	bool isStart = false;

};
#endif // !TITLESCENE_H_INCLUDED
