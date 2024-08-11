/**
* @file Behaviour.h
*/
#ifndef FGENGINE_BEHAVIOUR_H_INCLUDED
#define FGENGINE_BEHAVIOUR_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �R���|�[�l���g��L�������@�\��ǉ��������N���X
	*/
	class Behaviour : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Behaviour() = default;
		virtual ~Behaviour() = default;

		// �I�u�W�F�N�g��Ԃ�ݒ肷��
		virtual void SetEnable(bool value)
		{
			enabled = value;
		}

		bool GetEnabled() const
		{
			return enabled;
		}


	protected:

		// �L���ł���΍X�V����A�����ł���΍X�V����܂���
		bool enabled = true;
	};
}

#endif // !FGENGINE_BEHAVIOUR_H_INCLUDED
