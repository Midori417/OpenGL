/**
* @file ImGuiLayout.h
*/
#ifndef FGENGINE_IMGUILAYOUT_H_INCLUDED
#define FGENGINE_IMGUILAYOUT_H_INCLUDED
#include "Behaviour.h"

namespace FGEngine::UI
{
	/**
	* ImGui���g����UI�̊��N���X
	*/
	class ImGuiLayout : public Behaviour 
	{
	public:

		friend ObjectSystem::ObjectManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		ImGuiLayout() = default;
		virtual ~ImGuiLayout() = default;

	private:

		/**
		* UI���X�V 
		*/
		void UIUpdate();

	protected:

		/**
		* UI�̐ݒ菈��
		*/
		virtual void UISetting(){}

	public:

		// UI�̉���
		float w = 0;

		// UI�̏c��
		float h = 0;

	protected:

		// UI�̈ʒu
		Vector2 offsetPos = Vector2::zero;
	};
	using ImGuiLayoutPtr = std::shared_ptr<ImGuiLayout>;
}

#endif // !FGENGINE_IMGUILAYOUT_H_INCLUDED