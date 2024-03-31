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
	// ��s�錾
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* �`��̏���
	*/
	enum RenderQueue
	{
		RenderQueue_geometry = 2000,	// ��ʓI�Ȑ}�`
		RenderQueue_transparent = 3000,	// �������Ȑ}�`
		RenderQueue_overlay = 4000,		// UI�A�S��ʃG�t�F�N�g
		RenderQueue_max = 5000,			// �L���[�̍ő�l
	};

	/**
	* �}�e���A��
	*/
	class Material : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Material() = default;
		virtual ~Material() = default;

	public:

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

		// ���ʔ��ˎw��
		float specularPower = 16;					

		// ���K���W��
		float normalizeFactor = 24.0f / 25.13274f;

		// �\�ʂ̑e���A�Ȃ߂炩0�`1�e��
		float rouhness = 1;


		// �����_�[�L���[
		int renderQueue = RenderQueue_geometry;
	};
	using MaterialPtr = std::shared_ptr<Material>;
	using MaterialList = std::vector<MaterialPtr>;
}
#endif // !MATERIAL_H_INCLUDED
