/**
* @file Material.h
*/
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "Color.h"
#include <memory>
#include <vector>
#include <string>

// 先行宣言
class Texture;
using TexturePtr = std::shared_ptr<Texture>;


/**
* マテリアル
*/
struct Material
{
	std::string name = "<Default>";	// マテリアル名
	Color baseColor = Color{ 1,1,1,1 };	// 基本色+アルファ
	Color emission = Color{ 0,0,0,0};		// 発光色
	float specularPower = 16;					// 鏡面反射指数
	float normalizeFactor = 24.0f / 25.13274f;	// 正規化係数
	TexturePtr texBaseColor;		// 基本色テクスチャ
	TexturePtr texNormal;			// 法線テクスチャ
	TexturePtr texEmission;			// 発光色テクスチャ
};
using MaterialPtr = std::shared_ptr<Material>;
using MaterialList = std::vector<MaterialPtr>;

#endif // !MATERIAL_H_INCLUDED
