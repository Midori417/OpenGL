/**
* @file LightData.h
*/
#ifndef FGENGINE_LIGHTDATA_H_INCLUDED
#define FGENGINE_LIGHTDATA_H_INCLUDED
#include "Vector3.h"

namespace FGEngine::RenderingSystem
{

	/**
	* 光源情報
	*/
	struct LightData
	{
		// 位置
		Vector3 position = Vector3::zero;

		// 明るさ
		float intesity = 1;

		// ライトが届く最大半径
		float radius = 1;

		// 色
		Vector3 color = Vector3::one;


		// === スポットライト用の変数 === //

		// 向き
		Vector3 direction;	

		// スポットライトが照らす角度
		float coneAngle;

		// スポットライトの減衰開始角度
		float fallOffAngle;

		// 使用の有無
		bool used = false;

	};

	/**
	* 平行光源
	*/
	struct DirectionLight
	{
		// 色
		Vector3 color = Vector3{ 1.00f, 0.98f, 0.95f };

		// 明るさ
		float intensity = 5.0f;					

		// 向き
		Vector3 direction = Vector3{ 0.58f, -0.58f, 0.58f };
	};

}

#endif // !FGENGINE_LIGHTDATA_H_INCLUDED
