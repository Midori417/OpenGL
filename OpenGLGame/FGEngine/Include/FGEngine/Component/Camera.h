/**
* @file Camera.h
*/
#ifndef FGENGINE_CAMERA_H_INCLUDED
#define FGENGINE_CAMERA_H_INCLUDED
#include "Component.h"
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* �J�����R���|�[�l���g
	*/
	class Camera : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Camera() = default;
		virtual ~Camera() = default;

		// ����p�̊Ǘ�
		void SetFovY(float fovY) 
		{
			degFovY = fovY;
			radFovY = degFovY * 3.1415926535f / 180;	// �ʓx�@�ɕϊ�
			fovScale = 1 / static_cast<float>(tan(radFovY / 2));	// ����p�ɂ��g�嗦
		}

		float GetDegFovY() const 
		{
			return degFovY;
		}
		float GetRadgFovY() const
		{
			return radFovY;
		}
		float GetFovScale() const 
		{
			return fovScale;
		}

		static Vector2 WorldPointToScreenPoint(const Vector3& targetPos, const CameraPtr& targetCamera,
			float screenWidth, float screenHeight);

		virtual ComponentPtr Clone() const override;

	public:

		float far = 1000;

		float near = 0.35f;

		// ��ʂ̃A�X�y�N�g��
		float aspect = 16 / 9;

	private:

		// ��������p(�x���@)
		float degFovY = 60;

		// ��������p(�ʓx�@)
		float radFovY = degFovY * 3.1415926535f / 180;

		// ����p�̂ɖ�g�嗦�̋t��
		float fovScale = static_cast<float>(1 / tan(radFovY / 2));
	};
}

#endif // !FGENGINE_CAMERA_H_INCLUDED
