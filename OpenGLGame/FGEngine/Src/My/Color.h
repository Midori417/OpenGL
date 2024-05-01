/**
*
*/
#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

/**
* 色構造体
*/
struct Color
{
	Color() = default;
	explicit constexpr Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a){}
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

	// === スタティック定数 === //
	static const Color none;
	static const Color red;
	static const Color blue;
	static const Color green;
	static const Color white;
	static const Color black;

	float operator[](size_t i)const {
		return *(&r + i);
	}
	float& operator[](size_t i) {
		return *(&r + i);
	}

};

inline Color operator*(const Color& a, const Color& b) {
	return Color{ a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a };
}

// スタティック変数の初期化
inline const Color Color::none = Color(0, 0, 0, 0);		// 何もなし
inline const Color Color::red = Color(1, 0, 0, 1);		// 赤
inline const Color Color::blue = Color(0, 0, 1, 1);		// 青
inline const Color Color::green = Color(0, 1, 0, 1);	// 緑
inline const Color Color::white = Color(0, 0, 0, 1);	// 白	
inline const Color Color::black = Color(1, 1, 1, 1);	// 黒


#endif // !COLOR_H_INCLUDED
