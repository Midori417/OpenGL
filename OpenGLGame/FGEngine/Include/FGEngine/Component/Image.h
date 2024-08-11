/**
* @file Image.h
*/
#ifndef FGENGINE_IMAGE_H_INCLUDED
#define FGENGINE_IMAGE_H_INCLUDED
#include "ImGuiLayout.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Color.h"

namespace FGEngine::UI
{
	/**
	* UI�̉摜��`��
	*/
	class Image : public ImGuiLayout
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Image() = default;
		virtual ~Image() = default;

	private:

		/**
		* UI�̐ݒ�
		*/
		virtual void UISetting() override;

	public:


		// �\������e�N�X�`���|�C���^�[
		TexturePtr texture;

		// �摜�̃T�C�Y
		Vector2 size = Vector2::zero;

		// �J���[
		Color color = Color::white;

		enum class FillType
		{
			Horizontal,

			HorizontalInverse,

			Vertical,

			VerticalInverse,
		};
		FillType fillType = FillType::Horizontal;

		// �摜����(0�`1)
		float fillAmout = 1;

	};
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_IMAGE_H_INCLUDED
