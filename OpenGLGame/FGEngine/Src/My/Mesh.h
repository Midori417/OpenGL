/**
* @file Mesh.h
*/
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Package/Glad.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "VecMath.h"
#include "Material.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace FGEngine
{
	// ��s�錾
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;

	/**
	* ���_�f�[�^�`��
	*/
	struct Vertex
	{
		Vector3 position;	// ���_���W
		Vector2 texcoord;	// �e�N�X�`�����W
		Vector3 normal;	// �@���x�N�g��
	};

	/**
	* �`��p�����[�^
	*/
	struct DrawParams
	{
		GLenum mode = GL_TRIANGLES;	// �v���~�e�B�u�̎��
		GLsizei count = 0;			// �`�悷��C���f�b�N�X�̐�
		const void* indices = 0;	// �`��J�n�C���f�b�N�X�̃o�C�g�I�t�Z�b�g
		GLint baseVertex = 0;		// �C���f�b�N�X0�ƂȂ钸�_�z����̈ʒu

		int materialNo = -1;		// MaterialIndex
	};

	/**
	* 3D���f��
	*/
	struct StaticMesh
	{
		std::string name;	// ���b�V����
		std::vector<DrawParams> drawParamsList;	// �`��p�����[�^
		MaterialList materials;		// �}�e���A���z��
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	void Draw(const StaticMesh& mesh, GLuint program, const MaterialList& materials);

	// ���L�}�e���A���z��𕡐�
	inline MaterialList CloneMaterialList(const StaticMeshPtr& original) {
		MaterialList clone(original->materials.size());
		for (int i = 0; i < clone.size(); ++i) {
			clone[i] = std::make_shared<Material>(*original->materials[i]);
		}
		return clone;
	}


	/**
	* ���_�f�[�^���Ǘ�����N���X
	*/
	class MeshBuffer
	{
	public:

		MeshBuffer(size_t bufferSize);
		~MeshBuffer() = default;

		// �R�s�[�Ƒ�����֎~
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

		// �e�N�X�`���쐬�R�[���o�b�N�^
		using TextureCallback = std::function<TexturePtr(const char*)>;

		// �e�N�X�`���쐬�R�[���o�b�N��ݒ肷��
		void SetTextureCallback(const TextureCallback& callback) {
			textureCallback = callback;
		}

		/**
		* ���b�V���o�b�t�@���쐬
		*
		* @param bufferSize	�i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		*/
		static MeshBufferPtr Create(size_t bufferSize) {
			return std::make_shared<MeshBuffer>(bufferSize);
		}

		// ���_�f�[�^�̒ǉ�
		void AddVertexData(const Vertex* vertices, size_t vertexBytes, const uint16_t* indices, size_t indexBytes, GLenum mode = GL_TRIANGLES);

		// �����̕`��p�����[�^�ƃe�N�X�`������V�����X�^�e�B�b�N���b�V�����쐬����
		StaticMeshPtr CreateStaticMesh(const char* name, const DrawParams& params, const TexturePtr& texBaseColor);

		// ���ׂĂ̒��_�f�[�^�̍폜
		void Clear();

		// �`��p�����[�^�̎擾
		inline const DrawParams& GetDrawParams(size_t index) const {
			return drawParamsList[index];
		}

		// �`��p�����[�^�̐����擾
		size_t GetDrawParamsCount() const {
			return drawParamsList.size();
		}

		// VAO�̎擾
		VertexArrayObjectPtr GetVAO() const {
			return vao;
		}

		// �X�^�e�B�b�N���b�V���̎擾
		StaticMeshPtr GetStaticMesh(const char* name) const;

		// OBJ�t�@�C����ǂݍ���
		StaticMeshPtr LoadObj(const char* filename);

	private:

		// MTL�t�@�C����ǂݍ���
		std::vector<MaterialPtr> LoadMTL(const std::string& foldername, const char* filename);

	private:

		std::unordered_map<std::string, StaticMeshPtr> meshes;
		std::vector<DrawParams> drawParamsList;	// �`��p�����[�^�z��
		VertexArrayObjectPtr vao;	// ���_�A�g���r���[�g�z��
		BufferObjectPtr buffer;		// ���_�f�[�^����уC���f�b�N�X�f�[�^
		size_t usedBytes = 0;		// �o�b�t�@�̎g�p�ςݗe��(�o�C�g)
		TextureCallback textureCallback;	// �e�N�X�`���쐬�R�[���o�b�N
	};

	// �����Ă���@����₤
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE
