/**
* @file UsingAsset.h
*/
#ifndef FGENGINE_USINGASSET_H_INCLUDED
#define FGENGINE_USINGASSET_H_INCLUDED
#include <memory>
#include <vector>

namespace FGEngine
{
	// �A�j���[�V�����N���b�v
	struct AnimationClip;
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;

	// �e�N�X�`��
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;
	using TextureList = std::vector<TexturePtr>;

	// �}�e���A��
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	using MaterialList = std::vector<MaterialPtr>;

	// �X�^�e�B�b�N���b�V��
	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	using StaticMeshList = std::vector<StaticMeshPtr>;

	// �V�F�[�_
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;
	using ShaderList = std::vector<ShaderPtr>;

	// GltfFile
	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
}

#endif // !FGENGINE_USINGASSET_H_INCLUDED
