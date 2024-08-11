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
	* �X�^�e�B�b�N���b�V��
	*/
	struct StaticMesh
	{	
		// �X�^�e�B�b�N���b�V���̖��O
		std::string name;

		// �}�e���A���z��
		MaterialList materials;

		// �`��p�����[�^
		std::vector<RenderingSystem::DrawParams> drawParamsList;
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
}

#endif // !FGENGINE_MESH_H_INCLUDED
