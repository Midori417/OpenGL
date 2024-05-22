/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

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
};
#endif // !TITLESCENE_H_INCLUDED
