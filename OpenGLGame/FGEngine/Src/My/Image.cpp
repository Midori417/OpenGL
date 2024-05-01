#include "Image.h"
#include "ImGui/imgui.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"

/**
* UI����
*/
void Image::UIUpdate()
{
	// �`��e�N�X�e�N�X�`�����擾
	auto tex = GetGameObject()->GetEngine()->GetTexture(filename.c_str());
	

	// ImGui�Ŏg����e�N�X�`���ɕϊ�
	const ImTextureID texId = (void*)(std::intptr_t)(tex->GetId());

	// �摜��
	float w = size.x * fillAmout;

	// �F
	ImVec4 basecolor(color.r, color.g, color.b, color.a);

	// �摜��`��
	ImGui::Image(texId, ImVec2(w, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);

}
