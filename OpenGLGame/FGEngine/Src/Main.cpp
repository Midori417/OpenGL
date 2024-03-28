/**
* @file Main.cpp
*/
#include "My/Engine.h"

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
	auto engineCore = FGEngine::MainSystem::EngineCore::GetInstance();
	
	// エンジンを始動
	return engineCore->Run();
}