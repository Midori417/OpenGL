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
	* UIの設定
	*/
	void Image::UISetting()
	{
		// テクスチャが未設定なら何もしない
		if (!texture)
		{
			return;
		}

		// ImGuiで使えるテクスチャに変換
		const ImTextureID texId = (void*)(std::intptr_t)(*texture);


		// 色
		ImVec4 basecolor(color.r, color.g, color.b, color.a);
		
		switch (fillType)
		{
		case Image::FillType::Horizontal:

		{
			float imageW = size.x * fillAmout;
			// 画像を描画
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2(0, 1), ImVec2(fillAmout, 0), basecolor);
		}
		break;
		case Image::FillType::HorizontalInverse:

		{
			float imageW = size.x * fillAmout;
			float imagetWInverse = size.x - imageW;
			offsetPos.x = imagetWInverse;

			// 画像を描画
			ImGui::Image(texId, ImVec2(imageW, size.y), ImVec2((1 - fillAmout), 1), ImVec2(1, 0), basecolor);
		}

		break;
		case Image::FillType::Vertical:

		{
			float imageH = size.y * fillAmout;
			// 画像を描画
			ImGui::Image(texId, ImVec2(size.x, imageH), ImVec2(0, fillAmout), ImVec2(1, 0), basecolor);
		}
			break;
		}

		// 基底クラスに大きさを伝える
		w = size.x;
		h = size.y;

	}

	/**
	* イメージコンポーネントのクローンを作成
	*/
	ComponentPtr Image::Clone() const
	{
		auto p = std::make_shared<Image>();
		
		// 基底クラスの変数にコピーする
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
