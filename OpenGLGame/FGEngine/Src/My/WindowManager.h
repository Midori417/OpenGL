/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include "Singleton.h"
#include "VecMath.h"
#include "Color.h"
#include <string>
	
namespace FGEngine::WindowSystem
{
	/**
	* �E�B���h�E�Ǘ��N���X
	*/
	class WindowManager : public Singleton<WindowManager>
	{
	private:
		
		friend Singleton<WindowManager>;

		// �R���X�g���N�^
		WindowManager() = default;

	public:



		// �R�s�[�Ƒ�����֎~
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

		/**
		* �E�B���h�E���쐬
		*
		* @param windowTitle �E�B���h�E�^�C�g��
		*
		* @retval	�쐬�����E�B���h�E�I�u�W�F�N�g
		*			nullptr �쐬�Ɏ��s
		*/
		void CreateWindow(const std::string& windowTitle);

		/**
		* �E�B���h�E�̕`����J�n
		*/
		void Begin();

		/**
		* �E�B���h�E�ւ̕`����I��
		*/
		void End();

		/**
		* �E�B���h�E�����Ă��邩�擾
		*
		* @retval true	���Ă���
		* @retval false	���Ă��Ȃ�
		*/
		bool IsClose(size_t index = 0);

		/**
		* �E�B���h�E�I�u�W�F�N�g���擾
		*/
		GLFWwindow& GetWindow(size_t index = 0);

		/**
		* �E�B���h�E�̃T�C�Y��Vector2�Ŏ擾
		*/
		Vector2 GetWindowSize(size_t index = 0);

		/**
		* �E�B���h�E�T�C�Y���擾
		*
		* @param w �E�B���h�E�̉������i�[����
		* @param h �E�B���h�E�̏c�����i�[����
		*/
		void GetWindowSize(GLsizei& w, GLsizei& h, size_t index = 0);

		/**
		* �E�B���h�E�̃T�C�Y�̃A�X�y�N�g���擾
		*/
		float GetWindowAspectRatio();

		/**
		* �o�b�t�@�N���A�̃J���[��ݒ�
		*/
		void SeteBufferClearColor(const Color& color);

	private:

		std::vector<GLFWwindow*> windows;	// �E�B���h�E�z��
		Color bufferColor = Color::black;

	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED
