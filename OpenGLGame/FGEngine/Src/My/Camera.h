/**
* @file Camera.h
*/
#ifndef FGENGINE_CAMERA_H_INCLUDED
#define FGENGINE_CAMERA_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	// 先行宣言
	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;

	/**
	* カメラコンポーネント
	*/
	class Camera : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Camera() = default;
		virtual ~Camera() = default;

		static CameraPtr GetMainCamera();

	public:

		// メインカメラ
		static std::weak_ptr<Camera> mainCamera;	

		float far = 0.3f;
		float nera = 1000.0f;
		float aspect = 16 / 9;
	};
}

#endif // !FGENGINE_CAMERA_H_INCLUDED
