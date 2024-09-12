/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include <unordered_map>

// ��s�錾
struct GLFWwindow;

/**
* ���z��
*/
enum class Axis
{
	Horizontal,

	Vertical,
};

namespace FGEngine
{
	/**
	* ���͊Ǘ��N���X
	*/
	class InputManager : public Singleton<InputManager>
	{
		friend Singleton<InputManager>;
		friend class EngineCore;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		InputManager() = default;

	private: // EngineCore�ł����Ă΂Ȃ�

		/**
		* �C���v�b�g�}�l�[�W���[��������
		* 
		* @param window �E�B���h�E�I�u�W�F�N�g
		*
		* @retval true	����ɏ�����
		* @retval false	���������s
		*/
		bool Initialize(GLFWwindow* window);

		/**
		* �C���v�b�g�}�l�[�W���[�̏�Ԃ��X�V
		*/
		void Update();

	private:

		/**
		* Axis�̍X�V
		*/
		void AxisUpdate();

	public:

		/**
		* Axis���擾
		*
		* @parma axis �A�N�V�Y��
		*/
		static float GetAxis(Axis axis);

	private:	// ���͊Ǘ�

		// �L�[���͊Ǘ�
		static std::shared_ptr<class InputKey> inputKey;

		// �}�E�X���͊Ǘ�
		static std::shared_ptr<class InputMouse> inputMouse;

	private:

		// axis�z��
		static std::unordered_map<Axis, float> axisList;

		// �E�B���h�E�I�u�W�F�N�g
		GLFWwindow* window = nullptr;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
