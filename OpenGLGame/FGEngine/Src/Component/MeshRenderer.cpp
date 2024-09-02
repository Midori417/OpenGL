/**
* @file MeshRenderer.cpp
*/
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"
#include "FGEngine/Component/Transform.h"

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
			auto transform = GetTransform();
			if (drawType == DrawType::normal)
			{
				if (shader)
				{
					shader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());
					shader->SetMatrix3x3("normalMatrix", transform->GetNormalMatrix());
					// �`��
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
					// �`��
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
	ComponentPtr MeshRenderer::Clone() const
	{
		MeshRendererPtr p = std::make_shared<MeshRenderer>();

		// ���N���X�̕ϐ����R�s�[
		p->enabled = this->enabled;
		p->renderQueue = this->renderQueue;
		p->shader = this->shader;
		p->shadowShader = this->shadowShader;

		p->mesh = this->mesh;
		p->materials = this->materials;
		
		return p;
	}
}
