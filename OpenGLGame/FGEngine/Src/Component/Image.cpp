/**
* @file Image.cpp
*/
#include "FGEngine/Component/Image.h"
#include "FGEngine/Package/ImGUI.h"
#include "FGEngine/Other/Time.h"
#include "FGEngine/Window/WindowManager.h"

namespace FGEngine
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
		case Image::FillType::Horizontal:

		{
			float imageW = size.x * fillAmout;
			// �摜��`��
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);
		}
		break;
		case Image::FillType::HorizontalInverse:

		{
			float imageW = size.x * fillAmout;
			float imagetWInverse = size.x - imageW;
			offsetPos.x = imagetWInverse;

			// �摜��`��
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2((1 - fillAmout), 1), ImVec2(1, 0), basecolor);
		}

		break;
		case Image::FillType::Vertical:

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

	/**
	* �C���[�W�R���|�[�l���g�̃N���[�����쐬
	*/
	ComponentPtr Image::Clone() const
	{
		auto p = std::make_shared<Image>();
		
		// ���N���X�̕ϐ��ɃR�s�[����
		p->enabled = this->enabled;
		p->w = this->w;
		p->h = this->h;
		p->offsetPos = this->offsetPos;

		p->texture = this->texture;
		p->size = this->size;
		p->color = this->color;
		p->fillAmout = this->fillAmout;
		p->fillType = this->fillType;

		return p;
	}
}
