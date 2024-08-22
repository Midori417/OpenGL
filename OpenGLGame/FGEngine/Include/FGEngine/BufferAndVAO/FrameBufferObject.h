/**
* @file FrameBufferObject.h
*/
#ifndef FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#define FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#include "BufferAndVAOFrd.h"
#include "FGEngine/UsingNames/UsingAsset.h"

namespace FGEngine
{
	/**
	* �t���[���o�b�t�@�E�I�u�W�F�N�g(FBO)
	*/
	class FrameBufferObject
	{
	public:	// �R���X�g���N�^�E�f�X�g���N�^

		/**
		* �����̃e�N�X�`������FBO���쐬����
		*
		* @param color �J���[�o�b�t�@
		* @param depth �[�x�o�b�t�@
		*/
		FrameBufferObject(const TexturePtr& color, const TexturePtr& depth);

		/**
		* �f�X�g���N�^
		*/
		~FrameBufferObject();

	public:	// �֎~����

		// �R�s�[���֎~
		FrameBufferObject(const FrameBufferObject&) = delete;

		// ������֎~
		FrameBufferObject& operator=(const FrameBufferObject&) = delete;

	public:

		/**
		* �t���[���o�b�t�@�I�u�W�F�N�g���쐬
		* 
		* @param color �J���[�o�b�t�@
		* @param depth �[�x�o�b�t�@
		*
		* @return �쐬�����t���[���o�b�t�@�I�u�W�F�N�g�|�C���^�[
		*/
		static FrameBufferObjectPtr Create(const TexturePtr& color, const TexturePtr& depth);

	public:

		/**
		* �Ǘ��ԍ����擾
		*/
		operator GLuint() const;

		/**
		* ���̎擾
		*/
		int GetWidth() const;

		/**
		* �����̎擾
		*/
		int GetHeight() const;

		/**
		* �J���[�e�N�X�`�����擾
		*/
		const TexturePtr& GetColorTexture() const;

		/**
		* �[�x�e�N�X�`�����擾
		*/
		const TexturePtr& GetDepthTexture() const;

	private:

		// FBO�̊Ǘ��ԍ�
		GLuint id;

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
