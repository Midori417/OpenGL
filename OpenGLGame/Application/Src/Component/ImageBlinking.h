/**
* @file ImageBlinking.h
*/
#ifndef IMAGEBLINKING_H_INCLUDED
#define IMAGEBLINKING_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

/**
* �C���[�W��_�ł���
*/
class ImageBlinking : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	ImageBlinking() = default;

private:

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �C���[�W�_�ŃR���|�[�l���g�̃N���[�����쐬
	* 
	* @return �N���[�������C���[�W�_�ŃR���|�[�l���g
	*/
	virtual ComponentPtr Clone() const override;

public:

	// �_�ő��x
	float speed = 1;

private:

	// �C���[�W�R���|�[�l���g
	ImagePtr image = nullptr;

	// �_�ł̐���
	bool isBlinking = false;
};
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;

#endif // !IMAGEBLINKING_H_INCLUDED