/**
* @file Intersect.cpp
*/
#include "FGEngine/Physics/Intersect.h"
#include "FGEngine/Math/Mathf.h"
#include <algorithm>
#include <vector>

namespace FGEngine
{
	/**
	* AABB���m�̌�������
	*
	* @param a				����Ώۂ�AABB���̂P
	* @param b				����Ώۂ�AABB����2
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������ĂȂ�
	*/
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration)
	{
		// === X�� === //
		// a�̍����ʂ�b�̉E���ʂ��E�ɂ���Ȃ�A�������Ă��Ȃ�
		const float dx0 = b.max.x - a.min.x;
		if (dx0 <= 0)
		{
			return false;
		}
		// a�̉E���˂�b�̍����ʂ�荶�ɂ���̂Ȃ�A�������Ă��Ȃ�
		const float dx1 = a.max.x - b.min.x;
		if (dx1 <= 0)
		{
			return false;
		}
		// === Y�� === //
		// a�̉����ʂ�b�̏㑤�ʂ���ɂ���̂Ȃ�A�������Ă��Ȃ�
		const float dy0 = b.max.y - a.min.y;
		if (dy0 <= 0)
		{
			return false;
		}
		// a�̏㑤�ʂ�b�̉����ʂ�艺�ɂ���̂Ȃ�A�������Ă��Ȃ�
		const float dy1 = a.max.y - b.min.y;
		if (dy1 <= 0)
		{
			return false;
		}
		// === Z�� === //
		// a�̉����ʂ�b�̎�O���ʂ���O�ɂ���̂Ȃ�A�������Ă��Ȃ�
		const float dz0 = b.max.z - a.min.z;
		if (dz0 <= 0)
		{
			return false;
		}
		// a�̎�O�ʂ�b�̉����ʂ�艜�ɂ���̂Ȃ�A�������Ă��Ȃ�
		const float dz1 = a.max.z - b.min.z;
		if (dz1 <= 0)
		{
			return false;
		}

		// ���̎��_�Ō������m��

		// XYZ�̊e���ɂ��āA�d�Ȃ��Ă��鋗�����Z��������I��
		Vector3 length = Vector3{ dx1, dy1, dz1 };		// �ђʋ����̐�Βl
		Vector3 signedLength = length;			// �����t���̊ђʋ���
		// ��r�Ώۂ��R�Ɍ��炷
		// dx0�̂ق��������������ǂ���
		if (dx0 < dx1)
		{
			length.x = dx0;
			signedLength.x = -dx0;
		}
		// dy0�̂ق��������������ǂ���
		if (dy0 < dy1)
		{
			length.y = dy0;
			signedLength.y = -dy0;
		}
		// dz0�̂ق��������������ǂ���
		if (dz0 < dz1)
		{
			length.z = dz0;
			signedLength.z = -dz0;
		}

		// XYZ�̂����ł��Z��������I��
		// Y�������X�����̂ق��������������ǂ���
		if (length.x < length.y)
		{
			// Z�������X�����̂ق����������ǂ���
			if (length.x < length.z)
			{
				// x�̒������߂�
				penetration = Vector3{ signedLength.x, 0, 0 };
				return true;
			}
		}
		// Z�������Y�����̂ق����������ǂ���
		else if (length.y < length.z)
		{
			// y�̒������߂�
			penetration = Vector3{ 0,signedLength.y, 0 };
			return true;
		}

		// Z�������X�����̂ق������������ǂ���
		penetration = Vector3{ 0, 0, signedLength.z };
		return true;
	}

	/**
	* AABB����_�ւ̍ŋߐړ_
	*
	* @param aabb	����Ώۂ�AABB
	* @param point	����Ώۂ̓_
	*
	* @return	AABB�̒��ł��ł��_�ɋ߂����W
	*/
	Vector3 ClosetPoint(const AABB& aabb, const Vector3& point)
	{
		Vector3 result;
		for (int i = 0; i < 3; ++i)
		{
			result[i] = Mathf::Clamp(point[i], aabb.min[i], aabb.max[i]);
		}
		return result;
	}

	/**
	* AABB�Ƌ��̂̌�������
	*
	* @param aabb			����Ώۂ�AABB
	* @param sphere			����Ώۂ̋���
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true �������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration)
	{
		// �ŋߐړ_�܂ł̋��������̂̔��a��蒷����Ό������Ă��Ȃ�
		const Vector3 p = ClosetPoint(aabb, sphere.position);
		const Vector3 v = sphere.position - p;
		const float d2 = Vector3::Dot(v, v);
		if (d2 > sphere.radius * sphere.radius)
		{
			return false;
		}

		// �������Ă���̂ŁA�ђʃx�N�g�������߂�
		if (d2 > 0)
		{
			// ������0���傫���ꍇ�A���̂̒��S��AABB�̊O���ɂ���
			// ���̂̒��S���W����ŋߐړ_�֌�������������Փ˂����Ƃ݂Ȃ�
			const float d = Mathf::Sqrt(d2);
			penetration = v * ((sphere.radius - d) / d);
		}
		else
		{
			// ������0�̏ꍇ�A���ソ���̒��S��AABB�̓����ɂ���
			// �ђʋ������ł��Z���ʂ���Փ˂����Ƃ݂Ȃ�
			int faceIndex = 0;		// �ђʕ������߂�C���f�b�N�X
			float distance = FLT_MAX;	// �ђʋ���
			for (int i = 0; i < 3; ++i)
			{
				float t0 = p[i] - aabb.min[i];
				if (t0 < distance)
				{
					faceIndex = i * 2;
					distance = t0;
				}
				float t1 = aabb.max[i] - p[i];
				if (t1 < distance)
				{
					faceIndex = i * 2 + 1;
					distance = t1;
				}
			}

			// �uAABB�����̂ɑ΂��Ăǂꂾ���ђʂ��Ă��邩�v�������x�N�g�����ق����̂�
			// �ʂ̊O�����̃x�N�g�����g��
			static const Vector3 faceNormals[] = {
				Vector3{-1, 0, 0}, Vector3{ 1, 0, 0},	// -X, +X
				Vector3{ 0,-1, 0}, Vector3{ 0, 1, 0},	// -Y, +Y
				Vector3{ 0, 0,-1}, Vector3{ 0, 0, 1},	// -Z, +Z
			};
			penetration = faceNormals[faceIndex] * distance;
		}
		return true;
	}

	/**
	* AABB��Box�̌�������
	*
	* @param aabb			����Ώۂ�AABB
	* @param sphere			����Ώۂ�Sphere
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& aabb, const Box& box, Vector3& penetration)
	{
		return false;
	}

	/**
	* Sphere���m�̌�������
	*
	* @param a				����Ώۂ�Sphere����1
	* @param b				����Ώۂ�Sphere����2
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration)
	{
		// ���S�̊Ԃ̋�����2����v�Z
		const Vector3 v = b.position - a.position;	// a�̒��S����b�̒��S�Ɍ������x�N�g��
		const float d2 = Vector3::Dot(v, v);	// v�̒�����2��

		// d2�����a�̍��v��蒷���ꍇ�͌������Ă��Ȃ�
		const float r = a.radius + b.radius;	// a��b�̔��a�̍��v
		if (d2 > r * r)
		{ // �������������邽�߁A2�𓯎m�Ŕ�r����
			return false;
		}

		// �������Ă���̂Ŋђʃx�N�g�������߂�
		const float d = Mathf::Sqrt(d2);	// �u�����Q��v���u�����v�ɕϊ�
		const float t = (r - d) / d;	// �u���a�̍��v-�����v�́u�����ɑ΂���䗦�v�����߂�
		penetration = v * t;	// �ђʃx�N�g�����v�Z
		return true;
	}


	/**
	* OBB����_�ւ̍ŋߐړ_
	*
	* @param box		����Ώۂ�OBB
	* @param point		����Ώۂ̓_
	*
	* @return �����`�̂Ȃ��ōł��_�ɋ߂����W
	*/
	Vector3 ClosetPoint(const Box& box, const Vector3& point)
	{
		// OBB����_�Ɍ������x�N�g��
		const Vector3 v = point - box.position;

		Vector3 result = box.position;
		for (int i = 0; i < 3; ++i) 
		{
			// �x�N�g��OBB�̎��ɓ���
			float d = Vector3::Dot(v, box.axis[i]);

			// ���e�œ���ꂽ�l��OBB�͈͓̔��ɐ���
			d = Mathf::Clamp(d, -box.scale[i], box.scale[i]);

			// �ŋߐړ_���X�V
			result += box.axis[i] * d;
		}
		return result;
	}

	/**
	* Sphere��Box�̌�������
	*
	* @param sphere			����Ώۂ�Sphere
	* @param box			����Ώۂ�Box
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& sphere, const Box& box, Vector3& penetration)
	{
		// �ŋߐړ_���狅�̂܂ł̋������A���̂̔��a���傫����ΏՓ˂��Ă��Ȃ�
		const Vector3 p = ClosetPoint(box, sphere.position);
		const Vector3 v = sphere.position - p;
		const float d2 = Vector3::Dot(v, v);
		if (d2 > sphere.radius * sphere.radius) 
		{
			return false;
		}

		if (d2 > 0.00001f)
		{
			// ������0���傫���ꍇ�A���̂̒��S��OBB�̊O���ɂ���
			// ���̏ꍇ�A�ŋߐړ_���狅�̂̒��S�֌�������������Փ˂����Ƃ݂Ȃ�
			const float d = Mathf::Sqrt(d2);
			penetration = (v * ((sphere.radius - d) / d)) * -1;
		}
		else 
		{
			// �������̏ꍇ�A���̂̒��S��OBB�̓����ɂ���
			// ���̏ꍇ�ђʋ������ł��߂��ʂ���Փ˂����Ƃ݂Ȃ�
			const Vector3 a = p - box.position;	// OBB���S���狅�̒��S�ւ̃x�N�g��
			int faceIndex = 0;	// �ђʕ����������C���f�b�N�X
			float distance = FLT_MAX;	// �ђʋ���
			float sign = 1;	// �ђʃx�N�g���̕���
			for (int i = 0; i < 3; ++i) 
			{
				const float f = Vector3::Dot(box.axis[i], a);	// a�����Ƀx�N�g���𓊉e
				const float t0 = f - (-box.scale[i]);
				if (t0 < distance)
				{
					faceIndex = i;
					distance = t0;
					sign = -1;
				}
				const float t1 = box.scale[i] - f;
				if (t1 < distance) 
				{
					faceIndex = i;
					distance = t1;
					sign = 1;
				}
			}
			penetration = (box.axis[faceIndex] * (distance * sign)) * -1;
		}
		return true;
	}

	/**
	* Box���m�̌�������
	*
	* @param a				����Ώۂ�Box����1
	* @param b				����Ώۂ�Box����2
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Box& a, const Box& b, Vector3& penetration)
	{
		return false;
	}
}