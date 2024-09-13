/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

/**
* �t�F�[�h���J�n����
*/
void FadeOut::FadeStart()
{
	if (!image)
	{
		// �C���[�W�R���|�[�l���g���ݒ肳��Ă��Ȃ���Έ�x�擾���Ă݂�
		image = GetComponent<Image>();
	}

	// �擾�ł��Ă���΃X�^�[�g����
	if (image)
	{
		isStart = true;
		image->isActive = true;
	}
}

/**
* �t�F�[�h���J�n���Ă��邩�擾
*
* @retval true	�n�߂��Ă���
* @retval false �n�܂��Ă��Ȃ�
*/
bool FadeOut::IsFadeStart() const
{
	return isStart;
}

/**
* �t�F�[�h�̏󋵂��擾
*
* @retval true	�t�F�[�h�A�E�g����
* @retval false	�t�F�[�h���܂��̓t�F�[�h�J�n���Ă��Ȃ�
*/
bool FadeOut::IsFadeOut() const
{
	return isFadeOut;
}

/**
* Update���n�܂�O�Ɉ�x���s
*/
void FadeOut::Start()
{
	// �C���[�W�R���|�[�l���g���擾���Ă݂�
	image = GetComponent<Image>();

	// �擾�ł��Ȃ���΃C���[�W�R���|�[�l���g��ǉ�����
	if (!image)
	{
		image = OwnerObject()->AddComponent<Image>();
		image->texture = AssetManager::GetInstance()->GetTexture("white");
		image->color = Color::black;
		image->SetWindowSize();

		// �����ɂ��Ă��������̂ŃA���t�@�l���[���ɂ���
		image->color.a = 0;
		// �t�F�[�h����܂ŏ������Ăق����Ȃ��̂Ŕ�A�N�e�B�u��Ԃɂ���
		image->isActive = false;
	}
}

/**
* ���t���[�����s
*/
void FadeOut::Update()
{
	if (!image)
	{
		// �C���[�W�R���|�[�l���g���擾�ł��Ă��Ȃ���Ή������Ȃ�
		return;
	}

	// �t�F�[�h���J�n���Ă��Ȃ��܂��̓t�F�[�h�����łɏI�����Ă���ꍇ�͍X�V���~�߂�
	if (!isStart || isFadeOut)
	{
		return;
	}

	// �C���[�W�̃A���t�@�l�𑝉�
	image->color.a += speed * Time::DeltaTime();

	// �C���[�W�����S�ɕ\�����ꂽ��t�F�[�h���I������
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true;
	}
}

/**
* �t�F�[�h�A�E�g�R���|�[�l���g���N���[������
*
* @return �N���[�������t�F�[�h�A�E�g�R���|�[�l���g
*/
ComponentPtr FadeOut::Clone() const
{
	auto ptr = std::make_shared<FadeOut>();

	ptr->isActive = this->isActive;
	ptr->image = this->image;
	ptr->isStart = this->isStart;
	ptr->isFadeOut = this->isFadeOut;
	ptr->speed = this->speed;

	return ptr;
}
