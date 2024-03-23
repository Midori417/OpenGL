/**
* @file GameObject.cpp
*/
#include "GameObject.h"
#include <algorithm>

namespace FGEngine
{

	/**
	* �f�X�g���N�^
	*/
	GameObject::~GameObject()
	{
		// ���ʑO�ɐe�q�֌W����������
		SetParent(nullptr);
		for (auto child : children) {
			child->parent = nullptr;
		}
	}

	/**
	* �ŏ���Update�̒��O�ŌĂяo�����
	*/
	void GameObject::Start()
	{
		for (auto& e : components) {
			if (!e->isStarted) {
				e->Start();
				e->isStarted = true;
			}
		}
	}

	/**
	* ���t���[�����Ăяo��
	*
	* @param deltaTime	�O��̍X�V����̌o�ߎ���
	*/
	void GameObject::Update()
	{
		for (auto& e : components) {
			e->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto& e : components) {
			e->LateUpdate();
		}
		// �j���\��̃R���|�[�l���g���폜����
		RemoveDestroyedComponent();
	}

	/**
	* �Փ˂��N�����Ƃ��ɌĂяo�����
	*
	* @param self �Փ˂����R���|�[�l���g(����)
	* @param other �Փ˂����R���|�[�l���g(����)
	*/
	void GameObject::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
	{
		for (auto& e : components) {
			e->OnCollision(self, other);
		}
	}

	/**
	* �폜���ꂽ�Ƃ��ɌĂяo��
	*/
	void GameObject::OnDestroy()
	{
		for (auto& e : components) {
			e->OnDestroy();
		}
	}

	/**
	* �e�I�u�W�F�N�g��ݒ肷��
	*
	* @param parent �e�ɂ���Q�[���I�u�W�F�N�g
	*/
	void GameObject::SetParent(GameObject* parent)
	{
		// �����e�����Ă����ꂽ�ꍇ�͉������Ȃ�
		if (parent == this->parent) {
			return;
		}

		// �ʂ̐e������ꍇ���̐e�Ƃ̊֌W����������
		if (this->parent) {
			// �����̈ʒu������
			auto& c = this->parent->children;
			auto itr = std::find(c.begin(), c.end(), this);
			if (itr != c.end()) {
				c.erase(itr);	// �z�񂩂玩�����폜
			}
		}

		// �V���Ȑe�q�֌W��ݒ�
		if (parent) {
			parent->children.push_back(this);
		}
		this->parent = parent;
	}

	/**
	* �e�I�u�W�F�N�g��ݒ肷��
	*
	* @param parent �e�ɂ���Q�[���I�u�W�F�N�g
	*/
	void GameObject::SetParent(const GameObjectPtr& parent)
	{
		SetParent(parent.get());
	}

	/**
	* �Q�[���I�u�W�F�N�g����폜�\��̃R���|�[�l���g���폜����
	*/
	void GameObject::RemoveDestroyedComponent()
	{
		// �R���|�[�l���g�������Ă��Ȃ���Ή������Ȃ�
		if (components.empty())
		{
			return;
		}

		// �j���\��̗L���ŃR���|�[�l���g�𕪂���
		const auto iter = std::stable_partition(
			components.begin(), components.end(),
			[](const auto& p) {return !p->IsDestroyed(); });

		// �j���\��̃R���|�[�l���g��ʂ̔z��Ɉړ�
		std::vector<ComponentPtr> destroyList(
			std::move_iterator(iter),
			std::move_iterator(components.end()));

		// �z�񂩂�ړ��ς݃R���|�[�l���g���폜
		components.erase(iter, components.end());

		// �R���C�_�[��colliders�ɂ��o�^����Ă���̂ŁA��������폜����K�v������
		const auto iter2 = std::remove_if(
			colliders.begin(), colliders.end(),
			[](const auto& p) {return p->IsDestroyed(); });
		colliders.erase(iter2, colliders.end());

		// �j���\��̃R���|�[�l���g��OnDestroy�����s
		for (auto& e : destroyList)
		{
			e->OnDestroy();
		}
	}// ������destoryList�̎����������폜�����
}