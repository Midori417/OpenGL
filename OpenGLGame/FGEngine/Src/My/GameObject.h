/**
* @file GameObject.h
*/
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Object.h"

#include <string>
#include <vector>
#include <memory>
#include <type_traits>

namespace FGEngine
{

	// ��s�錾
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;
	class Renderer;
	using RendererPtr = std::shared_ptr<Renderer>;
	class MonoBehaviour;
	using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;

	/**
	* �Q�[���ɓo�ꂷ��l�X�ȃI�u�W�F�N�g�̊�{�N���X
	*/
	class GameObject : public Object
	{
		friend ObjectManager;
	public:

		GameObject() = default;
		virtual ~GameObject() = default;

		// �R�s�[�Ƒ�����֎~
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;



		// �Q�[���I�u�W�F�N�g�ɃR���|�[�l���g��ǉ�����
		template<class T>
		std::shared_ptr<T> AddComponent();

		// �R���|�[�l���g����������
		template<class T>
		std::shared_ptr<T> GetComponent() const;


	

	public:

		std::string tag = "Untagged";			// �^�O
		TransformPtr transform;
		RendererPtr renderer;

	private:

		bool isActive = true;
		std::vector<ComponentPtr> components;	// �R���|�[�l���g�z��
		std::vector<MonoBehaviourPtr> monoBehabiours;	
		std::vector<ColliderPtr> colliders;	// �R���C�_�[�z��

	public:

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}
#endif // !GAMEOBJECT_H_INCLUDED
