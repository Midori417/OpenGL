/**
* @file MeshRenderer.h
*/
#include "MeshRenderer.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "VecMath.h"

namespace FGEngine
{

	/**
	* 描画する
	*/
	void MeshRenderer::Draw(const ProgramObject& program, Type type) const
	{
		// スタティックメッシュがされていない場合は描画しない
		if (!mesh)
		{
			return;
		}

		// 座標変換ベクトルの配列をGPUメモリにコピー
		if (GetGameObject()->transform != nullptr)
		{
			auto trs = GetGameObject()->transform;
			glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, &trs->GetTransformMatrix()[0].x);
			if (type == Type::Standard)
			{
				glProgramUniformMatrix3fv(program, 1, 1, GL_FALSE, &trs->GetNormalMatrix()[0].x);
			}
		}
		::FGEngine::Draw(*mesh, program, mesh->materials);

	}
}