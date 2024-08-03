/**
* @file GltfFile.h
*/
#ifndef FGENGINE_GLTFFILE_H_INCLUDED
#define FGENGINE_GLTFFILE_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>
#include <vector>
#include "MatrixPoint.h"

namespace FGEngine
{
	/**
	* glTF�X�L��
	*/
	struct GltfSkin
	{
		// �X�L����
		std::string name;

		/**
		* �W���C���g(�{�[��)�f�[�^
		*/
		struct Joint
		{
			// �W���C���g�Ή�����m�[�h�ԍ�
			int nodeId = -1;

			// �t�o�C���h�|�[�Y�z��
			Matrix4x4 matInverseBindPose = Matrix4x4(1);
		};
		
		// �W���C���g�z��
		std::vector<Joint> joints;
	};

	/**
	* glTF�m�[�h
	*/
	struct GltfNode
	{
		// �m�[�h��
		std::string name;

		// ���b�V���ԍ�
		int mesh = -1;

		// �X�L���ԍ�
		int skin = -1;

		// �e�m�[�h
		GltfNode* parent = nullptr;

		// �q�m�[�h�z��
		std::vector<GltfNode*> children;

		// ���[�J���s��
		Matrix4x4 matLocal = Matrix4x4(1);

		// �O���[�o���s��
		Matrix4x4 matGlobal = Matrix4x4(1);
	};

	/**
	* glTf�V�[��
	*/
	struct GltfScene
	{
		// �m�[�h�z��
		std::vector<const GltfNode*> nodes;

		// ���b�V�������m�[�h�݂̂̔z��
		std::vector<const GltfNode*> meshNodes;
	};

	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	struct AnimationClip;
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace RenderingSystem
	{
		class GltfFileBuffer;
	}
	/**
	* glTf�t�@�C��
	*/
	struct GltfFile
	{
		// �t�@�C����
		std::string name;

		// �V�[���z��
		std::vector<GltfScene> scenes;

		// �m�[�h�z��
		std::vector<GltfNode> nodes;

		// �X�L���z��
		std::vector<GltfSkin> skins;

		// ���b�V���z��
		std::vector<StaticMeshPtr> meshes;

		// �}�e���A���z��
		std::vector<MaterialPtr> materials;

		// �A�j���[�V�����N���b�v�z��
		std::vector<AnimationClipPtr> animationClips;

		// ��{�p���s��
		Matrix4x4 matRoot = Matrix4x4(1);

		// GltfFileBuffer
		RenderingSystem::GltfFileBuffer* gltfFileBuffer;
	};
	using GltfFilePtr = std::shared_ptr<GltfFile>;

	/**
	* �p���s��̔z��
	*/
	struct AnimMatrixRange
	{
		GLintptr offset;

		size_t size;
	};


}

#endif // !FGENGINE_GLTFFILE_H_INCLUDED
