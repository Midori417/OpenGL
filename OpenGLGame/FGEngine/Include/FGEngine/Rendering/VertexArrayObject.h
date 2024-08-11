/**
* @file VertexArrayObject.h
*/
#ifndef FGENGINE_VECTEXARRAYOBJECT_H_INCLUDED
#define FGENGINE_VECTEXARRAYOBJECT_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include <memory>

namespace FGEngine::RenderingSystem
{
	// ��s�錾
	class VertexArrayObject;
	using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;

	/**
	* ���_�z��I�u�W�F�N�g(VAO)
	*
	* ���_�o�b�t�@�Ɋi�[����Ă��钸�_�f�[�^�ɂ���
	* �e�v�f���ǂ̂悤�ɔz�u����Ă��邩���L�q����I�u�W�F�N�g
	*/
	class VertexArrayObject
	{
	public:
		
		// �R���X�g���N�^�E�f�X�g���N�^
		VertexArrayObject();
		~VertexArrayObject();

		// �R�s�[�Ƒ�����֎~
		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		/**
		* ���_�z��I�u�W�F�N�g���쐬����
		*
		* @return �쐬�������_�z��I�u�W�F�N�g�̃|�C���^�[
		*/
		static VertexArrayObjectPtr Create();

		/**
		* ���_�z��I�u�W�F�N�g�̊Ǘ��ԍ����擾
		*/
		operator GLuint() const
		{
			return id;
		}

		/**
		* ���_�A�g���r���[�g��ݒ�
		*
		* @param index	�ݒ肷�钸�_�A�g���r���[�g�̔ԍ�(0�`15)
		* @param size	�v�f�̃f�[�^��
		* @param stride	���̒��_�f�[�^�ɂ��铯��v�f�܂ł̊��o(�o�C�g��)
		* @param offset ���_�f�[�^���ɂ�����v�f�̈ʒu(�o�C�g��)
		*/
		void SetAttribute(GLuint index, GLint size, size_t stride, size_t offset);

	private:

		// VertexArrayObject�̊Ǘ��ԍ�
		GLuint id = 0; 
	};
}
#endif // !VECTEXARRAYOBJECT_H_INCLUDED
