/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"

/**
* ガンダム
*/
class Gundam : public BaseMs
{
public:

	// コンストラクタ・デストラクタ
	Gundam() = default;
	virtual ~Gundam() = default;

	/**
	* 最初に実行
	*/
	virtual void Awake() override;

private:


	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

public:

	/**
	* 移動
	* 
	* @param moveAxis 入力軸
	*/
	virtual void Move(const Vector2& moveAxis) override;

	/**
	* CPU移動
	*/
	virtual void CpuMove() override;

	/**
	* ジャンプ
	*/
	virtual void Jump(bool isJump, const Vector2& moveAxis) override;

	/**
	* ダッシュ
	*/
	virtual void Dash(bool isDash, const Vector2& moveAxis) override;

	/**
	* 攻撃(ビームライフル)
	*/
	virtual void Attack1(bool attackKey) override;

	/**
	* ダメージ
	* 
	* @param damage 与えるダメージ
	*/
	virtual void Damage(float damage) override;

private:

	struct Rifle : NumWeapon
	{
		bool isShot = false;

		// メッシュ
		StaticMeshPtr mesh;

		//シェーダ
		ShaderPtr shader;
	};
	std::shared_ptr<Rifle> rifle;

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
