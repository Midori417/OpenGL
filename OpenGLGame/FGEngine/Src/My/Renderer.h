/**
* @file Renderer.h
*/
#ifndef FGENGINE_RENDERER_H_INCLUDED
#define FGENGINE_RENDERER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �`��R���|�[�l���g�̊��N���X
	*/
	class Renderer : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Renderer() = default;
		virtual ~Renderer() = default;

	public:

		// �`�悷�邷�邩�̗L��
		bool enabled = true;
	};
	using RendererPtr = std::shared_ptr<Renderer>;
}

#endif // !FGENGINE_RENDERER_H_INCLUDED
