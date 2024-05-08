/**
* @file BattleMap01Scene.h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* �퓬�V�[��
*/
class BattleMap01Scene : public Scene
{
public:

	// �R���X�g���N�^
	BattleMap01Scene() = default;

	// �f�X�g���N�^
	virtual ~BattleMap01Scene() = default;

private:

	// �퓬�V�[���̏�����
	virtual bool Initialize() override;

	// �퓬�V�[���̍X�V
	virtual void Update() override;

	// �퓬�V�[���̏I������
	virtual void Finalize() override;

public:

	// �}�b�v�̑傫����
	float mapX = 0;

	// �}�b�v�̑傫���c
	float mapZ = 0;

};
#endif // !MAINSCENE_H_INCLUDED