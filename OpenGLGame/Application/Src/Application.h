/**
* @file Application.h
*/
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include "FGEngine/Other/Singleton.h"

namespace FGEngine
{
	class EngineCore;
}

/**
* �A�v���P�[�V�����N���X
*/
class Application : public FGEngine::Singleton<Application>
{
	friend FGEngine::Singleton<Application>;
	friend FGEngine::EngineCore;
private:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	Application() = default;

private: // EngineCore�ŌĂяo��

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
