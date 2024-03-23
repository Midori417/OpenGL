/**
* @file Mathf.cpp
*/
#include "Mathf.h"
#include <cmath>

namespace FGEngine
{

    // スタティック変数を初期化
    const float Mathf::PI = 3.14159265358979f;
    const float Mathf::Deg2Rad = Mathf::PI / 180.0f;
    const float Mathf::Rad2Deg = 57.29578f;

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
    float Mathf::Acos(float f)
    {
        return acosf(f);
    }
    float Mathf::Atan(float f)
    {
        return atanf(f);
    }
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
    * value配列の中で最小値を返す
    */
    float Mathf::Min(std::vector<float> value)
    {
        // 配列が二つ以上なければ返す
        if (value.size() < 2) {
            return value[0];
        }
        float tmp = value[0];
        for (int i = 1; i < value.size(); ++i) {
            tmp = (tmp < value[i]) ? tmp : value[i];
        }
        return tmp;
    }
    /**
    * aとbの値の最小値を返す
    */
    int Mathf::Min(int a, int b)
    {
        return (a < b) ? a : b;
    }
    /**
    * value配列の中で最小値を返す
    */
    int Mathf::Min(std::vector<int> value)
    {
        // 配列が二つ以上なければ返す
        if (value.size() < 2) {
            return value[0];
        }
        int tmp = value[0];
        for (int i = 1; i < value.size(); ++i) {
            tmp = (tmp < value[i]) ? tmp : value[i];
        }
        return tmp;
    }
    /**
    * aとbの値から最大値を返す
    */
    float Mathf::Max(float a, float b)
    {
        return (a > b) ? a : b;
    }
    /**
    * value配列の中で最大値を返す
    */
    float Mathf::Max(std::vector<float> value)
    {
        // 配列が二つ以上なければ返す
        if (value.size() < 2) {
            return value[0];
        }
        float tmp = value[0];
        for (int i = 1; i < value.size(); ++i) {
            tmp = (tmp > value[i]) ? tmp : value[i];
        }
        return tmp;
    }
    /**
    * aとbの値から最大値を返す
    */
    int Mathf::Max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    /**
    * value配列の中で最大値を返す
    */
    int Mathf::Max(std::vector<int> value)
    {
        // 配列が二つ以上なければ返す
        if (value.size() < 2) {
            return value[0];
        }
        int tmp = value[0];
        for (int i = 1; i < value.size(); ++i) {
            tmp = (tmp > value[i]) ? tmp : value[i];
        }
        return tmp;
    }
    /**
    * fをp乗して返す
    */
    float Mathf::Pow(float f, float p)
    {
        return pow(f, p);
    }
    /**
    * minとmaxの間でvalueを調整する
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
    * valueをminとmaxの間で返す
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
    * valueを0～1の間で返す
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

    float Mathf::Floor(float value)
    {
        return std::floorf(value);
    }

    /**
    * 引数の対数(底が10)を返す
    */
    float Mathf::Log10(float value)
    {
        return std::log10f(value);
    }
}