/**
* @file Vector4.cpp
*/
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector3.h"

namespace FGEngine
{
	// Ã“I•Ï”‚Ì‰Šú‰»
	const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

	/**
	* 4ŒÂ‚Ìfloat‚©‚çVector4‚ğì¬‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*
	* @param x X¬•ª
	* @param y Y¬•ª
	* @param z Z¬•ª
	* @param w W¬•ª
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* 1ŒÂ‚Ìfloat‚©‚çVector4‚ğì¬‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*
	* @param v XYZW¬•ª
	*/
	Vector4::Vector4(float v)
		: x(v), y(v), z(v), w(v)
	{
	}

	/**
	* Vector2‚Æ2ŒÂ‚Ìfloat‚©‚çVector4‚ğ\’z‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*
	* @param v Vector2‚ÌXY¬•ª
	* @param z Z¬•ª
	* @param w W¬•ª
	*/
	Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x), y(v.y), z(z), w(w)
	{
	}

	/**
	* Vector3‚Æ1ŒÂ‚Ìfloat‚©‚çVector4‚ğ\’z‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*
	* @param v Vector3‚ÌXYZ¬•ª
	* @param w W¬•ª
	*/
	Vector4::Vector4(const Vector3& v, float w)
		: x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	/**
	* ’P€‰‰Zq
	*/
	Vector4 operator-(const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z, -v.w);
	}

	/**
	* Vector4“¯m‚Ì‰ÁZ
	*/
	Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
	* Vector4“¯m‚ÌŒ¸Z
	*/
	Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
	* Vector4“¯m‚ÌæZ
	*/
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	/**
	* Vector4“¯m‚ÌœZ
	*/
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		// 0œZ‚ğ‚µ‚È‚¢‚æ‚¤‚É
		if (b.x == 0 || b.y == 0 || b.z == 0 || b.w == 0)
		{
			return Vector4::zero;
		}

		return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	/**
	* Vector4“¯m‚Ì‘ã“ü‰ÁZ
	*/
	Vector4 operator+=(Vector4& a, const Vector4& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‘ã“üŒ¸Z
	*/
	Vector4 operator-=(Vector4& a, const Vector4& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‘ã“üæZ
	*/
	Vector4 operator*=(Vector4& a, const Vector4& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‘ã“üœZ
	*/
	Vector4 operator/=(Vector4& a, const Vector4& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector4“¯m‚Ì”äŠr‰‰Z
	*/
	bool operator==(const Vector4& a, const Vector4& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
	}

	/**
	* Vector4“¯m‚Ì”äŠr‰‰Z
	*/
	bool operator!=(const Vector4& a, const Vector4& b)
	{
		return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w));
	}
}