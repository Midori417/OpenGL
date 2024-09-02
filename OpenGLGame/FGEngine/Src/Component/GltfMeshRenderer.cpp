/**
* @file GltfMeshRenderer.cpp
*/
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Asset/GltfFile.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"

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

			auto transform = GetTransform();
			switch (drawType)
			{
			case FGEngine::DrawType::normal:

				// �V�F�[�_�����ݒ�
				if (!shader)
				{
					return;
				}

				// �ϊ����W�ϊ��s���GPU�ɃR�s�[
				shader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());
				shader->SetMatrix3x3("normalMatrix", transform->GetNormalMatrix());

				// �C���f�b�N�X�����̏ꍇ�͑S���b�V����`��,0�ȏ�͎w�肳�ꂽ���b�V�������`��
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						FGEngine::Draw(shader, *x, *pMaterials);
					}
				}
				else
				{
					FGEngine::Draw(shader, *glTFfile->meshes[meshIndex], *pMaterials);
				}

				break;
			case FGEngine::DrawType::shadow:

				// �V�F�[�_�����ݒ�
				if (!shadowShader)
				{
					return;
				}

				// �ϊ����W�ϊ��s���GPU�ɃR�s�[
				shadowShader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());

				// �C���f�b�N�X�����̏ꍇ�͑S���b�V����`��,0�ȏ�͎w�肳�ꂽ���b�V�������`��
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						FGEngine::Draw(shadowShader, *x, *pMaterials);
					}
				}
				else
				{
					FGEngine::Draw(shadowShader, *glTFfile->meshes[meshIndex], *pMaterials);
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
						FGEngine::Draw(shader, *mesh, *pMaterials);
					}

					break;
				case FGEngine::DrawType::shadow:

					if (shadowShader)
					{
						// ���b�V���Ɋ܂܂�邷�ׂẴv���~�e�B�u��`��
						FGEngine::Draw(shadowShader, *mesh, *pMaterials);
					}

					break;
				}
			}
		}
	}

	/**
	* Gltf���b�V��
	*/
	ComponentPtr GltfMeshRenderer::Clone() const
	{
		GltfMeshRendererPtr p = std::make_shared<GltfMeshRenderer>();

		// ���N���X�̕ϐ����R�s�[
		p->enabled = this->enabled;
		p->renderQueue = this->renderQueue;
		p->shader = this->shader;
		p->shadowShader = this->shadowShader;

		p->glTFfile = this->glTFfile;
		p->materials = this->materials;
		p->meshIndex = this->meshIndex;
		p->glTFfile = this->glTFfile;

		return p;
	}
}