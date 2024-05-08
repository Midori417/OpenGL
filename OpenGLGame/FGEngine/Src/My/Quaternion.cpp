/**
* @file Quaternion.cpp
*/
#include "Quaternion.h"
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Mathf.h"

namespace FGEngine
{
	// スタティック変数の初期化
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* 4個のfloatからクォータニオンを構築するコンストラクタ
	*/
	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* クォータニオンを正規化する
	*/
	void Quaternion::Normalize()
	{
		float magnitude = Mathf::Sqrt(Dot(*this, *this));
		if (magnitude > 0.0f)
		{
			*this = Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
		}
	}

	/**
	* 正規化したクォータニオンを取得
	*
	* @return 正規化したクォータニオン
	*/
	Quaternion Quaternion::Normalized() const
	{
		Quaternion result = *this;
		result.Normalize();
		return result;
	}

	/**
	* オイラー角に変換して取得
	*
	* @return 変換したオイラー角
	*/
	Vector3 Quaternion::EulerAngle() const
	{
		return QuaternionToEuler(*this);
	}

	/**
	* クォータニオンの逆数を取得
	*
	* @param クォータニオンの逆数
	*/
	Quaternion Quaternion::Inverse() const
	{
		Quaternion result = identity;
		float theta = Mathf::Sqrt(Dot(*this, *this));
		if (theta > 0.0f) 
		{
			result = Quaternion(
				-x / theta,
				-y / theta,
				-z / theta,
				w / theta
			);
		}
		return result;
	}

	/**
	* axisの周りをangle(度数法)回転するクォータニオンを返す
	*
	* @param angle	回転する角度(度数法)
	* @param axis	回転する軸
	*
	* @return 回転したクォータニオン
	*/
	Quaternion Quaternion::AngleAxis(float angle, const Vector3& axis)
	{
		float halfAngle = Mathf::DegToRad(angle) * 0.5f;
		Vector3 normalAxis = axis.Normalized();
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}

	/**
	* 2つのクォータニオンの内積を計算する
	*
	* @param a	クォータニオン1
	* @param b	クォータニオン2
	*
	* @return aとbの内積
	*/
	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/**
	* 前方ベクトルと上方ベクトルの方向に回転する
	*
	* @param foward	前方ベクトル
	* @param upward 上方べベクトル
	*
	* @return 作成したクォータニオン
	*/
	Quaternion Quaternion::LookRotation(const Vector3& foward, const Vector3& upward)
	{
		Quaternion result = identity;

		Vector3 forwardNormalized = foward.Normalized();
		Vector3 right = Vector3::Cross(upward, forwardNormalized).Normalized();
		Vector3 upAdjusted = Vector3::Cross(forwardNormalized, right).Normalized();
		float trace = right.x + upAdjusted.y + forwardNormalized.z;

		if (trace > 0)
		{
			float s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result = Quaternion(
				(upAdjusted.z - forwardNormalized.y) * s,
				(forwardNormalized.x - right.z) * s,
				(right.y - upAdjusted.x) * s,
				0.25f / s
			);
		}
		else if (right.x > upAdjusted.y && right.x > forwardNormalized.z) 
		{
			float s = 2.0f * Mathf::Sqrt(1.0f + right.x - upAdjusted.y - forwardNormalized.z);
			result = Quaternion(
				0.25f * s,
				(upAdjusted.x + right.y) / s,
				(forwardNormalized.x + right.z) / s,
				(upAdjusted.z - forwardNormalized.y) / s
			);
		}
		else if (upAdjusted.y > forwardNormalized.z)
		{
			float s = 2.0f * Mathf::Sqrt(1.0f + upAdjusted.y - right.x - forwardNormalized.z);
			result = Quaternion(
				(upAdjusted.x + right.y) / s,
				0.25f * s,
				(forwardNormalized.y + upAdjusted.z) / s,
				(forwardNormalized.x - right.z) / s
			);
		}
		else 
		{
			float s = 2.0f * Mathf::Sqrt(1.0f + forwardNormalized.z - right.x - upAdjusted.y);
			result = Quaternion(
				(forwardNormalized.x + right.z) / s,
				(forwardNormalized.y + upAdjusted.z) / s,
				0.25f * s,
				(right.y - upAdjusted.x) / s
			);
		}
		return result.Normalized();
	}

	/**
	* 前方ベクトルと上方ベクトルの方向に回転する
	*
	* @param foward	前方ベクトル
	*
	* @return 作成したクォータニオン
	*/
	Quaternion Quaternion::LookRotation(const Vector3& foward)
	{
		return LookRotation(foward, Vector3::up);
	}

	/**
	* Quaternionとfloatの乗算
	*/
	Quaternion operator*(const Quaternion& q, float f)
	{
		return Quaternion(q.x * f, q.y * f, q.z * f, q.w * f);
	}
	Quaternion operator*(float f, const Quaternion& q)
	{
		return q * f;
	}

