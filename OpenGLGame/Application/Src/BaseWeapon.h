/**
* @file BaseWeapon.h
*/
#ifndef BASEWEAPON_H_INCLUDED
#define BASEWEAPON_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* 武装の基底クラス
*/
class BaseWeapon
{
public:

	// コンストラクタ・デストラクタ
	BaseWeapon() = default;
	virtual ~BaseWeapon() = default;

	/**
	* 武装の初期化
	*/
	virtual void Initialize(){}

public:

	// 武装の名前
	std::string name = "";
};

/**
* UIの表示する武装の基底クラス
*/
class UIWeapon : public BaseWeapon
{
public:

	// コンストラクタ・デストラクタ
	UIWeapon() = default;
	virtual ~UIWeapon() = default;

public:

	// 残弾マックス
	float amoMax = 0;

	// 残弾
	float amo = 0;

	// リロードタイマー
	float reloadTimer = 0;

	// リロードタイム
	float reloadTime = 0;

	// 武器アイコン
	TexturePtr iconTexture;
};
/**
* 射撃武装
*/
class ShotWeapon : public BaseWeapon
{
public:

	// コンストラクタ・デストラクタ
	ShotWeapon() = default;
	virtual ~ShotWeapon() = default;

public:

	/**
	* 弾
	*/
	struct Bullet
	{
		// 与えるダメージ
		float damage = 0;

		// 誘導力
		float homingPower = 0;

		// 与えるダウン値
		float downPower = 0;

		// 速度
		float speed = 0;

		// メッシュ
		StaticMeshPtr mesh;

		//シェーダ
		ShaderPtr shader;

		// 影シェーダ
		ShaderPtr shadowShader;
	};
	Bullet bullet;
};

/**
* 射撃武装(UI)
*/
class ShotWeaponUI : public UIWeapon
{
public:

	// コンストラクタ・デストラクタ
	ShotWeaponUI() = default;
	virtual ~ShotWeaponUI() = default;

public:

	ShotWeapon::Bullet bullet;
};
#endif // !BASEWEAPON_H_INCLUDED
