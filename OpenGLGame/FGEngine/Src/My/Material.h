/**
* @file Material.h
*/
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "Color.h"
#include <memory>
#include <vector>
#include <string>

// ��s�錾
class Texture;
using TexturePtr = std::shared_ptr<Texture>;


/**
* �}�e���A��
*/
struct Material
{
	std::string name = "<Default>";	// �}�e���A����
	Color baseColor = Color{ 1,1,1,1 };	// ��{�F+�A���t�@
	Color emission = Color{ 0,0,0,0};		// �����F
	float specularPower = 16;					// ���ʔ��ˎw��
	float normalizeFactor = 24.0f / 25.13274f;	// ���K���W��
	TexturePtr texBaseColor;		// ��{�F�e�N�X�`��
	TexturePtr texNormal;			// �@���e�N�X�`��
	TexturePtr texEmission;			// �����F�e�N�X�`��
};
using MaterialPtr = std::shared_ptr<Material>;
using MaterialList = std::vector<MaterialPtr>;

#endif // !MATERIAL_H_INCLUDED
