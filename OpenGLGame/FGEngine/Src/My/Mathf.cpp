/**
* @file Mathf.cpp
*/
#include "Mathf.h"
#include <cmath>

namespace FGEngine
{

    // �X�^�e�B�b�N�ϐ���������
    const float Mathf::PI = 3.14159265358979f;
    const float Mathf::Deg2Rad = Mathf::PI / 180.0f;
    const float Mathf::Rad2Deg = 57.29578f;

    //=======================================
    //
    //  �֐�
    //
    //=======================================

    /**
    * f�x�̃T�C����Ԃ�
    */
    float Mathf::Sin(float f)
    {
        return sinf(f);
    }
    /**
    * f�x�̃R�T�C����Ԃ�
    */
    float Mathf::Cos(float f)
    {
        return cosf(f);
    }
    /**
    * f�x�̃^���W�F���g��Ԃ�
    */
    float Mathf::Tan(float f)
    {
        return tanf(f);
    }
    /**
    * f�x�̃A�[�N�T�C��(�T�C���̒l��f�ɂȂ�A���W�A���ŕ\���ꂽ�p�x)��Ԃ�
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
    * f�̕�������Ԃ�
    */
    float Mathf::Sqrt(float f)
    {
        return sqrtf(f);
    }
    /**
    * f�̐�Βl��Ԃ�
    */
    float Mathf::Abs(float f)
    {
        return (f < 0) ? -f : f;
    }
    /**
    * value�̐�Βl��Ԃ�
    */
    int Mathf::Abs(int value)
    {
        return (value < 0) ? -value : value;
    }
    /**
    * a��b�̒l�̍ŏ��l��Ԃ�
    */
    float Mathf::Min(float a, float b)
    {
        return (a < b) ? a : b;
    }
    /**
    * value�z��̒��ōŏ��l��Ԃ�
    */
    float Mathf::Min(std::vector<float> value)
    {
        // �z�񂪓�ȏ�Ȃ���ΕԂ�
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
    * a��b�̒l�̍ŏ��l��Ԃ�
    */
    int Mathf::Min(int a, int b)
    {
        return (a < b) ? a : b;
    }
    /**
    * value�z��̒��ōŏ��l��Ԃ�
    */
    int Mathf::Min(std::vector<int> value)
    {
        // �z�񂪓�ȏ�Ȃ���ΕԂ�
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
    * a��b�̒l����ő�l��Ԃ�
    */
    float Mathf::Max(float a, float b)
    {
        return (a > b) ? a : b;
    }
    /**
    * value�z��̒��ōő�l��Ԃ�
    */
    float Mathf::Max(std::vector<float> value)
    {
        // �z�񂪓�ȏ�Ȃ���ΕԂ�
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
    * a��b�̒l����ő�l��Ԃ�
    */
    int Mathf::Max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    /**
    * value�z��̒��ōő�l��Ԃ�
    */
    int Mathf::Max(std::vector<int> value)
    {
        // �z�񂪓�ȏ�Ȃ���ΕԂ�
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
    * f��p�悵�ĕԂ�
    */
    float Mathf::Pow(float f, float p)
    {
        return pow(f, p);
    }
    /**
    * min��max�̊Ԃ�value�𒲐�����
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
    * value��min��max�̊ԂŕԂ�
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
    * value��0�`1�̊ԂŕԂ�
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
    * �����̑ΐ�(�ꂪ10)��Ԃ�
    */
    float Mathf::Log10(float value)
    {
        return std::log10f(value);
    }
}