/**
* @file Light.h
*/
#ifndef FGENGINE_LIGHT_H_INCLUDED
#define FGENGINE_LIHGT_H_INCLUDED
#include "Component.h"
#include "Color.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* ���C�g�R���|�[�l���g
	*/
	class Light : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Light() = default;
		virtual ~Light();

	public:

		// ���C�g�̎��
		enum class Type
		{
			pointLihgt,		// �_����
			spotLight,		// �X�|�b�g���C�g����
			directionLight,	// �f�B���N�V��������
		};
		Type type = Type::pointLihgt;	// ���C�g�̎��

		// ���C�g�̐F
		Color color = Color::white;

		// ���C�g�̖��邳
		float intensity = 1;

		// ���C�g���͂��ő唼�a
		float radius = 1;

		// �X�|�b�g���C�g�p�̃p�����[�^
		float coneAngle = Mathf::DegToRad(30);
	};
	using LightPtr = std::shared_ptr<Light>;
}

#endif // !FGENGINE_LIGHT_H_INCLUDED
