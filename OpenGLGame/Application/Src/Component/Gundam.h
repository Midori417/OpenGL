/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"

/**
* �K���_��
*/
class Gundam : public BaseMs
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	Gundam() = default;

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �K���_���R���|�[�l���g���N���[��������
	* 
	* @return �N���[�����ꂽ�K���_���R���|�[�l���g
	*/
	virtual ComponentPtr Clone() const override;

private: // �ړ�

	/**
	* �ړ�
	* 
	* @param moveAxis �ړ�����
	*/
	void Move(const Vector2& moveAxis);

	/**
	* �W�����v
	*/
	void Jump(bool jumpBtn, const Vector2& moveAxis);

	/**
	* �_�b�V��
	*
	* @param dashBtn	�_�b�V���{�^���̏��
	* @param moveAxis	���͎�
	*/
	void Dash(bool dashBtn, const Vector2& moveAxis);

private: // �ˌ��U��

	/**
	* �U��(�r�[�����C�t��)
	*
	* @param acttion1Btn �A�N�V�����{�^��1�̏��
	*/
	void BeumRifle(bool acttion1Btn);

	/**
	* �U��2(�o�Y�[�J)
	*
	* @param acttion2Btn �A�N�V�����{�^��2�̏��
	*/
	void Bazooka(bool acttion2Btn);


private: // ����


private:

	/**
	*  �����Ă��镐��
	*/
	enum class HandWeapon
	{
		// ���C�t��
		Rifle,

		// �T�[�x��
		Sable,
	};
	// �����Ă��镐��
	HandWeapon handWeapon = HandWeapon::Rifle;

};

#endif // !GUNDAM_H_INCLUDED
