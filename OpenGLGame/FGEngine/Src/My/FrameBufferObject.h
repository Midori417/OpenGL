/**
* @file FrameBufferObject.h
*/
#ifndef FRAMEBUFFEROBJECT_H_INCLUDED
#define FRAMEBUFFEROBJECT_H_INCLUDED

#include "Package/Glad.h"
#include "Texture.h"

namespace FGEngine
{
	/**
	* �t���[���o�b�t�@�E�I�u�W�F�N�g(FBO)
	*/
	class FrameBufferObject
	{
	public:

		// �e�N�X�`������FBO���쐬����R���X�g���N�^
		FrameBufferObject(const TexturePtr& color, const TexturePtr& depth);
		~FrameBufferObject();

		// �R�s�[�Ƒ�����֎~
		FrameBufferObject(const FrameBufferObject&) = delete;
		FrameBufferObject& operator=(const FrameBufferObject&) = delete;

		// �Ǘ��ԍ����擾
		operator GLuint() const
		{
			return fbo;
		}

		// ���ƍ������擾
		int GetWidth() const
		{
			return widht;
		}
		int GetHeight() const
		{
			return height;
		}

		// �e�N�X�`�����擾
		const TexturePtr& GetColorTexture() const
		{
			return texColor;
		}
		const TexturePtr& GetDepthTexture() const
		{
			return texDepth;
		}

	private:

		GLuint fbo;		// FBO�̊Ǘ��ԍ�
		int widht = 0;	// FBO�̕�
		int height = 0;	// FBO�̍���
		TexturePtr texColor;	// �J���[�e�N�X�`��
		TexturePtr texDepth;	// �[�x�e�N�X�`��
	};
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;
}
#endif // !FRAMEBUFFEROBJECT_H_INCLUDED
