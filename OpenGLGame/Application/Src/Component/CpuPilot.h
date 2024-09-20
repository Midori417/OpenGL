/**
* @file CpuPilot.h
*/
#ifndef CPUPILOT_H_INCLUDED
#define CPUPILOT_H_INCLUDED
#include "BasePilot.h"
#include "FGEngine/Math/Vector2.h"

/**
* �R���s���[�^�p�C���b�g
*/
class CpuPilot : public BasePilot
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CpuPilot() = default;

private:	// �C�x���g

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}
};

#endif // !CPUPILOT_H_INCLUDED