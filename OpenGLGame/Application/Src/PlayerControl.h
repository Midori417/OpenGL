/**
* @file Player.h
*/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "ControlOwner.h"
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;

class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* プレイヤー操作
*/
class PlayerControl : public ControlOwner
{
public:

	// コンストラクタ・デストラクタ
	PlayerControl() = default;
	virtual ~PlayerControl() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* 毎フレーム実行(Updateより後)
	*/
	virtual void LateUpdate() override;

public:
	
	// カメラ
	LookOnCameraPtr lookOnCamera;
};


#endif // !PLAYER_H_INCLUDED
