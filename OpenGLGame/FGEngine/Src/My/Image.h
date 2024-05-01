/**
* @file Image.h
*/
#ifndef COMPONENT_IMAGE_H_INCLUDED
#define COMPONENT_IMAGE_H_INCLUDED
#include "ImGuiUI.h"
#include "Vector2.h"
#include "Color.h"
#include <string>

/**
* UI�摜
*/
class Image : public ImGuiUI
{
public:

	// �R���X�g���N�^
	Image() = default;

	// �f�X�g���N�^
	virtual ~Image() = default;


private:

	// UI������
	virtual void UIUpdate() override;

public:

	std::string filename;	// �e�N�X�`���̃t�@�C����

	Vector2 size = Vector2::zero;
	Color color = Color::black;

	float radian = 0;

	float fillAmout = 1;	
};
using ImagePtr = std::shared_ptr<Image>;

#endif // !COMPONENT_IMAGE_H_INCLUDED
