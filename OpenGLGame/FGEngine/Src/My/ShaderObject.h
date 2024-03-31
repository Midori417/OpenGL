/**
* @file ShaderObject.h
*/
#ifndef FGENGINE_SHADEROBJECT_H_INCLUDED
#define FGENGINE_SHADEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include "Object.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// 先行宣言
	class ShaderObject;
	using ShaderObjectPtr = std::shared_ptr<ShaderObject>;

	/**
	* シェーダオブジェクト
	*/
	class  ShaderObject : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		ShaderObject(const std::string& name, const char* filenameVS, const char* filenameFS);
		~ShaderObject();

		// コピーと代入を禁止
		ShaderObject(const ShaderObject&) = delete;
		ShaderObject& operator=(const ShaderObject&) = delete;

		/*
		* シェーダオブジェクトを作成
		* 
		* @param name シェーダの名前
		* @param filenameVS	バーテックスシェーダのファイル
		* @param filenameFS フラグメントシェーダのファイル
		* 
		* @return 作成したシェーダオブジェクト
		*/
		std::shared_ptr<ShaderObject> Create(const std::string& name, const char* filenameVS, const char* filenameFS);

		/**
		* プログラムオブジェクト管理番号を取得
		*/
		operator GLuint() const
		{
			return prog;
		}


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