	/**
	* Quaternio同士の加算
	*/
	Quaternion operator+(const Quaternion& a, const Quaternion& b)
	{
		return Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}


	/**
	* クォータニオン a と クォータニオン b の間を球状補間する
	*
	* @param a 補間の開始クォータニオン
	* @param b 補間の終了クォータニオン
	* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
	*
	* @return 補間されたクォータニオン
	*/
	Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
	{
		Quaternion result = Quaternion::identity;

		float tmp = Mathf::Clamp01(t);
		auto tmpA = a.Normalized();
		auto tmpB = b.Normalized();

		// クォータニオンの内積
		float dotProduct = Dot(a, b);

		// もし逆向きなら符号を反転
		if (dotProduct < 0.0f)
		{
			tmpB = Quaternion(-tmpB.x, -tmpB.y, -tmpB.z, -tmpB.w);
			dotProduct = -dotProduct;
		}

		// dotproductが1に近い場合は演算誤差が出るので線形保管する
		const float threshold = 0.9995f;
		if (dotProduct > threshold)
		{
			result = Quaternion{
			   tmpA.x + t * (tmpB.x - tmpA.x),
			   tmpA.y + t * (tmpB.y - tmpA.y),
			   tmpA.z + t * (tmpB.z - tmpA.z),
			   tmpA.w + t * (tmpB.w - tmpA.w)
			};
			return result.Normalized();
		}
		// サインとアークコサインを計算
		float theta_0 = Mathf::Acos(dotProduct);
		float theta = theta_0 * t;
		float sinTheta = Mathf::Sin(theta);
		float sinTheta_0 = Mathf::Sin(theta_0);

		// 補間の計算
		float s0 = Mathf::Cos(theta) - dotProduct * sinTheta / sinTheta_0;
		float s1 = sinTheta / sinTheta_0;
		result = s0 * tmpA + s1 * tmpB;

		return result;
	}

	/**
	* オイラー角からクォータニオンに変換
	*
	* @param euler	オイラー角
	*
	* @return 変換したクォータニオン
	*/
	Quaternion Quaternion::EulerToQuaternion(const Vector3& euler)
	{
		return EulerToQuaternion(euler.x, euler.y, euler.z);
	}

	/**
	* オイラー角からクォータニオンに変換
	*
	* @param x	Xの角度(度数法)
	* @param y	Yの角度(度数法)
	* @param z	Zの角度(度数法)
	*
	* @return 変換したクォータニオン
	*/
	Quaternion Quaternion::EulerToQuaternion(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;
		float tx = Mathf::DegToRad(x);
		float ty = Mathf::DegToRad(y);
		float tz = Mathf::DegToRad(z);

		// オイラー角の半分の値を計算
		float cx = Mathf::Cos(tx * 0.5f);
		float sx = Mathf::Sin(tx * 0.5f);

		// Y軸
		float cy = Mathf::Cos(ty * 0.5f);
		float sy = Mathf::Sin(ty * 0.5f);

		// Z軸
		float cz = Mathf::Cos(tz * 0.5f);
		float sz = Mathf::Sin(tz * 0.5f);

		// クォータニオンの各要素を計算
		result.x = sx * cy * cz - cx * sy * sz;
		result.y = cx * sy * cz + sx * cy * sz;
		result.z = cx * cy * sz - sx * sy * cz;
		result.w = cx * cy * cz + sx * sy * sz;

		return result;
	}

	/**
	* クォータニオンからオイラー角に変換
	*
	* @param qua クォータニオン
	*
	* @return 変換したオイラー角
	*/
	Vector3 Quaternion::QuaternionToEuler(const Quaternion& qua)
	{
		Vector3 axis;
		// X軸
		float t0 = 2.0f * (qua.w * qua.x + qua.y * qua.z);
		float t1 = 1.0f - 2.0f * (qua.x * qua.x + qua.y * qua.y);
		axis.x = Mathf::Atan2(t0, t1);
		axis.x = Mathf::RadToDeg(axis.x);

		// Y軸
		float t2 = 2.0f * (qua.w * qua.y - qua.z * qua.x);
		t2 = Mathf::Min(Mathf::Max(t2, -1.0f), 1.0f); 
		axis.y = Mathf::Asin(t2);
		axis.y = Mathf::RadToDeg(axis.y);

		// Z軸
		float t3 = 2.0f * (qua.w * qua.z + qua.x * qua.y);
		float t4 = 1.0f - 2.0f * (qua.y * qua.y + qua.z * qua.z);
		axis.z = Mathf::Atan2(t3, t4);
		axis.z = Mathf::RadToDeg(axis.z);

		return axis;
	}

