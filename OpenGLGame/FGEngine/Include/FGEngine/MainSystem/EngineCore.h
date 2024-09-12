/**
* @file EngineCore.h
*/
#ifndef FGENGINE_ENGINECORE_H_INCLUDED
#define FGENGINE_ENGINECORE_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

// ��s�錾
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine
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
		std::shared_ptr<class RenderingEngine> renderingEngine;

		// �����G���W��
		std::shared_ptr<class PhysicsEngine> physicsEngine;

		// �E�B���h�E�}�l�[�W���[�|�C���^�[
		std::shared_ptr<class WindowManager> windowManager;

		// �V�[���}�l�[�W���[�|�C���^�[
		std::shared_ptr<class SceneManager> sceneManager;

		// ���\�[�X�}�l�[�W���[
		std::shared_ptr<class AssetManager> assetManager;

		// �C���v�b�g�}�l�[�W���|�C���^�[
		std::shared_ptr<class InputManager> inputManager; 

		// �T�E���h�}�l�[�W���[�|�C���^�[
		std::shared_ptr<class SoundManager> soundManager;
	};
}
#endif // !ENGINE_H_INCLUDED
