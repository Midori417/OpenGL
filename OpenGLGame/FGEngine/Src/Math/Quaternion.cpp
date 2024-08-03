/**
* @file Quaternion.cpp
*/
#include "FGEngine/Math/Quaternion.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Mathf.h"
#include <cmath>

namespace FGEngine
{
	// 静的変数の初期化
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* 4個のfloatからQuaternionを作成するコンストラクタ
	*
	* @param x X成分
	* @param y Y成分
	* @param z Z成分
	* @param w W成分
	*/
	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* オイラー角をクォータニオンに変換する
	*
	* @param x	Xの角度(度数法)
	* @param y	Yの角度(度数法)
	* @param z	Zの角度(度数法)
	*/
	Quaternion Quaternion::Euler(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;

		// 弧度法に変換
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
	* オイラー角をクォータニオンに変換する
	*
	* @param v オイラー角
	*/
	Quaternion Quaternion::Euler(const Vector3& v)
	{
		return Euler(v.x, v.y, v.z);
	}

	/**
	* クォータニオンからオイラー角に変換する
	*/
	Vector3 Quaternion::EulerAngle(const Quaternion& q)
	{
		Vector3 axis = Vector3::zero;

		// ロール角 (x 軸周りの回転)
		float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		axis.x = Mathf::Atan2(sinr_cosp, cosr_cosp);
		axis.x = Mathf::RadToDeg(axis.x);

		// ピッチ角 (y 軸周りの回転)
		float sinp = 2 * (q.w * q.y - q.z * q.x);
		if (Mathf::Abs(sinp) >= 1)
		{
			axis.y = std::copysign(Mathf::PI / 2, sinp); // ピッチ角の特異点を処理
			axis.y = Mathf::RadToDeg(axis.y);
		}
		else
		{
			axis.y = Mathf::Asin(sinp);
			axis.y = Mathf::RadToDeg(axis.y);
		}

		// ヨー角 (z 軸周りの回転)
		float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		axis.z = Mathf::Atan2(siny_cosp, cosy_cosp);
		axis.z = Mathf::RadToDeg(axis.z);

		return axis;
	}

	/**
	* 回転行列をクォータニオンに変換
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix3x3& m)
	{
		float trace = m(0, 0) + m(1, 1) + m(2, 2);
		float s = 0.0f;
		Quaternion result = Quaternion::identity;
		if (trace > 0.0f)
		{
			s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result.x = (m(2, 1) - m(1, 2)) * s;
			result.y = (m(0, 2) - m(2, 0)) * s;
			result.z = (m(1, 0) - m(0, 1)) * s;
			result.w = 0.25f / s;
		}
		else if (m(0, 0) > m(1, 1) && m(1, 1) > m(2, 2))
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(0, 0) - m(1, 1) - m(2, 2));
			result.x = 0.25f * s;
			result.y = (m(0, 1) + m(1, 0)) / s;
			result.z = (m(0, 2) + m(2, 0)) / s;
			result.w = (m(2, 1) - m(1, 2)) / s;
		}
		else if (m(1, 1) > m(2, 2))
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(1, 1) - m(0, 0) - m(2, 2));
			result.x = (m(0, 1) + m(1, 0)) / s;
			result.y = 0.25f * s;
			result.z = (m(1, 2) + m(2, 1)) / s;
			result.w = (m(0, 2) - m(2, 0)) / s;
		}
		else
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(2, 2) - m(0, 0) - m(1, 1));
			result.x = (m(0, 2) + m(2, 0)) / s;
			result.y = (m(1, 2) + m(2, 1)) / s;
			result.z = 0.25f * s;
			result.w = (m(1, 0) - m(0, 1)) / s;
		}
		return Normalize(result);
	}

	/**
	* クォータニオンを回転行列に変換
	*/
	Matrix3x3 Quaternion::QuaternionToRotationMatrix(const Quaternion& q)
	{
		Matrix3x3 rotationMatrix;
		rotationMatrix(0, 0) = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		rotationMatrix(1, 0) = 2.0f * (q.x * q.y - q.z * q.w);
		rotationMatrix(2, 0) = 2.0f * (q.x * q.z + q.y * q.w);

		rotationMatrix(0, 1) = 2.0f * (q.x * q.y + q.z * q.w);
		rotationMatrix(1, 1) = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		rotationMatrix(2, 1) = 2.0f * (q.y * q.z - q.x * q.w);

		rotationMatrix(0, 2) = 2.0f * (q.x * q.z - q.y * q.w);
		rotationMatrix(1, 2) = 2.0f * (q.y * q.z + q.x * q.w);
		rotationMatrix(2, 2) = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

		return rotationMatrix;
	}

	/**
	* クォータニオンの正規化を計算する
	*/
	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		float magnitude = Mathf::Sqrt(Dot(q, q));
		if (magnitude > 0.0f)
		{
			return Quaternion(
				q.x / magnitude,
				q.y / magnitude,
				q.z / magnitude,
				q.w / magnitude);
		}
		return Quaternion::identity;
	}

