/**
* @file MatrixPoint.h
*/
#ifndef MATRIXPOINT_H_INCLUDED
#define MATRIXPOINT_H_INCLUDED

#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace FGEngine
{

	// mat4からmat3に変換数コンストラクタ
	inline Matrix3x3::Matrix3x3(const Matrix4x4& m)
	{
		data[0] = Vector3(m.data[0]);
		data[1] = Vector3(m.data[1]);
		data[2] = Vector3(m.data[2]);
	}

	// mat3からmat4に変換するコンストラクタ
	inline Matrix4x4::Matrix4x4(const Matrix3x3& m)
	{
		data[0] = Vector4{ m.data[0], 0 };
		data[1] = Vector4{ m.data[1], 0 };
		data[2] = Vector4{ m.data[2], 0 };
		data[3] = Vector4{ 0, 0, 0, 1 };
	}
}
#endif // !MATRIXPOINT_H_INCLUDED
