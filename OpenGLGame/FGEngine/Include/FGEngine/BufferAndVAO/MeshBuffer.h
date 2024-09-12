/**
* @file MeshBuffer.h
*/
#ifndef FGENGINE_MESHBUFFER_H_INCLUDED
#define FGENGINE_MESHBUFFER_H_INCLUDED
#include "BufferAndVAOFrd.h"
#include "FGEngine/UsingNames/UsingAsset.h"
#include <unordered_map>
#include <functional>
#include <string>

namespace FGEngine
{
	struct Vertex;
	struct DrawParams;
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;

	/**
	* ���_�f�[�^���Ǘ�����N���X
	*/
	class MeshBuffer
	{
	public:	// �R���X�g���N�^�E�f�X�g���N�^

		/**
		* �R���X�g���N�^
		*
		* @param bufferSize �i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		*/
		MeshBuffer(size_t bufferSize);

		/**
		* �f�X�g���N�^
		*/
		~MeshBuffer();

	public:	// �֎~����

		// �R�s�[�Ƒ�����֎~
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

	public:

		/**
		* ���b�V���o�b�t�@���쐬
		*
		* @param bufferSize	�i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		*
		* @return �쐬�������b�V���o�b�t�@�|�C���^�[
		*/
		static MeshBufferPtr Create(size_t bufferSize);

	public:

		/**
		* Obj�t�@�C���̓ǂݍ���
		*
		* @param name �ۑ����閼�O
		* @param filename Obj�t�@�C����
		*/
		StaticMeshPtr LoadObj(const std::string& name, const std::string& filename);

	private:

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
			size_t stride, GLenum mode);
		void AddVertexData(const void* vertices, size_t vertexBytes,
			const uint16_t* indices, size_t indexBytes,
			size_t stride);

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
	void Draw(const ShaderPtr& shader, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials);

	/**
	* �X�^�e�B�b�N���b�V����`�悷��
	*
	* @param mesh		�X�^�e�B�b�N���b�V��
	* @param materials	�}�e���A���z��
	*/
	void Draw(const ShaderPtr& shader, const StaticMesh& mesh, const MaterialList& materials);

	// �����Ă���@����₤
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE