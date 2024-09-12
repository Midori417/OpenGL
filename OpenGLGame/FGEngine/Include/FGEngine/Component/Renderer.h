/**
* @file Renderer.h
*/
#ifndef FGENGINE_RENDERER_H_INCLUDED
#define FGENGINE_RENDERER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;

	/**
	* �`��̏���
	*/
	enum RenderQueue
	{
		RenderQueue_geometry = 2000,	// ��ʓI�Ȑ}�`
		RenderQueue_transparent = 3000,	// �������Ȑ}�`
		RenderQueue_overlay = 4000,		// UI�A�S��ʃG�t�F�N�g
		RenderQueue_max = 5000,			// �L���[�̍ő�l
	};

	enum class DrawType
	{
		normal,
		shadow
	};

	/**
	* �`��R���|�[�l���g�̊��N���X
	*/
	class Renderer : public Component
	{
		friend class RenderingEngine;
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Renderer() = default;
		virtual ~Renderer() = default;

	protected:

		/**
		* �`��̑O����
		*/
		virtual void PreDraw(){}

		/**
		* �`��
		* 
		* @param �`��̃^�C�v
		*/
		virtual void Draw(DrawType drawType) const{}

	public:

		// �`�悷�邷�邩�̗L��
		bool enabled = true;

		// �����_�[�L���[
		int renderQueue = RenderQueue_geometry;

		// �V�F�[�_
		ShaderPtr shader;

		// �e�V�F�[�_
		ShaderPtr shadowShader;
	};
	using RendererPtr = std::shared_ptr<Renderer>;
}

#endif // !FGENGINE_RENDERER_H_INCLUDED
