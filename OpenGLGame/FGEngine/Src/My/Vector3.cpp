/**
* @file Vector3.cpp
*/
#include "Vector3.h"
#include "Mathf.h"

// ƒXƒ^ƒeƒBƒbƒN•Ï”‚Ì‰Šú‰»
const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);
const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::forward = Vector3(0, 0, -1);
const Vector3 Vector3::back = Vector3(0, 0, 1);



//=======================================
//
//  ŠÖ”
//
//=======================================

/**
* ©g‚ÌƒxƒNƒgƒ‹‚ğ³‹K‰»‚·‚é
*/
void Vector3::Normalize()
{
	float num = magnitude();
	if (num > 0.0f) {
		*this /= num;
	}
	else
	{
		*this = Vector3::zero;
	}
}

/**
* Še—v‘f‚ğv‚ÌŠe—v‘f‚ÆæZ‚·‚é
* 
* @param v æZ‚·‚é—v‘f
*/
void Vector3::Scale(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
}


/**
* a‚Æb‚ÌƒxƒNƒgƒ‹‚Ì“àÏ‚ğ•Ô‚·
* 
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
* 
* @return a‚Æb‚Ì“àÏ
*/
float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
* a‚Æb‚ÌƒxƒNƒgƒ‹‚ÌŠOÏ‚ğ•Ô‚·
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return a‚Æb‚ÌŠOÏ
*/
Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	float num = a.y * b.z - a.z * b.y;
	float num2 = a.z * b.x - a.x * b.z;
	float num3 = a.x * b.y - a.y * b.x;
	return Vector3(num, num2, num3);
}

/**
* a‚Æb‚ÌƒxƒNƒgƒ‹‚Ì’·‚³‚ğ•Ô‚·
* 
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return a‚Æb‚Ì’·‚³
*/
float Vector3::Distance(const Vector3& a, const Vector3& b)
{
	float num = a.x - b.x;
	float num2 = a.y - b.y;
	float num3 = a.z - b.z;
	return Mathf::Sqrt(num * num + num2 * num2 + num3 * num3);
}

/**
* a‚Æb‚ÌŠÔ‚ğt(Clamp0`1)‚ÅüŒ`•âŠÔ‚·‚é
* 
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
* @param t 
*/
Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	t = Mathf::Clamp01(t);
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

/**
* a‚Æb‚ÌŠÔ‚ğt‚ÅüŒ`•âŠÔ‚·‚é
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
* @param t
*/
Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

/**
* Œ»İ‚ÌˆÊ’ucurrent‚©‚çtarget‚ÉŒü‚¯‚ÄˆÚ“®‚·‚é
*
* @param current	Œ»İˆÊ’u
* @param target		ƒ^[ƒQƒbƒgˆÊ’u
*
*/
Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta)
{
	float num = target.x - current.x;
	float num2 = target.y - current.y;
	float num3 = target.z - current.z;
	float num4 = num * num + num2 * num2 + num3 * num3;
	if (num4 == 0.0f || (maxDistanceDelta >= 0.0f && num4 <= maxDistanceDelta * maxDistanceDelta))
	{
		return target;
	}

	float num5 = Mathf::Sqrt(num4);
	return Vector3(
		current.x + num / num5 * maxDistanceDelta,
		current.y + num2 / num5 * maxDistanceDelta,
		current.z + num3 / num5 * maxDistanceDelta);
}

/**
* a‚Æb‚ÌŠe¬•ª‚ğæZ‚µ‚Ä•Ô‚·
* 
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
* 
* @return a‚Æb‚ÌŠe¬•ª‚ğæZ‚µ‚½ƒxƒNƒgƒ‹
*/
Vector3 Vector3::Scale(const Vector3& a, const Vector3& b)
{
	float num = a.x * b.x;
	float num2 = a.y * b.y;
	float num3 = a.z * b.z;
	return Vector3(num, num2, num3);
}

/**
* a‚Æb‚ÌŠe—v‘f‚ÌÅ‘å’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return Še—v‘f‚ÌÅ‘å‚ÌƒxƒNƒgƒ‹
*/
Vector3 Vector3::Max(const Vector3& a, const Vector3& b)
{
	return Vector3(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y), Mathf::Max(a.z, b.z));
}

/**
* a‚Æb‚ÌŠe—v‘f‚ÌÅ¬’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
*
* @param a ŒvZ‘ÎÛ‚»‚Ì1
* @param b ŒvZ‘ÎÛ‚»‚Ì2
*
* @return Še—v‘f‚ÌÅ¬‚ÌƒxƒNƒgƒ‹
*/
Vector3 Vector3::Min(const Vector3& a, const Vector3& b)
{
	return Vector3(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y), Mathf::Min(a.z, b.z));
}

