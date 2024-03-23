/**
* @file ProgramObject.h
*/
#ifndef PROGRAMOBJECT_H_INCLUDED
#define PROGRAMOBJECT_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>

namespace FGEngine
{
	// 先行宣言
	class ProgramObject;
	using ProgramObjectPtr = std::shared_ptr<ProgramObject>;

	/**
	* プログラム・オブジェクトを管理するクラス
	*/
	class  ProgramObject
	{
	public:

		// コンストラクタ・デストラクタ
		ProgramObject(const std::string& name, const char* filenameVS, const char* filenameFS);
		~ProgramObject();

		// コピーと代入を禁止
		ProgramObject(const ProgramObject&) = delete;
		ProgramObject& operator=(const ProgramObject&) = delete;

		/*
		* プログラムオブジェクトを作成
		*/
		std::shared_ptr<ProgramObject> Create(const std::string& name, const char* filenameVS, const char* filenameFS);

		// 管理番号を取得
		operator GLuint() const
		{
			return prog;
		}


	private:

		std::string name = "Shader";	// シェーダーの名前
		GLuint vs = 0;			// 頂点シェーダー
		GLuint fs = 0;			// フラグメントシェーダー
		GLuint prog = 0;		// プログラムオブジェクト
		std::string filenameVS;	// 頂点シェーダーファイル名
		std::string filenameFS;	// フラグメントシェーダーファイル名
	};
}
#endif // !PROGRRAMOBJECT_H_INCLUDED
