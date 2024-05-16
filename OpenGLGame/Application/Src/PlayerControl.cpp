/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::ResouceSystem;

/**
* �ŏ��Ɏ��s
*/
void PlayerControl::Start()
{
	// ���\�[�X�}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();

	// UI�̍쐬
	{
		// ���g�̏��w�i���쐬
		{
			auto myInfoBack = Instantate("MysInfo", Vector3(-725, 330, 0));
			imgMyInfoBack = myInfoBack->AddComponent<Image>();
			imgMyInfoBack->texture = resManager->GetTexture("PlayerInfo");
			imgMyInfoBack->size = Vector2(imgMyInfoBack->texture->GetWidth() * 1.4f,
				imgMyInfoBack->texture->GetHeight() * 1.1f);
		}
		// ���g�̋@�̗̂̑͂��쐬
		{
			auto myMsHp = Instantate("MyMsHp", Vector3(-670, 280, 0));
			inMyMsHp = myMsHp->AddComponent<ImageNum>();
			inMyMsHp->space = -70;
			inMyMsHp->scale = 1.35f;
		}
		// �u�[�X�g�o�[�̔w�i���쐬
		{
			auto boostBarBack = Instantate("BoostBarBack", Vector3(250, 450, 0));
			imgBoostBarBack = boostBarBack->AddComponent<Image>();
			imgBoostBarBack->texture = resManager->GetTexture("BoostBarBack");
			imgBoostBarBack->size = imgBoostBarBack->texture->GetSize() * 1.2f;
		}
		// �u�[�X�g�o�[�̃I�[�o�[�q�[�g���쐬
		{
			auto boostBarOverHeat = Instantate("BoosetBarOverHeat", Vector3(245, 435, 0));
			imgBoostBarOverHeat = boostBarOverHeat->AddComponent<Image>();
			imgBoostBarOverHeat->texture = resManager->GetTexture("BoostBarOVERHEAT");
			imgBoostBarOverHeat->size = imgBoostBarOverHeat->texture->GetSize() * 1.2f;
			// �_�ŃR���|�[�l���g
			ibBoostBarOverHeat = boostBarOverHeat->AddComponent<ImageBlinking>();
			ibBoostBarOverHeat->image = imgBoostBarOverHeat;
			ibBoostBarOverHeat->speed = 5.0f;
		}
		// �u�[�X�g�o�[���쐬
		{
			auto boostBar = Instantate("BoostBar", Vector3(245, 435, 0));
			imgBoostBar = boostBar->AddComponent<Image>();
			imgBoostBar->texture = resManager->GetTexture("BoostBar");
			imgBoostBar->size = imgBoostBar->texture->GetSize() * 1.2f;
			imgBoostBar->fillAmout = 0.5f;
		}
		// �o���o�[�̔w�i���쐬
		{
			auto burstBarBack = Instantate("burstBarBack", Vector3(-250, 450, 0));
			imgBurstBarBack = burstBarBack->AddComponent<Image>();
			imgBurstBarBack->texture = resManager->GetTexture("BurstBarBack");
			imgBurstBarBack->size = imgBurstBarBack->texture->GetSize() * 1.2f;
		}
		// �o���o�[���쐬
		{
			auto burstBar = Instantate("burstBar", Vector3(-253, 428, 0));
			imgBurstBar = burstBar->AddComponent<Image>();
			imgBurstBar->texture = resManager->GetTexture("BurstBar");
			imgBurstBar->size = imgBurstBar->texture->GetSize() * 1.2f;
			imgBurstBar->fillType = Image::FillType::HorizontalInverse;
			imgBurstBar->fillAmout = 0.5f;
		}
		// ����UI
		{
			// ���g��MS�̕��킪��Ȃ牽�����Ȃ�
			if (!myMs->numWeapons.empty())
			{
				// �T�C�Y��\��
				imgWeaponBacks.reserve(myMs->numWeapons.size());
				int i = 0;
				for (auto x : myMs->numWeapons)
				{
					// ����A�C�R���̔w�i
					{
						auto weaponBack = Instantate("WeaponBack" + std::to_string(i), Vector3(765.0f, 400.0f + (-160.0f * i), 0));
						auto image = weaponBack->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBack");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBacks.push_back(image);
					}
					// ����̎c�e
					{
						auto weaponAmo = Instantate("WeapnAmo" + std::to_string(i), Vector3(715.0f, 410.0f + (-160.0f * i), 0));
						auto imageNum = weaponAmo->AddComponent<ImageNum>();
						imageNum->scale = 0.8f;
						imageNum->space = -45;
						inWeaponAmos.push_back(imageNum);
					}
					// ����̎c�e�o�[
					{
						auto weaponAmoBar = Instantate("WeapnAmoBar" + std::to_string(i), Vector3(665.0f, 448.0f + (-160 * i), 0));
						auto image = weaponAmoBar->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBar");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBars.push_back(image);
					}
					// ����̃A�C�R��
					{
						auto weaponIcon = Instantate(x->name, Vector3(830, 410, 0));
						auto image= weaponIcon->AddComponent<Image>();
						image->texture = x->iconTexture;
						image->size = image->texture->GetSize() * 1.3f;
						imgWeapnIcons.push_back(image);
					}
					i++;
				}
			}
		}
		// �^�[�Q�b�g�}�[�N���쐬
		{
			// �^�[�Q�b�g�}�[�N�̃e�N�X�`�����擾
			texTargetMark01 = resManager->GetTexture("TargetMark01");
			texTargetMark02 = resManager->GetTexture("TargetMark02");
			texTargetMark03 = resManager->GetTexture("TargetMark03");

			auto targetMark = Instantate("TargetMark");
			imgTargetMark = targetMark->AddComponent<Image>();
			imgTargetMark->texture = texTargetMark01;
			imgTargetMark->size = imgTargetMark->texture->GetSize();
		}
		// �^�[�Q�b�g�̏����쐬
		{
			auto targetMark = Instantate("TargetMsInfo", Vector3(120, -70, 0));
			imgTargetInfo = targetMark->AddComponent<Image>();
			imgTargetInfo->texture = resManager->GetTexture("TargetMsInfo");
			imgTargetInfo->size = imgTargetInfo->texture->GetSize();
		}
		// �^�[�Q�b�g�̗̑̓o�[���쐬
		{
			auto targetHP = Instantate("TargetMsHpBar", Vector3(162, -75, 0));
			imgTargetHPBar = targetHP->AddComponent<Image>();
			imgTargetHPBar->texture = resManager->GetTexture("TargetMsHpBar");
			imgTargetHPBar->size = imgTargetHPBar->texture->GetSize();
		}
		// ���`�[���̗̑̓o�[���쐬
		{
			auto myTeumHpBar = Instantate("TeumHpBar", Vector3(-640, -465, 0));
			imgMyTeumHpBar = myTeumHpBar->AddComponent<Image>();
			imgMyTeumHpBar->texture = resManager->GetTexture("TeumHpBar");
			imgMyTeumHpBar->size = imgMyTeumHpBar->texture->GetSize() * 1.2f;
		}
		// ����`�[���̗̑̓o�[���쐬
		{
			auto teumEnemyBar = Instantate("TeumEnemyBar", Vector3(-620, -420, 0));
			imgEnemyTeumHpBar = teumEnemyBar->AddComponent<Image>();
			imgEnemyTeumHpBar->texture = resManager->GetTexture("TeumEnemyHpBar");
			imgEnemyTeumHpBar->size = imgEnemyTeumHpBar->texture->GetSize() * 1.2f;

		}
		// �`�[���̗̓t���[�����쐬
		{
			auto teumHp = Instantate("TeumHpFrame", Vector3(-635, -430, 0));
			imgTeumHpFrame = teumHp->AddComponent<Image>();
			imgTeumHpFrame->texture = resManager->GetTexture("TeumFrame");
			imgTeumHpFrame->size = imgTeumHpFrame->texture->GetSize() * 1.2f;
		}
		// ����(����ڂ�)
		{
			auto timer = Instantate("Timer", Vector3(800, -450, 0));
			imgTimer = timer->AddComponent<Image>();
			imgTimer->texture = resManager->GetTexture("Timer");
			imgTimer->size = imgTimer->texture->GetSize() * 1.2f;
		}
	}
	// UI���\���ɂ���
	{
		imgMyInfoBack->SetEnable(false);
		inMyMsHp->SetEnable(false);
		imgBoostBarBack->SetEnable(false);
		imgBoostBar->SetEnable(false);
		imgBoostBarOverHeat->SetEnable(false);
		imgBurstBarBack->SetEnable(false);
		imgBurstBar->SetEnable(false);
		for (auto x : imgWeaponBacks)
		{
			x->SetEnable(false);
		}
		for (auto x : inWeaponAmos)
		{
			x->SetEnable(false);
		}
		for (auto x : imgWeaponBars)
		{
			x->SetEnable(false);
		}
		for (auto x : imgWeapnIcons)
		{
			x->SetEnable(false);
		}
		imgTargetMark->SetEnable(false);
		imgTargetInfo->SetEnable(false);
		imgTargetHPBar->SetEnable(false);
		imgTeumHpFrame->SetEnable(false);
		imgMyTeumHpBar->SetEnable(false);
		imgEnemyTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
	}

	// �J�����Ɏ��g��MS��ݒ�
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

/**
* ���t���[�����s
*/
void PlayerControl::Update()
{
	if (!isStart)
	{
		return;
	}
	else
	{
		// UI��\��
		imgMyInfoBack->SetEnable(true);
		inMyMsHp->SetEnable(true);
		imgBoostBarBack->SetEnable(true);
		imgBoostBar->SetEnable(true);
		imgBurstBarBack->SetEnable(true);
		imgBurstBar->SetEnable(true);
		for (auto x : imgWeaponBacks)
		{
			x->SetEnable(true);
		}
		for (auto x : inWeaponAmos)
		{
			x->SetEnable(true);
		}
		for (auto x : imgWeaponBars)
		{
			x->SetEnable(true);
		}
		for (auto x : imgWeapnIcons)
		{
			x->SetEnable(true);
		}
		imgTargetMark->SetEnable(true);
		imgTargetInfo->SetEnable(true);
		imgTargetHPBar->SetEnable(true);
		imgTeumHpFrame->SetEnable(true);
		imgMyTeumHpBar->SetEnable(true);;
		imgEnemyTeumHpBar->SetEnable(true);
		imgTimer->SetEnable(true);
	}

	// �^�[�Q�b�g��MS���擾
	auto targetMs = otherOwner->myMs;
	myMs->SetTargetMS(targetMs.get());

	// ���������߂�
	if (targetMs)
	{
		distance = Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
	}
	// Ms�X�V
	MsUpdate();

	// UI�X�V
	UIUpdate();
}

void PlayerControl::LateUpdate()
{

}

/**
* MS�̍X�V
*/
void PlayerControl::MsUpdate()
{
	if (!myMs)
	{
		return;
	}
	// �ړ�
	Vector2 moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	myMs->Move(moveAxis);

	// �W�����v
	bool jumpKey = InputKey::GetKey(KeyCode::Space);
	myMs->Jump(jumpKey, moveAxis);

	// �_�b�V��
	bool dashKey = InputKey::GetKey(KeyCode::LeftShift);
	myMs->Dash(dashKey, moveAxis);

	// �U��1
	bool attackKey = InputMouse::GetMouseButton(MouseButton::LeftButton);
	myMs->Attack1(attackKey);
}

/**
* UI�̍X�V
*/
void PlayerControl::UIUpdate()
{
	// MyMs
	{
		if (myMs)
		{
			// Hp
			if (inMyMsHp)
			{
				inMyMsHp->num = myMs->GetHP();
			}

			// BoostBar
			if (myMs->GetBoostEnergy() > 0)
			{
				imgBoostBar->fillAmout = myMs->GetBoostEnergy();
				imgBoostBarOverHeat->SetEnable(false);
			}
			else if (myMs->GetBoostEnergy() <= 0)
			{
				imgBoostBarOverHeat->SetEnable(true);
			}

			// WeponAmo
			for (int i = 0; i < inWeaponAmos.size(); ++i)
			{
				inWeaponAmos[i]->num = myMs->numWeapons[i]->amo;
			}
			// WeaponBar
			for (int i = 0; i < imgWeaponBars.size(); ++i)
			{
				float amo = static_cast<float>(myMs->numWeapons[i]->amo);
				float amoMax = static_cast<float>(myMs->numWeapons[i]->amoMax);
				imgWeaponBars[i]->fillAmout = Mathf::Clamp01((amoMax - (amoMax - amo)) / amoMax);
			}
		}

	}

	auto targetMs = otherOwner->myMs;
	if (myMs && targetMs)
	{
		// �^�[�Q�b�g�}�[�N�̏���
		if (imgTargetMark)
		{
			// �߂���Ώ��������A������Α傫������
			imgTargetMark->size = Vector2(Mathf::Clamp(distance, 100.0f, 200.0f));

			// �����ɂ���ăe�N�X�`����ς���
			if (distance <= myMs->proximityDistance)
			{
				imgTargetMark->texture = texTargetMark03;
			}
			else if (distance <= myMs->redLookDistace)
			{
				imgTargetMark->texture = texTargetMark02;
			}
			else
			{
				imgTargetMark->texture = texTargetMark01;
			}
		}
		// �^�[�Q�b�gHP�̏���
		if (imgTargetHPBar)
		{
			imgTargetHPBar->fillAmout = targetMs->GetHP01();

		}
	}
}
