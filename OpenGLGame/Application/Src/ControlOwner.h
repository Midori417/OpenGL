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
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* 操作
*/
class ControlOwner : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

	/**
	* 自チームのHpを取得
	*/
	int& GetTeumHp() const
	{
		return *myTeumHp;
	}

	/**
	* 自チームのHpを設定
	*/
	void SetTeumHP(int* teumHP)
	{
		myTeumHp = teumHP;
	}

	/**
	* チーム体力を減らす
	*/
	void TeumHpSud();

	/**
	* 終了
	*/
	virtual void Finish(){}


protected:

	/**
	* 機体の更新
	*/
	virtual void MsUpdate() {}

public:

	// カメラ
	LookOnCameraPtr lookOnCamera;

	// 距離
	float distance = 0;

	// 処理を開始するか
	bool isStart = false;

	// 使う機体
	MsList ms = MsList::None;

	// 自分以外のオーナー
	ControlOwner* otherOwner;

	// 自分の機体
	BaseMsPtr myMs;

protected:

	// 自分のMSの死亡の有無
	bool isMsDeath = false;

	// 自チームの体力
	int* myTeumHp;
};


#endif // !CONTROLOWNER_H_INCLUDED
