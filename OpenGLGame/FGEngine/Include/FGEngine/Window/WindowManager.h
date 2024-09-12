/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Color.h"
#include <string>
#include <vector>

// ��s�錾
struct GLFWwindow;
	
namespace FGEngine
{
	/**
	* �E�B���h�E�Ǘ��N���X
	*/
	class WindowManager : public Singleton<WindowManager>
	{
		friend Singleton<WindowManager>;
		friend class EngineCore;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		WindowManager() = default;

	public:	// �֎~����

		// �R�s�[���֎~
		WindowManager(const WindowManager&) = delete;

		// ������֎~
		WindowManager& operator=(const WindowManager&) = delete;

	private: // EngineCore�ŌĂяo��

		/**
		* �E�B���h�E�}�l�[�W���[��������
		* 
		* @retval true	����ɏ�����
		* @retval false	���������s
		*/
		bool Initialize();

		/**
		* �E�B���h�E�̕`����J�n
		*/
		void Begin();

		/**
		* �E�B���h�E�ւ̕`����I��
		*/
		void End();

	public:	// ���O���擾�Ɛݒ�

		/**
		* �E�B���h�E�^�C�g�����擾
		*/
		static std::string GetTitle();

		/**
		* �E�B���h�E�^�C�g����ݒ�
		* 
		* @param title �ݒ肷��E�B���h�E�^�C�g��
		*/
		static void SetTitle(const std::string& title);

	public:

		/**
		* �E�B���h�E���I��
		*/
		static void WindowClose();

		/**
		* �E�B���h�E�����Ă��邩�擾
		*
		* @retval true	���Ă���
		* @retval false	���Ă��Ȃ�
		*/
		static bool IsClose();

		/**
		* �E�B���h�E�I�u�W�F�N�g���擾
		*/
		static GLFWwindow& GetWindow();

		/**
		* �E�B���h�E�̃T�C�Y��Vector2�Ŏ擾
		*/
		static Vector2 GetWindowSize();

		/**
		* �o�b�t�@�N���A�̃J���[��ݒ�
		*/
		static void SeteBufferClearColor(const Color& color);

	private:

		// �E�B���h�E�I�u�W�F�N�g
		static GLFWwindow* window;

		// �N���A�o�b�t�@�̃J���[
		static Color bufferColor;
	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED