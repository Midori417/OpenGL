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

		// �E�B���h�E�̃T�C�Y��ݒ�
		ImGui::SetNextWindowSize(ImVec2(w, h));

		Vector2 windowSize = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

		Vector2 uiPos = Vector2(pos.x, pos.y) + (windowSize / 2);

		// �E�B���h�E�̈ʒu��ݒ�
		ImGui::SetNextWindowPos(ImVec2(uiPos.x, uiPos.y));

		// ImGUI��`��J�n
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

		// UI�̐ݒ���X�V
		UISetting();

		// ImBUi�̕`��I��
		ImGui::End();

	}
}