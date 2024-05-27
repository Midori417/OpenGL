/**
* @file HumanControl.cpp
*/
#include "HumanControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
#include "Global.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;

/**
* �ŏ��Ɏ��s
*/
void HumanControl::Start()
{
	// �K�v�ȃ}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// ��������
	Initialize();

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
						auto weaponIcon = Instantate(x->name, Vector3(830, 410 + (-160.0f * i), 0));
						auto image = weaponIcon->AddComponent<Image>();
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

			float max = static_cast<float>(teumMaxHp);
			float hp = static_cast<float>(MyTeumHp());
			imgMyTeumHpBar->fillAmout = (max - (max - hp)) / max;
		}
		// ����`�[���̗̑̓o�[���쐬
		{
			auto otherTeumHpBar = Instantate("OtherTeumHpBar", Vector3(-620, -420, 0));
			imgOtherTeumHpBar = otherTeumHpBar->AddComponent<Image>();
			imgOtherTeumHpBar->texture = resManager->GetTexture("TeumEnemyHpBar");
			imgOtherTeumHpBar->size = imgOtherTeumHpBar->texture->GetSize() * 1.2f;

			float max = static_cast<float>(teumMaxHp);
			float hp = static_cast<float>(OtherTeumHp());
			imgOtherTeumHpBar->fillAmout = (max - (max - hp)) / max;
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
		// WIN���쐬
		{
			auto win = Instantate("Win");
			imgWin = win->AddComponent<Image>();
			imgWin->texture = resManager->GetTexture("Win");
			imgWin->size = winManager->GetWindowSize();
		}
		// Lose���쐬
		{
			auto lose = Instantate("Lose");
			imgLose = lose->AddComponent<Image>();
			imgLose->texture = resManager->GetTexture("Lose");
			imgLose->size = winManager->GetWindowSize();
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
		imgOtherTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
		imgWin->SetEnable(false);
		imgLose->SetEnable(false);
	}
}

/**
* ���t���[�����s
*/
void HumanControl::Update()
{
	// �X�^�[�g�Ăяo����Ă��Ȃ���Ή������Ȃ�
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
		imgOtherTeumHpBar->SetEnable(true);
		imgTimer->SetEnable(true);
	}

	// ���g�̋@�̂����񂾂�
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			// ���`�[����Hp�����炷
			TeumHpSud();
			// Ms�̑�����ł��Ȃ��悤�ɂ���
			isMsControl = false;
			isMsDeath = true;
			responTimer = 0;
		}
		// �`�[���̗͂�0�ȏゾ�����畜��������
		if (MyTeumHp() > 0)
		{
			responTimer += Time::DeltaTime();
			if (responTimer > responTime)
			{
				int index = Random::Range(0, (int)responPoss.size() - 1);
				// ���`�[���̗̑͂��R�X�g�ȏ゠��΂��̂܂܂̗̑͂ŕ���
				if (MyTeumHp() >= myMs->GetCost())
				{
					myMs->Respon(responPoss[index], 1);
				}
				// ���`�[���̗̑͂��R�X�g�ȉ��Ȃ�Ἀ̗J�b�g���ĕ���
				else if (MyTeumHp() < myMs->GetCost())
				{
					float hp = static_cast<float>(MyTeumHp());
					float cost = static_cast<float>(myMs->GetCost());
					float hpCut = ((cost - hp) / cost);
					myMs->Respon(responPoss[index], hpCut);
				}
				// MS�̑��������
				isMsControl = true;
				isMsDeath = false;
			}
		}
	}

	// �Q�[������
	GameInputUpdate();

	// �e�X�g�^�[�Q�b�g��ύX
	if (gameInput->targetChange1Btn && otherTeumOwner[0] != nullptr)
	{
		targetOwner = otherTeumOwner[0];
		// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
		myMs->SetTargetMS(targetOwner->myMs.get());
		myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
	}
	else if(gameInput->targetChange2Btn && otherTeumOwner[1] != nullptr)
	{
		targetOwner = otherTeumOwner[1];
		// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
		myMs->SetTargetMS(targetOwner->myMs.get());
		myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
	}


	// UI�X�V
	UIUpdate();
}

