/**
* @file Mathf.h
*/
#ifndef FGENGINE_MATHF_H_INCLUDED
#define FGENGINE_MATHF_H_INCLUDED

namespace FGEngine
{

	/**
	* 一般的な数学関数を扱う構造体
	*/
	struct Mathf
	{
	public:

		// コンストラクタ
		Mathf() = default;

		/**
		* f度のサインを返す
		*/
		static float Sin(float f);


		/**
		* f度のコサインを返す
		*/
		static float Cos(float f);


		/**
		* f度のコサインを返す
		*/
		static float Tan(float f);

		/**
		* f度のアークサインを返す
		*/
		static float Asin(float f);

		/**
		* f度のアークコサイン返す
		*/
		static float Acos(float f);

		/**
		*  f度のアークタンジェントを返す
		*/
		static float Atan(float f);

		/**
		*  Tanがy / xになる角度をラジアンを返す
		*/
		static float Atan2(float x, float y);

		/**
		* fの平方根を返す
		*/
		static float Sqrt(float f);

		/**
		* fの絶対値を返す
		*/
		static float Abs(float f);

		/**
		* valueの絶対値を返す
		*/
		static int Abs(int value);

		/**
		* aとbの値から最小を返す
		*/
		static float Min(float a, float b);

		/**
		* aとbの値から最小を返す
		*/
		static int Min(int a, int b);

		/**
		* aとbの値から最大を返す
		*/
		static float Max(float a, float b);

		/**
		* aとbの最大値のほうをしゅ
		*/
		static int Max(int a, int b);

		/**
		* (float)valueを補完する(min～max)する
		*
		* @param (float)補完(min～max)する値
		* @param min (float)補間の最小値
		* @parma max (float)補間の最大値
		*
		* @return 補完(min～max)した値
		*/
		static float Clamp(float value, float min, float max);

		/**
		* (int)valueを補完する(min～max)する
		*
		* @param (int)補完(min～max)する値
		* @param min (int)補間の最小値
		* @parma max (int)補間の最大値
		*
		* @return 補完(min～max)した値
		*/
		static int Clamp(int value, int min, int max);

		/**
		* valueを補完(0～1)する
		*
		* @param value 補完(0～1)する値
		*
		* @return 補完(0～1)した値
		*/
		static float Clamp01(float value);

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

		// 円周率
		const static float PI;
	};

}
#endif // !MATHF_H_INCLUDED
