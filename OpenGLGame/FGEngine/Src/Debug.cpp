/**
* @file Debug.cpp
*/
#include "FGEngine/Debug.h"
#include <stdio.h>
#include <stdarg.h>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

#include "FGEngine/Package/Glad.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace Debug
{

	/**
	* 書式付き文字列をデバッグウィンドウに表示する
	*/
	void Log(Type type, const char* func, const char* format, ...)
	{
		char buffer[1050] = {""};
		char* p = buffer;
		size_t size = sizeof(buffer) - 1;	// 末尾に\nを追加させるため

		// ログの種類と関数名を設定
		static const  char* const typeNames[] = { "エラー", "警告", "情報" };
		size_t n = snprintf(p, size, "[%s] %s:", typeNames[static_cast<int>(type)], func);
		p += n;
		size -= n;

		// メッセージを設定
		va_list ap;
		va_start(ap, format);
		p += vsnprintf(p, size, format, ap);
		va_end(ap);

		// 末尾に改行を追加
		p[0] = '\n';
		p[1] = '\0';

		// 作成した文字列をデバッグウィンドウに表示
		OutputDebugString(buffer);
	}

	/**
	* OpenGLからのメッセージを処理するコールバック関数
	*
	* @param source		メッセージの発信者
	* @param type		メッセージの種類
	* @param id			メッセージを一位に選別する値
	* @param severiry	メッセージの重要度(高、中、小、最低)
	* @param length		メッセージの文字数、負数ならメッセージは0終端されている
	* @param message	メッセージ本体
	* @param userParam	コールバック設定時に指定したポインタ
	*/
	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string s;
		if (length < 0)
		{
			s = message;
		}
		else
		{
			s.assign(message, message + length);
		}
		s += '\n';
		LOG(s.c_str());
	}

	/**
	* OpenGLからのデバッグをする
	*/
	void OpenGLDebug()
	{
		// メッセージコールバック設定
		glDebugMessageCallback(DebugCallback, nullptr);
	}
}
