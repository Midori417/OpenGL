/**
* @file SystemFrd.h
*/
#ifndef FGENGINE_SYSTEMFRD_H_INCLUDED
#define FGENGINE_SYSTEMFRD_H_INCLUDED

namespace FGEngine
{
	namespace MainSystem
	{
		// すべてのシステムを管理するエンジンクラス
		class EngineCore;
	}
	namespace PhysicsSystem
	{
		// 物理エンジン
		class PhysicsEngine;
	}
	namespace RenderingSystem
	{
		// 描画エンジン
		class RenderingEngine;
	}
	namespace SoundSystem
	{
		// サウンド管理クラス
		class SoundManager;
	}

	// リソース管理クラス
	class AssetManager;
	// シーン管理クラス
	class SceneManager;
	// 入力管理クラス
	class InputManager;
	// ウィンドウ管理クラス
	class WindowManager;
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
