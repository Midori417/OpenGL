/**
* @file Mathf.h
*/
#ifndef MATHF_H_INCLUDED
#define MATHF_H_INCLUDED

#include <vector>

namespace FGEngine
{

	/**
	* 一般的な数学関数を扱う構造体
	*/
	struct Mathf
	{
	public:

		Mathf() = default;
		~Mathf() = default;

		// f度のサインを返す
		static float Sin(float f);
		// f度のコサインを返す
		static float Cos(float f);
		// f度のタンジェントを返す
		static float Tan(float f);
		// f度のアークサインを返す
		static float Asin(float f);
		// f度のアークコサイン返す
		static float Acos(float f);
		// f度のアークタンジェントを返す
		static float Atan(float f);
		// Tanがy/xになる角度をラジアンを返す
		static float Atan2(float x, float y);
		// fの平方根を返す
		static float Sqrt(float f);
		// fの絶対値を返す
		static float Abs(float f);
		// valueの絶対値を返す
		static int Abs(int value);
		// aとbの値から最小を返す
		static float Min(float a, float b);
		// valueの配列の中の値から最小を返す
		static float Min(std::vector<float> value);
		// aとbの値から最小を返す
		static int Min(int a, int b);
		// valueの配列の中の値から最小を返す
		static int Min(std::vector<int> value);
		// aとbの値から最大を返す
		static float Max(float a, float b);
		// valueの配列の中の値から最大を返す
		static float Max(std::vector<float> value);
		// aとbの値から最大を返す
		static int Max(int a, int b);
		// valueの配列の中の値から最大を返す
		static int Max(std::vector<int> value);
		// fのp状の値を返す
		static float Pow(float f, float p);
		// minとmaxの間でvalueを調整する
		static float Clamp(float value, float min, float max);
		// minとmaxの間でvalueを調整する
		static int Clamp(int value, int min, int max);
		// 0と1の間でvalueを調整する
		static float Clamp01(float value);
		static float Floor(float value);
		static float Log10(float value);

		/**
		* デグリー(度数法)からラジアン(弧度法)に変換する
		* 
		* @param deg デグリー(度数法)
		* 
		* @return ラジアンに変換したdeg
		*/
		static float DegToRad(float deg);

		/**
		* ラジアン(弧度法)からデグリー(度数法)に変換する
		* 
		* @param rad ラジアン(弧度法)
		* 
		* @return デグリーに変換したrad
		*/
		static float RadToDeg(float rad);


	public:

		const static float PI;			// 円周率
	};
}
#endif // !MATHF_H_INCLUDED
