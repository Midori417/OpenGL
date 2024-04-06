/**
* @file LightData.h
*/
#ifndef FGENGINE_LIGHTDATA_H_INCLUDED
#define FGENGINE_LIGHTDATA_H_INCLUDED
#include "Vector3.h"

namespace FGEngine::GraphicsSystem
{
	/**
	* �������
	*/
	struct LightData
	{
		// �ʒu
		Vector3 position = Vector3::zero;

		// ���邳
		float intesity = 1;

		// ���C�g���͂��ő唼�a
		float radius = 1;

		// �F
		Vector3 color = Vector3::one;


		// �X�|�b�g���C�g�p�̕ϐ�

		// ����
		Vector3 direction;	

		// �X�|�b�g���C�g���Ƃ炷�p�x
		float coneAngle;

		// �X�|�b�g���C�g�̌����J�n�p�x
		float fallOffAngle;

		// �g�p�̗L��
		bool used = false;

	};

}

#endif // !FGENGINE_LIGHTDATA_H_INCLUDED
