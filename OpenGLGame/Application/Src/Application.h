/**
* @file Application.h
*/
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include "FGEngine.h"

/**
* �A�v���P�[�V�����N���X
*/
class Application : public FGEngine::Singleton<Application>
{
private:

	friend FGEngine::Singleton<Application>;
	friend FGEngine::MainSystem::EngineCore;

	// �R���X�g���N�^
	Application() = default;

	/**
	* �A�v���P�[�V�����̏�����
	* 
	* @retval 0		����ɏI��
	* @retval 0�ȊO �������Ɏ��s
	*/
	int Initialize();

	/**
	* �A�v���P�[�V�����̍X�V
	*/
	void Update();

	/**
	* �A�v���P�[�V�����̏I��
	*/
	void Fainalize();
};


#endif // !APPLICATION_H_INCLUDED
