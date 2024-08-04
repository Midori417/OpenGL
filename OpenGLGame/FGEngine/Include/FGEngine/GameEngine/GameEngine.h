/**
* @file GameEngine.h
*/
#ifndef FGENGINE_GAMEENGINE_H_INCLUDED
#define FGENGINE_GAMEENGINE_H_INCLUDED
#include "FGEngine/Singleton.h"

namespace FGEngine
{
	// ��s�錾
	class RenderEngine;
	class PhysicsEngine;
	class AudioEngine;
	class InputManager;
	class AssetManager;
	class SceneManager;
	class WindowManager;

	/**
	* �Q�[���G���W��
	*/
	class GameEngine : public Singleton<GameEngine>
	{
		friend Singleton<GameEngine>;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		GameEngine() = default;


		// �R�s�[�Ƒ�����֎~
		GameEngine(const GameEngine&) = delete;
		GameEngine operator=(const GameEngine&) = delete;

	public:

		/**
		* �Q�[���G���W���ғ�
		* 
		* @retval 0		����ɉғ�
		* @retval 0�ȊO	�G���[����
		*/
		int Run();

	private:

		/**
		* �Q�[���G���W����������
		* 
		* @retval 0		����ɏ�����
		* @retval 0�ȊO	�G���[����
		*/
		int Initialize();

		/**
		* �Q�[���G���W���̏�Ԃ��X�V
		* 
		* @retval 0		����ɍX�V
		* @retval 0�ȊO	�G���[����
		*/
		int Update();

		/**
		* �Q�[���G���W���̏�Ԃ�`��
		*/
		void Render();

		/**
		* �Q�[�����I��
		*/
		void Finalze();

	public:

		/**
		* �G���W�����~�߂�
		*/
		void PowerOff();

	private:

		// �`��G���W��
		std::shared_ptr<RenderEngine> renderEngine;

		// �����G���W��
		std::shared_ptr<PhysicsEngine> physicsEngine;

		// �T�E���h�G���W��
		std::shared_ptr<AudioEngine> audioEngine;

		// ���̓}�l�[�W���[
		std::shared_ptr<InputManager> inputManager;

		// �A�Z�b�g�}�l�[�W���[
		std::shared_ptr<AssetManager> assetManager;

		// �V�[���}�l�[�W���[
		std::shared_ptr<SceneManager> sceneManager;

		// �E�B���h�E�}�l�[�W���[
		std::shared_ptr<WindowManager> windowManger;

		// true�Ȃ�G���W�����~�߂�
		bool isPowerOff = false;
	};
}

#endif // !FGENGINE_GAMEENGINE_H_INCLUDED
