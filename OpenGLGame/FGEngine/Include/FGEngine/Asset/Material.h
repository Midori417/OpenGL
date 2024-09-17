/**
* @file Material.h
*/
#ifndef FGENGINE_MATERIAL_H_INCLUDED
#define FGENGINE_MATERIAL_H_INCLUDED
#include "FGEngine/UsingNames/UsingAsset.h"
#include "FGEngine/Color.h"
#include "FGEngine/Math/Vector2.h"
#include <memory>
#include <vector>
#include <string>

namespace FGEngine
{
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

	public:

		/**
		* マテリアルを作成する
		* 
		* @param name マテリアルの名前
		* 
		* @return 作成したマテリアル
		*/
		static MaterialPtr Create(const std::string& name)
		{
			auto p = std::make_shared<Material>();
			p->name = name;
			return p;
		}

	};
}
#endif // !MATERIAL_H_INCLUDED
