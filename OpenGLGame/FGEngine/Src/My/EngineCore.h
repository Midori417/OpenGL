/**
* @file EngineCore.h
*/
#ifndef FGENGINE_ENGINECORE_H_INCLUDED
#define FGENGINE_ENGINECORE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "VecMath.h"
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

		// �Q�[���G���W����������
		int Initialize();

		// �Q�[���G���W�����X�V
		void Update();

		// �G���W���̏I��
		void Fainalize();

	private:

		// �A�v���P�[�V�����|�C���^�[
		ApplicationPtr application;

		// �E�B���h�E�}�l�[�W���[
		std::shared_ptr<WindowSystem::WindowManager> windowManager;

		// �V�[���}�l�[�W���[�|�C���^�[
		std::shared_ptr<SceneSystem::SceneManager> sceneManager;
	};
}
#endif // !ENGINE_H_INCLUDED