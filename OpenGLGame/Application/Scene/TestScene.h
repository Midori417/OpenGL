/**
* @file TestScene,h
*/
#ifndef TESTSCENE_H_INCLUDED
#define TESTSCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* �e�X�g�V�[���u
*/
class TestScene : public Scene
{
public:

	// �R���X�g���N�^
	TestScene() = default;

	// �f�X�g���N�^
	virtual ~TestScene() = default;

private:

	// �^�C�g���V�[���̏�����
	virtual bool Initialize() override;
};
#endif // !TITLESCENE_H_INCLUDED
