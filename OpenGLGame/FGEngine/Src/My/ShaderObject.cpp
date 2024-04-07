/**
* @file ShaderObject.cpp
*/
#include "ShaderObject.h"
#include "Debug.h"
#include <fstream>
#include <filesystem>

namespace FGEngine
{
	/**
	* シェーダファイルを読み込んでコンパイルする
	*
	* @param type		シェーダの種類
	* @param filename	シェーダファイル名
	*
	* @return	シェーダの管理番号
	*/
	GLuint CompileShader(GLenum type, const char* filename)
	{
		std::ifstream file(filename, std::ios::binary); // ファイルを開く
		if (!file)
		{
			LOG_ERROR("%sを開けません", filename);
			return 0;
		}

		// ファイルを読み込む
		const size_t filesize = std::filesystem::file_size(filename);
		std::vector<char> buffer(filesize);
		file.read(buffer.data(), filesize);
		file.close();

		// ソースコードを設定してコンパイル
		const char* source[] = {
			buffer.data()
		};
		const GLint	length[] = {
			int(buffer.size())
		};
		const GLuint object = glCreateShader(type);
		glShaderSource(object, 1, source, length);
		glCompileShader(object);

		// コンパイル結果をチェック
		GLint status = 0;	// 結果を格納する件数

		// コンパイル結果を取得
		glGetShaderiv(object, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			LOG_ERROR("シェーダーのコンパイルに失敗(%s)", filename);
			glDeleteShader(object);
			return 0;		// コンパイルに失敗
		}

		return object;
	}

	/**
	* コンストラクタ
	*
	* @param filenameVS 頂点シェーダーのファイル名
	* @param filenameFS フラグメントシェーダーのファイル名
	*/
	ShaderObject::ShaderObject(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		// シェーダの名前を設定
		SetName(name);

		// シェーダー読み込んでコンパイル
		vs = CompileShader(GL_VERTEX_SHADER, filenameVS.c_str());
		fs = CompileShader(GL_FRAGMENT_SHADER, filenameFS.c_str());

		if (vs == 0 || fs == 0)
		{
			return; // コンパイルに失敗
		}

		// 二つのシェーダーをリンク
		prog = glCreateProgram();
		glAttachShader(prog, vs);
		glAttachShader(prog, fs);
		glLinkProgram(prog);

		// リンク結果をチェック
		GLint status = 0;

		// リンク結果を取得
		glGetProgramiv(prog, GL_LINK_STATUS, &status);

		if (status != GL_TRUE)
		{
			LOG_ERROR("シェーダーのリンクに失敗(vs=%s, fs=%s)", filenameVS, filenameFS);
			return;		// シェーダーのリンクに失敗
		}

		LOG("シェーダーを作成(vs=%s, fs=%s)", filenameVS, filenameFS);
	}

	/**
	* デストラクタ
	*/
	ShaderObject::~ShaderObject()
	{
		glDeleteProgram(prog);
		glDeleteShader(fs);
		glDeleteShader(vs);
	}

	/*
	* プログラムオブジェクトを作成
	*/
	ShaderObjectPtr ShaderObject::Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		return std::make_shared<ShaderObject>(name, filenameVS, filenameVS);
	}
}