/**
* @file HomingBullet.h
*/
#include "HomingBullet.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Other/Time.h"

#include "BaseMs.h"

/**
* �ŏ��Ɏ��s
*/
void HomingBullet::Start()
{
    OwnerObject()->Destroy(destroyTime);
    shotPos = GetTransform()->position;
}

/**
* ���t���[�����s
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
* �N���[�����쐬����
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
* �z�[�~���O�\���`�F�b�N
*
* @retval true	�z�[�~���O�\
* @retval flase	�z�[�~���O�s��
*/
bool HomingBullet::HomingCheck() const
{
    if (!target)
    {
        return false;
    }
    else
    {
        // �^�[�Q�b�g���z�[�~���O�s���
        //if (!target->HomingCancel())
        //{
        //    return false;
        //}
    }
    return true;
}

/**
* �z�[�~���O����
*/
void HomingBullet::Homing() const
{
    // �����x�N�g�����v�Z
    Vector3 direction = (target->GetTransform()->position - shotPos);

    // �ڕW�̉�]���v�Z
    Quaternion targetRotation = Quaternion::LookRotation(direction);

    // �~�T�C���̉�]��ڕW�̉�]�ɋ߂Â���
    GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, homingPower);

    GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
}

/**
* �p�����[�^��ݒ�
*
* @param damage			�^����_���[�W
* @param speed			�e�̑���
* @param destroyTime	���ł���܂ł̎���
* @param homingPower	�U����
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
* �^�[�Q�b�g�@�̂�ݒ�
* �ݒ肵�Ȃ��ꍇ�܂�������Ԓe�ɂȂ�
*/
void HomingBullet::SetTarget(BaseMs* target)
{
    this->target = target;
}
