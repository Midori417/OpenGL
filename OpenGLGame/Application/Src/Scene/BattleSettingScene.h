/**
* @file BattleSettingScene.h
*/
#ifndef BATTLESETTINGSCENE_H_INCLUDED
#define BATTLESETTINGSCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* �o�g���ݒ�V�[��
*/
class BattleSettingScene : public Scene
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleSettingScene() = default;

private:

	/**
	* �o�g���ݒ�V�[���̏�����
	*
	* @return true  ����������
	* @return false ���������s
	*/
	virtual bool Initialize() override;
};

#endif // !BATTLESETTINGSCENE_H_INCLUDED
