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

	protected:

		// �L���ł���΍X�V����A�����ł���΍X�V����܂���
		bool enabled = true;
	};
}

#endif // !FGENGINE_BEHAVIOUR_H_INCLUDED
