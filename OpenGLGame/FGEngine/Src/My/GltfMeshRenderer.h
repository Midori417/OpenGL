/**
* @file GltfMeshRenderer.h
*/
#ifndef FGENGIEN_GLTFMESHRENDERER_H_INCLUDED
#define FGENGINE_GLTFMESHRENDERER_H_INCLUDED
#include "Renderer.h"

namespace FGEngine
{
	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	struct AnimMatrixRange;

	/**
	* glTF���b�V���`��R���|�[�l���g
	*/
	class GltfMeshRenderer : public Renderer
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		GltfMeshRenderer() = default;
		virtual ~GltfMeshRenderer() = default;

	private:

		/**
		* �`��̑O����
		*/
		virtual void PreDraw() override;

		/**
		* ���b�V����`��
		*/
		virtual void Draw(DrawType drawType) const override;

	public:

		// glTF�t�@�C��
		GltfFilePtr glTFfile;

		// �ŗL�}�e���A��
		std::vector<MaterialPtr> materials;

		// �`�悷�郁�b�V���̔ԍ�(�X�^�e�B�b�N���b�V���̏ꍇ)
		int meshIndex = -1;

	private:

		// Ssbo
		std::vector<AnimMatrixRange> ssboRanges;
	};
	using GltfMeshRendererPtr = std::shared_ptr<GltfMeshRenderer>;
}

#endif // !FGENGIEN_GLTFMESHRENDERER_H_INCLUDED
