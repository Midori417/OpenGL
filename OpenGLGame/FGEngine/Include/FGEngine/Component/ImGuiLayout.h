/**
* @file ImGuiLayout.h
*/
#ifndef FGENGINE_IMGUILAYOUT_H_INCLUDED
#define FGENGINE_IMGUILAYOUT_H_INCLUDED
#include "Component.h"
#include "FGEngine/Math/Vector2.h"

namespace FGEngine::UI
{
	/**
	* ImGuiを使ったUIの基底クラス
	*/
	class ImGuiLayout : public Component
	{
		friend Scene;
	protected:

		// コンストラクタ・デストラクタ
		ImGuiLayout() = default;
		virtual ~ImGuiLayout() = default;

	private:

		/**
		* UIを更新 
		*/
		void UIUpdate();

	protected:

		/**
		* UIの設定処理
		*/
		virtual void UISetting(){}

	public:

		// オブジェクト状態を設定する
		virtual void SetEnable(bool value)
		{
			enabled = value;
		}

		bool GetEnabled() const
		{
			return enabled;
		}

	public:

		virtual ComponentPtr Clone() const = 0;

	public:

		// 有効であれば更新され、無効であれば更新されません
		bool enabled = true;

		// UIの横幅
		float w = 0;

		// UIの縦幅
		float h = 0;

	protected:

		// UIの位置
		Vector2 offsetPos = Vector2::zero;
	};
	using ImGuiLayoutPtr = std::shared_ptr<ImGuiLayout>;
}

#endif // !FGENGINE_IMGUILAYOUT_H_INCLUDED
