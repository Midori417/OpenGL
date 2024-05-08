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
* 操作
*/
class ControlOwner : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

public:

	// 使う機体
	MsList ms = MsList::None;

	// 自分以外のオーナー
	ControlOwner* otherOwner;

	// 自分の機体
	BaseMsPtr myMs;

	// 相手の機体
	BaseMsPtr enemyMs;
};


#endif // !CONTROLOWNER_H_INCLUDED