	/**
	* クォータニオンの逆数を計算
	*/
	Quaternion Quaternion::Inverse(const Quaternion& q)
	{
		return Quaternion(-q.x, -q.y, -q.z, q.w);
	}

	/**
	* axisの周りをangle(度数法)回転するクォータニオンを返す
	*
	* @param axis	回転する軸
	* @param angle	回転する角度(度数法)
	*
	* @return 回転したクォータニオン
	*/
	Quaternion Quaternion::AngleAxis(const Vector3& axis, float angle)
	{
		float halfAngle = Mathf::DegToRad(angle) * 0.5f;
		Vector3 normalAxis = Vector3::Normalize(axis);
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}

	/**
	* aとbの角度を調べる
	*
	* @return aとbの角度(度数法)
	*/
	float Quaternion::Angle(const Quaternion& a, const Quaternion& b)
	{
		// 内積の絶対値を取得
		float dot = Mathf::Abs(Quaternion::Dot(a, b));
		return Mathf::RadToDeg(Mathf::Acos(dot) * 2.0f);
	}

	/**
	* クォータニオンの内積を計算
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
	Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upward)
	{
		// 前方ベクトルの正規化
		Vector3 forwardNormalized = Vector3::Normalize(forward);

		// 右方ベクトルを計算
		Vector3 right = Vector3::Normalize(Vector3::Cross(upward, forwardNormalized));

		// 上方ベクトルを再計算
		Vector3 upwardNormalized = Vector3::Normalize(Vector3::Cross(forwardNormalized, right));

		// 回転行列を作成
		Matrix3x3 rot(right, upwardNormalized, forwardNormalized);

		float tmp = (rot(0, 0) + rot(1, 1) + rot(2, 2));
		Quaternion result = identity;
		if (tmp > 0)
		{
			float num = 0.5f / Mathf::Sqrt(tmp + 1.0f);
			result.x = (rot(1, 2) - rot(2, 1)) * num;
			result.y = (rot(2, 0) - rot(0, 2)) * num;
			result.z = (rot(0, 1) - rot(1, 0)) * num;
			result.w = 0.25f / num;
			return result;
		}
		else if ((rot(0, 0) >= rot(1, 1)) && (rot(0, 0) >= rot(2, 2)))
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(0, 0)) - rot(1, 1)) - rot(2, 2));
			result.x = 0.25f * num;
			result.y = (rot(0, 1) + rot(1, 0)) / num;
			result.z = (rot(0, 2) + rot(2, 0)) / num;
			result.w = (rot(1, 2) - rot(2, 1)) / num;
			return result;
		}
		else if (rot(1, 1) > rot(2, 2))
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(1, 1)) - rot(0, 0)) - rot(2, 2));
			result.x = (rot(1, 0) + rot(0, 1)) / num;
			result.y = 0.25f * num;
			result.z = (rot(2, 1) + rot(1, 2)) / num;
			result.w = (rot(2, 0) - rot(0, 2)) / num;
			return result;
		}
		else
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(2, 2)) - rot(0, 0)) - rot(1, 1));
			result.x = (rot(2, 0) + rot(0, 2)) / num;
			result.y = (rot(2, 1) + rot(1, 2)) / num;
			result.z = 0.25f * num;
			result.w = (rot(0, 1) - rot(1, 0)) / num;
			return result;
		}
		return result;
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
		Quaternion tmpA = Normalize(a);
		Quaternion tmpB = Normalize(b);

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
			return Normalize(result);
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
	* Quaternion同士の乗算
	*/
	Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		return Quaternion(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
	}

	/**
	* QuaternionとVector3の乗算
	*/
	Vector3 operator*(const Quaternion& q, const Vector3& v)
	{
		float num = q.x * 2.0f;
		float num2 = q.y * 2.0f;
		float num3 = q.z * 2.0f;
		float num4 = q.x * num;
		float num5 = q.y * num2;
		float num6 = q.z * num3;
		float num7 = q.x * num2;
		float num8 = q.x * num3;
		float num9 = q.y * num3;
		float num10 = q.w * num;
		float num11 = q.w * num2;
		float num12 = q.w * num3;

		return Vector3(
			(1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z,
			(num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z,
			(num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z
		);
	}
}