/**
* @file Shader.h
*/
#ifndef FGENGINE_SHADER_H_INCLUDED
#define FGENGINE_SHADER_H_INCLUDED
#include "AssetObject.h"
#include "FGEngine/Math/MathFrd.h"

// ��s�錾
typedef unsigned int GLuint;

namespace FGEngine
{
	// ��s�錾
	struct Color;

	/**
	* �V�F�[�_�I�u�W�F�N�g
	*/
	class  Shader : public AssetObject
	{
	public:

		/**
		* �R���X�g���N�^
		*/
		Shader() = default;
		Shader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		/**
		* �f�X�g���N�^
		*/
		virtual ~Shader();

		// �R�s�[�Ƒ�����֎~
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

	public:

		static ShaderPtr Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		void Use();

		void SetBool(const std::string& name, bool value);

		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, float value, float value2);
		void SetFloat3(const std::string& name, float value, float value2, float value3);
		void SetFloat4(const std::string& name, float value, float value2, float value3, float value4);


		void SetVector2(const std::string& name, const Vector2& value);

		void SetVector3(const std::string& name, const Vector3& value);

		void SetVector4(const std::string& name, const Vector4& value);

		void SetMatrix3x3(const std::string& name, const Matrix3x3& value);

		void SetMatrix4x4(const std::string& name, const Matrix4x4& value);

		void SetColor(const std::string& name, const Color& value);

	private:

		// ���_�V�F�[�_�Ǘ��ԍ�
		GLuint vs = 0;

		// �t���O�����g�V�F�[�_�Ǘ��ԍ�
		GLuint fs = 0;

		// �v���O�����I�u�W�F�N�g�Ǘ��ԍ�
		GLuint prog = 0;
	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
