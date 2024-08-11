/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/SystemFrd.h"
#include "FGEngine/Singleton.h"
#include <string>
#include <unordered_map>

struct GLFWwindow;

enum class Axis
{
	Horizontal,

	Vertical,
};

namespace FGEngine::InputSystem
{
	/**
	* ���͊Ǘ��N���X
	*/
	class InputManager : public Singleton<InputManager>
	{
	private:

		friend MainSystem::EngineCore;
		friend Singleton<InputManager>;

		// �R���X�g���N�^
		InputManager() = default;

		/**
		* �C���v�b�g�}�l�[�W���[��������
		*/
		int Initialize();

		/**
		* ���͂��X�V
		* 
		* @param window �I�u�W�F�N�g�I�u�W�F�N�g
		*/
		void Update(GLFWwindow* window);

		/**
		* Axis�̍X�V
		*/
		static void AxisUpdate();

	public:

		/**
		* Axis���擾
		* 
		* @parma axis �A�N�V�Y��
		*/
		static float GetAxis(Axis axis);

	private:

		// axis�z��
		static std::unordered_map<Axis, float> axisList;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
