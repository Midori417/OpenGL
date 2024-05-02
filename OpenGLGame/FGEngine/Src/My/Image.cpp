/**
* @file Image.cpp
*/
#include "Image.h"
#include "Package/ImGUI.h"
#include "WindowManager.h"

namespace FGEngine::UI
{
	/**
	* UI�̐ݒ�
	*/
	void Image::UISetting()
	{

		// ImGui�Ŏg����e�N�X�`���ɕϊ�
		const ImTextureID texId = (void*)(std::intptr_t)(*texture);

		// �摜��
		float imageW = size.x * fillAmout;

		// �F
		ImVec4 basecolor(color.r, color.g, color.b, color.a);

		// �摜��`��
		ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);
		auto vec =  ImGui::GetWindowSize();

		// ���N���X�ɑ傫����`����
		w = size.x;
		h = size.y;

	}
}
