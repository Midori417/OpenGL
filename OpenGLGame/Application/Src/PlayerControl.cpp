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
	auto resManager = ResouceManager::GetInstance();

	// UI�̍쐬
	{
		auto playerInfo = Instantate("PlayerInfo", Vector3(-725, 330, 0));
		imgPlayerInfo = playerInfo->AddComponent<Image>();
		imgPlayerInfo->texture = resManager->GetTexture("PlayerInfo");
		imgPlayerInfo->size = Vector2(imgPlayerInfo->texture->GetWidth() * 1.4f, imgPlayerInfo->texture->GetHeight() * 1.1f);
	}
	// MyMSHP
	{
		auto playerHp = Instantate("PlayerHP", Vector3(-700, 280, 0));
		numPlayerImage = playerHp->AddComponent<ImageNum>();
		numPlayerImage->scale = 1.2f;
	}
	// BoostBarBack
	{
		auto boostBarBack = Instantate("BoostBarBack", Vector3(250, 450, 0));
		imgBoostBarBack = boostBarBack->AddComponent<Image>();
		imgBoostBarBack->texture = resManager->GetTexture("BoostBarBack");
		imgBoostBarBack->size = imgBoostBarBack->texture->GetSize() * 1.2f;
	}
	// BoostBarOverHeat
	{
		auto boostBarOverHeat = Instantate("BoosetBarOverHeat", Vector3(245, 435, 0));
		imgBoostBarOverHeat = boostBarOverHeat->AddComponent<Image>();
		imgBoostBarOverHeat->texture = resManager->GetTexture("BoostBarOVERHEAT");
		imgBoostBarOverHeat->size = imgBoostBarOverHeat->texture->GetSize() * 1.2f;
		ibBoostBarOverHeat = boostBarOverHeat->AddComponent<ImageBlinking>();
		ibBoostBarOverHeat->image = imgBoostBarOverHeat;
		ibBoostBarOverHeat->speed = 5.0f;
	}
	// BoostBar
	{
		auto boostBar = Instantate("BoostBar", Vector3(245, 435, 0));
		imgBoostBar = boostBar->AddComponent<Image>();
		imgBoostBar->texture = resManager->GetTexture("BoostBar");
		imgBoostBar->size = imgBoostBar->texture->GetSize() * 1.2f;
		imgBoostBar->fillAmout = 0.5f;
	}
	// BurstBarBack
	{
		auto burstBarBack = Instantate("burstBarBack", Vector3(-250, 450, 0));
		imgBurstBarBack = burstBarBack->AddComponent<Image>();
		imgBurstBarBack->texture = resManager->GetTexture("BurstBarBack");
		imgBurstBarBack->size = imgBurstBarBack->texture->GetSize() * 1.2f;
	}
	// BurstBar
	{
		auto burstBar = Instantate("burstBar", Vector3(-253, 428, 0));
		imgBurstBar = burstBar->AddComponent<Image>();
		imgBurstBar->texture = resManager->GetTexture("BurstBar");
		imgBurstBar->size = imgBurstBar->texture->GetSize() * 1.2f;
		imgBurstBar->fillType = Image::FillType::HorizontalInverse;
		imgBurstBar->fillAmout = 0.5f;
	}
	// WeaponBack
	{
		if (!myMs->numWeapons.empty())
		{
			// �T�C�Y��\��
			imgWeaponBack.reserve(myMs->numWeapons.size());
			int i = 0;
			for (auto x : myMs->numWeapons)
			{
				auto weaponBack = Instantate("WeaponBack" + std::to_string(i), Vector3(765.0f, 400.0f + (-160.0f * i), 0));
				auto image = weaponBack->AddComponent<Image>();
				image->texture = resManager->GetTexture("WeaponBack");
				image->size = image->texture->GetSize() * 1.3f;

				// �z��ɒǉ�
				imgWeaponBack.push_back(image);
				i++;
			}
		}
	}
	// TargetMark
	{
		// ���\�[�X��ۑ�
		texTargetMark01 = resManager->GetTexture("TargetMark01");
		texTargetMark02 = resManager->GetTexture("TargetMark02");
		texTargetMark03 = resManager->GetTexture("TargetMark03");

		auto targetMark = Instantate("TargetMark");
		imgTargetMark = targetMark->AddComponent<Image>();
		imgTargetMark->texture = texTargetMark01;
		imgTargetMark->size = imgTargetMark->texture->GetSize();
	}
	// TargetInfo
	{
		auto targetMark = Instantate("TargetMsInfo", Vector3(120, -70, 0));
		imgTargetInfo = targetMark->AddComponent<Image>();
		imgTargetInfo->texture = resManager->GetTexture("TargetMsInfo");
		imgTargetInfo->size = imgTargetInfo->texture->GetSize();
	}
	// TargetHp
	{
		auto targetHP = Instantate("TargetMsHpBar", Vector3(162, -75, 0));
		imgTargetHPBar = targetHP->AddComponent<Image>();
		imgTargetHPBar->texture = resManager->GetTexture("TargetMsHpBar");
		imgTargetHPBar->size = imgTargetHPBar->texture->GetSize();

	}

	// TeumHPBar
	{
		auto teumHpBar = Instantate("TeumHpBar", Vector3(-640, -465, 0));
		imgTeumHpBar = teumHpBar->AddComponent<Image>();
		imgTeumHpBar->texture = resManager->GetTexture("TeumHpBar");
		imgTeumHpBar->size = imgTeumHpBar->texture->GetSize() * 1.2f;
		imgTeumHpBar->fillAmout = 0.4f;
	}
	// TeumEnemyBar
	{
		auto teumEnemyBar = Instantate("TeumEnemyBar", Vector3(-620, -420, 0));
		imgTeumEnemyBar = teumEnemyBar->AddComponent<Image>();
		imgTeumEnemyBar->texture = resManager->GetTexture("TeumEnemyHpBar");
		imgTeumEnemyBar->size = imgTeumEnemyBar->texture->GetSize() * 1.2f;
		imgTeumEnemyBar->fillAmout = 0.8f;

	}
	// TeumFrame
	{
		auto teumHp = Instantate("TeumFrame", Vector3(-635, -430, 0));
		imgTeumFrame = teumHp->AddComponent<Image>();
		imgTeumFrame->texture = resManager->GetTexture("TeumFrame");
		imgTeumFrame->size = imgTeumFrame->texture->GetSize() * 1.2f;
	}
	// Timer
	{
		auto timer = Instantate("Timer", Vector3(800, -450, 0));
		imgTimer = timer->AddComponent<Image>();
		imgTimer->texture = resManager->GetTexture("Timer");
		imgTimer->size = imgTimer->texture->GetSize() * 1.2f;
	}

	// UI��S�ĂЂЂ傤���ɂ���
	imgPlayerInfo->SetEnable(false);
	numPlayerImage->SetEnable(false);
	imgBoostBarBack->SetEnable(false);
	imgBoostBar->SetEnable(false);
	imgBoostBarOverHeat->SetEnable(false);
	imgBurstBarBack->SetEnable(false);
	imgBurstBar->SetEnable(false);
	for (auto x : imgWeaponBack)
	{
		x->SetEnable(false);
	}
	imgTargetMark->SetEnable(false);
	imgTargetInfo->SetEnable(false);
	imgTargetHPBar->SetEnable(false);
	imgTeumFrame->SetEnable(false);
	imgTeumHpBar->SetEnable(false);
	imgTeumEnemyBar->SetEnable(false);
	imgTimer->SetEnable(false);


	// �J�����Ɏ��g��MS��ݒ�
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

