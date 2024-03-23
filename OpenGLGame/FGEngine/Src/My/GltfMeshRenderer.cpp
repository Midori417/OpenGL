/**
* @file GltfMeshRenderer.cpp
*/
#include "GltfMeshRenderer.h"
#include "GltfMesh.h"
#include "Transform.h"

namespace FGEngine
{

	void GltfMeshRenderer::Draw(const ProgramObject& program, Type type) const
	{
		if (!file || meshIndex >= static_cast<int>(file->meshes.size()))
		{
			return;		// ファイルまたはメッシュが存在しない
		}

		// 座標変換行列を設定
		const Matrix4x4 matModel = transform->GetTransformMatrix() * file->matRoot;

		glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, &matModel[0].x);
		if (type == Type::Standard)
		{
			glProgramUniformMatrix3fv(program, 1, 1, GL_FALSE, &transform->GetNormalMatrix()[0].x);

		}

		// マテリアルが指定されていない場合、共有マテリアルを使って描画する
		const auto* pMaterials = &materials;
		if (materials.empty())
		{
			pMaterials = &file->materials;
		}

		// インデックスが負の場合は全メッシュを描画、0以上の場合は指定されたメッシュだけ描画
		if (meshIndex < 0)
		{
			for (const auto& e : file->meshes)
			{
				::FGEngine::Draw(e, *pMaterials, program);
			}
		}
		else
		{
			::FGEngine::Draw(file->meshes[meshIndex], *pMaterials, program);
		}
	}
}