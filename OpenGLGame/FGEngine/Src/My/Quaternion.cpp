/**
* @file Quaternion.cpp
*/
#include "Quaternion.h"
#include "VecMath.h"

namespace FGEngine
{

	// スタティック変数の初期化
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* axisからangleのクォータニオンを返す
	*
	* @param axis 回転させたい任意軸
	* @parma angle 回転させる角度
	*
	* @reutrn axisからangleのクォータニオン
	*/
	Quaternion Quaternion::AngleAxis(float angle, const Vector3& axis)
	{
		float halfAngle = angle * 0.5f;
		Vector3 normalAxis = axis.normalized();
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}
	/**
	* aとbのクォータニオンの内積を返す
	*
	* @param a 計算対象その1
	* @param b 計算対象その2
	*
	* @return aとbの内積
	*/
	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	/**
	* オイラー角からクォータニオンに変換
	*/
	Quaternion Quaternion::Euler(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;
		float tx = x * Mathf::Deg2Rad;
		float ty = y * Mathf::Deg2Rad;
		float tz = z * Mathf::Deg2Rad;
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
		return result.normalized();
	}
	/**
	* オイラー角からクォータニオンに変換して返す
	*
	* @param v オイラー角
	*
	* @return 変換したクォータニオン
	*/
	Quaternion Quaternion::Euler(const Vector3& v)
	{
		return Euler(v.x, v.y, v.z);
	}
	/**
	* 指定されたforwardとupwardの方向に回転する
	*
	* @param foward 前方ベクトル
	* @param upward 上方ベクトル
	*
	* @return fowardとupwardの方向のクォータニオン
	*/
	Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upward)
	{
		Vector3 forwardNormalized = -forward.normalized();
		Vector3 right = Vector3::Cross(upward, forwardNormalized).normalized();
		Vector3 upAdjusted = Vector3::Cross(forwardNormalized, right).normalized();
		float trace = right.x + upAdjusted.y + forwardNormalized.z;
		Quaternion result = identity;
		if (trace > 0) {
			float s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result = Quaternion(
				(upAdjusted.z - forwardNormalized.y) * s,
				(forwardNormalized.x - right.z) * s,
				(right.y - upAdjusted.x) * s,
				0.25f / s
			);
		}
		else if (right.x > upAdjusted.y && right.x > forwardNormalized.z) {
			float s = 2.0f * Mathf::Sqrt(1.0f + right.x - upAdjusted.y - forwardNormalized.z);
			result = Quaternion(
				0.25f * s,
				(upAdjusted.x + right.y) / s,
				(forwardNormalized.x + right.z) / s,
				(upAdjusted.z - forwardNormalized.y) / s
			);
		}
		else if (upAdjusted.y > forwardNormalized.z) {
			float s = 2.0f * Mathf::Sqrt(1.0f + upAdjusted.y - right.x - forwardNormalized.z);
			result = Quaternion(
				(upAdjusted.x + right.y) / s,
				0.25f * s,
				(forwardNormalized.y + upAdjusted.z) / s,
				(forwardNormalized.x - right.z) / s
			);
		}
		else {
			float s = 2.0f * Mathf::Sqrt(1.0f + forwardNormalized.z - right.x - upAdjusted.y);
			result = Quaternion(
				(forwardNormalized.x + right.z) / s,
				(forwardNormalized.y + upAdjusted.z) / s,
				0.25f * s,
				(right.y - upAdjusted.x) / s
			);
		}
		Quaternion tmp = result.normalized();
		return tmp;
	}
	Quaternion Quaternion::LookRotation(const Vector3& foward)
	{
		return LookRotation(foward, Vector3::up);
	}

	/**
	* クォータニオンを正規化して返す
	*
	* @param q 正規化したいクォータニオン
	*
	* @return qの正規化したクォータニオン
	*/
	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		float magnitude = Mathf::Sqrt(Dot(q, q));
		if (magnitude > 0.0f) {
			return Quaternion(q.x / magnitude, q.y / magnitude, q.z / magnitude, q.w / magnitude);
		}
		else {
			return Quaternion::identity;
		}
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
	* aとbを球状補間してt[0～1]で返す
	*
	* @param a 計算対象その１
	* @param b 計算対象その２
	* @param t 補間[0～1]
	*/
	Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
	{
		Quaternion result = Quaternion::identity;

		float tmp = Mathf::Clamp01(t);
		auto tmpA = Normalize(a);
		auto tmpB = Normalize(b);

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
	* aとbを球状補間してtで返す
	*
	* @param a 計算対象その１
	* @param b 計算対象その２
	* @param t 補間
	*/
	Quaternion Quaternion::SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t)
	{
		// クォータニオンの内積
		float dotProduct = Quaternion::Dot(a, b);
		// aからbへの回転角度
		float theta = Mathf::Acos(dotProduct);
		// 補間パラメータに基づくSlerp補間
		float sinTheta = Mathf::Sin(theta);
		float coeff1 = Mathf::Sin((1 - t) * theta) / sinTheta;
		float coeff2 = Mathf::Sin(t * theta) / sinTheta;
		Quaternion result = coeff1 * a + coeff2 * b;
		return result.normalized();
	}

	/**
	* 自身のクォータニオンの正規化を返す
	*/
	Quaternion Quaternion::normalized() const
	{
		return Normalize(*this);
	}

	/**
	* 自身のクォータニオンのオイラー角を返す
	*/
	Vector3 Quaternion::eulerAngles() const
	{
		return QuaternionToEuler(*this);
	}

	/**
	* クォータニオンの逆数を取得
	*/
	Quaternion Quaternion::inverse() const
	{
		Quaternion result = identity;
		float theta = Mathf::Sqrt(Dot(*this, *this));
		if (theta > 0.0f) {
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
	* オイラー角からクォータニオンに変換処理
	*/
	Quaternion Quaternion::EulerToQuaternion(const Vector3& v)
	{
		float cx = cosf(v.x * 0.5f);
		float sx = sinf(v.x * 0.5f);
		float cy = cosf(v.y * 0.5f);
		float sy = sinf(v.y * 0.5f);
		float cz = cosf(v.z * 0.5f);
		float sz = sinf(v.z * 0.5f);
		// 各軸に対するクォータニオンを計算
		Quaternion qx(sx, 0.0, 0.0, cx);
		Quaternion qy(0.0, sy, 0.0, cy);
		Quaternion qz(0.0, 0.0, sz, cz);
		// 各軸のクォータニオンを結合
		return qx * qy * qz;
	}

	/**
	* クォータニオンからオイラー角に変換
	*
	* @param q 変換したいクォータニオン
	*
	* @reutrn クォータニオンから変換したオイラー角
	*/
	Vector3 Quaternion::QuaternionToEuler(const Quaternion& q)
	{
		Vector3 axis;
		// Roll (X-axis)
		float t0 = 2.0f * (q.w * q.x + q.y * q.z);
		float t1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		axis.x = Mathf::Atan2(t0, t1);
		// Pitch (Y-axis)
		float t2 = 2.0f * (q.w * q.y - q.z * q.x);
		t2 = Mathf::Min(Mathf::Max(t2, -1.0f), 1.0f); // クリッピング
		axis.y = Mathf::Asin(t2);
		// Yaw (Z-axis)
		float t3 = 2.0f * (q.w * q.z + q.x * q.y);
		float t4 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		axis.z = Mathf::Atan2(t3, t4);
		return axis;
	}

	/**
	* オイラー角から回転行列に変換して返す
	*
	* @param eulerAngle 変換したいオイラー角
	*
	* @return オイラー角から変換した回転行列
	*/
	Matrix3x3 Quaternion::EulerToRotationMatrix(const Vector3& eulerAngle)
	{
		const float sinX = sinf(eulerAngle.x);
		const float cosX = cosf(eulerAngle.x);
		const float sinY = sinf(eulerAngle.y);
		const float cosY = cosf(eulerAngle.y);
		const float sinZ = sinf(eulerAngle.z);
		const float cosZ = cosf(eulerAngle.z);
		//XYZの回転順
		return{
			Vector3{ (cosY * cosZ),							(cosY * sinZ),							(-sinY)},
			Vector3{ (sinX * sinY * cosZ) + (cosX * -sinZ),	(sinX * sinY * sinZ) + (cosX * cosZ),	(sinX * cosY)},
			Vector3{ (cosX * sinY * cosZ) + (sinX * sinZ),		(cosX * sinY * sinZ) + (-sinX * cosZ),	(cosX * cosY)}
		};
	}
	/**
	* 回転行列からクォータニオンに変換して返す
	*　
	* @param rotationMatrix 変換したい回転行列
	*
	*/
	Quaternion Quaternion::RotationMatrixToQuaternio(const Matrix3x3& rotationMatrix)
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
		return result.normalized();
	}

	/**
	* クォータニオンから3x3行列に変換
	*
	* @param qua 変換するクォータニオン
	*
	* @return 3x3行列に変換したqua
	*/
	Matrix3x3 Quaternion::Matrix3x3Cast(const Quaternion& qua)
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
	* クォータニオンから4x4行列に変換
	*
	* @param qua 変換するクォータニオン
	*
	* @return 4x4行列に変換したqua
	*/
	Matrix4x4 Quaternion::Matrix4x4Cast(const Quaternion& qua)
	{
		return Matrix4x4(Matrix3x3Cast(qua));
	}

	//=======================================
	//
	//  Operator
	//
	//=======================================
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
	* クォータニオンとベクトルの乗算
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
		Vector3 result = v;
		result.x = (1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z;
		result.y = (num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z;
		result.z = (num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z;
		return result;
	}
	/**
	* 二つのクォータニオンが一致するかどうか
	*/
	bool operator==(const Quaternion& a, const Quaternion& b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
	}
}