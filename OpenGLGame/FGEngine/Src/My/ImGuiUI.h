/**
* @file ImGuiUI.h
*/
#ifndef IMGUIUI_H_INCLUDED
#define IMGUIUI_H_INCLUDED
#include "Component.h"

/**
* IMGUIを使ったUIコンポーネントの基底クラス
*/
class ImGuiUI : public Component
{
public:

	//コンストラクタ
	ImGuiUI() = default;

	// デストラクタ
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
