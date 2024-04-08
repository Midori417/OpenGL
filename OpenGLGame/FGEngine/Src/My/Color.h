/**
* @file Color.h
*/
#ifndef FGENGINE_COLOR_H_INCLUDED
#define FGENGINE_COLOR_H_INCLUDED

namespace FGEngine
{
	/**
	* 色構造体
	*/
	struct Color
	{
		Color() = default;
		explicit constexpr Color(float r, float g, float b, float a)
			:r(r), g(g), b(b), a(a) {}
		explicit constexpr Color(float rgba)
			: r(rgba), g(rgba), b(rgba), a(rgba) {}
		~Color() = default;

	public:

		// カラーの赤成分
		float r;

		// カラーの緑成分
		float g;

		// カラーの青成分
		float b;

		// カラーの透明度
		float a;

		// 何もなし
		static const Color none;

		// 赤(1, 0, 0, 1)
		static const Color red;

		// 青(0, 0, 1, 1)
		static const Color blue;

		// 緑(0, 1, 0, 1)
		static const Color green;

		// 白(1, 1, 1, 1)
		static const Color white;

		// 黒(0, 0, 0, 1)
		static const Color black;

		float operator[](size_t i)const {
			return *(&r + i);
		}
		float& operator[](size_t i) {
			return *(&r + i);
		}

	};

	// Color同士の乗算
	inline Color operator*(const Color& a, const Color& b) 
	{
		return Color{ a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a };
	}

	// スタティック変数の初期化
	inline const Color Color::none = Color(0, 0, 0, 0);		// 何もなし
	inline const Color Color::red = Color(1, 0, 0, 1);		// 赤
	inline const Color Color::blue = Color(0, 0, 1, 1);		// 青
	inline const Color Color::green = Color(0, 1, 0, 1);	// 緑
	inline const Color Color::white = Color(1, 1, 1, 1);	// 白	
	inline const Color Color::black = Color(0, 0, 0, 1);	// 黒

}
#endif // !COLOR_H_INCLUDED
