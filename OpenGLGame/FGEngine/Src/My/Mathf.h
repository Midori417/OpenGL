/**
* @file Mathf.h
*/
#ifndef MATHF_H_INCLUDED
#define MATHF_H_INCLUDED

#include <vector>

/**
* ��ʓI�Ȑ��w�֐��������\����
*/
struct Mathf
{
public:

	Mathf() = default;
	~Mathf() = default;

	// f�x�̃T�C����Ԃ�
	static float Sin(float f);
	// f�x�̃R�T�C����Ԃ�
	static float Cos(float f);
	// f�x�̃^���W�F���g��Ԃ�
	static float Tan(float f);
	// f�x�̃A�[�N�T�C����Ԃ�
	static float Asin(float f);
	// f�x�̃A�[�N�R�T�C���Ԃ�
	static float Acos(float f);
	// f�x�̃A�[�N�^���W�F���g��Ԃ�
	static float Atan(float f);
	// Tan��y/x�ɂȂ�p�x�����W�A����Ԃ�
	static float Atan2(float x, float y);
	// f�̕�������Ԃ�
	static float Sqrt(float f);
	// f�̐�Βl��Ԃ�
	static float Abs(float f);
	// value�̐�Βl��Ԃ�
	static int Abs(int value);
	// a��b�̒l����ŏ���Ԃ�
	static float Min(float a, float b);
	// value�̔z��̒��̒l����ŏ���Ԃ�
	static float Min(std::vector<float> value);
	// a��b�̒l����ŏ���Ԃ�
	static int Min(int a, int b);
	// value�̔z��̒��̒l����ŏ���Ԃ�
	static int Min(std::vector<int> value);
	// a��b�̒l����ő��Ԃ�
	static float Max(float a, float b);
	// value�̔z��̒��̒l����ő��Ԃ�
	static float Max(std::vector<float> value);
	// a��b�̒l����ő��Ԃ�
	static int Max(int a, int b);
	// value�̔z��̒��̒l����ő��Ԃ�
	static int Max(std::vector<int> value);
	// f��p��̒l��Ԃ�
	static float Pow(float f, float p);
	// min��max�̊Ԃ�value�𒲐�����
	static float Clamp(float value, float min, float max);
	// min��max�̊Ԃ�value�𒲐�����
	static int Clamp(int value, int min, int max);
	// 0��1�̊Ԃ�value�𒲐�����
	static float Clamp01(float value);
	static float Floor(float value);
	static float Log10(float value);
	

public:

	const static float PI;			// �~����
	const static float Deg2Rad;		// �x���烉�W�A���ɕϊ�����萔
	const static float Rad2Deg;		// ���W�A������x�ɕϊ�����萔
};
#endif // !MATHF_H_INCLUDED
