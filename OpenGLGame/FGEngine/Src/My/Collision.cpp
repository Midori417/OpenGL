/**
* @file Collision.cpp
*/
#include "Collision.h"
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
		Vector3 length = { dx1, dy1, dz1 };		// �ђʋ����̐�Βl
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
				penetration = { signedLength.x, 0, 0 };
				return true;
			}
		}
		// Z�������Y�����̂ق����������ǂ���
		else if (length.y < length.z)
		{
			// y�̒������߂�
			penetration = { 0,signedLength.y, 0 };
			return true;
		}

		// Z�������X�����̂ق������������ǂ���
		penetration = { 0, 0, signedLength.z };
		return true;
	}

	/**
	* ���̂Ƌ��̂̌�������
	*
	* @param a				����Ώۂ̋���A
	* @param b				����Ώۂ̋���B
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false �������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration)
	{
		// ���S�̊Ԃ̋�����2����v�Z
		const Vector3 v = b.position - a.position;	// a�̒��S����b�̒��S�Ɍ������x�N�g��
		const float d2 = Vector3::Dot(v, v);	// v�̒�����2��

		// d2�����a�̍��v��蒷���ꍇ�͌������Ă��Ȃ�
		const float r = a.radius + b.radius;	// a��b�̔��a�̍��v
		if (d2 > r * r) { // �������������邽�߁A2�𓯎m�Ŕ�r����
			return false;
		}

		// �������Ă���̂Ŋђʃx�N�g�������߂�
		const float d = sqrtf(d2);	// �u�����Q��v���u�����v�ɕϊ�
		const float t = (r - d) / d;	// �u���a�̍��v-�����v�́u�����ɑ΂���䗦�v�����߂�
		penetration = v * t;	// �ђʃx�N�g�����v�Z
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
		for (int i = 0; i < 3; ++i) {
			result[i] = std::clamp(point[i], aabb.min[i], aabb.max[i]);
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
		if (d2 > sphere.radius * sphere.radius) {
			return false;
		}

		// �������Ă���̂ŁA�ђʃx�N�g�������߂�
		if (d2 > 0) {
			// ������0���傫���ꍇ�A���̂̒��S��AABB�̊O���ɂ���
			// ���̂̒��S���W����ŋߐړ_�֌�������������Փ˂����Ƃ݂Ȃ�
			const float d = sqrtf(d2);
			penetration = v * ((sphere.radius - d) / d);
		}
		else {
			// ������0�̏ꍇ�A���ソ���̒��S��AABB�̓����ɂ���
			// �ђʋ������ł��Z���ʂ���Փ˂����Ƃ݂Ȃ�
			int faceIndex = 0;		// �ђʕ������߂�C���f�b�N�X
			float distance = FLT_MAX;	// �ђʋ���
			for (int i = 0; i < 3; ++i) {
				float t0 = p[i] - aabb.min[i];
				if (t0 < distance) {
					faceIndex = i * 2;
					distance = t0;
				}
				float t1 = aabb.max[i] - p[i];
				if (t1 < distance) {
					faceIndex = i * 2 + 1;
					distance = t1;
				}
			}

			// �uAABB�����̂ɑ΂��Ăǂꂾ���ђʂ��Ă��邩�v�������x�N�g�����ق����̂�
			// �ʂ̊O�����̃x�N�g�����g��
			static const Vector3 faceNormals[] = {
				{-1, 0, 0}, { 1, 0, 0},	// -X, +X
				{ 0,-1, 0}, { 0, 1, 0}, // -Y, +Y
				{ 0, 0,-1}, { 0, 0, 1}, // -Z, +Z
			};
			penetration = faceNormals[faceIndex] * distance;
		}
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
		for (int i = 0; i < 3; ++i) {
			// �x�N�g��OBB�̎��ɓ���
			float d = Vector3::Dot(v, box.axis[i]);

			// ���e�œ���ꂽ�l��OBB�͈͓̔��ɐ���
			d = std::clamp(d, -box.scale[i], box.scale[i]);

			// �ŋߐړ_���X�V
			result += d * box.axis[i];
		}
		return result;
	}


	/**
	* �L�����E�{�b�N�X�Ƌ��̂��������Ă��邩�ǂ���
	*
	* @param box	����Ώۂ�OBB
	* @param sphere	�����Ώۂ̋���
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Box& box, const Sphere& sphere, Vector3& peneteration)
	{
		// �ŋߐړ_���狅�̂܂ł̋������A���̂̔��a���傫����ΏՓ˂��Ă��Ȃ�
		const Vector3 p = ClosetPoint(box, sphere.position);
		const Vector3 v = sphere.position - p;
		const float d2 = Vector3::Dot(v, v);
		if (d2 > sphere.radius * sphere.radius) {
			return false;
		}

		if (d2 > 0.00001f) {
			// ������0���傫���ꍇ�A���̂̒��S��OBB�̊O���ɂ���
			// ���̏ꍇ�A�ŋߐړ_���狅�̂̒��S�֌�������������Փ˂����Ƃ݂Ȃ�
			const float d = sqrtf(d2);
			peneteration = v * ((sphere.radius - d) / d);
		}
		else {
			// �������̏ꍇ�A���̂̒��S��OBB�̓����ɂ���
			// ���̏ꍇ�ђʋ������ł��߂��ʂ���Փ˂����Ƃ݂Ȃ�
			const Vector3 a = p - box.position;	// OBB���S���狅�̒��S�ւ̃x�N�g��
			int faceIndex = 0;	// �ђʕ����������C���f�b�N�X
			float distance = FLT_MAX;	// �ђʋ���
			float sign = 1;	// �ђʃx�N�g���̕���
			for (int i = 0; i < 3; ++i) {
				const float f = Vector3::Dot(box.axis[i], a);	// a�����Ƀx�N�g���𓊉e
				const float t0 = f - (-box.scale[i]);
				if (t0 < distance) {
					faceIndex = i;
					distance = t0;
					sign = -1;
				}
				const float t1 = box.scale[i] - f;
				if (t1 < distance) {
					faceIndex = i;
					distance = t1;
					sign = 1;
				}
			}
			peneteration = box.axis[faceIndex] * (distance * sign);
		}
		return true;
	}


	/**
	* �X���u(���鎲�ɐ����ȂQ���ʂɈ͂܂ꂽ�͈�)�ƌ��̌�������
	*
	* @param[in] min		�X���u�̊J�n����
	* @param[in] max		�X���u�̏I������
	* @param[in] start		�����̔��˓_
	* @param[in] direction	�����̌���
	* @param[out] tmin		AABB�ƌ���̌����J�n����
	* @param[out] tmax		AABB�ƌ����̌����I������
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool IntersectSlab(float min, float max, float start, float direction, float& tmin, float& tmax)
	{
		// �������X���u�ƕ��s�ȏꍇ
		// ���˓_���X���u���ɂ���Ό������Ă���A�O�ɂ���Ό������Ă��Ȃ�
		// abs��Βl
		if (abs(direction) < 0.0001f) {
			return (start >= min) && (start <= max);
		}

		// �����ƃX���u����������J�n�����ƏI�����������߂�
		float t0 = (min - start) / direction;
		float t1 = (max - start) / direction;

		// �����̑��������J�n�����Ƃ���
		if (t0 > t1) {
			// swap���g��ϊ�
			std::swap(t0, t1);
		}

		// ���ʂ̌����͈͂����߂�
		// �ȑO�̊J�n�����ƍ���̏I���������r���A�x���ق���I��
		if (t0 > tmin) {
			tmin = t0;
		}

		// ���ʂ͈̔͂����߂�
		if (t1 < tmax) {
			tmax = t1;
		}

		//	�u�J�n���� <= �I�������v�̏ꍇ�͌������Ă���
		return tmin <= tmax;
	}

	/**
	* AABB�ƌ����̌�������
	*
	* @param[in] aabb		����Ώۂ�AABB
	* @param[in] ray		����Ώۂ̌���
	* @param[out] distance	������AABB�ƍŏ��Ɍ������鋗��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& aabb, const Ray& ray, float& distance)
	{
		// ���ʂ̌����͈�
		float tmin = 0;
		float tmax = FLT_MAX;

		// X�X���u�Ƃ̌�������
		if (!IntersectSlab(aabb.min.x, aabb.max.x, ray.start.x, ray.direction.x, tmin, tmax)) {
			return false;
		}

		// Y�X���u�Ƃ̌�������
		if (!IntersectSlab(aabb.min.y, aabb.max.y, ray.start.y, ray.direction.y, tmin, tmax)) {
			return false;
		}

		// Z�X���u�Ƃ̌�������
		if (!IntersectSlab(aabb.min.z, aabb.max.z, ray.start.z, ray.direction.z, tmin, tmax)) {
			return false;
		}

		// ��_�܂ł̋�����ݒ�
		distance = tmin;
		return true;
	}

	/**
	* ���̂ƌ����̌�������
	*
	* @param[in] sphere		����Ώۂ̋���
	* @param[in] ray		����Ώۂ̌���
	* @param[out] distance	���������̂ƍŏ��Ɍ������鋗��
	*
	* @retavl true	�������Ă���
	* @retval fals	�������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& sphere, const Ray& ray, float& distance)
	{
		const Vector3 m = ray.start - sphere.position;
		const float b = Vector3::Dot(m, ray.direction);
		const float c = Vector3::Dot(m, m) - sphere.radius * sphere.radius;

		// �����̎n�_�����̂̊O�ɂ���(c > 0)�A���������̂��痣��Ă���������
		// ���˂��ꂽ(b > 0)�ꍇ�A���̂ƌ��͌������Ȃ�
		if (c > 0 && b > 0) {
			return false;
		}

		// ���ʎ������̏ꍇ�͉��Ȃ�
		const float d = b * b - c; // ���ʎ�
		if (d < 0) {
			return false;
		}

		// �ŏ��Ɍ�������ʒu���v�Z
		distance = -b - sqrtf(d);

		// ���̈ʒu�͎��_����O���w���A���������̓����甭�˂��ꂽ���Ƃ��Ӗ�����
		// (�n�_�����̊O�ɂ���󋵂́A���̂��痣��Ă��������̔���ŏ��O�ς�)
		// ���̏ꍇ�A�n�_���u�ŏ��Ɍ�������ʒu�v�Ƃ���
		if (distance < 0) {
			distance = 0;
		}
		return true;

		return false;
	}

	/**
	* �X���u(���鎲�ɐ����ȂQ���ʂɈ͂܂ꂽ�͈�)�ƌ����̌�������
	*
	* @param[in] axis		�X���u�̎��x�N�g��
	* @param[in] scale		�X���u�̕�
	* @param[in] start		�����̔��˓_(�X���u�̒��S�����_�Ƃ���)
	* @param[in] direction	�����̌���
	* @param[out] tmin		AABB�ƌ��̌�������J�n����
	* @param[out] tmax		AABB�ƌ����̌�������I������
	*
	* @retval true	�������Ă���
	* @retval false �������Ă��Ȃ�
	*/
	bool IntersectSlab(const Vector3& axis, float scale, const Vector3& start,
		const Vector3& direction, float& tmin, float& tmax)
	{
		// �����x�N�g���Ɣ��˓_�ɂ��āA���x�N�g�������̐��������߂�
		const float e = Vector3::Dot(axis, direction);
		const float f = Vector3::Dot(axis, start);

		// �������X���u�ƕ��s�ȏꍇ
		// ���˓_���X���u���ɂ���Ό������Ă���A�O�ɂ���Ό������Ă��Ȃ�
		if (abs(e) < 0.0001f) {
			return (f >= -scale) && (f <= scale);
		}

		// �����ƃX���u�������͈͂̊J�n�����ƏI������
		float t0 = (-scale - f) / e;
		float t1 = (scale - f) / e;

		// �����̑��������J�n�����Ƃ���
		if (t0 > t1) {
			const float tmp = t0;
			t0 = t1;
			t1 = tmp;
		}

		// �ȑO�̊J�n�����ƍ���̊J�n�������r���A�x���ق���I��
		if (t0 > tmin) {
			tmin = t0;
		}

		// �ȑO�̏I�������ƍ���̏I���������r���A�����ق���I��
		if (t1 < tmax) {
			tmax = t1;
		}

		// �u�J�n���� <= �I�������v�̏ꍇ�͌������Ă���
		return tmin <= tmax;
	}

	/**
	* OBB�ƌ����̌�������
	*
	* @param[in] box ����Ώۂ�OBB
	* @param[in] ray ����Ώۂ̌���
	* @param[out] distance �ђʃx�N�g��
	*
	* @retval ��������
	* @retval �������Ă��Ȃ�
	*/
	bool Intersect(const Box& box, const Ray& ray, float& distance)
	{
		// �X���u���S�����_�ɂ����ꍇ�̌��̔��˓_���v�Z
		const Vector3 start = ray.start - box.position;

		// �X���u�Ƃ̌�������
		float tmin = 0;
		float tmax = FLT_MAX;
		for (int i = 0; i < 3; ++i) {
			if (!IntersectSlab(box.axis[i], box.scale[i],
				start, ray.direction, tmin, tmax)) {
				return false;
			}
		}

		// ��_�܂ł̋�����ݒ�
		distance = tmin;
		return true;
	}
}