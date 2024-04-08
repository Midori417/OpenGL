/**
* @file MeshRenderer,h
*/
#ifndef FGENGINE_MESHRENDERER_H_INCLUDED
#define FGENGINE_MESHRENDERER_H_INCLUDED
#include "Renderer.h"

namespace FGEngine
{
	class StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	class Material;
	using MaterialPtr = std::shared_ptr<Material>;

	/**
	* スタティックメッシュを描画
	*/
	class MeshRenderer : public Renderer
	{
	public:

		// コンストラクタ・デストラクタ
		MeshRenderer() = default;
		virtual ~MeshRenderer() = default;

	private:

		/**
		* スタティックメッシュを描画
		*/
		virtual void Draw(DrawType drawType) const override;

	public:

		// 描画のメッシュ
		StaticMeshPtr mesh;
		
		// マテリアル配列
		std::vector<MaterialPtr> materials;
	};
}

#endif // !FGENGINE_MESHRENDERER_H_INCLUDED
