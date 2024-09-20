/**
* @file GroundCheck.h
*/
#ifndef GROUNDCHECK_H_INCLUDED
#define GROUNDCHECK_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

/**
* 地面チェック
*/
class GroundCheck : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	GroundCheck() = default;

private: // イベント

	/**
	* Updateの前に実行
	*/
	virtual void Start() override;

	/**
	* 他のコリジョンに触れたときに実行
	*/
	virtual void OnCollisionEnter(const CollisionPtr& other) override;

	/**
	* 他のコリジョンから離れたときに実行
	*/
	virtual void OnCollisionExit(const CollisionPtr& other) override;

private:
	
	// メッシュレンダラー
	MeshRendererPtr renderer;
	
	// trueなら地面についている
	bool isGround = false;

public:

	// コライダーを表示するか
	bool isRender = true;
};

#endif // !GROUNDCHECK_H_INCLUDED
