/**
* @file ImGuiLayout.cpp
*/
#include "ImGuiLayout.h"
#include "GameObject.h"
#include "Transform.h"
#include "Package/ImGUI.h"
#include "WindowManager.h"

namespace FGEngine::UI
{
	/**
	* UIを更新
	*/
	void ImGuiLayout::UIUpdate()
	{
		auto name = OwnerObject()->ToString();
		Vector3 pos = OwnerObject()->GetTransform()->position;

		Vector2 windowSize = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

		Vector2 uiPos = Vector2(pos.x - (w / 2), pos.y - (h / 2)) + (windowSize / 2);

		// ウィンドウのサイズを設定
		ImGui::SetNextWindowSize(ImVec2(w, h));

		// ウィンドウの位置を設定
		ImGui::SetNextWindowPos(ImVec2(uiPos.x, uiPos.y));

		// ImGUIを描画開始
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		// UIの設定を更新
		UISetting();

		// ImBUiの描画終了
		ImGui::End();

	}
}