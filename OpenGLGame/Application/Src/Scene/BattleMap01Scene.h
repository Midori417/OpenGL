/**
* @file BattleMap01Scene,h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* �o�g���}�b�v01�V�[��
*/
class BattleMap01Scene : public Scene
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleMap01Scene() = default;

private:

	/**
	* �o�g���}�b�v01�V�[���̏�����
	*
	* @return true  ����������
	* @return false ���������s
	*/
	virtual bool Initialize() override;
};


#endif // !BATTLEMAP01SCENE_H_INCLUDED
