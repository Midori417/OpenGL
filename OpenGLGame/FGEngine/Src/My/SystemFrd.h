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
	namespace ResouceSystem
	{
		// ���\�[�X�Ǘ��N���X
		class ResouceManager;
	}
	namespace SceneSystem
	{
		// �V�[���Ǘ��N���X
		class SceneManager;
	}
	namespace InputSystem
	{
		// ���͊Ǘ��N���X
		class InputManager;
	}
	namespace ObjectSystem
	{
		// �I�u�W�F�N�g�Ǘ��N���X
		class ObjectManager;
	}
	namespace WindowSystem
	{
		// �E�B���h�E�Ǘ��N���X
		class WindowManager;
	}
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
