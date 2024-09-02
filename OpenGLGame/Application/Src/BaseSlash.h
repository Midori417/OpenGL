/**
* @file BaseSlash.h
*/
#ifndef BASESLASH_H_INCLUDED
#define BASESLASH_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* 基礎衝撃破
*/
class BaseSlash : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	BaseSlash() = default;
	virtual ~BaseSlash() = default;

private:

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 他のコリジョンに触れたときに実行
	*/
	virtual void OnCollisionEnter(const CollisionPtr other) override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	// 与えるダメージ
	float damage = 0;

	// 与えるダウン値
	float downPower = 0;

	// 吹き飛ぶ力
	float blowPower = 0;

	// 消えるまでの時間
	float destoryTime = 0;

	struct Col
	{
		float radius = 1;
		Vector3 ceneter = Vector3::zero;
	};
	Col colllider;

	std::string filenameSE;

private:

	AudioSourcePtr audioSource;
};

#endif // !BASESLASH_H_INCLUDED
