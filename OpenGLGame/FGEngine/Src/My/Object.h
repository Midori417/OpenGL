/**
* @file Object.h
*/
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <memory>
#include <vector>
#include <string>
#include "VecMath.h"

namespace FGEngine
{
	// ��s�錾
	class Object;
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;

	/**
	* ���ׂẴI�u�W�F�N�g�̊��N���X
	*/
	class Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Object() = default;
		virtual ~Object() = default;

		/**
		* �I�u�W�F�N�g�̖��O���擾����
		*/
		std::string ToString() const;

		/**
		* �I�u�W�F�N�g�̖��O��ݒ肷��
		*
		* @param value �ݒ肷�閼�O
		*/
		void SetName(const std::string& value);


		/**
		* �I�u�W�F�N�g�̏��
		*/
		enum class HideFlag
		{
			None,		// �ʏ�
			Destory,	// �j��
		};

		/**
		* �I�u�W�F�N�g�̏�Ԃ��擾����
		*/
		HideFlag GetHideFlag() const;


		/**
		* �I�u�W�F�N�g�𐶐�����
		*/
		template<typename T>
		std::shared_ptr<T> Instantate(const std::string& name);

		/**
		* �Q�[���I�u�W�F�N�g�𐶐�����
		*/
		GameObjectPtr Instantate(const std::string& name, const TransformPtr& transform);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* �I�u�W�F�N�g�̏�Ԃ�j��\��ɂ���
		*
		* @param obj �j���\��ɂ���I�u�W�F�N�g
		* @parma t	�j�󂳂�鎞��
		*/
		void Destory(Object* obj, float t = 0);

		/**
		* �j���\�肩�擾
		* 
		* @return true �j���\��
		* @return false �j���\�肶��Ȃ�
		*/
		bool IsDestroyed() const
		{
			return isDestoryed;
		}

	private:

		std::string name;	// �I�u�W�F�N�g�̖��O
		bool isDestoryed;	// �j��\�肩
		float destoryTime = 0;	// �j�󎞊�
		HideFlag hideFlag = HideFlag::None;	// �I�u�W�F�N�g�̏��

	};
	using ObjectPtr = std::shared_ptr<Object>;
	using ObjectList = std::vector<ObjectPtr>;
}
#endif // !OBJECT_H_INCLUDED
