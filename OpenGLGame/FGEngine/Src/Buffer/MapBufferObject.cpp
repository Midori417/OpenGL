/**
* @file MapBufferObject.cpp
*/
#include "FGEngine/Buffer/MapBufferObjecth.h"
#include "FGEngine/Debug.h"

namespace FGEngine
{
	/**
	* �o�b�t�@�I�u�W�F�N�g���쐬����
	*
	* @parma size		�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
	* @param type		�o�b�t�@�I�u�W�F�N�g�̎��
	* @param access		�ȉ��̂����ꂩ���w�肷��
	*					GL_READ_WRITE �ǂݎ�菑�����݂̗��Ή��Ń}�b�v����
	*					GL_READ_ONLY�@�ǂ݂Ƃ��p�Ƃ��ă}�b�v����
	*					GL_WRITE_ONLY �������ݐ�p�Ƃ��ă}�b�v����
	*/
	MappedBufferObject::MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access)
		:type(type)
	{
		// �_�u���o�b�t�@�̂��߁A�T�C�Y��256�o�C�g���E�ɌJ��グ��
		bufferSize = ((size + 255) / 256) * 256;

		// �A�N�Z�X�̎�ނɂ���ăt���O��I��
		GLbitfield flags = GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		switch (access)
		{
		default:
			LOG_ERROR("�������Ԉ���Ă��܂�(access=%d)", access);

			// �t�H�[�X���[����
			// break���ȗ��\��break�ɉ�܂Ō㑱��case�u���b�N�����s����
			[[fallthrough]];
		case GL_READ_WRITE:
			flags |= GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
			break;
		case GL_READ_ONLY:
			flags |= GL_MAP_READ_BIT;
			break;
		case GL_WRITE_ONLY:
			flags |= GL_MAP_WRITE_BIT;
			break;
		}

		// �o�b�t�@�I�u�W�F�N�g���쐬
		glCreateBuffers(2, id);
		glNamedBufferStorage(id[0], bufferSize, nullptr, flags);
		glNamedBufferStorage(id[1], bufferSize, nullptr, flags);

		// GPU��������CPU�������A�h���X�Ƀ}�b�v����
		p[0] = static_cast<uint8_t*>(glMapNamedBuffer(id[0], access));
		p[1] = static_cast<uint8_t*>(glMapNamedBuffer(id[1], access));
	}

	/**
	* �f�X�g���N�^
	*/
	MappedBufferObject::~MappedBufferObject()
	{
		glDeleteBuffers(2, id);
	}

	/**
	* �o�b�t�@�I�u�W�F�N�g���쐬����
	*
	* @parma size		�o�b�t�@�I�u�W�F�N�g�̃o�C�g�T�C�Y
	* @param type		�o�b�t�@�I�u�W�F�N�g�̎��
	* @param access		�ȉ��̂����ꂩ���w�肷��
	*					GL_READ_WRITE �ǂݎ�菑�����݂̗��Ή��Ń}�b�v����
	*					GL_READ_ONLY�@�ǂ݂Ƃ��p�Ƃ��ă}�b�v����
	*					GL_WRITE_ONLY �������ݐ�p�Ƃ��ă}�b�v����
	*
	* @return �쐬�����o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
	*/
	MappedBufferObjectPtr MappedBufferObject::Create(GLsizeiptr size, GLenum type, GLenum acceess)
	{
		return std::make_shared<MappedBufferObject>(size, type, acceess);
	}

	/**
	* �o�b�t�@�I�u�W�F�N�g�̊Ǘ��ԍ����擾
	*/
	MappedBufferObject::operator GLuint() const
	{
		return id[bufferIndex];
	}

	/**
	* �o�b�t�@�T�C�Y���擾
	*/
	GLsizeiptr MappedBufferObject::GetSize() const
	{
		return bufferSize;
	}

	/**
	* GPU���o�b�t�@���g���I���̂�҂�
	*/
	void MappedBufferObject::WaitSync()
	{
		for (GLsync& sync = syncList[bufferIndex]; sync;)
		{
			const GLuint64 timeout = 16'700'000;	// 16.7�~���b(��1/60�b)
			const GLenum status = glClientWaitSync(sync, 0, timeout);
			if (status != GL_TIMEOUT_EXPIRED)
			{
				// �g���I����������I�u�W�F�N�g�͍폜���Ȃ��Ă͂Ȃ�Ȃ�
				glDeleteSync(sync);
				sync = 0;
				break;
			}
		}
	}

	/**
	* �f�[�^�̃R�s�[��A�h���X���擾����
	*
	* @return �R�s�[��A�h���X
	*/
	uint8_t* MappedBufferObject::GetMappedAddress() const
	{
		return p[bufferIndex];
	}

	/**
	* �w�肵���͈͂�OpenGL�R���e�L�X�g�Ɋ��蓖�Ă�
	*
	* @parma index	���蓖�Ă�o�C���f�B���O�|�C���g�ԍ�
	* @param offset	���蓖�Ĕ͈͂̐擪�ʒu
	* @parma size	���蓖�Ĕ͈͂̃o�C�g�T�C�Y
	*/
	void MappedBufferObject::Bind(GLuint index, size_t offset, size_t size)
	{
		glBindBufferRange(type, index, id[bufferIndex], offset, size);
	}

	/**
	* �R�s�[��o�b�t�@��؂�ւ���
	*/
	void MappedBufferObject::SwapBuffers()
	{
		syncList[bufferIndex] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		bufferIndex = (bufferIndex + 1) % 2;
	}
}