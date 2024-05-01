/**
* @file GameObject.h
*/
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "Renderer.h"
#include "Collision.h"
#include "Texture.h"
#include "VecMath.h"
#include "Color.h"

#include <string>
#include <vector>
#include <memory>
#include <type_traits>


// ��s�錾
class Engine;
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = std::vector<GameObjectPtr>;
class Transform;
using TransformPtr = std::shared_ptr<Transform>;

/**
* �`��̏���
*/
enum RenderQueue
{
	RenderQueue_geometry = 2000,	// ��ʓI�Ȑ}�`
	RenderQueue_transparent = 3000,	// �������Ȑ}�`
	RenderQueue_overlay = 4000,		// UI�A�S��ʃG�t�F�N�g
	RenderQueue_max = 5000,			// �L���[�̍ő�l
};

/**
* �Q�[���ɓo�ꂷ��l�X�ȃI�u�W�F�N�g�̊�{�N���X
*/
class GameObject : public Object
{
	friend Engine;
public:

	GameObject() = default;
	virtual ~GameObject();

	// �R�s�[�Ƒ�����֎~
	GameObject(GameObject&) = delete;
	GameObject& operator=(GameObject&) = delete;

	// === �C�x���g���� === //

	// �ŏ���Update�̒��O�ŌĂяo�����
	virtual void Start();

	// ���t���[�����Ăяo��
	virtual void Update();

	virtual void LateUpdate();

	// �Փ˂����Ƃ��ɌĂяo��
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other);

	// �폜���ꂽ�Ƃ��̌Ăяo��
	virtual void OnDestroy();

	// �e�I�u�W�F�N�g���擾����
	GameObject* GetParent() const {
		return parent;
	}

	// �e�I�u�W�F�N�g��ݒ肷��
	void SetParent(GameObject* parent);
	void SetParent(const GameObjectPtr& parent);

	// �q�I�u�W�F�N�g�̐����擾����
	size_t GetChildCount() const {
		return children.size();
	}

	// �q�I�u�W�F�N�g���擾����
	GameObject* GetChild(size_t index)const {
		return children[index];
	}


	// �Q�[���I�u�W�F�N�g�ɃR���|�[�l���g��ǉ�����
	template<class T>
	std::shared_ptr<T> AddComponent() 
	{
		auto p = std::make_shared<T>();
		if constexpr (std::is_base_of_v<Collider, T>) {
			colliders.push_back(p);
		}
		if constexpr (std::is_base_of_v<Renderer, T>)
		{
			renderer = p;
		}
		if constexpr (std::is_base_of_v<Transform, T>)
		{
			transform = p;
		}
		p->gameObject = this;
		p->transform = transform.get();
		components.push_back(p);
		p->Awake();
		return p;
	}

	// �R���|�[�l���g����������
	template<class T>
	std::shared_ptr<T> GetComponent() const {
		for (auto& e : components) {
			// shared_ptr�̏ꍇ��dynamic_cast�łȂ�dynamic_pointer_cast���g��
			auto p = std::dynamic_pointer_cast<T>(e);
			if (p) {
				return p;
			}
		}
		return nullptr;
	}

	// �����̐e�̃I�u�W�F�N�g�̃R���|�[�l���g������
	template<class T>
	std::shared_ptr<T> GetComponentParent() const {
		if (parent == nullptr) {
			return nullptr; // �e�����Ȃ�
		}
		return parent->GetComponent<T>();
	}


	// �����̎q���̃I�u�W�F�N�g�̃R���|�[�l���g������
	template<class T>
	std::shared_ptr<T> GetComponenChildren() const {
		if (children.empty()) {
			return nullptr; // �q�������Ȃ�
		}
		for (auto x : children) {
			
			auto t = x->GetComponent<T>();
			// �R���|�[�l���g�����������甲����
			if (t != nullptr) {
				return t;
			}
		}
		return nullptr; // ������Ȃ�����
	}

	// �Q�[���I�u�W�F�N�g����j���\��̃R���|�[�l���g���폜����
	void RemoveDestroyedComponent();


public:

	std::string tag = "Untagged";			// �^�O
	TransformPtr transform;
	RendererPtr renderer;
	int renderQueue = RenderQueue_geometry;	// �`�揇
	bool isGrounded = false;			// ����ƂȂ镨�̂̏�ɍڂ��Ă����true

private:

	Engine* engine = nullptr;				// �G���W���̃A�h���X
	bool isActive = true;
	bool isDestroyed = false;				// ���S�t���O
	GameObject* parent = nullptr;			// �e�I�u�W�F�N�g
	std::vector<GameObject*> children;		// �q�I�u�W�F�N�g
	std::vector<ComponentPtr> components;	// �R���|�[�l���g�z��
	std::vector<ColliderPtr> colliders;	// �R���C�_�[�z��

public:

	// �Q�[���G���W�����擾
	Engine* GetEngine() const 
	{
		return engine;
	}

	// �Q�[���I�u�W�F�N�g���G���W������폜����
	void Destory()
	{
		isDestroyed = true;
	}

	// �Q�[���I�u�W�F�N�g���j������Ă��邩���擾 �j������Ă���true
	bool IsDestroyed() const
	{
		return isDestroyed;
	}

};
#endif // !GAMEOBJECT_H_INCLUDED
