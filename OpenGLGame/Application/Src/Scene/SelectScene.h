/**
* @file SelectScene.h
*/
#ifndef SELECTSCENE_H_INCLUDED
#define SELECTSCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* �Q�[���I���V�[��
*/
class SelectScene : public Scene
{
public:
	
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SelectScene() = default;

private:

	/**
	* �Q�[���I���V�[���̏�����
	*
	* @return true  ����������
	* @return false ���������s
	*/
	virtual bool Initialize() override;
};

#endif // !SELECTSCENE_H_INCLUDED
