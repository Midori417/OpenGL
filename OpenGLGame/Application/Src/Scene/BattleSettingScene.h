/**
* @file BattleSettingScene.h
*/
#ifndef BATTLESETTINGSCENE_H_INCLUDED
#define BATTLESETTINGSCENE_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* �o�g���ݒ�V�[��
*/
class BattleSettingScene : public Scene
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BattleSettingScene() = default;
	virtual ~BattleSettingScene() = default;

private:

	/**
	* �o�g���ݒ�V�[���̏�����
	*/
	virtual bool Initialize() override;
};


#endif // !GAMESETTINGSCENE_H_INCLUDED
