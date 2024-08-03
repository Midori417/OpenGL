/**
* @file MathFrd.h
* My数学機能の先行宣言が欲しい場合はこのヘッダーをインクルード
*/
#ifndef FGENGINE_MATHFRD_H_INCLUDED
#define FGENGINE_MATHFRD_H_INCLUDED

namespace FGEngine
{
	// 二次元ベクトル
	struct Vector2;

	// 三次元ベクトル
	struct Vector3;

	// 四次元ベクトル
	struct Vector4;

	// 3x3行列
	struct Matrix3x3;

	// 4x4行列
	struct Matrix4x4;

	// クォータニオン
	struct Quaternion;

	// 乱数
	struct Random;
}

#endif // !FGENGINE_MATHFRD_H_INCLUDED
