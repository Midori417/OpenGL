/**
* @file GameObject.cpp
*/
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Renderer.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/AudioSource.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* �Q�[���I�u�W�F�N�g�̏�Ԃ��擾
	*/
	GameObjectState GameObject::GetState() const
	{
		return state;
	}

	/**
	* �V�[�����擾
	*/
	Scene* GameObject::GetScene() const
	{
		return ownerScene;
	}

	/**
	* �g�����X�t�H�[���R���|�[�l���g���擾
	*/
	TransformPtr GameObject::GetTransform() const
	{
		return transform;
	}

	/**
	* �Q�[���I�u�W�F�N�g��j������
	*
	* @param destroyTime �j���܂ł̎���
	*/
	void GameObject::Destroy(float destroyTime)
	{
		// �����̔j�����Ԃ�0�b�����Ȃ��Ԃ�j���ɂ���
		if (destroyTime <= 0)
		{
			state = GameObjectState::Destory;
			return;
		}

		// ���łɔj���Ȃ牽�����Ȃ�
		if (state == GameObjectState::Destory)
		{
			return;
		}

		// �j���҂�����Ȃ���Δj�����Ԃ�������
		if (state != GameObjectState::DestroyTime)
		{
			// ��Ԃ�j���҂��ɂ���
			state = GameObjectState::DestroyTime;
			// �j�����Ԃ�ݒ�
			this->destroyTime = destroyTime;
		}
	}

	/**
	* �N���[�������Q�[���I�u�W�F�N�g���擾����
	*/
	GameObjectPtr GameObject::CloneGameObject(const GameObjectPtr& object, const TransformPtr& transform)
	{
		auto p = std::make_shared<GameObject>();

		p->isActive = object->isActive;
		p->name = object->name + "Clone";
		p->tag = object->tag;

		// �N���[������g�����X�t�H�[�����Ȃ����object�̃g�����X�t�H�[�����N���[�����邷��
		if (transform != nullptr)
		{
			// �N���[�����ƂɃg�����X�t�H�[���R���|�[�l���g�������
			if (object->transform)
			{
				ComponentPtr clone = object->transform->Clone();
				clone->ownerObject = p;
				p->transform = std::dynamic_pointer_cast<Transform>(clone);
			}
		}
		else
		{
			ComponentPtr clone = transform->Clone();
			clone->ownerObject = p;
			p->transform = std::dynamic_pointer_cast<Transform>(clone);
		}
		// �N���[�����ƂɃ����_���[�R���|�[�l���g�������
		if (object->renderer)
		{
			ComponentPtr clone = object->renderer->Clone();
			clone->ownerObject = p;
			p->renderer = std::dynamic_pointer_cast<Renderer>(clone);
		}
		// �N���[�����ƂɃ��W�b�h�{�f�B�R���|�[�l���g�������
		if (object->rigidbody)
		{
			ComponentPtr clone = object->rigidbody->Clone();
			clone->ownerObject = p;
			p->rigidbody = std::dynamic_pointer_cast<Rigidbody>(clone);
		}
		// �N���[�����ƂɃA�j���[�^�R���|�[�l���g�������
		if (object->animator)
		{
			ComponentPtr clone = object->animator->Clone();
			clone->ownerObject = p;
			p->animator = std::dynamic_pointer_cast<Animator>(clone);
		}
		// �N���[������Imgui�R���|�[�l���g�������
		if (object->imGuiLayout)
		{
			ComponentPtr clone = object->imGuiLayout->Clone();
			clone->ownerObject = p;
			p->imGuiLayout = std::dynamic_pointer_cast<UI::ImGuiLayout>(clone);
		}
		// �N���[�����ƂɃJ�����R���|�[�l���g�������
		if (object->camera)
		{
			ComponentPtr clone = object->camera->Clone();
			clone->ownerObject = p;
			p->camera = std::dynamic_pointer_cast<Camera>(clone);
		}
		// �N���[�����ƂɃR���C�_�[�R���|�[�l���g�������
		if (!object->colliders.empty())
		{
			for (auto& x : object->colliders)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->colliders.push_back(std::dynamic_pointer_cast<Collider>(clone));
			}
		}
		// �N���[�����ƂɃQ�[���C�x���g�R���|�[�l���g�������
		if (!object->gameEvents.empty())
		{
			for (auto& x : object->gameEvents)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->gameEvents.push_back(std::dynamic_pointer_cast<GameEvent>(clone));
			}
		}
		// �N���[�����ƂɃI�E�f�B�I�\�[�X�R���|�[�l���g�������
		if (!object->audioSources.empty())
		{
			for (auto& x : object->audioSources)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->audioSources.push_back(std::dynamic_pointer_cast<AudioSource>(clone));
			}
		}

		return p;
	}

	/**
	* �폜�\��̃R���|�[�l���g���폜
	*/
	void GameObject::DestroyComponent()
	{

	}
}