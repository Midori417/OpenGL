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
	* UI���X�V
	*/
	void ImGuiLayout::UIUpdate()
	{
		auto name = OwnerObject()->ToString();
		Vector3 pos = OwnerObject()->GetTransform()->position;

		Vector2 windowSize = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

		auto uiPos = Vector2(pos.x - (w / 2), pos.y - (h / 2)) + (windowSize / 2);

		// �E�B���h�E�̃T�C�Y��ݒ�
		ImGui::SetNextWindowSize(ImVec2(w, h));

		// �E�B���h�E�̈ʒu��ݒ�
		ImGui::SetNextWindowPos(ImVec2(uiPos.x + offsetPos.x, uiPos.y + offsetPos.y));

		// ImGUI��`��J�n
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoInputs);

		// UI�̐ݒ���X�V
		UISetting();

		// ImBUi�̕`��I��
		ImGui::End();
	}
}