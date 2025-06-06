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
	* UIの画像を描画
	*/
	class Image : public ImGuiLayout
	{
	public:

		/**
		* デフォルトコンストラクタ
		*/
		Image() = default;

	public:

		/**
		* 現在のウィンドウのサイズに設定
		*/
		void SetWindowSize();

	private:

		/**
		* UIの設定
		*/
		virtual void UISetting() override;

		/**
		* イメージコンポーネントのクローンを作成
		* 
		* @return クローンしたイメージコンポーネント
		*/
		virtual ComponentPtr Clone() const override;

	public:

		// 表示するテクスチャポインター
		TexturePtr texture;

		// 画像のサイズ
		Vector2 size = Vector2::zero;

		// カラー
		Color color = Color::white;

		// 画像埋めタイプ
		enum class FillType
		{
			// 右から左
			Horizontal,

			// 左から右
			HorizontalInverse,

			// 上から下
			Vertical,

			// 下から上
			VerticalInverse,
		};
		FillType fillType = FillType::Horizontal;

		// 画像埋め(0〜1)
		float fillAmout = 1;

	};
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_IMAGE_H_INCLUDED
