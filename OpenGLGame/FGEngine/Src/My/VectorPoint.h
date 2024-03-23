/**
* @file VectorPoint.h
*/
#ifndef VECTORPOINT_H_INCLUDED
#define VECTORPOINT_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace FGEngine
{

	//==========================
	//	vec2コンストラクタ
	//==========================

	// vec3からvec2に作成
	constexpr Vector2::Vector2(const Vector3& v)
		:x(v.x)
		, y(v.y) {}

	// vec4からvec2に作成
	constexpr Vector2::Vector2(const Vector4& v)
		: x(v.x)
		, y(v.y) {}



	//==========================
	//	vec3コンストラクタ
	//==========================

	// vec2 + float からvec3を作成
	constexpr Vector3::Vector3(const Vector2& v, float z)
		: x(v.x)
		, y(v.y)
		, z(z) {}

	// vec4からvec3を作成
	constexpr Vector3::Vector3(const Vector4& v)
		: x(v.x)
		, y(v.y)
		, z(v.z) {}

	//==========================
	//	vec4コンストラクタ
	//==========================

	// vec2からvec4を作成
	constexpr Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x)
		, y(v.y)
		, z(z)
		, w(w) {}

	// vec3からvec4を作成
	constexpr Vector4::Vector4(const Vector3& v, float w)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(w) {}
}
#endif // !VECTORPOINT_H_INCLUDEDX
