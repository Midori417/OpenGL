/**
* @file Component.h
*/
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include <memory>

// ��s�錾
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
class Component;
using ComponentPtr = std::shared_ptr<Component>;
class Transform;

/**
* �R���|�[�l���g�̊��N���X
*/
class Component
{
	friend GameObject;
public:

	Component() = default;
	virtual ~Component() = default;

	// �R���|�[�l���g�̏��L��
	GameObject* GetGameObject() const {
		return gameObject;
	}

	// �R���|�[�l���g���Q�[���I�u�W�F�N�g����폜����
	void Desotroy() {
		isDestroyed = true;
	}

	// �R���|�[�l���g���j���\�肩�擾���� true���Ɣj���\��
	bool IsDestroyed() const {
		return isDestroyed;
	}

	// ���g�̏��L�҂̃R���|�[�l���g���擾
	template<class T>
	inline std::shared_ptr<T> GetComponent() const;

	// �e�̃R���|�[�l���g���擾
	template<class T>
	inline std::shared_ptr<T> GetComponentParent() const;

	// �q���̃R���|�[�l���g���擾
	template<class T>
	inline std::shared_ptr<T> GetComponentChildren()const;

	// �Q�[���I�u�W�F�N�g�ɒǉ����ꂽ�Ƃ�����Ăяo�����
	virtual void Awake() {}

	// �ŏ���Update�̒��O�ŌĂяo�����
	virtual void Start() {}

	// ���t���[�����Ăяo�����
	virtual void Update() {}

	// ���t���[�����Ăяo�����(Update��肠��)
	virtual void LateUpdate() {}

	// �Փ˂��N�����Ƃ��ɌĂяo�����
	virtual void OnCollision(const ComponentPtr& slef, const ComponentPtr& other) {}

	// �Q�[���I�u�W�F�N�g���G���W�����폜�����Ƃ��̌Ăяo�����
	virtual void OnDestroy() {}

public:

	Transform* transform = nullptr;

private:

	GameObject* gameObject = nullptr; // �R���|�[�l���g�̏��L��
	bool isActive = true;
	bool isStarted = false;		// Start�����s���ꂽ��true�ɂȂ�
	bool isDestroyed = false;	// Destroy�����s���ꂽ��true�ɂȂ�
};
#endif // !COMPONENT_H_INCLUDED
