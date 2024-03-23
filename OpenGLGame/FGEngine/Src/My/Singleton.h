/**
* @file Singleton.h
*/
#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED
#include <memory>

namespace FGEngine
{
	/**
	* �V���O���g�����N���X
	*/
	template <typename T>
	class Singleton
	{
	protected:

		// �R���X�g���N�^
		Singleton() = default;

	public:

		// �f�X�g���N�^
		virtual ~Singleton() = default;

		// �R�s�[�Ƒ�����֎~
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		/**
		* ���g�̃C���X�^���X���擾����
		* �Ȃ���΍쐬����
		* 
		* @return ���g�̃C���X�^���X
		*/
		static std::shared_ptr<T> GetInstance()
		{
			auto ptr = instance.lock();
			if (!ptr)
			{
				ptr = std::shared_ptr<T>(new T{});
				instance = std::weak_ptr<T>(ptr);
			}
			return instance.lock();
		}

	private:

		static std::weak_ptr<T> instance;	// ���g�̃C���X�^���X
	};

	// �X�^�e�B�b�N�ϐ���������
	template <typename T>
	inline std::weak_ptr<T> Singleton<T>::instance;

}

#endif // !SINGLETON_H_INCLUDED
