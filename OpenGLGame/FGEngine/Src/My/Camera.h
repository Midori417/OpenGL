/**
* @file Camera.h
*/
#ifndef FGENGINE_CAMERA_H_INCLUDED
#define FGENGINE_CAMERA_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	// ��s�錾
	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;

	/**
	* �J�����R���|�[�l���g
	*/
	class Camera : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Camera() = default;
		virtual ~Camera() = default;

		static CameraPtr GetMainCamera();

		// ����p�̊Ǘ�
		void SetFovY(float fovY) 
		{
			degFovY = fovY;
			radFovY = degFovY * 3.1415926535f / 180;	// �ʓx�@�ɕϊ�
			fovScale = 1 / static_cast<float>(tan(radFovY / 2));	// ����p�ɂ��g�嗦
		}

		float GetFovY() const 
		{
			return degFovY;
		}
		float GetFovScale() const 
		{
			return fovScale;
		}


	public:

		// ���C���J����
		static std::weak_ptr<Camera> mainCamera;	


		float far = 0.3f;

		float nera = 1000.0f;

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
