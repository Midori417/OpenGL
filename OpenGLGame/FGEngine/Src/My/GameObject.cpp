/**
* @file GameObject.cpp
*/
#include "GameObject.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* �폜�\��̃R���|�[�l���g���폜
	*/
	void GameObject::DestroyComponent()
	{
		// �R���|�[�l���g�������Ă��Ȃ���Ή������Ȃ�
		if (components.empty())
		{
			return;
		}

		// �j��̗L���ŃR���|�[�l���g�𕪂���
		const auto iter = std::stable_partition(
			components.begin(), components.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });

		// �j��������̂��Ȃ�
		if (iter == components.end())
		{
			return;
		}

		// �R���|�[�l���g�z�񂩂�폜
		components.erase(iter, components.end());

		// �R���C�_�[�z�񂩂���폜����
		const auto iter2 = std::remove_if(
			colliders.begin(), colliders.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });

		// �R���C�_�[�z�񂩂�폜
		colliders.erase(iter2, colliders.end());

		// ���m�r�w�C�r�A�z�񂩂�폜����
		const auto iter3 = std::stable_partition(
			monoBehaviours.begin(),monoBehaviours.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });
		
		// �j���̃��m�r�w�C�r�A��ʂ̔z��Ɉړ�
		std::vector<MonoBehaviourPtr> destorylist(
			std::move_iterator(iter3),
			std::move_iterator(monoBehaviours.end()));

		// ���m�r�w�C�r�A�z�񂩂�폜
		monoBehaviours.erase(iter3, monoBehaviours.end());

		// �j���̃��m�r�w�C�r�A��OnDestroy�����s
		for (auto x : destorylist)
		{
			x->OnDestory();
		}

		// Transform���j���\��Ȃ�폜
		if (transform->GetHideFlag() == HideFlag::Destory)
		{
			transform = nullptr;
		}

		// Renderer���j���\��Ȃ�폜
		if (renderer->GetHideFlag() == HideFlag::Destory)
		{
			renderer = nullptr;
		}

		// Rigidbody���j���\��Ȃ�폜
		if (rigidbody->GetHideFlag() == HideFlag::Destory)
		{
			rigidbody = nullptr;
		}

	}
}