/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED

#include "MyEngine.h"

/**
* �^�C�g���V�[��
*/
class TitleScene : public SceneManagment::Scene
{
public:

	// �R���X�g���N�^
	TitleScene() = default;

	// �f�X�g���N�^
	virtual ~TitleScene() = default;

private:

	// �^�C�g���V�[���̏�����
	virtual bool Initialize(Engine& engine) override;

	// �^�C�g���V�[���̍X�V
	virtual void Update(Engine& engine) override;

	// �^�C�g���V�[���̏I��
	virtual void Finalize(Engine& engine) override;

private:

};
#endif // !TITLESCENE_H_INCLUDED
