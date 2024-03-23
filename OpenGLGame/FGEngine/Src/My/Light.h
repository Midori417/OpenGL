/**
* @file Light.h
*/
#ifndef LIGHT_H_INCULDED
#define LIGHT_H_INCLUDED

#include "Component.h"
#include "VecMath.h"

namespace FGEngine
{

	/**
	* ライトコンポーネント
	*/
	class Light : public Component
	{
	public:

		Light() = default;
		virtual ~Light();

		// コンポーネントの初期化
		virtual void Awake() override;
		// コンポーネントの更新
		virtual void Update() override;

	public:

		// ライトの種類
		enum class Type {
			pointLight, // 点光源
			spotLight,	// スポットライト光源
		};
		Type type = Type::pointLight; // ライトの種類

		Vector3 color = { 1,1,1 }; // 色
		float intensity = 1;	// 明るさ
		float radius = 1;		// ライトが届く最大半径

		// スポットライト用のパラメータ
		// 方向はGameObject::rotationから計算
		float coneAngle = 30 * Mathf::Deg2Rad;	// スポットライトが照らす角度
		float falloffAngle = 20 * Mathf::Deg2Rad;	// スポットライトの減衰開始角度

	private:

		int lightIndex = -1;		// ライトインデックス

	};
}
#endif // !LIGHT_H_INCULDED