	/**
	* 回転行列(Matrix3x3)からクォータニオンに変換
	*
	* @param mat 回転行列(Matrix3x3)
	*
	* @return 変換したクォータニオン
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix3x3& rotationMatrix)
	{
		float trace = rotationMatrix[0][0] + rotationMatrix[1][1] + rotationMatrix[2][2];
		float s = 0.0f;
		Quaternion result = Quaternion::identity;
		if (trace > 0.0f) {
			s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result.x = (rotationMatrix[2][1] - rotationMatrix[1][2]) * s;
			result.y = (rotationMatrix[0][2] - rotationMatrix[2][0]) * s;
			result.z = (rotationMatrix[1][0] - rotationMatrix[0][1]) * s;
			result.w = 0.25f / s;
		}
		else if (rotationMatrix[0][0] > rotationMatrix[1][1] && rotationMatrix[1][1] > rotationMatrix[2][2]) {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[0][0] - rotationMatrix[1][1] - rotationMatrix[2][2]);
			result.x = 0.25f * s;
			result.y = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
			result.z = (rotationMatrix[0][2] + rotationMatrix[2][0]) / s;
			result.w = (rotationMatrix[2][1] - rotationMatrix[1][2]) / s;
		}
		else if (rotationMatrix[1][1] > rotationMatrix[2][2]) {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[1][1] - rotationMatrix[0][0] - rotationMatrix[2][2]);
			result.x = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
			result.y = 0.25f * s;
			result.z = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
			result.w = (rotationMatrix[0][2] - rotationMatrix[2][0]) / s;
		}
		else {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[2][2] - rotationMatrix[0][0] - rotationMatrix[1][1]);
			result.x = (rotationMatrix[0][2] + rotationMatrix[2][0]) / s;
			result.y = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
			result.z = 0.25f * s;
			result.w = (rotationMatrix[1][0] - rotationMatrix[0][1]) / s;
		}
		return result.Normalized();
	}

	/**
	* 回転行列(Matrix4x4)からクォータニオンに変換
	*
	* @param rotationMatrix 回転行列(Matrix4x4)
	*
	* @return 変換したクォータニオン
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix4x4& rotationMatrix)
	{
		return RotationMatrixToQuaternion(Matrix3x3(rotationMatrix));
	}

	/**
	* クォータニオンから回転行列(Matrix3x3)に変換
	*
	* @param qua クォータニオン
	*
	* @return 変換した回転行列(Matrix3x3)
	*/
	Matrix3x3 Quaternion::QuaternionToRotationMatrix3x3(const Quaternion& qua)
	{
		Matrix3x3 rotationMatrix;
		rotationMatrix.data[0].x = 1.0f - 2.0f * (qua.y * qua.y + qua.z * qua.z);
		rotationMatrix.data[1].x = 2.0f * (qua.x * qua.y - qua.z * qua.w);
		rotationMatrix.data[2].x = 2.0f * (qua.x * qua.z + qua.y * qua.w);

		rotationMatrix.data[0].y = 2.0f * (qua.x * qua.y + qua.z * qua.w);
		rotationMatrix.data[1].y = 1.0f - 2.0f * (qua.x * qua.x + qua.z * qua.z);
		rotationMatrix.data[2].y = 2.0f * (qua.y * qua.z - qua.x * qua.w);

		rotationMatrix.data[0].z = 2.0f * (qua.x * qua.z - qua.y * qua.w);
		rotationMatrix.data[1].z = 2.0f * (qua.y * qua.z + qua.x * qua.w);
		rotationMatrix.data[2].z = 1.0f - 2.0f * (qua.x * qua.x + qua.y * qua.y);

		return rotationMatrix;
	}

	/**
	* クォータニオンから回転行列(Matrix4x4)に変換
	*
	* @param qua クォータニオン
	*
	* @return 変換した回転行列(Matrix4x4)
	*/
	Matrix4x4 Quaternion::QuaternionToRotationMatrix4x4(const Quaternion& qua)
	{
		return Matrix4x4(QuaternionToRotationMatrix3x3(qua));
	}

	/**
	* クォータニオン同士の乗算
	*/
	Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		Quaternion result(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
		return result;
	}

	/**
	* クォータニオンとベクトル3の乗算
	*/
	Vector3 operator*(const Quaternion& qua, const Vector3& v)
	{
		float num = qua.x * 2.0f;
		float num2 = qua.y * 2.0f;
		float num3 = qua.z * 2.0f;
		float num4 = qua.x * num;
		float num5 = qua.y * num2;
		float num6 = qua.z * num3;
		float num7 = qua.x * num2;
		float num8 = qua.x * num3;
		float num9 = qua.y * num3;
		float num10 = qua.w * num;
		float num11 = qua.w * num2;
		float num12 = qua.w * num3;
		Vector3 result = v;
		result.x = (1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z;
		result.y = (num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z;
		result.z = (num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z;
		return result;
	}

	/**
	* クォータニオンの比較演算
	*/
	bool operator==(const Quaternion& a, const Quaternion& b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
	}

}