/**
* @file ImageBlinking.h
*/
#include "ImageBlinking.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Other/Time.h"

/**
* ���t���[�����s
*/
void ImageBlinking::Update()
{
	if (!image)
	{
		image = GetComponent<Image>();
		return;
	}

	// �\�����Ă���
	if (isBlinking)
	{
		image->color.a += speed * Time::DeltaTime();

		// ���S�ɕ\�����ꂽ��
		if (image->color.a >= 1)
		{
			image->color.a = 1;
			// �����Ă�����Ԃɂ���
			isBlinking = false;
		}
	}
	// �����Ă���
	else
	{
		image->color.a -= speed * Time::DeltaTime();

		// �����ɂȂ�����
		if (image->color.a <= 0)
		{
			image->color.a = 0;
			
			// �\�����Ă���
			isBlinking = true;
		}
	}
}

/**
* �C���[�W�_�ŃR���|�[�l���g�̃N���[�����쐬
*
* @return �N���[�������C���[�W�_�ŃR���|�[�l���g
*/
ComponentPtr ImageBlinking::Clone() const
{
	auto ptr = std::make_shared<ImageBlinking>();

	ptr->image = this->image;
	ptr->speed = this->speed;

	return ptr;
}
