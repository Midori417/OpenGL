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
	namespace ResouceSystem
	{
		// リソース管理クラス
		class ResouceManager;
	}
	namespace SceneSystem
	{
		// シーン管理クラス
		class SceneManager;
	}
	namespace InputSystem
	{
		// 入力管理クラス
		class InputManager;
	}
	namespace ObjectSystem
	{
		// オブジェクト管理クラス
		class ObjectManager;
	}
	namespace WindowSystem
	{
		// ウィンドウ管理クラス
		class WindowManager;
	}
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
