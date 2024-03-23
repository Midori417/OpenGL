/**
* @file Light.h
*/
#ifndef LIGHT_H_INCULDED
#define LIGHT_H_INCLUDED

#include "Component.h"
#include "VecMath.h"

namespace FGEngine
{

	/**
	* ���C�g�R���|�[�l���g
	*/
	class Light : public Component
	{
	public:

		Light() = default;
		virtual ~Light();

		// �R���|�[�l���g�̏�����
		virtual void Awake() override;
		// �R���|�[�l���g�̍X�V
		virtual void Update() override;

	public:

		// ���C�g�̎��
		enum class Type {
			pointLight, // �_����
			spotLight,	// �X�|�b�g���C�g����
		};
		Type type = Type::pointLight; // ���C�g�̎��

		Vector3 color = { 1,1,1 }; // �F
		float intensity = 1;	// ���邳
		float radius = 1;		// ���C�g���͂��ő唼�a

		// �X�|�b�g���C�g�p�̃p�����[�^
		// ������GameObject::rotation����v�Z
		float coneAngle = 30 * Mathf::Deg2Rad;	// �X�|�b�g���C�g���Ƃ炷�p�x
		float falloffAngle = 20 * Mathf::Deg2Rad;	// �X�|�b�g���C�g�̌����J�n�p�x

	private:

		int lightIndex = -1;		// ���C�g�C���f�b�N�X

	};
}
#endif // !LIGHT_H_INCULDED
