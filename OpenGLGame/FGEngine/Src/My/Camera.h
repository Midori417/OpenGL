/**
* @file Camera.h
*/
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Component.h"

namespace FGEngine
{

	/**
	* ƒJƒƒ‰
	*/
	class Camera : public Component
	{
	public:

		Camera() = default;
		virtual ~Camera() = default;

		// ‹–ìŠp‚ÌŠÇ—
		void SetFovY(float fovY) {
			degFovY = fovY;
			radFovY = degFovY * 3.1415926535f / 180;	// ŒÊ“x–@‚É•ÏŠ·
			fovScale = 1 / static_cast<float>(tan(radFovY / 2));	// ‹–ìŠp‚É‚æ‚éŠg‘å—¦
		}

		float GetFovY() const {
			return degFovY;
		}
		float GetFovScale() const {
			return fovScale;
		}

	private:

		float degFovY = 60;												// ‚’¼‹–ìŠp(“x”–@)
		float radFovY = degFovY * 3.1415926535f / 180;					// ‚’¼‹–ìŠp(ŒÊ“x–@)
		float fovScale = static_cast<float>(1 / tan(radFovY / 2));		// ‹–ìŠp‚Ì‚É–éŠg‘å—¦‚Ì‹t”

		const float near = 0.35f;
		const float far = 1000;
	};
}
#endif // !CAMERA_H_INCLUDED