/**
* �Q�[�����͂��X�V
*/
void HumanControl::GameInputUpdate()
{
	// MS������ł��ꂩ�A���삪������Ă��Ȃ���Ή������Ȃ�
	if (myMs->IsDeath() || !isMsControl)
	{
		return;
	}

	// �Q�[������
	gameInput->moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	gameInput->jumpBtn = InputKey::GetKey(KeyCode::Space);
	gameInput->dashBtn = InputKey::GetKey(KeyCode::LeftShift);
	gameInput->action1Btn = InputMouse::GetMouseButton(MouseButton::LeftButton);
	gameInput->action2Btn = InputKey::GetKey(KeyCode::E);
	gameInput->targetChange1Btn = InputKey::GetKey(KeyCode::Alpha1);
	gameInput->targetChange2Btn = InputKey::GetKey(KeyCode::Alpha2);
}

/**
* UI�̍X�V
*/
void HumanControl::UIUpdate()
{
	// ���`�[���̗͂̐ݒ�
	if (imgMyTeumHpBar)
	{
		float max = static_cast<float>(teumMaxHp);
		float hp = static_cast<float>(MyTeumHp());
		imgMyTeumHpBar->fillAmout = (max - (max - hp)) / max;
	}
	// ����`�[���̗̑͂̐ݒ�
	if (imgOtherTeumHpBar)
	{
		float max = static_cast<float>(teumMaxHp);
		float hp = static_cast<float>(OtherTeumHp());
		imgOtherTeumHpBar->fillAmout = (max - (max - hp)) / max;
	}


	// �����̋@�̗̂̑͂�ݒ�
	if (inMyMsHp)
	{
		inMyMsHp->num = myMs->GetHP();
	}
	// �u�[�X�g�Q�[�W��ݒ�
	if (imgBoostBar && imgBoostBarOverHeat)
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
	// �����̎c�e��ݒ�
	for (int i = 0; i < inWeaponAmos.size(); ++i)
	{
		inWeaponAmos[i]->num = static_cast<int>(myMs->numWeapons[i]->amo);
	}
	// �����̎c�e�Q�[�W��ݒ�
	for (int i = 0; i < imgWeaponBars.size(); ++i)
	{
		float amo = (myMs->numWeapons[i]->amo);
		float amoMax = (myMs->numWeapons[i]->amoMax);
		imgWeaponBars[i]->fillAmout = Mathf::Clamp01((amoMax - (amoMax - amo)) / amoMax);
	}

	if (targetOwner)
	{
		auto targetMs = targetOwner->myMs;
		if (!targetMs->IsDeath())
		{
			// �^�[�Q�b�g�}�[�N�̏���
			if (imgTargetMark)
			{
				// �߂���Ώ��������A������Α傫������
				imgTargetMark->size = Vector2(Mathf::Clamp(GetDistance(), 100.0f, 200.0f));

				// �����ɂ���ăe�N�X�`����ς���
				if (GetDistance() <= myMs->proximityDistance)
				{
					imgTargetMark->texture = texTargetMark03;
				}
				else if (GetDistance() <= myMs->redLookDistace)
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
}


/**
* �I������
*/
void HumanControl::Finish(VictoryState victoryState)
{
	// UI���\���ɂ���
	{
		imgMyInfoBack->SetEnable(false);
		inMyMsHp->Stop();
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
			x->Stop();
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
		imgOtherTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
	}

	// ���s�ɂ����UI��\������
	switch (victoryState)
	{
	case VictoryState::None:
		break;
	case VictoryState::Win:
		imgWin->SetEnable(true);
		break;
	case VictoryState::Lose:
		imgLose->SetEnable(true);
		break;
	case VictoryState::Drow:
		break;
	}
}