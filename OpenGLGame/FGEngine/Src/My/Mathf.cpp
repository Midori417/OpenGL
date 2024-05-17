/**
* @file Mathf.cpp
*/
#include "Mathf.h"
#include <cmath>

namespace FGEngine
{

    // スタティック変数を初期化
    const float Mathf::PI = 3.14159265358979f;

    //=======================================
    //
    //  関数
    //
    //=======================================

    /**
    * f度のサインを返す
    */
    float Mathf::Sin(float f)
    {
        return sinf(f);
    }

    /**
    * f度のコサインを返す
    */
    float Mathf::Cos(float f)
    {
        return cosf(f);
    }

    /**
    * f度のタンジェントを返す
    */
    float Mathf::Tan(float f)
    {
        return tanf(f);
    }

    /**
    * f度のアークサイン(サインの値がfになる、ラジアンで表された角度)を返す
    */
    float Mathf::Asin(float f)
    {
        return asinf(f);
    }

    /**
    * f度のアークコサイン返す
    */
    float Mathf::Acos(float f)
    {
        return acosf(f);
    }

    /**
    *  f度のアークタンジェントを返す
    */
    float Mathf::Atan(float f)
    {
        return atanf(f);
    }


    /**
    *  Tanがy / xになる角度をラジアンを返す
    */
    float Mathf::Atan2(float x, float y)
    {
        return atan2f(x, y);
    }

    /**
    * fの平方根を返す
    */
    float Mathf::Sqrt(float f)
    {
        return sqrtf(f);
    }

    /**
    * fの絶対値を返す
    */
    float Mathf::Abs(float f)
    {
        return (f < 0) ? -f : f;
    }

    /**
    * valueの絶対値を返す
    */
    int Mathf::Abs(int value)
    {
        return (value < 0) ? -value : value;
    }

    /**
    * aとbの値の最小値を返す
    */
    float Mathf::Min(float a, float b)
    {
        return (a < b) ? a : b;
    }

    /**
    * aとbの値の最小値を返す
    */
    int Mathf::Min(int a, int b)
    {
        return (a < b) ? a : b;
    }

    /**
    * aとbの値から最大値を返す
    */
    float Mathf::Max(float a, float b)
    {
        return (a > b) ? a : b;
    }

    /**
    * aとbの値から最大値を返す
    */
    int Mathf::Max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    /**
    * (float)valueを補完する(min～max)する
    *
    * @param (float)補完(min～max)する値
    * @param min (float)補間の最小値
    * @parma max (float)補間の最大値
    *
    * @return 補完(min～max)した値
    */
    float Mathf::Clamp(float value, float min, float max)
    {
        if (value < min) {
            value = min;
        }
        else if (value > max) {
            value = max;
        }
        return value;
    }

    /**
    * (int)valueを補完する(min～max)する
    * 
    * @param (int)補完(min～max)する値
    * @param min (int)補間の最小値
    * @parma max (int)補間の最大値
    *
    * @return 補完(min～max)した値
    */
    int Mathf::Clamp(int value, int min, int max)
    {
        if (value < min) {
            value = min;
        }
        else if (value > max) {
            value = max;
        }
        return value;
    }


    /**
    * valueを補完(0～1)する
    * 
    * @param value 補完(0～1)する値
    * 
    * @return 補完(0～1)した値
    */
    float Mathf::Clamp01(float value)
    {
        if (value < 0) {
            value = 0;
        }
        else if (value > 1) {
            value = 1;
        }
        return value;
    }


    /**
    *
    */
    float Mathf::Floor(float value)
    {
        return std::floorf(value);
    }

    /**
    * デグリー(度数法)からラジアン(弧度法)に変換する
    *
    * @param deg デグリー(度数法)
    *
    * @return ラジアンに変換したdeg
    */
    float Mathf::DegToRad(float deg)
    {
        return deg * PI / 180.0f;
    }

    /**
    * ラジアン(弧度法)からデグリー(度数法)に変換する
    *
    * @param rad ラジアン(弧度法)
    *
    * @return デグリーに変換したrad
    */
    float Mathf::RadToDeg(float rad)
    {
        return rad * 18.0f / PI;
    }
}