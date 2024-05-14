/**
* ImageBlinking.cpp
*/
#include "ImageBlinking.h"

/**
* ���t���[�����s
*/
void ImageBlinking::Update()
{
	// �C���[�W���Ȃ���Ή������Ȃ��܂��̓��[�v����Ȃ�
	if (!image)
	{
		return;
	}

	if (is)
	{
		image->color.a += speed *Time::DeltaTime();
		if (image->color.a >= 1)
		{
			image->color.a = 1;
			// �����Ă����ɐݒ�
			is = false;
		}
	}
	else
	{
		image->color.a -= speed * Time::DeltaTime();
		if (image->color.a <= 0)
		{
			image->color.a = 0;
			// �����Ă����ɐݒ�
			is = true;
		}

	}
}
