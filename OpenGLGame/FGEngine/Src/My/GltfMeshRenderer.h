/**
* @file GltfMeshRenderer.h
*/
#ifndef COMPONENT_GLTFMESHRENDERER_H_INCLUDED
#define COMPONENT_GLTFMESHRENDERER_H_INCLUDED
#include "Renderer.h"
#include "ProgramObject.h"

// 先行宣言
struct GltfFile;
using GltfFilePtr = std::shared_ptr<GltfFile>;
struct GltfMaterial;
using GltfMaterialPtr = std::shared_ptr<GltfMaterial>;

/**
* glTFメッシュ描画コンポーネント
*/
class GltfMeshRenderer : public Renderer
{
public:

	// コンストラクタ・デストラクタ
	GltfMeshRenderer() = default;
	virtual ~GltfMeshRenderer() = default;

	virtual ModelFormat GetModelFormat() const override
	{
		return ModelFormat::gltfStatic;
	}

	virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const override;

public:

	static const int drawAllMeshes = -1;		// すべてのメッシュを描画するための番号
	GltfFilePtr file;							// 描画に使うglTFファイル
	std::vector<GltfMaterialPtr> materials;		// 固有マテリアル
	int meshIndex = drawAllMeshes;				// 描画するメッシュ番号
};
using GltfMeshRendererPtr = std::shared_ptr<GltfMeshRenderer>;

#endif // !COMPONENT_GLTFMESHRENDERER_H_INCLUDED
