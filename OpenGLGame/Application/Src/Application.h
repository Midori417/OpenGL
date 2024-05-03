/**
* @file Application.h
*/
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include "FGEngine.h"

/**
* アプリケーションクラス
*/
class Application : public FGEngine::Singleton<Application>
{
private:

	friend FGEngine::Singleton<Application>;
	friend FGEngine::MainSystem::EngineCore;

	// コンストラクタ
	Application() = default;

	/**
	* アプリケーションの初期化
	* 
	* @retval 0		正常に終了
	* @retval 0以外 初期化に失敗
	*/
	int Initialize();

	/**
	* アプリケーションの更新
	*/
	void Update();

	/**
	* アプリケーションの終了
	*/
	void Fainalize();
};


#endif // !APPLICATION_H_INCLUDED
