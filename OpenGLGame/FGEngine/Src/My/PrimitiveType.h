/**
* @file PrimitiveType.h
*/
#ifndef PRIMITIVETYPE_H_INCLUDED
#define PRIMITIVETYPE_H_INCLUDED

namespace FGEngine
{
	/**
	* プリミティブタイプ
	*/
	enum PrimitiveType
	{
		// 球体
		Sphere,

		// capsule
		Capsule,

		// 円柱
		Cylinder,

		// キューブ
		Cube,

		// プレーン
		Plane,
	};
}

#endif // !PRIMITIVETYPE_H_INCLUDED
