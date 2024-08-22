/**
* @file Shader.h
*/
#ifndef FGENGINE_SHADER_H_INCLUDED
#define FGENGINE_SHADER_H_INCLUDED
#include "AssetObject.h"
#include "FGEngine/UsingNames/UsingMath.h"

// 先行宣言
typedef unsigned int GLuint;

namespace FGEngine
{
	// 先行宣言
	struct Color;

	/**
	* シェーダオブジェクト
	*/
	class  Shader : public AssetObject
	{
	public:

		/**
		* コンストラクタ
		* 
		* @param name			シェーダの名前
		* @param filenameVS		頂点シェーダファイル
		* @param filenameFS		フラグメントシェーダファイル
		*/
		Shader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		/**
		* デストラクタ
		*/
		virtual ~Shader();

	public:	// 禁止事項

		// コピーを禁止
		Shader(const Shader&) = delete;

		// 代入を禁止
		Shader& operator=(const Shader&) = delete;

	public:

		/**
		* シェーダを作成
		* 
		* @param name			シェーダの名前
		* @param filenameVS		頂点シェーダファイル
		* @param filenameFS		フラグメントシェーダファイル
		* 
		* @return 作成したシェーダポインター
		*/
		static ShaderPtr Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

	public:

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

		// 頂点シェーダ管理番号
		GLuint vs = 0;

		// フラグメントシェーダ管理番号
		GLuint fs = 0;

		// プログラムオブジェクト管理番号
		GLuint prog = 0;
	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
