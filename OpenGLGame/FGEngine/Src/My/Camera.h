/**
* @file Camera.h
*/
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Component.h"

namespace FGEngine
{

	/**
	* �J����
	*/
	class Camera : public Component
	{
	public:

		Camera() = default;
		virtual ~Camera() = default;

		// ����p�̊Ǘ�
		void SetFovY(float fovY) {
			degFovY = fovY;
			radFovY = degFovY * 3.1415926535f / 180;	// �ʓx�@�ɕϊ�
			fovScale = 1 / static_cast<float>(tan(radFovY / 2));	// ����p�ɂ��g�嗦
		}

		float GetFovY() const {
			return degFovY;
		}
		float GetFovScale() const {
			return fovScale;
		}

	private:

		float degFovY = 60;												// ��������p(�x���@)
		float radFovY = degFovY * 3.1415926535f / 180;					// ��������p(�ʓx�@)
		float fovScale = static_cast<float>(1 / tan(radFovY / 2));		// ����p�̂ɖ�g�嗦�̋t��

		const float near = 0.35f;
		const float far = 1000;
	};
}
#endif // !CAMERA_H_INCLUDED
