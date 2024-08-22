/**
* @file SystemFrd.h
*/
#ifndef FGENGINE_SYSTEMFRD_H_INCLUDED
#define FGENGINE_SYSTEMFRD_H_INCLUDED

namespace FGEngine
{
	namespace MainSystem
	{
		// ���ׂẴV�X�e�����Ǘ�����G���W���N���X
		class EngineCore;
	}
	namespace PhysicsSystem
	{
		// �����G���W��
		class PhysicsEngine;
	}
	namespace RenderingSystem
	{
		// �`��G���W��
		class RenderingEngine;
	}
	// ���\�[�X�Ǘ��N���X
	class AssetManager;
	// �V�[���Ǘ��N���X
	class SceneManager;

	namespace InputSystem
	{
		// ���͊Ǘ��N���X
		class InputManager;
	}
	namespace WindowSystem
	{
		// �E�B���h�E�Ǘ��N���X
		class WindowManager;
	}
	namespace SoundSystem
	{
		// �T�E���h�Ǘ��N���X
		class SoundManager;
	}
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
