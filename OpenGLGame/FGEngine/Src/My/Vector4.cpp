/**
* @file Vector4.cpp
*/
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"

namespace FGEngine
{

	// ƒXƒ^ƒeƒBƒbƒN•Ï”‚Ì‰Šú‰»
	const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

	/**
	* 4ŒÂ‚Ìfloat‚©‚çVector4‚ğ\’z‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* Vector2‚Æ2ŒÂ‚Ìfloat‚©‚çVector4‚ğ\’z‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*/
	Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x), y(v.y), z(z), w(w)
	{
	}

	/**
	* Vector3‚Æ‚PŒÂ‚Ìfloat‚©‚çVector3‚ğ\’z‚·‚éƒRƒ“ƒXƒgƒ‰ƒNƒ^
	*/
	Vector4::Vector4(const Vector3& v, float w)
		: x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	/**
	* ƒxƒNƒgƒ‹‚ğ³‹K‰»‚³‚ê‚½ƒxƒNƒgƒ‹(’PˆÊƒxƒNƒgƒ‹)‚É‚·‚é
	*/
	void Vector4::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector4::zero;
		}
	}

	/**
	* ³‹K‰»‚³‚ê‚½ƒxƒNƒgƒ‹(’PˆÊƒxƒNƒgƒ‹)‚ğæ“¾
	*
	* @return ³‹K‰»‚³‚ê‚½ƒxƒNƒgƒ‹
	*/
	Vector4 Vector4::Normalized() const
	{
		Vector4 result = Vector4(x, y, z, w);
		result.Normalize();
		return result;
	}

	/**
	* ƒxƒNƒgƒ‹‚Ì‘å‚«‚³(’·‚³)‚ğŒvZ‚·‚é
	*
	* @return ƒxƒNƒgƒ‹‚Ì‘å‚«‚³
	*/
	float Vector4::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z + w * w);
	}


	//=======================================
	//
	//  Operator
	//
	//=======================================

	/**
	* -’P€‰‰Zq
	*/
	Vector4 operator-(const Vector4& a)
	{
		return Vector4(-a.x, -a.y, -a.z, -a.w);
	}

	//=======================================
	//  ‰ÁZ
	//=======================================

	/**
	* Vector4“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator+=(Vector4& a, const Vector4& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		a.w += b.w;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‰‰Z
	*/
	Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
	* Vector4‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator+=(Vector4& a, float b)
	{
		return a += Vector4(b, b, b, b);
	}

	/**
	* Vector4‚Æfloat‚Ì‰‰Z
	*/
	Vector4 operator+(const Vector4& a, float b)
	{
		return a + Vector4(b, b, b, b);
	}

	/**
	* float‚ÆVector4‚Ì‰‰Z
	*/
	Vector4 operator+(float a, const Vector4& b)
	{
		return b + a;
	}

	//=======================================
	//  ‰ÁZ
	//=======================================

	/**
	* Vector4“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator-=(Vector4& a, const Vector4& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		a.w -= b.w;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‰‰Z
	*/
	Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
	* Vector4‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator-=(Vector4& a, float b)
	{
		return a -= Vector4(b, b, b, b);
	}

	/**
	* Vector4‚Æfloat‚Ì‰‰Z
	*/
	Vector4 operator-(const Vector4& a, float b)
	{
		return a - Vector4(b, b, b, b);
	}

	/**
	* float‚ÆVector4‚Ì‰‰Z
	*/
	Vector4 operator-(float a, const Vector4& b)
	{
		return b - a;
	}

	//=======================================
	//  æZ
	//=======================================

	/**
	* Vector4“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator*=(Vector4& a, const Vector4& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		a.w *= b.w;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‰‰Z
	*/
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	/**
	* Vector4‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator*=(Vector4& a, float b)
	{
		return a *= Vector4(b, b, b, b);
	}

	/**
	* Vector4‚Æfloat‚Ì‰‰Z
	*/
	Vector4 operator*(const Vector4& a, float b)
	{
		return a * Vector4(b, b, b, b);
	}

	/**
	* float‚ÆVector4‚Ì‰‰Z
	*/
	Vector4 operator*(float a, const Vector4& b)
	{
		return b * a;
	}

	//=======================================
	//	œZ
	//=======================================

	/**
	*@Vector4“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator/=(Vector4& a, const Vector4& b)
	{
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		a.w /= b.w;
		return a;
	}

	/**
	* Vector4“¯m‚Ì‰‰Z
	*/
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	/**
	* Vector4‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector4& operator/=(Vector4& a, float b)
	{
		return a /= Vector4(b, b, b, b);
	}

	/**
	* Vector4‚Æfloat‚Ì‰‰Z
	*/
	Vector4 operator/(const Vector4& a, float b)
	{
		return a / Vector4(b, b, b, b);
	}

	Vector4 operator/(float a, const Vector4& b)
	{
		return b / a;
	}

	//=======================================
	//	”äŠr
	//=======================================

	bool operator==(const Vector4& a, const Vector4& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
	}

	bool operator!=(const Vector4& a, const Vector4& b)
	{
		return !(a == b);
	}

}