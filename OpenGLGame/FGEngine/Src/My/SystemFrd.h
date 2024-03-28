/**
* @file SystemFrd.h
*/
#ifndef FGENGINE_SYSTEMFRD_H_INCLUDED
#define FGENGINE_SYSTEMFRD_H_INCLUDED

namespace FGEngine
{
	namespace MainSystem
	{
		// ���ׂẴV�X�e�����Ǘ�����R�A��
		class EngineCore;
	}
	namespace PhysicsSystem
	{
		// �����G���W��
		class PhysicsEngine;
	}
	namespace RenderSystem
	{
		// �O���t�B�b�N�G���W��
		class GraphicsEngine;
	}
	namespace SceneSystem
	{
		// �V�[���̊Ǘ��N���X
		class SceneManager;
	}
	namespace ObjectSystem
	{
		// �I�u�W�F�N�g�̊Ǘ��N���X
		class ObjectManager;
	}
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
