/**
* @file Image.h
*/
#ifndef FGENGINE_IMAGE_H_INCLUDED
#define FGENGINE_IMAGE_H_INCLUDED
#include "ImGuiLayout.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Color.h"

namespace FGEngine
{
	/**
	* UI�̉摜��`��
	*/
	class Image : public ImGuiLayout
	{
	public:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Image() = default;

	public:

		/**
		* ���݂̃E�B���h�E�̃T�C�Y�ɐݒ�
		*/
		void SetWindowSize();

	private:

		/**
		* UI�̐ݒ�
		*/
		virtual void UISetting() override;

		/**
		* �C���[�W�R���|�[�l���g�̃N���[�����쐬
		* 
		* @return �N���[�������C���[�W�R���|�[�l���g
		*/
		virtual ComponentPtr Clone() const override;

	public:

		// �\������e�N�X�`���|�C���^�[
		TexturePtr texture;

		// �摜�̃T�C�Y
		Vector2 size = Vector2::zero;

		// �J���[
		Color color = Color::white;

		// �摜���߃^�C�v
		enum class FillType
		{
			// �E���獶
			Horizontal,

			// ������E
			HorizontalInverse,

			// �ォ�牺
			Vertical,

			// �������
			VerticalInverse,
		};
		FillType fillType = FillType::Horizontal;

		// �摜����(0�`1)
		float fillAmout = 1;

	};
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_IMAGE_H_INCLUDED
