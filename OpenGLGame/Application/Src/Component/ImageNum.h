/**
* @file ImageNum.h
*/
#ifndef IMAGENUM_H_INCLUDED
#define IMAGENUM_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class ImageNum : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	ImageNum() = default;

private:

	/**
	* �������ꂽ�Ƃ��Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void  Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	void Stop();

public:

	// �`�悷�鐔��
	int num = 0;

	// ����
	Vector2 offsetPos = Vector2::zero;

	// �Ԋu
	float space = 50;

	// �����̑傫��
	float scale = 1;

private:
	
	// ����������`�悷��C���[�W�R���|�[�l���g
	std::vector<ImagePtr> imgNums;

	// �����e�N�X�`���z��
	std::vector<TexturePtr> texNums;
};


#endif // !IMAGENUM_H_INCLUDED
