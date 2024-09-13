/**
* @file BattleSettingInfo.h
*/
#ifndef BATTLESETTINGINFO_H_INCLUDED
#define BATTLESETTINGINFO_H_INCLUDED
#include "MSList.h"
#include <memory>
#include <vector>

// �`�[���ő�̗�
static const int teumMaxHp = 6000;

// �ő�v���C���[��
static const int playerMax = 4;

/**
* ���s���
*/
enum class VictoryState
{
	// �����Ȃ�
	None,

	// ����
	Win,

	// �s�k
	Lose,

	// ��������
	Drow,
};

/**
* �R���g���[�����
*/
struct ControlInfo
{
	// �`�[��Id
	// 0 = �o�ꖳ��, 1 = �`�[���P, 2 = �`�[��2
	int teumId = -1;

	// PlayerId
	// 0 = �l�� , 1 = CPU
	int playerId = -1;

	// �g��MS
	MsList ms;
};
using ControlInfoPtr = std::shared_ptr<ControlInfo>;

/**
* �o�g���ݒ���
*/
struct BattleSettingInfo
{
	// �`�[��1�̗�
	// -1 = ��
	int teum1Hp = teumMaxHp;

	// �`�[��2�̗�
	// -1 = ��
	int teum2Hp = teumMaxHp;

	// �Q�[������
	// -1 = ��
	float time = 0;

	// �R���g���[�����z��
	std::vector<ControlInfoPtr> controlInfo;
};
using BattleSettingInfoPtr = std::shared_ptr<BattleSettingInfo>;

#endif // !BATTLESETTINGINF_H_INCLUDED