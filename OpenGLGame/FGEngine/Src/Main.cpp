/**
* @file Main.cpp
*/
#include "FGEngine/MainSystem/EngineCore.h"
using namespace FGEngine;

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

/**
* エントリーポイント
*/
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// エンジンを生成と取得
	auto engineCore = EngineCore::GetInstance();
	
	// エンジンを始動
	return engineCore->Run();
}