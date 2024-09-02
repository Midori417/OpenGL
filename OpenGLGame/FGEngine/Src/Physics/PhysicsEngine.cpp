/**
* @file PhysicsEngine.cpp
*/
#include "FGEngine/Physics/PhysicsEngine.h"
#include "FGEngine/Physics/Intersect.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Component/BoxCollider.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* �^�ɂ���Č�������֐����Ăѕ����邽�߂̊֐��e���v���[�g
	*/
	template<class T, class U>
	bool CallIntersect(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		return Intersect(static_cast<T&>(*a).GetShape(), static_cast<U&>(*b).GetShape(), p);
	}

	/**
	* �^�ɂ���Č�������֐����Ăѕ����邽�߂̊֐��e���v���[�g
	*
	* ��������֐��ɓn���������t�ɂ���o�[�W����
	*/
	template<class T, class U>
	bool CallIntersectRevers(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		if (Intersect(static_cast<U&>(*b).GetShape(), static_cast<T&>(*a).GetShape(), p)) {
			p *= -1;	// �ђʃx�N�g�����t�����ɂ���
			return true;
		}
		return false;
	}

	/**
	* ���false��Ԃ��֐��e���v���[�g
	*
	* �������܂��͎����\��̂Ȃ��g�ݍ��킹�p
	*/
	template<class T, class U>
	bool NotImplemented(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		return false;
	}

	/**
	* �ђʃx�N�g�����Q�[���I�u�W�F�N�g�ɔ��f����
	*/
	void PhysicsEngine::ApplyPenetration(WorldColliderList* worldColliders, GameObject* gameObject, const Vector3& penetration)
	{
		// �ݒu����
		// �Փ˃x�N�g���������ɋ߂��ꍇ�A���ƐG�ꂽ�Ƃ݂Ȃ�
		static const float cosGround = Mathf::Cos(Mathf::DegToRad(90)); //�@���Ƃ݂Ȃ��p�x
		if (penetration.y > 0 && gameObject->rigidbody)
		{
			// �Ώۂ��P�ʐ����x�N�g���ł��邱�Ƃ𗘗p���āA���ςɂ��p�x�̔�r��P����
			const float d = Vector3::Magnitude(penetration);
			if (penetration.y >= d * cosGround)
			{
				gameObject->rigidbody->isGrounded = true; // �ݒu����
			}
		}

		// ���ׂẴ��[���h�R���C�_�[���ړ�
		for (auto& e : *worldColliders)
		{
			Vector3 pen = penetration;
			pen.z *= -1;
			e.AddPosition(pen);
		}
	}

	/**
	* �Q�[���I�u�W�F�N�g�̃R���C�_�[�̏Փ˔���
	*
	* @param a ����Ώۂ̃��[���h�R���C�_�[�z�񂻂̂P
	* @param b ����Ώۂ̃��[���h�R���C�_�[�z�񂻂̂Q
	*/
	void PhysicsEngine::HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b)
	{
		// �֐��|�C���^�^���`
		using FuncType = bool(*)(const ColliderPtr&, const ColliderPtr&, Vector3&);

		// �g�ݍ��킹�ɑΉ������������֐���I�Ԃ��߂̔z��
		static const FuncType funcList[3][3] = {
			{
				CallIntersect<AabbCollider, AabbCollider>,
				CallIntersect<AabbCollider, SphereCollider>,
				NotImplemented<AabbCollider, BoxColliderPtr>,
			},
			{
				CallIntersectRevers<SphereCollider, AabbCollider>,
				CallIntersect<SphereCollider, SphereCollider>,
				CallIntersect<SphereCollider, BoxCollider>,
			},
			{
				NotImplemented<BoxCollider, AabbCollider>,
				CallIntersectRevers<BoxCollider, SphereCollider>,
				NotImplemented<BoxCollider, BoxCollider>,
			},
		};

		// �R���C�_�[�P�ʂ̏Փ˔���
		for (auto& colA : *a)
		{
			for (auto& colB : *b)
			{
				// �ǂ��炩�̃R���C�_�[��Rigidbody�����Ă��Ȃ���ΏՓ˂��Ȃ�
				if (!colA.origin->GetAttachedRigidbody() && !colB.origin->GetAttachedRigidbody())
				{
					continue;
				}
				// �R���C�_�[���@�\���Ă��Ȃ���΂��Ȃ���ΏՓ˂��Ȃ�
				if (!colA.origin->enabled || !colB.origin->enabled)
				{
					continue;
				}
				// �Փ˔�����s��
				Vector3 penetration;
				const int typeA = static_cast<int>(colA.origin->GetType());
				const int typeB = static_cast<int>(colB.origin->GetType());
				if (funcList[typeA][typeB](colA.world, colB.world, penetration))
				{
					// �I�u�W�F�N�g���擾
					GameObjectPtr goA = colA.origin->OwnerObject();
					GameObjectPtr goB = colB.origin->OwnerObject();

					// �R���C�_�[���d�Ȃ�Ȃ��悤�ɍ��W�𒲐�
					if (!colA.origin->isTrigger && !colB.origin->isTrigger)
					{
						if (!colA.origin->GetAttachedRigidbody())
						{
							// A�͓����Ȃ��̂�B���ړ�������
							ApplyPenetration(b, goB.get(), penetration);
						}
						else if (!colB.origin->GetAttachedRigidbody())
						{
							// B�͓����Ȃ��̂�A���ړ�������
							ApplyPenetration(a, goA.get(), -penetration);
						}
						else
						{
							// A��B���ϓ��Ɉړ�������
							ApplyPenetration(b, goB.get(), penetration * 0.5f);
							ApplyPenetration(a, goA.get(), penetration * -0.5f);
						}
					}

					// �C�x���g����
					if (!goA->gameEvents.empty())
					{
						// �Փˏ����쐬
						CollisionPtr colInfoB = std::make_shared<Collision>();
						colInfoB->gameObject = goB;
						colInfoB->transform = goB->GetTransform();
						colInfoB->rigidBody = goB->rigidbody;
						colInfoB->collider = colB.origin;
						for (auto x : goA->gameEvents)
						{
							// �O��̎��Փ˂��Ă��Ȃ����OnCollisionEnter���Ăяo��
							if (!colA.origin->old)
							{
								x->OnCollisionEnter(colInfoB);
							}
							x->OnCollisionStay(colInfoB);
						}
					}
					if (!goB->gameEvents.empty())
					{
						// �Փˏ����쐬
						CollisionPtr colInfoA = std::make_shared<Collision>();
						colInfoA->gameObject = goA;
						colInfoA->transform = goA->GetTransform();
						colInfoA->rigidBody = goA->rigidbody;
						colInfoA->collider = colA.origin;
						for (auto x : goB->gameEvents)
						{
							// �O��̎��Փ˂��Ă��Ȃ����OnCollisionEnter���Ăяo��
							if (!colB.origin->old)
							{
								x->OnCollisionEnter(colInfoA);
							}
							x->OnCollisionStay(colInfoA);
						}

					}

					// �R���C�_�[�O��̏�Ԃ��Փ˂����ɂ���
					colA.origin->old = true;
					colB.origin->old = true;
					// �C�x���g�̌��ʁA�ǂ��炩�̃Q�[���I�u�W�F�N�g���j�󂳂ꂽ�烋�[�v�I��
					if (goA->GetState() == GameObjectState::Destroyed || goB->GetState() == GameObjectState::Destroyed)
					{
						return;	// �֐��I��
					}
				}
				else
				{
					// �I�u�W�F�N�g���擾
					GameObjectPtr goA = colA.origin->OwnerObject();
					GameObjectPtr goB = colB.origin->OwnerObject();

					// �C�x���g����
					if (!goA->gameEvents.empty())
					{
						// �Փˏ����쐬
						CollisionPtr colInfoB = std::make_shared<Collision>();
						colInfoB->gameObject = goB;
						colInfoB->transform = goB->GetTransform();
						colInfoB->rigidBody = goB->rigidbody;
						colInfoB->collider = colB.origin;
						for (auto x : goA->gameEvents)
						{
							if (colA.origin->old)
							{
								x->OnCollisionExit(colInfoB);
							}
						}
					}
					if (!goB->gameEvents.empty())
					{
						// �Փˏ����쐬
						CollisionPtr colInfoA = std::make_shared<Collision>();
						colInfoA->gameObject = goA;
						colInfoA->transform = goA->GetTransform();
						colInfoA->rigidBody = goA->rigidbody;
						colInfoA->collider = colA.origin;
						for (auto x : goB->gameEvents)
						{
							if (colB.origin->old)
							{
								x->OnCollisionExit(colInfoA);
							}
						}
					}


					// �R���C�_�[�O��̏�Ԃ��Փ˂��Ă��Ȃ��ɂ���
					colA.origin->old = false;
					colB.origin->old = false;

					// �C�x���g�̌��ʁA�ǂ��炩�̃Q�[���I�u�W�F�N�g���j�󂳂ꂽ�烋�[�v�I��
					if (goA->GetState() == GameObjectState::Destroyed || goB->GetState() == GameObjectState::Destroyed)
					{
						return;	// �֐��I��
					}
				}
			}
		}

	}
}