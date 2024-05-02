/**
* @file Debug.h
*/
#ifndef FGENIGNE_DEBUG_H_INCLUDED
#define FGENIGNE_DEBUG_H_INCLUDED

/**
* �f�o�b�O�p�̋@�\���i�[���閼�O���
*/
namespace Debug
{
	// ���b�Z�[�W�̎��
	enum class Type {
		error,		// �G���[
		warning,	// �x��
		info,		// ���̑��̏��
	};

	void Log(Type type, const char* func, const char* format, ...);
}

// Debug���ǂ���
# ifndef NODEBUG
	# define ENABLE_DEBUG_LOG // ���̃}�N�����`����ƃf�o�b�O�o�͂��L��
# endif // !NODEBUG
  
// �f�o�b�O�o�̓}�N��
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
