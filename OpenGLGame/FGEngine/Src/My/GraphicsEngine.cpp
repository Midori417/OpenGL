/**
* @file GraphicsEngine.cpp
*/
#include "GraphicsEngine.h"
#include "MeshBuffer.h"

namespace FGEngine::GraphicsSystem
{
	/**
	* グラフィックエンジンを初期化
	*
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int GraphicsEngine::Initialize()
	{
		// メッシュバッファを作成
		meshBuffer = Rendering::MeshBuffer::Create(32'000'000);

		return 0;
	}

	/**
	* グラフィックエンジンを更新
	*/
	void GraphicsEngine::Update()
	{
	}

	/**
	* グラフィックエンジンを終了
	*/
	void GraphicsEngine::Fainalize()
	{
	}

	void GraphicsEngine::DrawGameObject(GameObjectList::iterator begin, GameObjectList::iterator end)
	{
	}
	void GraphicsEngine::InitializeLight(GameObjectList::iterator begin, GameObjectList::iterator end)
	{
	}
	void GraphicsEngine::DrawSkySphere()
	{
	}
	void GraphicsEngine::ShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end)
	{
	}
	int GraphicsEngine::AllocateLight()
	{
		return 0;
	}
	void GraphicsEngine::DeallocateLight(int index)
	{
	}
	LightData* GraphicsEngine::GetLight(int index)
	{
		return nullptr;
	}
	const LightData* GraphicsEngine::GetLight(int index) const
	{
		return nullptr;
	}
}