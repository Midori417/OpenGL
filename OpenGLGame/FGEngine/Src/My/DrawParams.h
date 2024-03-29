/**
* @file DrawParams.h
*/
#ifndef FGENGINE_DRAWPARAMS_H_INCLUDED
#define FGENGINE_DRAWPARAMS_H_INCLUDED
#include "Package/Glad.h"

namespace FGEngine::Rendering
{
	/**
	* �`��p�����[�^
	*/
	struct DrawParams
	{
		// �v���~�e�B�u�̎��
		GLenum mode = GL_TRIANGLES;	

		// �`�悷��C���f�b�N�X�̐�
		GLsizei count = 0;

		// �`��J�n�C���f�b�N�X�̃o�C�g�I�t�Z�b�g
		const void* indices = 0;

		// �C���f�b�N�X0�ƂȂ钸�_�z����̈ʒu
		GLint baseVertex = 0;		

		// �}�e���A���C���f�b�N�X
		int materialNo = -1;
	};
}

#endif // !FGENGINE_DRAWPARAMS_H_INCLUDED
