/**
* @file MeshRenderer.cpp
*/
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Buffer/MeshBuffer.h"

namespace FGEngine
{
	/**
	* スタティックメッシュを描画
	*/
	void MeshRenderer::Draw(DrawType drawType) const
	{
		// メッシュが設定されていない場合は描画しない
		if (!mesh)
		{
			return;
		}

		// 座標変換行列をGPUにコピー
		if (GetTransform())
		{
			auto transform = GetTransform();
			if (drawType == DrawType::normal)
			{
				if (shader)
				{
					shader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());
					shader->SetMatrix3x3("normalMatrix", transform->GetNormalMatrix());
					// 描画
					if (materials.empty())
					{
						FGEngine::Draw(shader, *mesh, mesh->materials);
					}
					else
					{
						FGEngine::Draw(shader, *mesh, materials);
					}
				}
			}
			else if (drawType == DrawType::shadow)
			{
				if (shadowShader)
				{
					shader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());
					// 描画
					if (materials.empty())
					{
						FGEngine::Draw(shadowShader, *mesh, mesh->materials);
					}
					else
					{
						FGEngine::Draw(shadowShader, *mesh, materials);
					}
				}
			}
		}
	}
}
