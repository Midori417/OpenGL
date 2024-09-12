/**
* @file CrateGameObjectType.h
*/
#ifndef FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
#define FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
#include <string>

namespace FGEngine
{
	namespace CreateObjectType
	{
		// �������ĂȂ��Q�[���I�u�W�F�N�g
		inline const std::string Empty = "Empty";

		// �J����
		inline const std::string Camera = "Camera";

		// 3D�I�u�W�F�N�g
		namespace GameObject3D
		{
			// �l�p�`
			inline const std::string Cube = "Cube";

			// ����
			inline const std::string Sphere = "Sphere";
		}
		// ���[�U�[�C���^�[�t�F�[�X
		namespace UI
		{
			// �摜
			inline const std::string Image = "Image";

			// �{�^��
			inline const std::string Button = "Button";
		}
	}
}
#endif // !FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
