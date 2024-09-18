/**
* @file Global.h
*/
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include "MsList.h"
#include <memory>
#include <vector>

// �`�[���ő�̗�
static const int teamMaxHp = 6000;

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
* �p�C���b�g���
*/
struct PilotInfo
{
	// �`�[��Id
	// 0 = �o�ꖳ��, 1 = �`�[���P, 2 = �`�[��2
	int teamId = 0;

	// PlayerId
	// 0 = �l�� , 1 = CPU
	int playerId = -1;

	// �g���@��
	MsList ms;
};

/**
* �o�g�����
*/
struct BattleInfo
{
	// �`�[��1�̗�
	// -1 = ��
	int team1Hp = teamMaxHp;

	// �`�[��2�̗�
	// -1 = ��
	int team2Hp = teamMaxHp;

	// �Q�[������
	// -1 = ��
	float time = 0;

	// �p�C���b�g���
	std::vector<PilotInfo> pilotInfos;
};

#endif // !GLOBAL_H_INCLUDED