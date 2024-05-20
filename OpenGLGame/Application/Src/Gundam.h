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

	/**
	* リロード更新
	*/
	void ReloadUpdate();

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
	virtual void CpuMove(const Vector2& moveAxis) override;

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

	/**
	* 生き返る
	*/
	virtual void Remove(const Vector3& removePos, float hp) override;

private:

	/**
	* ライフル構造体
	*/
	struct Rifle : NumWeapon
	{
		// 与えるダメージ
		float damage = 0;

		// 誘導力
		float homingPower = 0;

		// 速度
		float speed = 0;

		// 射撃状態か
		bool isNow = false;

		// 撃ったか
		bool isShot = false;

		// 停止して打つか
		bool isStopShot = false;

		// メッシュ
		StaticMeshPtr mesh;

		//シェーダ
		ShaderPtr shader;

		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
		}
	};
	std::shared_ptr<Rifle> rifle;

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
