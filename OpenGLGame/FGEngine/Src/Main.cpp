/**
* @file Main.cpp
*/
#include "My/Engine.h"

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

/**
* �G���g���[�|�C���g
*/
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// �G���W���𐶐��Ǝ擾
	auto engineCore = FGEngine::MainSystem::EngineCore::GetInstance();
	
	// �G���W�����n��
	return engineCore->Run();
}