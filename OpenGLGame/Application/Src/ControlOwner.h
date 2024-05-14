/**
* @file ControlOwner.h
*/
#ifndef CONTROLOWNER_H_INCLUDED
#define CONTROLOWNER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
#include "MsLilst.h"

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;

/**
* ����
*/
class ControlOwner : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

public:

	// �������J�n���邩
	bool isStart = false;

	// �g���@��
	MsList ms = MsList::None;

	// �����ȊO�̃I�[�i�[
	ControlOwner* otherOwner;

	// �����̋@��
	BaseMsPtr myMs;
};


#endif // !CONTROLOWNER_H_INCLUDED
