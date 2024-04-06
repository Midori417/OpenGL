/**
* @file Mesh.h
*/
#ifndef FGENGINE_MESH_H_INCLUDED
#define FGENGINE_MESH_H_INCLUDED
#include "Object.h"
#include "Material.h"
#include "DrawParams.h"

namespace FGEngine
{
	/**
	* �X�^�e�B�b�N���b�V��
	*/
	class StaticMesh : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		StaticMesh() = default;
		virtual ~StaticMesh() = default;

	public:

		// �w�肷��V�F�[�_�[�̖��O
		std::string shaderName;

		// �}�e���A���z��
		MaterialList materials;

		// �`��p�����[�^
		std::vector<Rendering::DrawParams> drawParamsList;
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;

	/**
	* �X�P���^�����b�V��
	*/
	class SkeletalMesh : public StaticMesh
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		SkeletalMesh() = default;
		virtual ~SkeletalMesh() = default;

	public:
		
		/**
		* �֐߃f�[�^
		*/
		struct Joint
		{
			// �o�C���h�|�[�Y�s��
			Matrix4x4 bindPose = Matrix4x4(1);	

			// �t�o�C���h�|�[�Y�s��
			Matrix4x4 incerseBindPose = Matrix4x4(1);

			// �e�֐߂̔ԍ�
			int32_t parent = -1;
		};
		std::vector<Joint> joints;
	};
	using SkeletalMeshPtr = std::shared_ptr<SkeletalMesh>;
}

#endif // !FGENGINE_MESH_H_INCLUDED
