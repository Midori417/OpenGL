/**
* @file Mesh.h
*/
#ifndef FGENGINE_MESH_H_INCLUDED
#define FGENGINE_MESH_H_INCLUDED
#include "Material.h"
#include "FGEngine/Rendering/DrawParams.h"

namespace FGEngine
{
	/**
	* スタティックメッシュ
	*/
	struct StaticMesh
	{	
		// スタティックメッシュの名前
		std::string name;

		// マテリアル配列
		MaterialList materials;

		// 描画パラメータ
		std::vector<RenderingSystem::DrawParams> drawParamsList;
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
}

#endif // !FGENGINE_MESH_H_INCLUDED