void PlayerControl::Update()
{
	if (!isStart)
	{
		return;
	}
	else
	{
		// UI��\��
		imgPlayerInfo->SetEnable(true);
		numPlayerImage->SetEnable(true);
		imgBoostBarBack->SetEnable(true);
		imgBoostBar->SetEnable(true);
		imgBurstBarBack->SetEnable(true);
		imgBurstBar->SetEnable(true);
		for (auto x : imgWeaponBack)
		{
			x->SetEnable(true);
		}
		imgTargetMark->SetEnable(true);
		imgTargetInfo->SetEnable(true);
		imgTargetHPBar->SetEnable(true);
		imgTeumFrame->SetEnable(true);
		imgTeumHpBar->SetEnable(true);;
		imgTeumEnemyBar->SetEnable(true);
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

void PlayerControl::UIUpdate()
{
	// �^�[�Q�b�g�}�[�N�̏���
	if (imgTargetMark)
	{
		// �߂���Ώ��������A������Α傫������
		imgTargetMark->size = Vector2(Mathf::Clamp(distance, 100.0f, 200.0f));
		if (myMs)
		{
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
	}

	// BoostBar�̏���
	{
		if (myMs)
		{
			if (myMs->GetBoostEnergy() > 0)
			{
				imgBoostBar->fillAmout = myMs->GetBoostEnergy();
				imgBoostBarOverHeat->SetEnable(false);
			}
			else if (myMs->GetBoostEnergy() <= 0)
			{
				imgBoostBarOverHeat->SetEnable(true);
			}
		}
	}

	// TargetHPBar
	{
		auto targetMs = otherOwner->myMs;
		if (targetMs)
		{
			imgTargetHPBar->fillAmout = targetMs->GetHP01();
		}
	}
}
