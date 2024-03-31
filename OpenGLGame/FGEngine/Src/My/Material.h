/**
* @file Material.h
*/
#ifndef FGENGINE_MATERIAL_H_INCLUDED
#define FGENGINE_MATERIAL_H_INCLUDED
#include "Object.h"
#include "Color.h"
#include <memory>
#include <vector>
#include <string>

namespace FGEngine
{
	// 先行宣言
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* 描画の順序
	*/
	enum RenderQueue
	{
		RenderQueue_geometry = 2000,	// 一般的な図形
		RenderQueue_transparent = 3000,	// 半透明な図形
		RenderQueue_overlay = 4000,		// UI、全画面エフェクト
		RenderQueue_max = 5000,			// キューの最大値
	};

	/**
	* マテリアル
	*/
	class Material : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		Material() = default;
		virtual ~Material() = default;

	public:

		// 基本色+アルファ
		Color color = Color::white;

		// 発光色
		Color emissionColor = Color::none;

		// メインテクスチャ
		TexturePtr mainTexture;

		// メインテクスチャオフセット
		Vector2 mainTextureOffset = Vector2::zero;

		// メインテクスチャスケール
		Vector2 mainTextureScale = Vector2::one;

		// 法線テクスチャ
		TexturePtr normalTexture;

		// 発光色テクスチャ
		TexturePtr emissionTexture;

		// 鏡面反射指数
		float specularPower = 16;					

		// 正規化係数
		float normalizeFactor = 24.0f / 25.13274f;

		// 表面の粗さ、なめらか0～1粗い
		float rouhness = 1;


		// レンダーキュー
		int renderQueue = RenderQueue_geometry;
	};
	using MaterialPtr = std::shared_ptr<Material>;
	using MaterialList = std::vector<MaterialPtr>;
}
#endif // !MATERIAL_H_INCLUDED
