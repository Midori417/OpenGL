/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;
#include "../GameInput.h"

// 先行宣言
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class UIWeapon;
using UIWeaponPtr = std::shared_ptr<UIWeapon>;

/**
* MSの基底クラス
*/
class BaseMs : public GameEvent
{
protected: // 派生先で生成する

	/**
	* デフォルトコンストラクタ
	*/
	BaseMs() = default;

public:

	/**
	* 機体入力を設定
	*/
	void SetMsInput(const GameInputPtr& gameInput);

	/**
	* カメラのトランスフォームを設定する
	*/
	void SetTrsCamera(const TransformPtr& camera);

	/**
	* ターゲット機体を設定
	*/
	void SetTargetMs(const BaseMsPtr& targetMs);

protected:

	/**
	* 必要なコンポーネント、変数が取得できているかチェック
	*/
	virtual bool Check() { return false; }

	/**
	* カメラ正面を基準に移動方向を計算する
	*/
	Vector3 MoveForward(const Vector2& moveAxis);

	/**
	* 共通コンポーネントの取得
	*/
	void ComponentGet();

	/**
	* カメラのトランスフォームを取得する
	*/
	Transform* GetTrsCamera() const;

	/**
	* ターゲット機体を取得
	*/
	BaseMs* GetTarget() const;

private:

	// カメラトランスフォーム
	Transform* trsCamera = nullptr;

	// ターゲット機体
	BaseMs* targetMs = nullptr;

protected:

	// 機体入力
	GameInputPtr msInput = nullptr;

	// リジッドボディ
	RigidbodyPtr rb = nullptr;

	// レンダラー
	GltfMeshRendererPtr renderer = nullptr;

	// アニメータ
	AnimatorPtr anim = nullptr;

protected:

	/**
	* 基礎パラメータ
	*/
	struct Paramater
	{
		// 耐久力の最大値
		int durabilityMax = 0;

		// 現在の耐久力
		int durability = 0;

		// 戦力値
		int strengthValue = 0;
	};
	Paramater paramater;

	/**
	* 移動パラメータ
	*/
	struct MoveParamater
	{
		// 移動速度
		float speed = 0;

		// 旋回速度
		float rotationSpeed = 0;
	};
	MoveParamater move;

	struct DashParamater
	{

	};

	struct JumpParamater
	{

	};
};

#endif // !BASEMS_H_INCLUDED
