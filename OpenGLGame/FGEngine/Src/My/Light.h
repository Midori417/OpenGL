/**
* @file Light.h
*/
#ifndef FGENGINE_LIGHT_H_INCLUDED
#define FGENGINE_LIHGT_H_INCLUDED
#include "Component.h"
#include "Color.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* ライトコンポーネント
	*/
	class Light : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Light() = default;
		virtual ~Light();

	public:

		// ライトの種類
		enum class Type
		{
			pointLihgt,		// 点光源
			spotLight,		// スポットライト光源
			directionLight,	// ディレクション光源
		};
		Type type = Type::pointLihgt;	// ライトの種類

		// ライトの色
		Color color = Color::white;

		// ライトの明るさ
		float intensity = 1;

		// ライトが届く最大半径
		float radius = 1;

		// スポットライト用のパラメータ
		float coneAngle = Mathf::DegToRad(30);
	};
	using LightPtr = std::shared_ptr<Light>;
}

#endif // !FGENGINE_LIGHT_H_INCLUDED
