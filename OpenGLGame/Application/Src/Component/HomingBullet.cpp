/**
* @file HomingBullet.h
*/
#include "HomingBullet.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Other/Time.h"

#include "BaseMs.h"

/**
* 最初に実行
*/
void HomingBullet::Start()
{
    OwnerObject()->Destroy(destroyTime);
    shotPos = GetTransform()->position;
}

/**
* 毎フレーム実行
*/
void HomingBullet::Update()
{
    isHoming = HomingCheck();

    if (isHoming)
    {
        Homing();
    }
    else
    {
        GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
    }
}

/**
* クローンを作成する
*/
ComponentPtr HomingBullet::Clone() const
{
    std::shared_ptr<HomingBullet> p = std::make_shared<HomingBullet>();

    p->damage = this->damage;
    p->speed = this->speed;
    p->destroyTime = this->destroyTime;
    p->homingPower = this->homingPower;

    return p;
}

/**
* ホーミング可能かチェック
*
* @retval true	ホーミング可能
* @retval flase	ホーミング不可
*/
bool HomingBullet::HomingCheck() const
{
    if (!target)
    {
        return false;
    }
    else
    {
        // ターゲットがホーミング不可状態
        //if (!target->HomingCancel())
        //{
        //    return false;
        //}
    }
    return true;
}

/**
* ホーミング処理
*/
void HomingBullet::Homing() const
{
    // 方向ベクトルを計算
    Vector3 direction = (target->GetTransform()->position - shotPos);

    // 目標の回転を計算
    Quaternion targetRotation = Quaternion::LookRotation(direction);

    // ミサイルの回転を目標の回転に近づける
    GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, homingPower);

    GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
}

/**
* パラメータを設定
*
* @param damage			与えるダメージ
* @param speed			弾の速さ
* @param destroyTime	消滅するまでの時間
* @param homingPower	誘導力
*/
void HomingBullet::SetParamater(float damage, float speed, float destroyTime, float homingPower)
{
    this->damage = damage;
    this->speed = speed;
    this->destroyTime = destroyTime;
    this->target = target;
    this->homingPower = homingPower;
}

/**
* ターゲット機体を設定
* 設定しない場合まっすぐ飛ぶ弾になる
*/
void HomingBullet::SetTarget(BaseMs* target)
{
    this->target = target;
}
