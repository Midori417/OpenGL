/**
* @file MeshRenderer.h
*/
#ifndef COMPONENT_MESHRENDERER_H_INCLUDED
#define COMPONENT_MESHRENDERER_H_INCLUDED
#include "Renderer.h"
#include "ProgramObject.h"
#include "Mesh.h"
namespace FGEngine
{

	/**
	* ���b�V���`��R���|�[�l���g
	*/
	class MeshRenderer : public Renderer
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		MeshRenderer() = default;
		virtual ~MeshRenderer() = default;

		virtual ModelFormat GetModelFormat() const override
		{
			return ModelFormat::obj;
		}

		virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const override;

	public:

		StaticMeshPtr mesh;
		MaterialList materials;
	};
}
#endif // !