/**
* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ•Ô‚·
*
* @returnƒxƒNƒgƒ‹‚Ì’·‚³
*/
float Vector3::magnitude() const
{
	return Mathf::Sqrt(x * x + y * y + z * z);
}

/**
* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ“ñæ‚µ‚Ä•Ô‚·
*
* @return ƒxƒNƒgƒ‹‚Ì“ñæ‚µ‚½’·‚³
*/
float Vector3::sqrtMagnitude() const
{
	return x * x + y * y + z * z;
}

/**
* ƒxƒNƒgƒ‹‚ğ³‹K‰»‚µ‚Ä•Ô‚·
*
* @return ³‹K‰»‚µ‚½ƒxƒNƒgƒ‹
* @return zero 0œZ‚³‚ê‚½
*/
Vector3 Vector3::normalized() const
{
	Vector3 result = Vector3(x, y, z);
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
Vector3 operator-(const Vector3& a)
{
	return Vector3(-a.x, -a.y, -a.z);
}

//=======================================
//  ‰ÁZ
//=======================================

/**
* Vector3“¯m‚Ì‘ã“ü‰‰Z
*/
Vector3& operator+=(Vector3& a, const Vector3& b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

/**
* Vector3“¯m‚Ì‰‰Z
*/
Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
* Vector3‚Æfloat‚Ì‘ã“ü‰‰Z
*/
Vector3& operator+=(Vector3& a, float b)
{
	return a += Vector3(b, b, b);
}

/**
* Vector3‚Æfloat‚Ì‰‰Z
*/
Vector3 operator+(const Vector3& a, float b)
{
	return a + Vector3(b, b, b);
}

/**
* float‚ÆVector3‚Ì‰‰Z
*/
Vector3 operator+(float a, const Vector3& b)
{
	return b + a;
}

//=======================================
//  ‰ÁZ
//=======================================

/**
* Vector3“¯m‚Ì‘ã“ü‰‰Z
*/
Vector3& operator-=(Vector3& a, const Vector3& b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

/**
* Vector3“¯m‚Ì‰‰Z
*/
Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
* Vector3‚Æfloat‚Ì‘ã“ü‰‰Z
*/
Vector3& operator-=(Vector3& a, float b)
{
	return a -= Vector3(b, b, b);
}

/**
* Vector3‚Æfloat‚Ì‰‰Z
*/
Vector3 operator-(const Vector3& a, float b)
{
	return a - Vector3(b, b, b);
}

/**
* float‚ÆVector3‚Ì‰‰Z
*/
Vector3 operator-(float a, const Vector3& b)
{
	return b - a;
}

//=======================================
//  æZ
//=======================================

/**
* Vector3“¯m‚Ì‘ã“ü‰‰Z
*/
Vector3& operator*=(Vector3& a, const Vector3& b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return a;
}

/**
* Vector3“¯m‚Ì‰‰Z
*/
Vector3 operator*(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

/**
* Vector3‚Æfloat‚Ì‘ã“ü‰‰Z
*/
Vector3& operator*=(Vector3& a, float b)
{
	return a *= Vector3(b, b, b);
}

/**
* Vector3‚Æfloat‚Ì‰‰Z
*/
Vector3 operator*(const Vector3& a, float b)
{
	return a * Vector3(b, b, b);
}

/**
* float‚ÆVector3‚Ì‰‰Z
*/
Vector3 operator*(float a, const Vector3& b)
{
	return b * a;
}

//=======================================
//	œZ
//=======================================

/**
*@Vector3“¯m‚Ì‘ã“ü‰‰Z
*/
Vector3& operator/=(Vector3& a, const Vector3& b)
{
	if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
	}
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return a;
}

/**
* Vector3“¯m‚Ì‰‰Z
*/
Vector3 operator/(const Vector3& a, const Vector3& b)
{
	if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
	}
	return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

/**
* Vector3‚Æfloat‚Ì‘ã“ü‰‰Z
*/
Vector3& operator/=(Vector3& a, float b)
{
	if (a.x == 0 || a.y == 0 || a.z == 0 || b == 0) {
	}
	return a /= Vector3(b, b, b);
}

/**
* Vector3‚Æfloat‚Ì‰‰Z
*/
Vector3 operator/(const Vector3& a, float b)
{
	if (a.x == 0 || a.y == 0 || b == 0) {
	}
	return a / Vector3(b, b, b);
}

Vector3 operator/(float a, const Vector3& b)
{
	if (b.x == 0 || b.y == 0 || b.z == 0 || a == 0) {
	}
	return b / a;
}

//=======================================
//	”äŠr
//=======================================

bool operator==(const Vector3& a, const Vector3& b)
{
	return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

bool operator!=(const Vector3& a, const Vector3& b)
{
	return !(a == b);
}
