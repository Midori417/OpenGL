/**
* @file ImGUI.cpp
*/
#include "ImGuiUI.h"
#include "GameObject.h"
#include "Transform.h"
#include "ImGui/imgui.h"

/**
* �X�V�C�x���g
*/
void ImGuiUI::Update()
{
	auto name = GetGameObject()->ToString();
	auto pos = GetGameObject()->transform->position;

	ImGui::SetNextWindowSize(ImVec2(w, h));
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

	UIUpdate();

	ImGui::End();
}
