/**
* @file Text.h
*/
#ifndef COMPONENT_TEXT_H_INCLUDED
#define COMPONENT_TEXT_H_INCLUDED
#include "ImGuiUI.h"
#include <string>

namespace FGEngine
{

	/**
	* ImGuiテキストコンポーネント
	*/
	class Text : public ImGuiUI
	{
	public:

		// コンストラクタ
		Text() = default;

		// デストラクタ
		virtual ~Text() = default;

	private:

		// UI処理部
		virtual void UIUpdate() override;

	public:

		std::string text = "new Text";
		int index = 0;								// フォントインデックスの配列番号
		std::string fontName = "Res/Font/arial.ttf";	// フォント名
		float fontSize = 64;							// フォントのサイズ


	};
	using TextPtr = std::shared_ptr<Text>;
}
#endif // !COMPONENT_TEXT_H_INCLUDED
