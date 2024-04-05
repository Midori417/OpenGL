/**
* @file FrameBufferObject.h
*/
#ifndef FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#define FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include "Texture.h"

namespace FGEngine::Rendering
{
	// ��s�錾
	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;


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

		/**
		* �t���[���o�b�t�@�I�u�W�F�N�g���쐬
		* 
		* @param color �J���[�o�b�t�@
		* @param depth �[�x�o�b�t�@
		*
		* @return �쐬�����t���[���o�b�t�@�I�u�W�F�N�g�|�C���^�[
		*/
		static FrameBufferObjectPtr Create(const TexturePtr& color, const TexturePtr& depth);

		/**
		* �Ǘ��ԍ����擾
		*/
		operator GLuint() const
		{
			return fbo;
		}

		/**
		* ���̎擾
		*/
		int GetWidth() const
		{
			return widht;
		}

		/**
		* �����̎擾
		*/
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

		// FBO�̊Ǘ��ԍ�
		GLuint fbo;

		// FBO�̕�
		int widht = 0;

		// FBO�̍���
		int height = 0;

		// �J���[�e�N�X�`��
		TexturePtr texColor;

		// �[�x�e�N�X�`��
		TexturePtr texDepth;
	};
}
#endif // !FRAMEBUFFEROBJECT_H_INCLUDED
