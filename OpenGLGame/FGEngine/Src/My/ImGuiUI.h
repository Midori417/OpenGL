/**
* @file ImGuiUI.h
*/
#ifndef IMGUIUI_H_INCLUDED
#define IMGUIUI_H_INCLUDED
#include "Component.h"

/**
* IMGUI���g����UI�R���|�[�l���g�̊��N���X
*/
class ImGuiUI : public Component
{
public:

	//�R���X�g���N�^
	ImGuiUI() = default;

	// �f�X�g���N�^
	virtual ~ImGuiUI() = default;

private:

	virtual void Update() override;

protected:

	virtual void UIUpdate(){}

public:

	float w = 0;
	float h = 0;
};

#endif // !IMGUIUI_H_INCLUDED
