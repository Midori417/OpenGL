/**
* @file Shader.h
*/
#ifndef FGENGINE_SHADER_H_INCLUDED
#define FGENGINE_SHADER_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// 先行宣言
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;

	/**
	* シェーダオブジェクト
	*/
	class  Shader
	{
	public:

		// コンストラクタ・デストラクタ
		Shader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);
		~Shader();

		// コピーと代入を禁止
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		/*
		* シェーダオブジェクトを作成
		* 
		* @param name シェーダの名前
		* @param filenameVS	バーテックスシェーダのファイル
		* @param filenameFS フラグメントシェーダのファイル
		* 
		* @return 作成したシェーダオブジェクト
		*/
		static ShaderPtr Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		/**
		* プログラムオブジェクト管理番号を取得
		*/
		GLuint GetProgId() const
		{
			return prog;
		}

		/**
		* シェーダの名前を取得
		*/
		std::string ToString() const
		{
			return name;
		}

	public:

		bool isNormal = false;

		bool isShadow = false;

		bool isLight = false;

		bool isUseLight = false;

	private:

		// シェーダの名前
		std::string name;

		// 頂点シェーダ管理番号
		GLuint vs = 0;

		// フラグメントシェーダ管理番号
		GLuint fs = 0;

		// プログラムオブジェクト管理番号
		GLuint prog = 0;

	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
