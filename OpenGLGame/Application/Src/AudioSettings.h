/**
* @file AudioSetting.h
*/
# pragma once

/**
* 音声再生プレイヤー番号
*/
namespace AudioPlayer
{
	inline constexpr int bgm = 10; // BGMの再生に使うプレイヤー番号
	inline constexpr int player = 0;
	inline constexpr int palyer1 = 1;
	inline constexpr int player2 = 2;
	inline constexpr int player3 = 3;
}

/**
* BGM設定
*/
namespace BGM
{
	inline constexpr char title[] = "";
}

/**
* 効果音設定
*/
namespace SE
{
	inline constexpr char gundamLegSound[] = "Application/Res/Ms/Gundam/Sound/LegSound.mp3";
	inline constexpr char gundamBeumRifleShot[] = "Application/Res/Ms/Gundam/Sound/BeumRifleShot.mp3";
	inline constexpr char gundamBazookaShot[] = "Application/Res/Ms/Gundam/Sound/BazookaShot.mp3";
	inline constexpr char gundamDead[] = "Application/Res/Ms/Gundam/Sound/Dead.mp3";
}