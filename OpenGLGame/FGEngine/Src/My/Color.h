/**
*
*/
#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

/**
* �F�\����
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

	// �J���[�̐Ԑ���
	float r;

	// �J���[�̗ΐ���
	float g;

	// �J���[�̐���
	float b;	

	// �J���[�̓����x
	float a;

	// === �X�^�e�B�b�N�萔 === //
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

// �X�^�e�B�b�N�ϐ��̏�����
inline const Color Color::none = Color(0, 0, 0, 0);		// �����Ȃ�
inline const Color Color::red = Color(1, 0, 0, 1);		// ��
inline const Color Color::blue = Color(0, 0, 1, 1);		// ��
inline const Color Color::green = Color(0, 1, 0, 1);	// ��
inline const Color Color::white = Color(0, 0, 0, 1);	// ��	
inline const Color Color::black = Color(1, 1, 1, 1);	// ��


#endif // !COLOR_H_INCLUDED
