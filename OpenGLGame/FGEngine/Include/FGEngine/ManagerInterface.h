/**
* @file ManagerInterface.h
*/
#ifndef FGENGINE_MANAGERINTERFACE_H_INCLUDED
#define FGENGINE_MANAGERINTERFACE_H_INCLUDED
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class EngineCore;

	/**
	* �}�l�[�W���[�̊��N���X
	* ���̃N���X�����̉����Ȃ����߃R���X�g���N�^��protected
	*/
	class ManagerInterface
	{
		friend EngineCore;
	protected:

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		ManagerInterface() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~ManagerInterface() = default;

	public:

		/**
		* ������
		*
		* @retval 0		����ɏ�����
		* @retval 0�ȊO	�G���[����
		*/
		virtual int Initialize() { return 0; }

		/**
		* ��Ԃ̍X�V
		*/
		virtual void Update() {}

		/**
		* �I��
		*/
		virtual void Finaliz() {}
	};
	using ManagerInterfacePtr = std::shared_ptr<ManagerInterface>;
}

#endif // !FGENGINE_MANAGERINTERFACE_H_INCLUDED
