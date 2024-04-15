/**
* @file MeshRenderer.cpp
*/
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Mesh.h"
#include "ShaderObject.h"
#include "ShaderLocationNum.h"
#include "MeshBuffer.h"

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
			// VAOをバインド
			glBindVertexArray(*mesh->vao);


			if (drawType == DrawType::normal)
			{
				if (glGetUniformLocation(shader->GetProgId(), "transformMatrix") >= 0)
				{
					glProgramUniformMatrix4fv(shader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
						GL_FALSE, &GetTransform()->GetTransformMatrix()[0].x);
				}
				if (glGetUniformLocation(shader->GetProgId(), "normalMatrix") >= 0)
				{
					glProgramUniformMatrix3fv(shader->GetProgId(), RenderingSystem::locNormalMatrix, 1,
						GL_FALSE, &GetTransform()->GetNormalMatrix()[0].x);
				}
				// 描画
				RenderingSystem::Draw(shader->GetProgId(), *mesh, materials);
			}
			else if (drawType == DrawType::shadow)
			{
				if (glGetUniformLocation(shader->GetProgId(), "transformMatrix") >= 0)
				{

					glProgramUniformMatrix4fv(shadowShader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
						GL_FALSE, &GetTransform()->GetTransformMatrix()[0].x);
				}// 描画
				RenderingSystem::Draw(shadowShader->GetProgId(), *mesh, materials);
			}

			// VAOのバインド解除
			glBindVertexArray(0);
		}
	}
}
