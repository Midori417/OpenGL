/**
* @file ImageNum.h
*/
#ifndef IMAGENUM_H_INCLUDED
#define IMAGENUM_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class ImageNum : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ImageNum() = default;
	virtual ~ImageNum() = default;

public:

	/**
	* �������ꂽ�Ƃ��Ɏ��s
	*/
	virtual void Awake() override;

	void Stop();

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void  Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;


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
