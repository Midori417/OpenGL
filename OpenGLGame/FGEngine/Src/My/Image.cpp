/**
* @file Image.cpp
*/
#include "Image.h"
#include "Package/ImGUI.h"
#include "WindowManager.h"
#include "Time.h"

namespace FGEngine::UI
{
	/**
	* UI�̐ݒ�
	*/
	void Image::UISetting()
	{
		// �e�N�X�`�������ݒ�Ȃ牽�����Ȃ�
		if (!texture)
		{
			return;
		}

		// ImGui�Ŏg����e�N�X�`���ɕϊ�
		const ImTextureID texId = (void*)(std::intptr_t)(*texture);


		// �F
		ImVec4 basecolor(color.r, color.g, color.b, color.a);
		
		switch (fillType)
		{
		case FGEngine::UI::Image::FillType::Horizontal:

		{
			float imageW = size.x * fillAmout;
			// �摜��`��
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);
		}
		break;
		case FGEngine::UI::Image::FillType::HorizontalInverse:

		{
			float imageW = size.x * fillAmout;
			float imagetWInverse = size.x - imageW;
			offsetPos.x = imagetWInverse;

			// �摜��`��
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2((1 - fillAmout), 1), ImVec2(1, 0), basecolor);
		}

		break;
		case FGEngine::UI::Image::FillType::Vertical:

		{
			float imageH = size.y * fillAmout;
			// �摜��`��
			ImGui::Image(texId, ImVec2(size.x, imageH), ImVec2(0, fillAmout), ImVec2(1, 0), basecolor);
		}
			break;
		}

		// ���N���X�ɑ傫����`����
		w = size.x;
		h = size.y;

	}
}
