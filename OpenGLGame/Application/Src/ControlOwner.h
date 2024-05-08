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

	// �g���@��
	MsList ms = MsList::None;

	// �����ȊO�̃I�[�i�[
	ControlOwner* otherOwner;

	// �����̋@��
	BaseMsPtr myMs;

	// ����̋@��
	BaseMsPtr enemyMs;
};


#endif // !CONTROLOWNER_H_INCLUDED
