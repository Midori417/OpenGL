/**
* @file BaseSlash.h
*/
#ifndef BASESLASH_H_INCLUDED
#define BASESLASH_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* ��b�Ռ��j
*/
class BaseSlash : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BaseSlash() = default;
	virtual ~BaseSlash() = default;

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	*/
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// �^����_���[�W
	float damage = 0;

	// �^����_�E���l
	float downPower = 0;

	// ������ԗ�
	float blowPower = 0;

	// ������܂ł̎���
	float destoryTime = 0;

	struct Col
	{
		float radius = 1;
		Vector3 ceneter = Vector3::zero;
	};
	Col colllider;
};

#endif // !BASESLASH_H_INCLUDED