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
		// シーンの管理クラス
		class SceneManager;
	}
	namespace ObjectSystem
	{
		// オブジェクトの管理クラス
		class ObjectManager;
	}
}

#endif // !FGENGINE_SYSTEMFRD_H_INCLUDED
