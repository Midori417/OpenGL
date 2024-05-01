/**
* @file Vector4.cpp
*/
#include "Vector4.h"
#include "Mathf.h"

// ƒXƒ^ƒeƒBƒbƒN•Ï”‚Ì‰Šú‰»
const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

//=======================================
//
//  ŠÖ”
//
//=======================================

/**
* ©g‚ÌƒxƒNƒgƒ‹‚ğ³‹K‰»‚·‚é
*/
void Vector4::Normalize()
{
	float num = magnitude();
	if (num > 0.0f) {
		*this /= num;
	}
	else
	{
		*this = Vector4::zero;
	}
}


/**
* a‚Æb‚ÌŠe—v‘f‚ÌÅ‘å’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return Še—v‘f‚ÌÅ‘å‚ÌƒxƒNƒgƒ‹
*/
Vector4 Vector4::Max(const Vector4& a, const Vector4& b)
{
	return Vector4(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y), Mathf::Max(a.z, b.z), Mathf::Max(a.w, b.w));
}

/**
* a‚Æb‚ÌŠe—v‘f‚ÌÅ¬’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return Še—v‘f‚ÌÅ¬‚ÌƒxƒNƒgƒ‹
*/
Vector4 Vector4::Min(const Vector4& a, const Vector4& b)
{
	return Vector4(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y), Mathf::Min(a.z, b.z), Mathf::Min(a.w, b.w));
}

/**
* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ•Ô‚·
*
* @returnƒxƒNƒgƒ‹‚Ì’·‚³
*/
float Vector4::magnitude() const
{
	return Mathf::Sqrt(x * x + y * y + z * z + w * w);
}

/**
* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ“ñæ‚µ‚Ä•Ô‚·
*
* @return ƒxƒNƒgƒ‹‚Ì“ñæ‚µ‚½’·‚³
*/
float Vector4::sqrtMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

/**
* ƒxƒNƒgƒ‹‚ğ³‹K‰»‚µ‚Ä•Ô‚·
*
* @return ³‹K‰»‚µ‚½ƒxƒNƒgƒ‹
* @return zero 0œZ‚³‚ê‚½
*/
Vector4 Vector4::normalized() const
{
	Vector4 result = Vector4(x, y, z, w);
	result.Normalize();
	return result;
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

