/**
* @file Engine.h
*/
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include "Singleton.h"
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

namespace FGEngine
{
	namespace SceneSystem
	{
		class SceneManager;
		using SceneManagerPtr = std::shared_ptr<SceneManager>;
	}

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

		// �t���[���o�b�t�@�̑傫�����擾����
		Vector2 GetFramebufferSize() const;

		// �t���[���o�b�t�@�̃A�X�y�N�g����擾����
		float GetAspectRatio() const;

	private:

		// �Q�[���G���W����������
		int Initialize();

		// �Q�[���G���W�����X�V
		void Update();

		// �G���W���̏I��
		void Fainalize();

	private:

		// �E�B���h�E
		GLFWwindow* window = nullptr;	// �E�B���h�E�I�u�W�F�N�g
		const std::string title = "OpenGLGame";	// �E�B���h�E�^�C�g��

		// �A�v���P�[�V�����|�C���^�[
		ApplicationPtr application;

		// �V�[���}�l�[�W���[�|�C���^�[
		SceneSystem::SceneManagerPtr sceneManager;
	};
}
#endif // !ENGINE_H_INCLUDED
