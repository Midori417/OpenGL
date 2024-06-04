/**
* @file AudioSetting.h
*/
# pragma once

/**
* �����Đ��v���C���[�ԍ�
*/
namespace AudioPlayer
{
	inline constexpr int bgm = 10; // BGM�̍Đ��Ɏg���v���C���[�ԍ�
	inline constexpr int player = 0;
	inline constexpr int palyer1 = 1;
	inline constexpr int player2 = 2;
	inline constexpr int player3 = 3;
}

/**
* BGM�ݒ�
*/
namespace BGM
{
	inline constexpr char title[] = "";
}

/**
* ���ʉ��ݒ�
*/
namespace SE
{
	inline constexpr char gundamLegSound[] = "Application/Res/Ms/Gundam/Sound/LegSound.mp3";
	inline constexpr char gundamBeumRifleShot[] = "Application/Res/Ms/Gundam/Sound/BeumRifleShot.mp3";
	inline constexpr char gundamBazookaShot[] = "Application/Res/Ms/Gundam/Sound/BazookaShot.mp3";
	inline constexpr char gundamDead[] = "Application/Res/Ms/Gundam/Sound/Dead.mp3";
}