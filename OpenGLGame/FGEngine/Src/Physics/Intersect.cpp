/**
* @file Intersect.cpp
*/
#include "FGEngine/Physics/Intersect.h"
#include "FGEngine/Math/Mathf.h"
#include <algorithm>
#include <vector>

namespace FGEngine
{
	/**
	* AABB同士の交差判定
	*
	* @param a				判定対象のAABBその１
	* @param b				判定対象のAABBその2
	* @param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差してない
	*/
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration)
	{
		// === X軸 === //
		// aの左側面がbの右側面より右にあるなら、交差していない
		const float dx0 = b.max.x - a.min.x;
		if (dx0 <= 0)
		{
			return false;
		}
		// aの右側麺がbの左側面より左にあるのなら、交差していない
		const float dx1 = a.max.x - b.min.x;
		if (dx1 <= 0)
		{
			return false;
		}
		// === Y軸 === //
		// aの下側面がbの上側面より上にあるのなら、交差していない
		const float dy0 = b.max.y - a.min.y;
		if (dy0 <= 0)
		{
			return false;
		}
		// aの上側面がbの下側面より下にあるのなら、交差していない
		const float dy1 = a.max.y - b.min.y;
		if (dy1 <= 0)
		{
			return false;
		}
		// === Z軸 === //
		// aの奥側面がbの手前側面より手前にあるのなら、交差していない
		const float dz0 = b.max.z - a.min.z;
		if (dz0 <= 0)
		{
			return false;
		}
		// aの手前面がbの奥側面より奥にあるのなら、交差していない
		const float dz1 = a.max.z - b.min.z;
		if (dz1 <= 0)
		{
			return false;
		}

		// この時点で交差が確定

		// XYZの各軸について、重なっている距離が短い方向を選択
		Vector3 length = Vector3{ dx1, dy1, dz1 };		// 貫通距離の絶対値
		Vector3 signedLength = length;			// 符号付きの貫通距離
		// 比較対象を３つに減らす
		// dx0のほうがちいさいかどうか
		if (dx0 < dx1)
		{
			length.x = dx0;
			signedLength.x = -dx0;
		}
		// dy0のほうがちいさいかどうか
		if (dy0 < dy1)
		{
			length.y = dy0;
			signedLength.y = -dy0;
		}
		// dz0のほうがちいさいかどうか
		if (dz0 < dz1)
		{
			length.z = dz0;
			signedLength.z = -dz0;
		}

		// XYZのうち最も短い方向を選択
		// Y方向よりX方向のほうがちいさいかどうか
		if (length.x < length.y)
		{
			// Z方向よりX方向のほうがちいかどうか
			if (length.x < length.z)
			{
				// xの長さ分戻す
				penetration = Vector3{ signedLength.x, 0, 0 };
				return true;
			}
		}
		// Z方向よりY方向のほうがちいかどうか
		else if (length.y < length.z)
		{
			// yの長さ分戻す
			penetration = Vector3{ 0,signedLength.y, 0 };
			return true;
		}

		// Z方向よりX方向のほうが小さいかどうか
		penetration = Vector3{ 0, 0, signedLength.z };
		return true;
	}

	/**
	* AABBから点への最近接点
	*
	* @param aabb	判定対象のAABB
	* @param point	判定対象の点
	*
	* @return	AABBの中でも最も点に近い座標
	*/
	Vector3 ClosetPoint(const AABB& aabb, const Vector3& point)
	{
		Vector3 result;
		for (int i = 0; i < 3; ++i)
		{
			result[i] = Mathf::Clamp(point[i], aabb.min[i], aabb.max[i]);
		}
		return result;
	}

	/**
	* AABBと球体の交差判定
	*
	* @param aabb			判定対象のAABB
	* @param sphere			判定対象の球体
	* @param penetration	貫通ベクトル
	*
	* @retval true 交差している
	* @retval false	交差していない
	*/
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration)
	{
		// 最近接点までの距離が球体の半径より長ければ交差していない
		const Vector3 p = ClosetPoint(aabb, sphere.position);
		const Vector3 v = sphere.position - p;
		const float d2 = Vector3::Dot(v, v);
		if (d2 > sphere.radius * sphere.radius)
		{
			return false;
		}

		// 交差しているので、貫通ベクトルを求める
		if (d2 > 0)
		{
			// 距離が0より大きい場合、球体の中心はAABBの外側にある
			// 球体の中心座標から最近接点へ向かう方向から衝突したとみなす
			const float d = Mathf::Sqrt(d2);
			penetration = v * ((sphere.radius - d) / d);
		}
		else
		{
			// 距離が0の場合、きゅたいの中心はAABBの内部にある
			// 貫通距離が最も短い面から衝突したとみなす
			int faceIndex = 0;		// 貫通方向を占めるインデックス
			float distance = FLT_MAX;	// 貫通距離
			for (int i = 0; i < 3; ++i)
			{
				float t0 = p[i] - aabb.min[i];
				if (t0 < distance)
				{
					faceIndex = i * 2;
					distance = t0;
				}
				float t1 = aabb.max[i] - p[i];
				if (t1 < distance)
				{
					faceIndex = i * 2 + 1;
					distance = t1;
				}
			}

			// 「AABBが球体に対してどれだけ貫通しているか」を示すベクトルがほしいので
			// 面の外向きのベクトルを使う
			static const Vector3 faceNormals[] = {
				Vector3{-1, 0, 0}, Vector3{ 1, 0, 0},	// -X, +X
				Vector3{ 0,-1, 0}, Vector3{ 0, 1, 0},	// -Y, +Y
				Vector3{ 0, 0,-1}, Vector3{ 0, 0, 1},	// -Z, +Z
			};
			penetration = faceNormals[faceIndex] * distance;
		}
		return true;
	}

	/**
	* AABBとBoxの交差判定
	*
	* @param aabb			判定対象のAABB
	* @param sphere			判定対象のSphere
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const AABB& aabb, const Box& box, Vector3& penetration)
	{
		return false;
	}

	/**
	* Sphere同士の交差判定
	*
	* @param a				判定対象のSphereその1
	* @param b				判定対象のSphereその2
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration)
	{
		// 中心の間の距離の2乗を計算
		const Vector3 v = b.position - a.position;	// aの中心からbの中心に向かうベクトル
		const float d2 = Vector3::Dot(v, v);	// vの長さの2乗

		// d2が半径の合計より長い場合は交差していない
		const float r = a.radius + b.radius;	// aとbの半径の合計
		if (d2 > r * r)
		{ // 平方根をさけるため、2条同士で比較する
			return false;
		}

		// 交差しているので貫通ベクトルを求める
		const float d = Mathf::Sqrt(d2);	// 「長さ２乗」を「長さ」に変換
		const float t = (r - d) / d;	// 「半径の合計-長さ」の「長さに対する比率」を求める
		penetration = v * t;	// 貫通ベクトルを計算
		return true;
	}


	/**
	* OBBから点への最近接点
	*
	* @param box		判定対象のOBB
	* @param point		判定対象の点
	*
	* @return 長方形のなかで最も点に近い座標
	*/
	Vector3 ClosetPoint(const Box& box, const Vector3& point)
	{
		// OBBから点に向かうベクトル
		const Vector3 v = point - box.position;

		Vector3 result = box.position;
		for (int i = 0; i < 3; ++i) 
		{
			// ベクトルOBBの軸に投射
			float d = Vector3::Dot(v, box.axis[i]);

			// 投影で得られた値をOBBの範囲内に制限
			d = Mathf::Clamp(d, -box.scale[i], box.scale[i]);

			// 最近接点を更新
			result += box.axis[i] * d;
		}
		return result;
	}

	/**
	* SphereとBoxの交差判定
	*
	* @param sphere			判定対象のSphere
	* @param box			判定対象のBox
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Sphere& sphere, const Box& box, Vector3& penetration)
	{
		// 最近接点から球体までの距離が、球体の半径より大きければ衝突していない
		const Vector3 p = ClosetPoint(box, sphere.position);
		const Vector3 v = sphere.position - p;
		const float d2 = Vector3::Dot(v, v);
		if (d2 > sphere.radius * sphere.radius) 
		{
			return false;
		}

		if (d2 > 0.00001f)
		{
			// 距離が0より大きい場合、球体の中心はOBBの外側にある
			// この場合、最近接点から球体の中心へ向かう方向から衝突したとみなす
			const float d = Mathf::Sqrt(d2);
			penetration = (v * ((sphere.radius - d) / d)) * -1;
		}
		else 
		{
			// 距離がの場合、球体の中心はOBBの内部にある
			// この場合貫通距離が最も近い面から衝突したとみなす
			const Vector3 a = p - box.position;	// OBB中心から球体中心へのベクトル
			int faceIndex = 0;	// 貫通方向を示すインデックス
			float distance = FLT_MAX;	// 貫通距離
			float sign = 1;	// 貫通ベクトルの符号
			for (int i = 0; i < 3; ++i) 
			{
				const float f = Vector3::Dot(box.axis[i], a);	// aを軸にベクトルを投影
				const float t0 = f - (-box.scale[i]);
				if (t0 < distance)
				{
					faceIndex = i;
					distance = t0;
					sign = -1;
				}
				const float t1 = box.scale[i] - f;
				if (t1 < distance) 
				{
					faceIndex = i;
					distance = t1;
					sign = 1;
				}
			}
			penetration = (box.axis[faceIndex] * (distance * sign)) * -1;
		}
		return true;
	}

	/**
	* Box同士の交差判定
	*
	* @param a				判定対象のBoxその1
	* @param b				判定対象のBoxその2
	* @param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Box& a, const Box& b, Vector3& penetration)
	{
		return false;
	}
}