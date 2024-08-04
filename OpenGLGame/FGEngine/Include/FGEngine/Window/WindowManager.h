/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/Math/MathFrd.h"
#include <vector>
#include <string>

// ��s�錾
struct GLFWwindow;

namespace FGEngine
{
	/**
	* �E�B���h�E�Ǘ��N���X
	*/
	class WindowManager :  public Singleton<WindowManager>
	{
		friend Singleton<WindowManager>;
		friend class GameEngine;
	private:
		
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		WindowManager() = default;

		/**
		* �f�X�g���N�^
		*/
		~WindowManager();

		// �R�s�[�Ƒ�����֎~
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

	private:

		/**
		* �E�B���h�E�}�l�[�W���[��������
		* 
		* @retval 0		����������
		* @retval 0�ȊO	���������s
		*/
		int Initialze();

		/**
		* �E�B���h�E�̕`��J�n
		*/
		void Begin();

		/**
		* �E�B���h�E�̕`��I��
		*/
		void End();

	public:

		/**
		* �E�B���h�E�^�C�g�����擾
		*/
		std::string GetTitle() const;

		/**
		* �E�B���h�E�^�C�g����ύX
		* 
		* @param title �ύX����^�C�g��
		*/
		void SetTitle(const std::string& title);

		/**
		* �E�B���h�E�̃T�C�Y���擾
		*/
		Vector2 GetSize() const;

		/**
		* �E�B���h�E�I�u�W�F�N�g���擾
		*/
		GLFWwindow& GetObject() const;

		/**
		* �E�B���h�E�����Ă��邩�擾
		* 
		* @retval true	�E�B���h�E�����Ă���
		* @retval false �E�B���h�E���J���Ă���
		*/
		bool IsClose() const;

		/**
		* �E�B���h�E�����
		*/
		void Close();

	private:

		// �E�B���h�E�I�u�W�F�N�g
		GLFWwindow* window = nullptr;
	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED
