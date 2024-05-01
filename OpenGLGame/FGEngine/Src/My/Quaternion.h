/**
* @file Quaternion.h
*/
#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "VectorFrd.h"
#include "MatrixFrd.h"

/**
* クォータニオン
*/
struct Quaternion
{
public:		
	
	Quaternion() = default;
	constexpr explicit Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {}
	constexpr Quaternion(const Quaternion& q)
		: x(q.x), y(q.y), z(q.z), w(q.w){}
	~Quaternion() = default;
	
	// axisの周りをangle度回転する回転を返す
	static Quaternion AngleAxis(float angle, const Vector3& axis);
	
	// aとbの内積を返す
	static float Dot(const Quaternion& a, const Quaternion& b);
	
	// オイラー角からクォータニオンに変換
	static Quaternion Euler(float x, float y, float z);
	static Quaternion Euler(const Vector3& v);

	// 指定されたforwardとupwards方向に回転する
	static Quaternion LookRotation(const Vector3& forward, const Vector3& upward);
	static Quaternion LookRotation(const Vector3& foward);

	// qを正規化して返す
	static Quaternion Normalize(const Quaternion& q);
	
	// aとbを球状補間してt[0～1]で返す
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
	
	// aとbを球状保管してtで返す
	static Quaternion SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

public:

	float x, y, z, w;

	static const Quaternion identity;

	// クォータニオンの正規化
	Quaternion normalized() const;

	// オイラー角を取得
	Vector3 eulerAngles() const;

	// クォータニオンの逆数を取得
	Quaternion inverse() const;


	float operator[](size_t i)const {
		return *(&x + i);
	}
	float& operator[](size_t i) {
		return *(&x + i);
	}

	// 回転行列からクォータニオンに変換
	static Quaternion RotationMatrixToQuaternio(const Matrix3x3& rotationMatrix);

	// クォータニオンを行列に変換する
	static Matrix3x3 Matrix3x3Cast(const Quaternion& qua); 
	static Matrix4x4 Matrix4x4Cast(const Quaternion& qua);

private:

	// オイラー角からクォータニオンに変換
	static Quaternion EulerToQuaternion(const Vector3& v);
	
	// クォータニオンからオイラー角に変換
	static Vector3 QuaternionToEuler(const Quaternion& q);
	
	// オイラー角から回転行列に変換
	static Matrix3x3 EulerToRotationMatrix(const Vector3& rotation);
};

// クォータニオン同士の乗算
Quaternion operator*(const Quaternion& a, const Quaternion& b);

// クォータニオンとベクトルの乗算
Vector3 operator*(const Quaternion& q, const Vector3& v);

// 二つのクォータニオンが一致するかどうか
bool operator==(const Quaternion& a, const Quaternion& b);
#endif // !QUATERNION_H_INCLUDED
