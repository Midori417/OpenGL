/**
* @file PhysicsEngine.h
*/
#ifndef FGENGINE_PHYSICSENGINE_H_INCLUDED
#define FGENGINE_PHYSICSENGINE_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/Transform.h"

namespace FGEngine
{
	/**
	* ���[���h���W�n�̃R���C�_�[
	*/
	struct WorldCollider
	{
		/**
		* ���W��ύX����
		*
		* @param v �ύX����l
		*/
		void AddPosition(const Vector3& v)
		{
			origin->GetTransform()->position += v;
			world->AddPosition(v);
		}
		ColliderPtr origin;
		ColliderPtr world;
	};
	using WorldColliderList = std::vector<WorldCollider>;

	/**
	* �����G���W��
	*/
	class PhysicsEngine : public Singleton<PhysicsEngine>
	{
		friend Singleton<PhysicsEngine>;
		friend class EngineCore;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		PhysicsEngine() = default;

	private:

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
