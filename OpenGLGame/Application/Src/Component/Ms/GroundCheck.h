/**
* @file GroundCheck.h
*/
#ifndef GROUNDCHECK_H_INCLUDED
#define GROUNDCHECK_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

/**
* �n�ʃ`�F�b�N
*/
class GroundCheck : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	GroundCheck() = default;

private: // �C�x���g

	/**
	* Update�̑O�Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	*/
	virtual void OnCollisionEnter(const CollisionPtr& other) override;

	/**
	* ���̃R���W�������痣�ꂽ�Ƃ��Ɏ��s
	*/
	virtual void OnCollisionExit(const CollisionPtr& other) override;

private:
	
	// ���b�V�������_���[
	MeshRendererPtr renderer;
	
	// true�Ȃ�n�ʂɂ��Ă���
	bool isGround = false;

public:

	// �R���C�_�[��\�����邩
	bool isRender = true;
};

#endif // !GROUNDCHECK_H_INCLUDED
