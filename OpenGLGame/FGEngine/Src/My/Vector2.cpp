/**
* @file Vector2.cpp
*/
#include "Vector2.h"
#include "Mathf.h"

namespace FGEngine
{

	// ƒXƒ^ƒeƒBƒbƒN•Ï”‚Ì‰Šú‰»
	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);
	const Vector2 Vector2::up = Vector2(0, 1);
	const Vector2 Vector2::down = Vector2(0, -1);
	const Vector2 Vector2::left = Vector2(-1, 0);
	const Vector2 Vector2::right = Vector2(1, 0);

	//=======================================
	//
	//  ŠÖ”
	//
	//=======================================

	/**
	* ©g‚ÌƒxƒNƒgƒ‹‚ğ³‹K‰»‚·‚é
	*/
	void Vector2::Normalize()
	{
		float num = magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector2::zero;
		}
	}

	/**
	* Še—v‘f‚ğ‚–‚ÌŠe—v‘f‚ÆæZ‚·‚é
	*
	* @param v æZ‚·‚é—v‘f
	*/
	void Vector2::Scale(const Vector2& v)
	{
		x *= v.x;
		y += v.y;
	}

	/**
	* a‚Æb‚ÌƒxƒNƒgƒ‹‚Ì“àÏ‚ğ•Ô‚·
	*
	* @param a ŒvZ‘ÎÛ‚»‚Ì1
	* @param b ŒvZ‘ÎÛ‚»‚Ì2
	*
	* @return “ñ‚Â‚ÌƒxƒNƒgƒ‹‚Ì“àÏ
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	* a‚Æb‚ÌƒxƒNƒgƒ‹‚Ì‹——£‚ğ•Ô‚·
	*
	* @param a ŒvZ‘ÎÛ‚»‚Ì1
	* @param b ŒvZ‘ÎÛ‚»‚Ì2
	*
	* @return “ñ‚Â‚ÌƒxƒNƒgƒ‹‚Ì‹——£
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		float num = a.x - b.x;
		float num2 = a.y - b.y;
		return Mathf::Sqrt(num * num + num2 * num2);
	}

	/**
	* a‚Æb‚ÌŠÔ‚ğt(Clamp0`1)‚ÅüŒ`•âŠÔ‚·‚é
	*/
	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	/**
	* a‚Æb‚ÌŠÔ‚ğt‚ÅüŒ`•âŠÔ‚·‚é
	*/
	Vector2 Vector2::LerpUnclamped(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	/**
	* Œ»İ‚ÌˆÊ’ucurrent‚©‚çtarget‚ÉŒü‚¯‚ÄˆÚ“®‚·‚é
	*
	* @param current	Œ»İˆÊ’u
	* @param target		ƒ^[ƒQƒbƒgˆÊ’u
	*
	*/
	Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
	{
		float num = target.x - current.x;
		float num2 = target.y - current.y;
		float num3 = num * num + num2 * num2;
		if (num3 == 0.0f || (maxDistanceDelta >= 0.0f && num3 <= maxDistanceDelta * maxDistanceDelta))
		{
			return target;
		}

		float num4 = Mathf::Sqrt(num3);
		return Vector2(current.x + num / num4 * maxDistanceDelta, current.y + num2 / num4 * maxDistanceDelta);
	}

	/**
	* a‚Æb‚ÌŠe—v‘f‚ğæZ‚µ‚Ä•Ô‚·
	*
	* @param a ŒvZ‘ÎÛ‚»‚Ì1
	* @param b ŒvZ‘ÎÛ‚»‚Ì2
	*
	* @return a‚Æb‚ğæZ‚µ‚½ƒxƒNƒgƒ‹
	*/
	Vector2 Vector2::Scale(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* a‚Æb‚ÌŠe—v‘f‚ÌÅ‘å’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
	*
	* @param a ŒvZ‘ÎÛ‚»‚Ì1
	* @param b ŒvZ‘ÎÛ‚»‚Ì2
	*
	* @return Še—v‘f‚ÌÅ‘å‚ÌƒxƒNƒgƒ‹
	*/
	Vector2 Vector2::Max(const Vector2& a, const Vector2& b)
	{
		return Vector2(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y));
	}

	/**
	* a‚Æb‚ÌŠe—v‘f‚ÌÅ¬’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
	*
	* @param a ŒvZ‘ÎÛ‚»‚Ì1
	* @param b ŒvZ‘ÎÛ‚»‚Ì2
	*
	* @return Še—v‘f‚ÌÅ¬‚ÌƒxƒNƒgƒ‹
	*/
	Vector2 Vector2::Min(const Vector2& a, const Vector2& b)
	{
		return Vector2(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y));
	}

	/**
	* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ•Ô‚·
	*
	* @returnƒxƒNƒgƒ‹‚Ì’·‚³
	*/
	float Vector2::magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y);
	}

	/**
	* ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ“ñæ‚µ‚Ä•Ô‚·
	*
	* @return ƒxƒNƒgƒ‹‚Ì“ñæ‚µ‚½’·‚³
	*/
	float Vector2::sqrtMagnitude() const
	{

		return x * x + y * y;
	}

	/**
	* ƒxƒNƒgƒ‹‚ğ³‹K‰»‚µ‚Ä•Ô‚·
	*
	* @return ³‹K‰»‚µ‚½ƒxƒNƒgƒ‹
	* @return zero 0œZ‚³‚ê‚½
	*/
	Vector2 Vector2::normalized() const
	{
		Vector2 result = Vector2(x, y);
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
	Vector2 operator-(const Vector2& a)
	{
		return Vector2(-a.x, -a.y);
	}

	//=======================================
	//  ‰ÁZ
	//=======================================

	/**
	* Vector2“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator+=(Vector2& a, const Vector2& b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	/**
	* Vector2“¯m‚Ì‰‰Z
	*/
	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/**
	* Vector2‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator+=(Vector2& a, float b)
	{
		return a += Vector2(b, b);
	}

	/**
	* Vector2‚Æfloat‚Ì‰‰Z
	*/
	Vector2 operator+(const Vector2& a, float b)
	{
		return a + Vector2(b, b);
	}

	/**
	* float‚ÆVector2‚Ì‰‰Z
	*/
	Vector2 operator+(float a, const Vector2& b)
	{
		return b + a;
	}

	//=======================================
	//  ‰ÁZ
	//=======================================

	/**
	* Vector2“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator-=(Vector2& a, const Vector2& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	/**
	* Vector2“¯m‚Ì‰‰Z
	*/
	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/**
	* Vector2‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator-=(Vector2& a, float b)
	{
		return a -= Vector2(b, b);
	}

	/**
	* Vector2‚Æfloat‚Ì‰‰Z
	*/
	Vector2 operator-(const Vector2& a, float b)
	{
		return a - Vector2(b, b);
	}

	/**
	* float‚ÆVector2‚Ì‰‰Z
	*/
	Vector2 operator-(float a, const Vector2& b)
	{
		return b - a;
	}

	//=======================================
	//  æZ
	//=======================================

	/**
	* Vector2“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator*=(Vector2& a, const Vector2& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}

	/**
	* Vector2“¯m‚Ì‰‰Z
	*/
	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* Vector2‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator*=(Vector2& a, float b)
	{
		return a *= Vector2(b, b);
	}

	/**
	* Vector2‚Æfloat‚Ì‰‰Z
	*/
	Vector2 operator*(const Vector2& a, float b)
	{
		return a * Vector2(b, b);
	}

	/**
	* float‚ÆVector2‚Ì‰‰Z
	*/
	Vector2 operator*(float a, const Vector2& b)
	{
		return b * a;
	}

	//=======================================
	//	œZ
	//=======================================

	/**
	*@Vector2“¯m‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator/=(Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}

	/**
	* Vector2“¯m‚Ì‰‰Z
	*/
	Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		return Vector2(a.x / b.x, a.y / b.y);
	}

	/**
	* Vector2‚Æfloat‚Ì‘ã“ü‰‰Z
	*/
	Vector2& operator/=(Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a /= Vector2(b, b);
	}

	Vector2 operator/(const Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a / Vector2(b, b);
	}

	Vector2 operator/(float a, const Vector2& b)
	{
		if (b.x == 0 || b.y == 0 || a == 0) {
		}
		return b / a;
	}

	//=======================================
	//	”äŠr
	//=======================================

	bool operator==(const Vector2& a, const Vector2& b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return ((a.x != b.x) || (a.y != b.y));
	}
}