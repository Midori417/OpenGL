/**
* @file MeshRenderer,h
*/
#ifndef FGENGINE_MESHRENDERER_H_INCLUDED
#define FGENGINE_MESHRENDERER_H_INCLUDED
#include "Renderer.h"

namespace FGEngine
{
	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	/**
	* �X�^�e�B�b�N���b�V����`��
	*/
	class MeshRenderer : public Renderer
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		MeshRenderer() = default;
		virtual ~MeshRenderer() = default;

	private:

		/**
		* �X�^�e�B�b�N���b�V����`��
		*/
		virtual void Draw(DrawType drawType) const override;

	public:

		// �`��̃��b�V��
		StaticMeshPtr mesh;
		
		// �}�e���A���z��
		std::vector<MaterialPtr> materials;
	};
}

#endif // !FGENGINE_MESHRENDERER_H_INCLUDED
