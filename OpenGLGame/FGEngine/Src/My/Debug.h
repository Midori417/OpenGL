/**
* @file Debug.h
*/
#ifndef FGENIGNE_DEBUG_H_INCLUDED
#define FGENIGNE_DEBUG_H_INCLUDED

/**
* デバッグ用の機能を格納する名前空間
*/
namespace Debug
{
	// メッセージの種類
	enum class Type {
		error,		// エラー
		warning,	// 警告
		info,		// その他の情報
	};

	void Log(Type type, const char* func, const char* format, ...);
}

// Debugかどうか
# ifndef NODEBUG
	# define ENABLE_DEBUG_LOG // このマクロを定義するとデバッグ出力が有効
# endif // !NODEBUG
  
// デバッグ出力マクロ
# ifdef ENABLE_DEBUG_LOG
 	# define LOG_ERROR(...) Debug::Log(Debug::Type::error, __func__, __VA_ARGS__)
 	# define LOG_WARNINGS(...) Debug::Log(Debug::Type::warning, __func__, __VA_ARGS__)
 	# define LOG(...) Debug::Log(Debug::Type::info, __func__, __VA_ARGS__)
# else
	# define LOG_ERROR(...)		((void)0)
	# define LOG_WARNINGS(...)	((void)0)
	# define LOG(...)			((void)0)
# endif // !ENABLE_DEBUG_LOG

#endif // !FGENGINE_DEBUG_H_INCLUDED
