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
			return;		// �t�@�C���܂��̓��b�V�������݂��Ȃ�
		}

		// ���W�ϊ��s���ݒ�
		const Matrix4x4 matModel = transform->GetTransformMatrix() * file->matRoot;

		glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, &matModel[0].x);
		if (type == Type::Standard)
		{
			glProgramUniformMatrix3fv(program, 1, 1, GL_FALSE, &transform->GetNormalMatrix()[0].x);

		}

		// �}�e���A�����w�肳��Ă��Ȃ��ꍇ�A���L�}�e���A�����g���ĕ`�悷��
		const auto* pMaterials = &materials;
		if (materials.empty())
		{
			pMaterials = &file->materials;
		}

		// �C���f�b�N�X�����̏ꍇ�͑S���b�V����`��A0�ȏ�̏ꍇ�͎w�肳�ꂽ���b�V�������`��
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