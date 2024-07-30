/**
* @file BattleMap01Scene.h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* �퓬�V�[���̏�����
*
* @return true  ����������
* @return false ���������s
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

private:

	// �}�b�v�̑傫��
	Vector2 mapSize = Vector2(150, 180);

	// ���\�[�X�̓ǂݍ���
	static bool isResouceLoad;
};
#endif // !MAINSCENE_H_INCLUDED