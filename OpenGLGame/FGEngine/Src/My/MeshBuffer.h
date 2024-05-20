/**
* @file MeshBuffer.h
*/
#ifndef FGENGINE_MESHBUFFER_H_INCLUDED
#define FGENGINE_MESHBUFFER_H_INCLUDED
#include "Package/Glad.h"
#include <unordered_map>
#include <functional>

namespace FGEngine
{
	// ��s�錾
	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	using MaterialList = std::vector<MaterialPtr>;
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	namespace RenderingSystem
	{
		class BufferObject;
		using BufferObjectPtr = std::shared_ptr<BufferObject>;
		class VertexArrayObject;
		using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;
		struct DrawParams;
		struct Vertex;
		class MeshBuffer;
		using MeshBufferPtr = std::shared_ptr<MeshBuffer>;

		/**
		* ���_�f�[�^���Ǘ�����N���X
		*/
		class MeshBuffer
		{
		public:

			/**
			* �R���X�g���N�^
			*
			* @param bufferSize �i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
			*/
			MeshBuffer(size_t bufferSize);

			/**
			* �f�X�g���N�^
			*/
			~MeshBuffer() = default;

			// �R�s�[�Ƒ�����֎~
			MeshBuffer(const MeshBuffer&) = delete;
			MeshBuffer& operator=(const MeshBuffer&) = delete;

			/**
			* ���b�V���o�b�t�@���쐬
			*
			* @param bufferSize	�i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
			*
			* @return �쐬�������b�V���o�b�t�@�|�C���^�[
			*/
			static MeshBufferPtr Create(size_t bufferSize);

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
			* @param filename Obj�t�@�C����
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

		private:

			/**
			* MTL�t�@�C����ǂݍ���
			*
			* @param foldername	OBJ�t�@�C���̂���t�@���_��
			* @param filename	MTL�t�@�C����
			*
			* @return MTL�t�@�C���Ɋ܂܂��}�e���A���̔z��
			*/
			MaterialList LoadMTL(const std::string& foldername, const char* filename);

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

			// �X�^�e�B�b�N���b�V���z��
			std::unordered_map<std::string, StaticMeshPtr> meshes;

			// �`��p�����[�^�z��
			std::vector<DrawParams> drawParamsList;

			// �o�b�t�@�̎g�p�ςݗe��(�o�C�g)
			size_t usedBytes = 0;

			// �}�e���A�����ݒ莞�Ɏg�p����}�e���A��
			MaterialPtr defaultMaterial;

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
}
#endif // !MESH_H_INCLUDE