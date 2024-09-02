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
	* ImGui���g����UI�̊��N���X
	*/
	class ImGuiLayout : public Component
	{
		friend Scene;
	protected:

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

		// �I�u�W�F�N�g��Ԃ�ݒ肷��
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

		// �L���ł���΍X�V����A�����ł���΍X�V����܂���
		bool enabled = true;

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
