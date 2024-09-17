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
	* �}�e���A��
	*/
	struct Material
	{
		// �}�e���A���̖��O
		std::string name;

		// ��{�F+�A���t�@
		Color color = Color::white;

		// �����F
		Color emissionColor = Color::none;

		// ���C���e�N�X�`��
		TexturePtr mainTexture;

		// ���C���e�N�X�`���I�t�Z�b�g
		Vector2 mainTextureOffset = Vector2::zero;

		// ���C���e�N�X�`���X�P�[��
		Vector2 mainTextureScale = Vector2::one;

		// �@���e�N�X�`��
		TexturePtr normalTexture;

		// �����F�e�N�X�`��
		TexturePtr emissionTexture;

		// �����̃J�b�g��
		float alphatCutOff = 0.5f;

		// ���ʔ��ˎw��
		float specularPower = 16;					

		// ���K���W��
		float normalizeFactor = 24.0f / 25.13274f;

		// �\�ʂ̑e���A�Ȃ߂炩0�`1�e��
		float rouhness = 1;

	public:

		/**
		* �}�e���A�����쐬����
		* 
		* @param name �}�e���A���̖��O
		* 
		* @return �쐬�����}�e���A��
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
