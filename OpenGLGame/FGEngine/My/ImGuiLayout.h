/**
* @file ImGuiLayout.h
*/
#ifndef FGENGINE_IMGUILAYOUT_H_INCLUDED
#define FGENGINE_IMGUILAYOUT_H_INCLUDED
#include "Behaviour.h"

namespace FGEngine::UI
{
	/**
	* ImGuiを使ったUIの基底クラス
	*/
	class ImGuiLayout : public Behaviour 
	{
	public:

		friend ObjectSystem::ObjectManager;

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
