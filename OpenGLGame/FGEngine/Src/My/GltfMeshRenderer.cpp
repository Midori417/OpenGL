/**
* @file GltfMeshRenderer.cpp
*/
#include "GltfMeshRenderer.h"
#include "GltfFile.h"
#include "GltfFileBuffer.h"
#include "MeshBuffer.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "Animator.h"
#include "Transform.h"
#include "ShaderLocationNum.h"
#include "ComponentHelper.h"

namespace FGEngine
{
	/**
	* �`��̑O����
	*/
	void GltfMeshRenderer::PreDraw()
	{
		if (!glTFfile)
		{
			return;
		}
		auto animator = GetComponent<Animator>();
		if (!animator)
		{
			return;
		}

		// �V�[���Ɋ܂܂�郁�b�V���̃A�j���[�V�����s����X�V
		// �V�[���Ɋ܂܂�郁�b�V���̃A�j���[�V�����s����X�V
		const auto scene = &glTFfile->scenes[0];
		const Matrix4x4 matModel = GetTransform()->GetLocalTransformMatrix();
		ssboRanges.clear();
		for (const auto e : scene->meshNodes)
		{
			// �A�j���[�V�����s����v�Z
			auto matBones = CalcAnimationMatrices(glTFfile, e, animator->GetAnimationClip().get(), animator->time);
			for (auto& m : matBones)
			{
				m = matModel * m; // �A�j���[�V�����s��Ƀ��f���s�������
			}
			// �A�j���[�V�����s����o�b�t�@�ɒǉ����A�ǉ���̃I�t�Z�b�g�ƃT�C�Y���L�^
			ssboRanges.push_back(glTFfile->gltfFileBuffer->AddAnimationMatrices(matBones));
		}
	}

	/**
	* ���b�V����`��
	*/
	void GltfMeshRenderer::Draw(DrawType drawType) const
	{
		if (!glTFfile)
		{
			return;
		}

		// �֐߂̗L��
		if (ssboRanges.empty())
		{
			// �C���f�b�N�X�Ƀ��b�V���͑��݂��Ȃ�
			if (meshIndex >= static_cast<int>(glTFfile->meshes.size()))
			{
				return;
			}

			// ���W�ϊ��s����v�Z
			const Matrix4x4 matModel = GetTransform()->GetWorldTransformMatrix() * glTFfile->matRoot;

			// �}�e���A�����ݒ肳�ꂽ���Ȃ��ꍇ�A�����͂��g���ĕ`�悷��
			const auto* pMaterials = &materials;
			if (materials.empty())
			{
				pMaterials = &glTFfile->materials;
			}

			
			switch (drawType)
			{
			case FGEngine::DrawType::normal:
				
				// �V�F�[�_�����ݒ�
				if (!shader)
				{
					return;
				}

				// �ϊ����W�ϊ��s���GPU�ɃR�s�[
				if (glGetUniformLocation(shader->GetProgId(), "transformMatrix") >= 0)
				{
					glProgramUniformMatrix4fv(shader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
						GL_FALSE, &GetTransform()->GetWorldTransformMatrix()[0].x);
				}
				if (glGetUniformLocation(shader->GetProgId(), "normalMatrix") >= 0)
				{
					glProgramUniformMatrix3fv(shader->GetProgId(), RenderingSystem::locNormalMatrix, 1,
						GL_FALSE, &GetTransform()->GetNormalMatrix()[0].x);
				}

				// �C���f�b�N�X�����̏ꍇ�͑S���b�V����`��,0�ȏ�͎w�肳�ꂽ���b�V�������`��
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						RenderingSystem::Draw(shader->GetProgId(), *x, *pMaterials);
					}
				}
				else
				{
					RenderingSystem::Draw(shader->GetProgId(), *glTFfile->meshes[meshIndex], *pMaterials);
				}

				break;
			case FGEngine::DrawType::shadow:

				// �V�F�[�_�����ݒ�
				if (!shadowShader)
				{
					return;
				}

				// �ϊ����W�ϊ��s���GPU�ɃR�s�[
				if (glGetUniformLocation(shader->GetProgId(), "transformMatrix") >= 0)
				{
					glProgramUniformMatrix4fv(shader->GetProgId(), RenderingSystem::locTransformMatrix, 1,
						GL_FALSE, &GetTransform()->GetWorldTransformMatrix()[0].x);
				}

				// �C���f�b�N�X�����̏ꍇ�͑S���b�V����`��,0�ȏ�͎w�肳�ꂽ���b�V�������`��
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						RenderingSystem::Draw(shadowShader->GetProgId(), *x, *pMaterials);
					}
				}
				else
				{
					RenderingSystem::Draw(shadowShader->GetProgId(), *glTFfile->meshes[meshIndex], *pMaterials);
				}

				break;
			}
		}
		else
		{
			// �V�[���Ɋ܂܂�郁�b�V����`��
			const auto scene = &glTFfile->scenes[0];
			for (size_t i = 0; i < scene->meshNodes.size(); ++i)
			{
				const int meshNo = scene->meshNodes[i]->mesh;
				const StaticMeshPtr mesh = glTFfile->meshes[meshNo];

				// SSBO���o�C���f�B���O�|�C���g0�ԂɊ��蓖�Ă�
				glTFfile->gltfFileBuffer->BindAnimationBuffer(0, ssboRanges[i]);

				// �}�e���A�����w�肳��Ă��Ȃ��ꍇ�A���L�}�e���A�����g���ĕ`�悷��
				const auto* pMaterials = &materials;
				if (materials.empty())
				{
					pMaterials = &glTFfile->materials;
				}

				switch (drawType)
				{
				case FGEngine::DrawType::normal:

					if (shader)
					{
						// ���b�V���Ɋ܂܂�邷�ׂẴv���~�e�B�u��`��
						RenderingSystem::Draw(shader->GetProgId(), *mesh, *pMaterials);
					}

					break;
				case FGEngine::DrawType::shadow:

					if (shadowShader)
					{
						// ���b�V���Ɋ܂܂�邷�ׂẴv���~�e�B�u��`��
						RenderingSystem::Draw(shadowShader->GetProgId(), *mesh, *pMaterials);
					}

					break;
				}
			}
		}
	}
}