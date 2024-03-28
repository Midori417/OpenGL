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

	public:

		// ���C���J����
		static std::weak_ptr<Camera> mainCamera;	

		float far = 0.3f;
		float nera = 1000.0f;
		float aspect = 16 / 9;
	};
}

#endif // !FGENGINE_CAMERA_H_INCLUDED
