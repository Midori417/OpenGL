/**
* @file PhysicsEngine.h
*/
#ifndef FGENGINE_PHYSICSENGINE_H_INCLUDED
#define FGENGINE_PHYSICSENGINE_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/SystemFrd.h"
#include "WorldCollider.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* �����G���W��
	*/
	class PhysicsEngine : public Singleton<PhysicsEngine>
	{
	private:

		friend Singleton<PhysicsEngine>;
		friend MainSystem::EngineCore;

		// �R���X�g���N�^
		PhysicsEngine() = default;

		/**
		* �ђʃx�N�g�����Q�[���I�u�W�F�N�g�ɔ��f����
		*/
		void ApplyPenetration(WorldColliderList* worldColliders, GameObject* gameObject, const Vector3& penetration);

	public:

		/**
		* �Q�[���I�u�W�F�N�g�̃R���C�_�[�̏Փ˔���
		*
		* @param a ����Ώۂ̃��[���h�R���C�_�[�z�񂻂̂P
		* @param b ����Ώۂ̃��[���h�R���C�_�[�z�񂻂̂Q
		*/
		void HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b);

	};
}

#endif // !FGENGINE_PHYSICSENGINE_H_INCLUDED
