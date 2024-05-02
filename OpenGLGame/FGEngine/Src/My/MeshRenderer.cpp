/**
* @file MeshRenderer.cpp
*/
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
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

			if (drawType == DrawType::normal)
			{
				if (shader)
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
			}
			else if (drawType == DrawType::shadow)
			{
				if (shadowShader)
				{
					if (glGetUniformLocation(shadowShader->GetProgId(), "transformMatrix") >= 0)
					{
						glProgramUniformMatrix4fv(shadowShader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
							GL_FALSE, &GetTransform()->GetTransformMatrix()[0].x);
					}// 描画
					RenderingSystem::Draw(shadowShader->GetProgId(), *mesh, materials);
				}
			}
		}
	}
}
