/**
* @file GltfMeshRenderer.h
*/
#ifndef FGENGINE_GLTFMESHRENDERER_H_INCLUDED
#define FGENGINE_GLTFMESHRENDERER_H_INCLUDED
#include "Renderer.h"
#include "FGEngine/Asset/GltfFile.h"

namespace FGEngine
{
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	/**
	* glTFメッシュ描画コンポーネント
	*/
	class GltfMeshRenderer : public Renderer
	{
	public:

		// コンストラクタ・デストラクタ
		GltfMeshRenderer() = default;
		virtual ~GltfMeshRenderer() = default;

	private:

		/**
		* 描画の前処理
		*/
		virtual void PreDraw() override;

		/**
		* メッシュを描画
		*/
		virtual void Draw(DrawType drawType) const override;

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// glTFファイル
		GltfFilePtr glTFfile;

		// 固有マテリアル
		std::vector<MaterialPtr> materials;

		// 描画するメッシュの番号(スタティックメッシュの場合)
		int meshIndex = -1;

	private:

		// Ssbo
		std::vector<AnimMatrixRange> ssboRanges;
	};
}

#endif // !FGENGIEN_GLTFMESHRENDERER_H_INCLUDED
