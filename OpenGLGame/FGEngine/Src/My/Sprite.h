/**
* @file Sprite.h
*/
#ifndef FGENGINE_SPRITE_H_INCLUDED
#define FGENGINE_SPRITE_H_INCLUDED
#include "VectorPoint.h"

namespace FGEngine
{
	/**
	* �}�`�ɕ\������͈͂�\���\����
	*/
	struct Texcoord
	{
		// �e�N�X�`�����W
		Vector2 uv;

		// �}�`�̑傫��
		Vector2 size;
	};

	/**
	* �摜�\���p�f�[�^(�X�v���C�g)���i�[����\����
	*/
	struct Sprite
	{
		// �摜��\��������W
		Vector4 pos;

		// �e�N�X�`�����W�Ƒ傫��
		Texcoord texcoord;
	};
}

#endif // !FGENGINE_SPRITE_H_INCLUDED
