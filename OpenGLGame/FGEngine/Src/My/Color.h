/**
* @file Color.h
*/
#ifndef FGENGINE_COLOR_H_INCLUDED
#define FGENGINE_COLOR_H_INCLUDED

namespace FGEngine
{
	/**
	* �F�\����
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

		// �J���[�̐Ԑ���
		float r;

		// �J���[�̗ΐ���
		float g;

		// �J���[�̐���
		float b;

		// �J���[�̓����x
		float a;

		// �����Ȃ�
		static const Color none;

		// ��(1, 0, 0, 1)
		static const Color red;

		// ��(0, 0, 1, 1)
		static const Color blue;

		// ��(0, 1, 0, 1)
		static const Color green;

		// ��(1, 1, 1, 1)
		static const Color white;

		// ��(0, 0, 0, 1)
		static const Color black;

		float operator[](size_t i)const {
			return *(&r + i);
		}
		float& operator[](size_t i) {
			return *(&r + i);
		}

	};

	// Color���m�̏�Z
	inline Color operator*(const Color& a, const Color& b) 
	{
		return Color{ a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a };
	}

	// �X�^�e�B�b�N�ϐ��̏�����
	inline const Color Color::none = Color(0, 0, 0, 0);		// �����Ȃ�
	inline const Color Color::red = Color(1, 0, 0, 1);		// ��
	inline const Color Color::blue = Color(0, 0, 1, 1);		// ��
	inline const Color Color::green = Color(0, 1, 0, 1);	// ��
	inline const Color Color::white = Color(1, 1, 1, 1);	// ��	
	inline const Color Color::black = Color(0, 0, 0, 1);	// ��

}
#endif // !COLOR_H_INCLUDED
