/**
* @file Shader.cpp
*/
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Math/Math.h"
#include "FGEngine/Color.h"
#include "FGEngine/Debug.h"

#include "FGEngine/Package/Glad.h"

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
	Shader::Shader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
		: AssetObject(name)
	{
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
			LOG_ERROR("シェーダーのリンクに失敗(vs=%s, fs=%s)", filenameVS.c_str(), filenameFS.c_str());
			return;		// シェーダーのリンクに失敗
		}
	}

	/**
	* デストラクタ
	*/
	Shader::~Shader()
	{
		// シェーダのメモリを開放する
		glDeleteProgram(prog);
		glDeleteShader(fs);
		glDeleteShader(vs);
	}

	/**
	* シェーダを作成
	*/
	ShaderPtr Shader::Create(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		return std::make_shared<Shader>(name, filenameVS, filenameFS);
	}

	void Shader::Use()
	{
		glUseProgram(prog);
	}

	void Shader::SetBool(const std::string& name, bool value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform1i(prog, location, value);
		}
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform1i(prog, location, value);
		}
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform1f(prog, location, value);
		}
	}

	void Shader::SetFloat2(const std::string& name, float value, float value2)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform2f(prog, location, value, value2);
		}
	}

	void Shader::SetFloat3(const std::string& name, float value, float value2, float value3)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform3f(prog, location, value, value2, value3);
		}
	}

	void Shader::SetFloat4(const std::string& name, float value, float value2, float value3, float value4)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform4f(prog, location, value, value2, value3, value4);
		}
	}

	void Shader::SetVector2(const std::string& name, const Vector2& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform2fv(prog, location, 1, &value.x);
		}
	}

	void Shader::SetVector3(const std::string& name, const Vector3& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform3fv(prog, location, 1, &value.x);
		}
	}

	void Shader::SetVector4(const std::string& name, const Vector4& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform4fv(prog, location, 1, &value.x);
		}
	}

	void Shader::SetMatrix3x3(const std::string& name, const Matrix3x3& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniformMatrix3fv(prog, location, 1, GL_FALSE, &value(0, 0));
		}
	}

	void Shader::SetMatrix4x4(const std::string& name, const Matrix4x4& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniformMatrix4fv(prog, location, 1, GL_FALSE, &value(0, 0));
		}
	}

	void Shader::SetColor(const std::string& name, const Color& value)
	{
		const GLint location = glGetUniformLocation(prog, name.c_str());
		if (location >= 0)
		{
			glProgramUniform4fv(prog, location, 1, &value.r);
		}
	}
}