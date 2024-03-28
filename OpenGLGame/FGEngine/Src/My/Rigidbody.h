/**
* @file Rigidbody.h
*/
#ifndef FGENGINE_RIGIDBODY_H_INCLUDED
#define FGENGINE_RIGIDBODY_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* 物理挙動を有効にするコンポーネントの
	*/
	class Rigidbody : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Rigidbody() = default;
		virtual ~Rigidbody() = default;

	public:

		// 物体の速度
		Vector3 velocity = Vector3::zero;

		// 重力の有無
		bool isGravity = true;

		// 重力の影響を制御する係数
		float gravityScale = 1;

	private:

		// 重力加速度
		static constexpr float gravity = 9.81f;
	};
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
}

#endif // !FGENGINE_RIGIDBODY_H_INCLUDED
