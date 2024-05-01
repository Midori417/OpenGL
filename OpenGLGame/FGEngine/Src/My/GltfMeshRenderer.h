/**
* @file GltfMeshRenderer.h
*/
#ifndef COMPONENT_GLTFMESHRENDERER_H_INCLUDED
#define COMPONENT_GLTFMESHRENDERER_H_INCLUDED
#include "Renderer.h"
#include "ProgramObject.h"

// ��s�錾
struct GltfFile;
using GltfFilePtr = std::shared_ptr<GltfFile>;
struct GltfMaterial;
using GltfMaterialPtr = std::shared_ptr<GltfMaterial>;

/**
* glTF���b�V���`��R���|�[�l���g
*/
class GltfMeshRenderer : public Renderer
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	GltfMeshRenderer() = default;
	virtual ~GltfMeshRenderer() = default;

	virtual ModelFormat GetModelFormat() const override
	{
		return ModelFormat::gltfStatic;
	}

	virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const override;

public:

	static const int drawAllMeshes = -1;		// ���ׂẴ��b�V����`�悷�邽�߂̔ԍ�
	GltfFilePtr file;							// �`��Ɏg��glTF�t�@�C��
	std::vector<GltfMaterialPtr> materials;		// �ŗL�}�e���A��
	int meshIndex = drawAllMeshes;				// �`�悷�郁�b�V���ԍ�
};
using GltfMeshRendererPtr = std::shared_ptr<GltfMeshRenderer>;

#endif // !COMPONENT_GLTFMESHRENDERER_H_INCLUDED
