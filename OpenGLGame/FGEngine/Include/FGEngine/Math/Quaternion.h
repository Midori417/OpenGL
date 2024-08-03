/**
* @file Quaternion.h
*/
#ifndef FGENGINE_QUATERNION_H_INCLUDED
#define FGENGINE_QUATERNION_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* クォータニオン
	*/
	struct Quaternion
	{
		/**
		* デフォルトコンストラクタ
		*/
		Quaternion() = default;

		/**
		* 4個のfloatからQuaternionを作成するコンストラクタ
		*
		* @param x X成分
		* @param y Y成分
		* @param z Z成分
		* @param w W成分
		*/
		explicit Quaternion(float x, float y, float z, float w);

		/**
		* オイラー角をクォータニオンに変換する
		*
		* @param x	Xの角度(度数法)
		* @param y	Yの角度(度数法)
		* @param z	Zの角度(度数法)
		*/
		static Quaternion Euler(float x, float y, float z);

		/**
		* オイラー角をクォータニオンに変換する
		*
		* @param v オイラー角
		*/
		static Quaternion Euler(const Vector3& v);

		/**
		* クォータニオンからオイラー角に変換する
		*/
		static Vector3 EulerAngle(const Quaternion& q);

		/**
		* 回転行列をクォータニオンに変換
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix3x3& m);

		/**
		* クォータニオンを回転行列に変換
		*/
		static Matrix3x3 QuaternionToRotationMatrix(const Quaternion& q);

		/**
		* クォータニオンの正規化を計算する
		*/
		static Quaternion Normalize(const Quaternion& q);

		/**
		* クォータニオンの逆数を計算
		*/
		static Quaternion Inverse(const Quaternion& q);

		/**
		* axisの周りをangle(度数法)回転するクォータニオンを返す
		*
		* @param axis	回転する軸
		* @param angle	回転する角度(度数法)
		*
		* @return 回転したクォータニオン
		*/
		static Quaternion AngleAxis(const Vector3& axis, float angle);

		/**
		* aとbの角度を調べる
		*
		* @return aとbの角度(度数法)
		*/
		static float Angle(const Quaternion& a, const Quaternion& b);

		/**
		* クォータニオンの内積を計算
		*
		* @return aとbの内積
		*/
		static float Dot(const Quaternion& a, const Quaternion& b);

		/**
		* 前方ベクトルと上方ベクトルの方向に回転する
		*
		* @param foward	前方ベクトル
		* @param upward 上方べベクトル
		*
		* @return 作成したクォータニオン
		*/
		static Quaternion LookRotation(const Vector3& forward, const Vector3& upward);

		/**
		* 前方ベクトルと上方ベクトルの方向に回転する
		*
		* @param foward	前方ベクトル
		*
		* @return 作成したクォータニオン
		*/
		static Quaternion LookRotation(const Vector3& forward);

		/**
		* クォータニオン a と クォータニオン b の間を球状補間する
		*
		* @param a 補間の開始クォータニオン
		* @param b 補間の終了クォータニオン
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたクォータニオン
		*/
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

	public:

		// X成分
		float x;

		// Y成分
		float y;

		// Z成分
		float z;

		// W成分
		float w;

		// デフォルトクォータニオン
		static const Quaternion identity;
	};

	// Quaternion同士の乗算
	Quaternion operator*(const Quaternion& a, const Quaternion& b);

	// QuaternionとVector3の乗算
	Vector3 operator*(const Quaternion& q, const Vector3& v);
}

#endif // !FGENGINE_QUATERNION_H_INCLUDED