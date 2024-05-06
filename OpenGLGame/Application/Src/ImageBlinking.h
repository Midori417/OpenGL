/**
* @file ImagaeBlinking.h
*/
#ifndef IMAGEBLINKING_H_INCLUDED
#define IMAGEBLINKING_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class ImageBlinking : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ImageBlinking() = default;
	virtual ~ImageBlinking() = default;

private:

	/**
	* �X�V
	*/
	virtual void Update() override;

public:
	
	// �_�ł�����Image�R���|�[�l���g
	UI::ImagePtr image;

	// �_�ł̑��x
	float speed = 0.1f;

private:

	// true=����:false=������
	bool is = false;
};

#endif // !GUNDAMEYEBLINKING_H_INCLUDEDD
