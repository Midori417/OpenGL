/**
* @file Material.h
*/
#ifndef FGENGINE_MATERIAL_H_INCLUDED
#define FGENGINE_MATERIAL_H_INCLUDED
#include "Color.h"
#include "Vector2.h"
#include <memory>
#include <vector>
#include <string>

namespace FGEngine
{
	// 先行宣言
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* マテリアル
	*/
	struct Material
	{
		// マテリアルの名前
		std::string name;

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

		// 透明のカット率
		float alphatCutOff = 0.5f;

		// 鏡面反射指数
		float specularPower = 16;					

		// 正規化係数
		float normalizeFactor = 24.0f / 25.13274f;

		// 表面の粗さ、なめらか0～1粗い
		float rouhness = 1;
	};
	using MaterialPtr = std::shared_ptr<Material>;
	using MaterialList = std::vector<MaterialPtr>;
}
#endif // !MATERIAL_H_INCLUDED
