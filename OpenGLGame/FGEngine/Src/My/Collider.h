/**
* @file Collider.h
*/
#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "Component.h"
#include "VectorFrd.h"
#include "MatrixFrd.h"
#include <memory>

namespace FGEngine
{

	// ��s�錾
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;

	/**
	* �R���C�_�[���N���X
	*/
	class Collider : public Component
	{
	public:

		Collider() = default;
		virtual ~Collider() = default;

		enum class Type
		{
			AABB,	// �����s���E�{�b�N�X
			Sphere, // ����
			Box,	// �L�����E�{�b�N�X
		};
		virtual Type GetType() const = 0;

		// ���W��ύX����
		virtual void AddPosition(const Vector3& translate) = 0;

		// ���W�ϊ������R���C�_�[���擾����
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const = 0;

	public:

		bool isTrigger = false;	// true=�d���Afalse=�d���s��
		bool isStatic = false;	// true=�����Ȃ����́Afalse=��������
	};
}
#endif // !COLLIDER_H_INCLUDED
