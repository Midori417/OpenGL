/**
* @file Light.cpp
*/
#include "Light.h"
#include "Engine.h"

namespace FGEngine
{

	/**
	* デストラクタ
	*/
	Light::~Light()
	{
		// ライトを開放する
		GetGameObject()->GetEngine()->DeallocateLight(lightIndex);
	}

	/**
	* コンポーネントの初期化
	*/
	void Light::Awake()
	{
		// ライトを取得していなければ、ライトを取得する
		if (lightIndex < 0)
		{
			lightIndex = GetGameObject()->GetEngine()->AllocateLight();
		}
	}

	/**
	* コンポーネントの更新
	*/
	void Light::Update()
	{
		auto light = GetGameObject()->GetEngine()->GetLight(lightIndex);
		if (light)
		{
			light->position = transform->position;
			light->intensity = intensity;
			light->color = color;
			light->radius = radius;
			light->coneAngle = 0;	// 照射角度が0以下ならポイントライト扱い

			// スポットライトの場合、スポットライトのパラメータを反映
			if (type == Type::spotLight)
			{
				// ライトの向きを計算
				Vector3 direction = { 0,0,-1 }; // 回転アン氏の向きベクトル

				// X軸回転
				const float sinX = sin(transform->eulerAngles().x);
				const float cosX = cos(transform->eulerAngles().x);
				direction = {
					direction.x,
					direction.y * cosX - direction.z * sinX,
					direction.y * sinX + direction.z * cosX
				};

				// Y軸回転
				const float sinY = sin(transform->eulerAngles().y);
				const float cosY = cos(transform->eulerAngles().y);
				direction = {
					direction.x * cosY + direction.z * sinY,
					direction.y,
					direction.x * sinY + direction.z * cosY
				};

				// パラメーターを反映
				light->direction = direction;
				light->coneAngle = coneAngle;
				light->falloffAngle = falloffAngle;
			}
		}
	}
}