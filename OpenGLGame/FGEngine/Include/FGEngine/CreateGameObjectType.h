/**
* @file CrateGameObjectType.h
*/
#ifndef FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
#define FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
#include <string>

namespace FGEngine
{
	namespace CreateObjectType
	{
		// 何もついてないゲームオブジェクト
		inline const std::string Empty = "Empty";

		// カメラ
		inline const std::string Camera = "Camera";

		// 3Dオブジェクト
		namespace GameObject3D
		{
			// 四角形
			inline const std::string Cube = "Cube";

			// 球体
			inline const std::string Sphere = "Sphere";
		}
		// ユーザーインターフェース
		namespace UI
		{
			// 画像
			inline const std::string Image = "Image";

			// ボタン
			inline const std::string Button = "Button";
		}
	}
}
#endif // !FGENGINE_CREATEGAMEOBJECTTYPE_H_INCLUDED
