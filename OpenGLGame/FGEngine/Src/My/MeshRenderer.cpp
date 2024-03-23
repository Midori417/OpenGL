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
	* �`�悷��
	*/
	void MeshRenderer::Draw(const ProgramObject& program, Type type) const
	{
		// �X�^�e�B�b�N���b�V��������Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		if (!mesh)
		{
			return;
		}

		// ���W�ϊ��x�N�g���̔z���GPU�������ɃR�s�[
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