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
	* �X�^�e�B�b�N���b�V����`��
	*/
	void MeshRenderer::Draw(DrawType drawType) const
	{
		// ���b�V�����ݒ肳��Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		if (!mesh)
		{
			return;
		}

		// ���W�ϊ��s���GPU�ɃR�s�[
		if (GetTransform())
		{
			// VAO���o�C���h
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
				// �`��
				RenderingSystem::Draw(shader->GetProgId(), *mesh, materials);
			}
			else if (drawType == DrawType::shadow)
			{
				if (glGetUniformLocation(shader->GetProgId(), "transformMatrix") >= 0)
				{

					glProgramUniformMatrix4fv(shadowShader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
						GL_FALSE, &GetTransform()->GetTransformMatrix()[0].x);
				}// �`��
				RenderingSystem::Draw(shadowShader->GetProgId(), *mesh, materials);
			}

			// VAO�̃o�C���h����
			glBindVertexArray(0);
		}
	}
}
