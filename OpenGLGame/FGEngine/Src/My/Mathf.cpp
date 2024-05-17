/**
* @file Mathf.cpp
*/
#include "Mathf.h"
#include <cmath>

namespace FGEngine
{

    // �X�^�e�B�b�N�ϐ���������
    const float Mathf::PI = 3.14159265358979f;

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

    /**
    * f�x�̃A�[�N�R�T�C���Ԃ�
    */
    float Mathf::Acos(float f)
    {
        return acosf(f);
    }

    /**
    *  f�x�̃A�[�N�^���W�F���g��Ԃ�
    */
    float Mathf::Atan(float f)
    {
        return atanf(f);
    }


    /**
    *  Tan��y / x�ɂȂ�p�x�����W�A����Ԃ�
    */
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
    * a��b�̒l�̍ŏ��l��Ԃ�
    */
    int Mathf::Min(int a, int b)
    {
        return (a < b) ? a : b;
    }

    /**
    * a��b�̒l����ő�l��Ԃ�
    */
    float Mathf::Max(float a, float b)
    {
        return (a > b) ? a : b;
    }

    /**
    * a��b�̒l����ő�l��Ԃ�
    */
    int Mathf::Max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    /**
    * (float)value��⊮����(min�`max)����
    *
    * @param (float)�⊮(min�`max)����l
    * @param min (float)��Ԃ̍ŏ��l
    * @parma max (float)��Ԃ̍ő�l
    *
    * @return �⊮(min�`max)�����l
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
    * (int)value��⊮����(min�`max)����
    * 
    * @param (int)�⊮(min�`max)����l
    * @param min (int)��Ԃ̍ŏ��l
    * @parma max (int)��Ԃ̍ő�l
    *
    * @return �⊮(min�`max)�����l
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
    * value��⊮(0�`1)����
    * 
    * @param value �⊮(0�`1)����l
    * 
    * @return �⊮(0�`1)�����l
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
    * �f�O���[(�x���@)���烉�W�A��(�ʓx�@)�ɕϊ�����
    *
    * @param deg �f�O���[(�x���@)
    *
    * @return ���W�A���ɕϊ�����deg
    */
    float Mathf::DegToRad(float deg)
    {
        return deg * PI / 180.0f;
    }

    /**
    * ���W�A��(�ʓx�@)����f�O���[(�x���@)�ɕϊ�����
    *
    * @param rad ���W�A��(�ʓx�@)
    *
    * @return �f�O���[�ɕϊ�����rad
    */
    float Mathf::RadToDeg(float rad)
    {
        return rad * 18.0f / PI;
    }
}