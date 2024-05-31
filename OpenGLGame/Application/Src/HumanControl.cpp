/**
* @file HumanControl.cpp
*/
#include "HumanControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
#include "BaseWeapon.h"
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
			if (!myMs->uiWeapons.empty())
			{
				// �T�C�Y��\��
				imgWeaponBacks.reserve(myMs->uiWeapons.size());
				int i = 0;
				for (auto x : myMs->uiWeapons)
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
		// ���`�[���̖����̗�
		if (myTeumOtherOwner)
		{
			// �����̗�
			{
				auto myTeumOtherMsHp = Instantate("MyTeumOtherMsHp", Vector3(-770, 100, 0));
				inMyTeumOtherMsHp = myTeumOtherMsHp->AddComponent<ImageNum>();
				inMyTeumOtherMsHp->space = -50;
				inMyTeumOtherMsHp->scale = 1.0f;
				inMyTeumOtherMsHp->num = 888;
			}

			// �����@�̂̏����쐬
			{
				auto myTeumOtherMsInfo = Instantate("MyTeumOtherMsInfo", Vector3(120, -70, 0));
				imgMyTeumOtherMsInfo = myTeumOtherMsInfo->AddComponent<Image>();
				imgMyTeumOtherMsInfo->texture = resManager->GetTexture("MyTeumOtherMsInfo");
				imgMyTeumOtherMsInfo->size = imgMyTeumOtherMsInfo->texture->GetSize();
			}
			// �����@�̗̂̑̓o�[���쐬
			{
				auto myTeumOtherMsHpBar = Instantate("MyTeumOtherMsHpBar", Vector3(162, -75, 0));
				imgMyTeumOtherMsHpBar = myTeumOtherMsHpBar->AddComponent<Image>();
				imgMyTeumOtherMsHpBar->texture = resManager->GetTexture("MyTeumOtherMsHpBar");
				imgMyTeumOtherMsHpBar->size = imgMyTeumOtherMsHpBar->texture->GetSize();
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
		for (int i = 0; i < otherTeumOwner.size(); ++i)
		{
			// �^�[�Q�b�g�̏����쐬
			{
				auto targetMark = Instantate("OtherTeumMsInfo" + std::to_string(i), Vector3(120, -70, 0));
				auto imgOtherTeumMsInfo = targetMark->AddComponent<Image>();
				imgOtherTeumMsInfo->texture = resManager->GetTexture("OtherTeumMsInfo");
				imgOtherTeumMsInfo->size = imgOtherTeumMsInfo->texture->GetSize();
				imgOtherTeumMsInfoBacks.push_back(imgOtherTeumMsInfo);
			}
			// �^�[�Q�b�g�̗̑̓o�[���쐬
			{
				auto otherMsHpBar = Instantate("OtherTeumMsHpBar" + std::to_string(i), Vector3(162, -75, 0));
				auto imgOtherMsHpBar = otherMsHpBar->AddComponent<Image>();
				imgOtherMsHpBar->texture = resManager->GetTexture("OtherTeumMsHpBar");
				imgOtherMsHpBar->size = imgOtherMsHpBar->texture->GetSize();
				imgOtherTeumMsHpBars.push_back(imgOtherMsHpBar);
			}
		}

		// �`�[���̗�
		{
			// ���`�[���̗̑̓o�[���쐬
			{
				auto myTeumHpBar = Instantate("MyTeumHpBar", Vector3(-640, -465, 0));
				imgMyTeumHpBar = myTeumHpBar->AddComponent<Image>();
				imgMyTeumHpBar->texture = resManager->GetTexture("MyTeumHpBar");
				imgMyTeumHpBar->size = imgMyTeumHpBar->texture->GetSize() * 1.2f;

				float max = static_cast<float>(teumMaxHp);
				float hp = static_cast<float>(MyTeumHp());
				imgMyTeumHpBar->fillAmout = (max - (max - hp)) / max;
			}
			// ����`�[���̗̑̓o�[���쐬
			{
				auto otherTeumHpBar = Instantate("OtherTeumHpBar", Vector3(-620, -420, 0));
				imgOtherTeumHpBar = otherTeumHpBar->AddComponent<Image>();
				imgOtherTeumHpBar->texture = resManager->GetTexture("OtherTeumHpBar");
				imgOtherTeumHpBar->size = imgOtherTeumHpBar->texture->GetSize() * 1.2f;

				float max = static_cast<float>(teumMaxHp);
				float hp = static_cast<float>(OtherTeumHp());
				imgOtherTeumHpBar->fillAmout = (max - (max - hp)) / max;
			}
			// �`�[���̗̓t���[�����쐬
			{
				auto teumHp = Instantate("TeumHpFrame", Vector3(-635, -430, 0));
				imgTeumHpFrame = teumHp->AddComponent<Image>();
				imgTeumHpFrame->texture = resManager->GetTexture("TeumHpFrame");
				imgTeumHpFrame->size = imgTeumHpFrame->texture->GetSize() * 1.2f;
			}
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
		if (myTeumOtherOwner)
		{
			inMyTeumOtherMsHp->SetEnable(false);
			imgMyTeumOtherMsHpBar->SetEnable(false);
			imgMyTeumOtherMsInfo->SetEnable(false);
		}
		imgTargetMark->SetEnable(false);
		for (int i = 0; i < otherTeumOwner.size(); ++i)
		{
			imgOtherTeumMsInfoBacks[i]->SetEnable(false);
			imgOtherTeumMsHpBars[i]->SetEnable(false);
		}
		imgTeumHpFrame->SetEnable(false);
		imgMyTeumHpBar->SetEnable(false);
		imgOtherTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
		imgWin->SetEnable(false);
		imgLose->SetEnable(false);
	}

	// ��������
	Initialize();

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
		if (inMyTeumOtherMsHp)
		{
			inMyTeumOtherMsHp->SetEnable(true);
		}
		imgTargetMark->SetEnable(true);
		imgTeumHpFrame->SetEnable(true);
		imgMyTeumHpBar->SetEnable(true);;
		imgOtherTeumHpBar->SetEnable(true);
		imgTimer->SetEnable(true);
		myCamera->StartOk();
	}

	// ���g�̋@�̂����񂾂�
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			if (!GetTeumHPInifinit())
			{
				// ���`�[����Hp�����炷
				TeumHpSud();
			}
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

	// �^�[�Q�b�g�؂�ւ�
	if (gameInput->targetChangeBtn && otherTeumOwner.size() > 0)
	{
		if (targetOwner == otherTeumOwner[0])
		{
			targetOwner = otherTeumOwner[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
		else if (targetOwner == otherTeumOwner[1])
		{
			targetOwner = otherTeumOwner[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
	}
	// �^�[�Q�b�g�̋@�̂����񂾂�
	if (targetOwner->myMs->IsDeath() && otherTeumOwner.size() > 0)
	{
		if (targetOwner == otherTeumOwner[0])
		{
			targetOwner = otherTeumOwner[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
		else if (targetOwner == otherTeumOwner[1])
		{
			targetOwner = otherTeumOwner[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
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
	gameInput->targetChangeBtn = InputMouse::GetMouseButtonDown(MouseButton::CenterButton);
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

	// �����̗̑�
	if (myTeumOtherOwner)
	{
		if (inMyTeumOtherMsHp)
		{
			inMyTeumOtherMsHp->num = myTeumOtherOwner->myMs->GetHP();
		}

		auto otherMs = myTeumOtherOwner->myMs;
		if (!otherMs->IsDeath())
		{
			// MS�̕����𒲂ׂ�
			Vector3 directionToTarget = Vector3(otherMs->GetTransform()->position - myCamera->GetTransform()->position).Normalized();
			float dot = Vector3::Dot(directionToTarget, myCamera->GetTransform()->Forward());
			if (dot > 0.4f)
			{
				imgMyTeumOtherMsInfo->SetEnable(true);
				imgMyTeumOtherMsHpBar->SetEnable(true);
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(otherMs->GetTransform()->position,
						camera, size.x, size.y);
					imgMyTeumOtherMsInfo->GetTransform()->position = Vector3(screenPos, 1) + Vector3(120, -50, 0);
					imgMyTeumOtherMsHpBar->GetTransform()->position = Vector3(screenPos, 1) + Vector3(170, -55, 0);
				}
				imgMyTeumOtherMsHpBar->fillAmout = otherMs->GetHP01();
			}
			else
			{
				imgMyTeumOtherMsInfo->SetEnable(false);
				imgMyTeumOtherMsHpBar->SetEnable(false);
			}
		}
		else if (otherMs->IsDeath())
		{
			imgMyTeumOtherMsInfo->SetEnable(false);
			imgMyTeumOtherMsHpBar->SetEnable(false);
		}

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
		inWeaponAmos[i]->num = static_cast<int>(myMs->uiWeapons[i]->amo);
	}
	// �����̎c�e�Q�[�W��ݒ�
	for (int i = 0; i < imgWeaponBars.size(); ++i)
	{
		float amo = (myMs->uiWeapons[i]->amo);
		float amoMax = (myMs->uiWeapons[i]->amoMax);
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
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(targetMs->GetTransform()->position,
						camera, size.x, size.y);
					imgTargetMark->GetTransform()->position = Vector3(screenPos, 1);
				}
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
		}

	}
	// ����`�[���̋@�̗̑�
	for (int i = 0; i < otherTeumOwner.size(); ++i)
	{
		auto otherMs = otherTeumOwner[i]->myMs;

		if (!otherMs->IsDeath())
		{
			// MS�̕����𒲂ׂ�
			Vector3 directionToTarget = Vector3(otherMs->GetTransform()->position - myCamera->GetTransform()->position).Normalized();
			float dot = Vector3::Dot(directionToTarget, myCamera->GetTransform()->Forward());
			if (dot > 0.4f)
			{
				imgOtherTeumMsInfoBacks[i]->SetEnable(true);
				imgOtherTeumMsHpBars[i]->SetEnable(true);
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(otherMs->GetTransform()->position,
						camera, size.x, size.y);
					imgOtherTeumMsInfoBacks[i]->GetTransform()->position = Vector3(screenPos, 1) + Vector3(120, -50, 0);
					imgOtherTeumMsHpBars[i]->GetTransform()->position = Vector3(screenPos, 1) + Vector3(170, -55, 0);
				}
				imgOtherTeumMsHpBars[i]->fillAmout = otherMs->GetHP01();
			}
			else
			{
				imgOtherTeumMsInfoBacks[i]->SetEnable(false);
				imgOtherTeumMsHpBars[i]->SetEnable(false);
			}
		}
		else if (otherMs->IsDeath())
		{
			imgOtherTeumMsInfoBacks[i]->SetEnable(false);
			imgOtherTeumMsHpBars[i]->SetEnable(false);
		}
	}

}


/**
* �I������
*/
void HumanControl::Finish(VictoryState victoryState)
{
	// �@�̂̋������~�߂�
	myMs->Stop();

	// UI���\���ɂ���
	{
		imgMyInfoBack->SetEnable(false);
		inMyMsHp->Stop();
		imgBoostBarBack->SetEnable(false);
		imgBoostBar->SetEnable(false);
		imgBoostBarOverHeat->SetEnable(false);
		imgBurstBarBack->SetEnable(false);
		imgBurstBar->SetEnable(false);
		if (myTeumOtherOwner)
		{
			imgMyTeumOtherMsHpBar->SetEnable(false);
			imgMyTeumOtherMsInfo->SetEnable(false);
			inMyTeumOtherMsHp->Stop();
		}
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
		for (int i = 0; i < otherTeumOwner.size(); ++i)
		{
			imgOtherTeumMsInfoBacks[i]->SetEnable(false);
			imgOtherTeumMsHpBars[i]->SetEnable(false);
		}
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