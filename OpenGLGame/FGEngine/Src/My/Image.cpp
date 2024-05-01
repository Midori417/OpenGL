#include "Image.h"
#include "ImGui/imgui.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"

/**
* UI処理
*/
void Image::UIUpdate()
{
	// 描画テクステクスチャを取得
	auto tex = GetGameObject()->GetEngine()->GetTexture(filename.c_str());
	

	// ImGuiで使えるテクスチャに変換
	const ImTextureID texId = (void*)(std::intptr_t)(tex->GetId());

	// 画像幅
	float w = size.x * fillAmout;

	// 色
	ImVec4 basecolor(color.r, color.g, color.b, color.a);

	// 画像を描画
	ImGui::Image(texId, ImVec2(w, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);

}
