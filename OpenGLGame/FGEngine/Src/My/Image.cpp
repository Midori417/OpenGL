/**
* @file Image.cpp
*/
#include "Image.h"
#include "Package/ImGUI.h"

namespace FGEngine::UI
{
	/**
	* UIの設定
	*/
	void Image::UISetting()
	{

		// ImGuiで使えるテクスチャに変換
		const ImTextureID texId = (void*)(std::intptr_t)(*texture);

		// 画像幅
		float w = size.x * fillAmout;

		// 色
		ImVec4 basecolor(color.r, color.g, color.b, color.a);

		// 画像を描画
		ImGui::Image(texId, ImVec2(w, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);

	}
}
