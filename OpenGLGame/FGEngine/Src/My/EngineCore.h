/**
* @file EngineCore.h
*/
#ifndef FGENGINE_ENGINECORE_H_INCLUDED
#define FGENGINE_ENGINECORE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

// ��s�錾
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine::MainSystem
{
	/**
	* �Q�[���G���W��
	*/
	class EngineCore : public Singleton<EngineCore>
	{
	private:

		friend Singleton<EngineCore>;

		// �R���X�g���N�^
		EngineCore() = default;

	public:

		~EngineCore() = default;

		// �Q�[���G���W�������s
		int Run();

	private:

		/**
		* �Q�[���G���W����������
		* 
		* @retval 0		����ɏI��
		* @ratval 0�ȊO	�G���[������
		*/
		int Initialize();

		/**
		* �Q�[���G���W�����X�V
		*/
		void Update();

		/**
		* �G���W�����I��
		*/
		void Fainalize();

	private:

		// �A�v���P�[�V�����|�C���^�[
		ApplicationPtr application;

		// �����_�����O�G���W��
		std::shared_ptr<RenderingSystem::RenderingEngine> renderingEngine;

		// �����G���W��
		std::shared_ptr<PhysicsSystem::PhysicsEngine> physicsEngine;

		// �E�B���h�E�}�l�[�W���[�|�C���^�[
		std::shared_ptr<WindowSystem::WindowManager> windowManager;

		// �I�u�W�F�N�g�}�l�[�W���[�|�C���^�[
		std::shared_ptr<ObjectSystem::ObjectManager> objectManager;

		// �V�[���}�l�[�W���[�|�C���^�[
		std::shared_ptr<SceneSystem::SceneManager> sceneManager;

		// ���\�[�X�}�l�[�W���[
		std::shared_ptr<ResouceSystem::ResouceManager> resouceManager;

		// �C���v�b�g�}�l�[�W���|�C���^�[
		std::shared_ptr<InputSystem::InputManager> inputManager;
	};
}
#endif // !ENGINE_H_INCLUDED