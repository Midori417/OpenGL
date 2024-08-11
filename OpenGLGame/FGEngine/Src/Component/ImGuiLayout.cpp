/**
* @file ImGuiLayout.cpp
*/
#include "FGEngine/Component/ImGuiLayout.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Package/ImGUI.h"

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

		auto uiPos = Vector2(pos.x - (w / 2), pos.y - (h / 2)) + (windowSize / 2);

		// ウィンドウのサイズを設定
		ImGui::SetNextWindowSize(ImVec2(w, h));

		// ウィンドウの位置を設定
		ImGui::SetNextWindowPos(ImVec2(uiPos.x + offsetPos.x, uiPos.y + offsetPos.y));

		// ImGUIを描画開始
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoInputs);

		// UIの設定を更新
		UISetting();

		// ImBUiの描画終了
		ImGui::End();
	}
}