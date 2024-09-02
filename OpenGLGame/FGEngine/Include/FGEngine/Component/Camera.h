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
	* カメラコンポーネント
	*/
	class Camera : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Camera() = default;
		virtual ~Camera() = default;

		// 視野角の管理
		void SetFovY(float fovY) 
		{
			degFovY = fovY;
			radFovY = degFovY * 3.1415926535f / 180;	// 弧度法に変換
			fovScale = 1 / static_cast<float>(tan(radFovY / 2));	// 視野角による拡大率
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

		// 画面のアスペクト比
		float aspect = 16 / 9;

	private:

		// 垂直視野角(度数法)
		float degFovY = 60;

		// 垂直視野角(弧度法)
		float radFovY = degFovY * 3.1415926535f / 180;

		// 視野角のに夜拡大率の逆数
		float fovScale = static_cast<float>(1 / tan(radFovY / 2));
	};
}

#endif // !FGENGINE_CAMERA_H_INCLUDED
