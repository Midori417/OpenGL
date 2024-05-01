/**
* @file Text.cpp
*/
#include "Text.h"
#include "ImGui/imgui.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"

/**
* UIˆ—
*/
void Text::UIUpdate()
{
	ImGuiIO io = ImGui::GetIO();
	ImFont* font = io.Fonts->Fonts[index];
	ImGui::PushFont(font);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}
