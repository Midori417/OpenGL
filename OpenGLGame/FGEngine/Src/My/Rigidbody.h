/**
* @file Rigidbody.h
*/
#ifndef FGENGINE_RIGIDBODY_H_INCLUDED
#define FGENGINE_RIGIDBODY_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* ����������L���ɂ���R���|�[�l���g��
	*/
	class Rigidbody : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Rigidbody() = default;
		virtual ~Rigidbody() = default;

	public:

		// ���̂̑��x
		Vector3 velocity = Vector3::zero;

		// �d�̗͂L��
		bool isGravity = true;

		// �d�͂̉e���𐧌䂷��W��
		float gravityScale = 1;

	private:

		// �d�͉����x
		static constexpr float gravity = 9.81f;
	};
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
}

#endif // !FGENGINE_RIGIDBODY_H_INCLUDED
