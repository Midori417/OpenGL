/**
* @file FrameBufferObject.cpp
*/
#include "FrameBufferObject.h"
#include "Debug.h"

namespace FGEngine::Rendering::Rall
{
	/**
	* �����̃e�N�X�`������FBO���쐬����
	* 
	* @param color �J���[�o�b�t�@
	* @param depth �[�x�o�b�t�@
	*/
	FrameBufferObject::FrameBufferObject(const TexturePtr& color, const TexturePtr& depth)
		: texColor(color), texDepth(depth)
	{
		glCreateFramebuffers(1, &fbo);

		// �J���[�o�b�t�@��ݒ�
		if (color)
		{
			glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, *color, 0);
			widht = texColor->GetWidth();
			height = texColor->GetHeight();
		}
		else
		{
			// �e�N�X�`�������蓖�ĂȂ�
			glNamedFramebufferDrawBuffer(fbo, GL_NONE);
		}

		// �[�x�o�b�t�@��ݒ�
		if (depth)
		{
			glNamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, *depth, 0);
			widht = texDepth->GetWidth();
			height = texDepth->GetHeight();
		}

		// FBO�̃G���[�`�F�b�N
		if (glCheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glDeleteFramebuffers(1, &fbo);
			fbo = 0;
			texColor.reset();
			texDepth.reset();
			LOG_ERROR("FBO�̍쐬�Ɏ��s");
			return;
		}

		// �쐬����
		LOG("FBO(width=%d, height=%d)���쐬", widht, height);

	}

	/**
	* �f�X�g���N�^
	*/
	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &fbo);
	}

	/**
	* FraneBufferObject���쐬
	*
	* @param color �J���[�o�b�t�@
	* @param depth �[�x�o�b�t�@
	*
	* @return �쐬�����t���[���o�b�t�@�I�u�W�F�N�g�|�C���^�[
	*/
	FrameBufferObjectPtr FrameBufferObject::Create(const TexturePtr& color, const TexturePtr& depth)
	{
		return std::make_shared<FrameBufferObject>(color, depth);
	}
}