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
	* UIの画像を描画
	*/
	class Image : public ImGuiLayout
	{
	public:

		// コンストラクタ・デストラクタ
		Image() = default;
		virtual ~Image() = default;

	private:

		/**
		* UIの設定
		*/
		virtual void UISetting() override;

	public:


		// 表示するテクスチャポインター
		TexturePtr texture;

		// 画像のサイズ
		Vector2 size = Vector2::zero;

		// カラー
		Color color = Color::white;

		enum class FillType
		{
			Horizontal,

			HorizontalInverse,

			Vertical,

			VerticalInverse,
		};
		FillType fillType = FillType::Horizontal;

		// 画像埋め(0～1)
		float fillAmout = 1;

	};
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_IMAGE_H_INCLUDED
