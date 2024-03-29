/**
* @file SystemFrd.h
*/
#ifndef FGENGINE_SYSTEMFRD_H_INCLUDED
#define FGENGINE_SYSTEMFRD_H_INCLUDED

namespace FGEngine
{
	namespace MainSystem
	{
		// すべてのシステムを管理するコア部
		class EngineCore;
	}
	namespace PhysicsSystem
	{
		// 物理エンジン
		class PhysicsEngine;
	}
	namespace RenderSystem
	{
		// グラフィックエンジン
		class GraphicsEngine;
	}
	namespace SceneSystem
	{
		// シーン管理クラス
		class SceneManager;
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
