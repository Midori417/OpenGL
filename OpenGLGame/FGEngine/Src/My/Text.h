/**
* @file Text.h
*/
#ifndef COMPONENT_TEXT_H_INCLUDED
#define COMPONENT_TEXT_H_INCLUDED
#include "ImGuiUI.h"
#include <string>

namespace FGEngine
{

	/**
	* ImGui�e�L�X�g�R���|�[�l���g
	*/
	class Text : public ImGuiUI
	{
	public:

		// �R���X�g���N�^
		Text() = default;

		// �f�X�g���N�^
		virtual ~Text() = default;

	private:

		// UI������
		virtual void UIUpdate() override;

	public:

		std::string text = "new Text";
		int index = 0;								// �t�H���g�C���f�b�N�X�̔z��ԍ�
		std::string fontName = "Res/Font/arial.ttf";	// �t�H���g��
		float fontSize = 64;							// �t�H���g�̃T�C�Y


	};
	using TextPtr = std::shared_ptr<Text>;
}
#endif // !COMPONENT_TEXT_H_INCLUDED
