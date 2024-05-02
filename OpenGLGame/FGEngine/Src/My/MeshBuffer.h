/**
* @file MeshBuffer.h
*/
#ifndef FGENGINE_MESHBUFFER_H_INCLUDED
#define FGENGINE_MESHBUFFER_H_INCLUDED

#include "Package/Glad.h"
#include "Mesh.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "Material.h"
#include <unordered_map>
#include <functional>

namespace FGEngine::RenderingSystem
{
	// ��s�錾
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	struct Vertex;

	/**
	* ���_�f�[�^���Ǘ�����N���X
	*/
	class MeshBuffer
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		MeshBuffer(size_t bufferSize);
		~MeshBuffer() = default;

		// �R�s�[�Ƒ�����֎~
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

		/**
		* ���b�V���o�b�t�@���쐬
		*
		* @param bufferSize	�i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		*/
		static MeshBufferPtr Create(size_t bufferSize)
		{
			return std::make_shared<MeshBuffer>(bufferSize);
		}

		/**
		* ���_�f�[�^�̒ǉ�
		*
		* @param vertices		GPU�������ɃR�s�[���钸�_�f�[�^�z��
		* @param vertexBytes	vertices�̃o�C�g��
		* @param indices		GPU�������ɂɃR�s�[����C���f�b�N�X�f�[�^�z��
		* @param indexBytes		indcies�̃o�C�g��
		* @param mode			�v���~�e�B�u�̎��
		*/
		void AddVertexData(const void* vertices, size_t vertexBytes,
			const uint16_t* indices, size_t indexBytes,
			size_t stride, GLenum mode = GL_TRIANGLES);

		/**
		* ���ׂĂ̒��_�f�[�^�̍폜
		*/
		void Clear();

		/**
		* Obj�t�@�C���̓ǂݍ���
		*
		* @param name �ۑ����閼�O
		* @param filename Obj�t�@�C���̈ʒu
		*/
		void LoadObj(const std::string& name, const std::string& filename);


		/**
		* �X�^�e�B�b�N���b�V���̎擾
		* 
		* @param name �擾�������X�^�e�B�b�N���b�V���̖��O
		* 
		* @param name�ɑΉ������X�P���^�����b�V��
		*/
		StaticMeshPtr GetStaticMesh(const std::string& name) const;

		/**
		* �X�P���^�����b�V���̎擾
		* 
		* @param name �擾�������X�P���^�����b�V���̖��O
		* 
		* @return name�ɑΉ������X�P���^�����b�V��
		*/
		SkeletalMeshPtr GetSkeletalMesh(const std::string& name) const;

		/**
		* VAO�̎擾
		*/
		VertexArrayObjectPtr GetVAO() const
		{
			return vao;
		}

		/**
		* SkeletalVAO�̎擾
		* */
		VertexArrayObjectPtr GetSkeletalVAO() const
		{
			return vaoSkeletal;
		}

	private:

		/**
		* MTL�t�@�C����ǂݍ���
		*
		* @param foldername	OBJ�t�@�C���̂���t�@���_��
		* @param filename	MTL�t�@�C����
		*
		* @return MTL�t�@�C���Ɋ܂܂��}�e���A���̔z��
		*/
		std::vector<MaterialPtr> LoadMTL(const std::string& foldername, const char* filename);

		/**
		* ���b�V���\�z�p�̒��ԃf�[�^
		*/
		struct MeshData
		{
			std::vector<Vertex> vertices;	// ���_�f�[�^
			std::vector<uint16_t> indices;	// �C���f�b�N�X�f�[�^
			std::vector<DrawParams> drawParamsList; // �`��p�����[�^�z��
			MaterialList materials;
		};
		/**
		* OBJ�t�@�C�������b�V���f�[�^��ϊ�����
		*
		* @param filename OBJ�t�@�C����
		*
		* @return filename����쐬�������b�V���f�[�^
		*/
		MeshData CreateMeshDataFormObj(const std::string& filename);

	private:
		
		// ���_�f�[�^����уC���f�b�N�X�f�[�^
		BufferObjectPtr buffer;

		// �X�^�e�B�b�N���b�V�����_�A�g���r���[�g
		VertexArrayObjectPtr vao;

		//�X�P���^�����b�V�����_�A�g���r���[�g
		VertexArrayObjectPtr vaoSkeletal;

		// �X�^�e�B�b�N���b�V���z��
		std::unordered_map<std::string, StaticMeshPtr> meshes;

		// �X�P���^�����b�V���z��
		std::unordered_map<std::string, SkeletalMeshPtr> skeletalMeshes;

		// �`��p�����[�^�z��
		std::vector<DrawParams> drawParamsList;

		// �o�b�t�@�̎g�p�ςݗe��(�o�C�g)
		size_t usedBytes = 0;

	};

	/**
	* �`��p�����[�^�͔z���`�悷��
	* 
	* @param drawParamList	�`��p�����[�^�z��
	* @param materials		�}�e���A���z��
	*/
	void Draw(GLuint program, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials);

	/**
	* �X�^�e�B�b�N���b�V����`�悷��
	* 
	* @param mesh		�X�^�e�B�b�N���b�V��
	* @param materials	�}�e���A���z��
	*/
	void Draw(GLuint program, const StaticMesh& mesh, const MaterialList& materials);

	// �����Ă���@����₤
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE