/**
* @file TitleScene.h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* �^�C�g���V�[��
*/
class TitleScene : public FGEngine::Scene
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleScene() = default;

private:

	/**
	* �^�C�g���V�[���̏�����
	*
	* @return true  ����������
	* @return false ���������s
	*/
	virtual bool Initialize() override;
};

#endif // !FGENGINE_TITLESCENE_H_INCLUDED
