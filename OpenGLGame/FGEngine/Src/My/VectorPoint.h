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
	//	vec2�R���X�g���N�^
	//==========================

	// vec3����vec2�ɍ쐬
	constexpr Vector2::Vector2(const Vector3& v)
		:x(v.x)
		, y(v.y) {}

	// vec4����vec2�ɍ쐬
	constexpr Vector2::Vector2(const Vector4& v)
		: x(v.x)
		, y(v.y) {}



	//==========================
	//	vec3�R���X�g���N�^
	//==========================

	// vec2 + float ����vec3���쐬
	constexpr Vector3::Vector3(const Vector2& v, float z)
		: x(v.x)
		, y(v.y)
		, z(z) {}

	// vec4����vec3���쐬
	constexpr Vector3::Vector3(const Vector4& v)
		: x(v.x)
		, y(v.y)
		, z(v.z) {}

	//==========================
	//	vec4�R���X�g���N�^
	//==========================

	// vec2����vec4���쐬
	constexpr Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x)
		, y(v.y)
		, z(z)
		, w(w) {}

	// vec3����vec4���쐬
	constexpr Vector4::Vector4(const Vector3& v, float w)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(w) {}
}
#endif // !VECTORPOINT_H_INCLUDEDX
