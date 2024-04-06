/**
* @file GraphicsEngine.cpp
*/
#include "GraphicsEngine.h"
#include "MeshBuffer.h"

namespace FGEngine::GraphicsSystem
{
	/**
	* �O���t�B�b�N�G���W����������
	*
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int GraphicsEngine::Initialize()
	{
		// ���b�V���o�b�t�@���쐬
		meshBuffer = Rendering::MeshBuffer::Create(32'000'000);

		return 0;
	}

	/**
	* �O���t�B�b�N�G���W�����X�V
	*/
	void GraphicsEngine::Update()
	{
	}

	/**
	* �O���t�B�b�N�G���W�����I��
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