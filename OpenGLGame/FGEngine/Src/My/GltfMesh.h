/**
* @file GltfMesh.h
*/
#ifndef GLTFMESH_H_INCLUDED
#define GLTFMESH_H_INCLUDED
#include "Package/Glad.h"
#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include "VecMath.h"
#include "Texture.h"
#include "Material.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "MapBufferObjecth.h"


namespace FGEngine::Rendering
{

	/**
	* �v���~�e�B�u�f�[�^
	*/
	struct GltfPrimitive
	{
		GLenum mode = GL_TRIANGLES;	// �v���~�e�B�u�̎��
		GLsizei count = 0;			// �`�悷��C���f�b�N�X��
		GLenum type = GL_UNSIGNED_SHORT;	// �C���f�b�N�X�f�[�^�^
		const GLvoid* indeices = 0;			// �`��J�n�C���f�b�N�X�̃I�t�Z�b�g
		GLint baseVertex = 0;				// �C���f�b�N�X0�ԂƂ݂Ȃ���钸�_�z����̈ʒu

		Rall::VertexArrayObjectPtr vao;	// �v���~�e�B�u�pVAO
		size_t materialNo = -1;	// �}�e���A���ԍ�
	};

	/**
	* ���b�V���f�[�^
	*/
	struct GltfMesh
	{
		std::string name;	// ���b�V����
		std::vector<GltfPrimitive> primitives;	// �v���~�e�B�u�z��
	};

	/**
	*�@�X�L��
	*/
	struct GltfSkinn
	{
		std::string name;	// �X�L����

		// �W���C���g(�{�[��)�f�[�^
		struct Joint
		{
			int nodeId;						// �W���C���g�Ή�����m�[�h�ԍ�
			Matrix4x4 matInverseBindPose;	// �t�o�C���h�|�[�Y�z��
		};
		std::vector<Joint> joints;	// �W���C���g�z��
	};

	/**
	* �m�[�h
	*/
	struct GltfNode
	{
		std::string name;					// �m�[�h��
		int mesh = -1;						// ���b�V���ԍ�
		int skin = -1;						// �X�L���ԍ�
		GltfNode* parent = nullptr;			// �e�m�[�h
		std::vector<GltfNode*> children;	// �q�m�[�h�z��
		Matrix4x4 matLocal = Matrix4x4(1);	// ���[�J���s��
		Matrix4x4 matGlobal = Matrix4x4(1);	// �O���[�o���z��
	};

	/**
	* �V�[��
	*/
	struct GltfScene
	{
		std::vector<const GltfNode*> nodes;		// �m�[�h�z��
		std::vector<const GltfNode*> meshNodes;	// ���b�V�������m�[�h�݂̂̔z��
	};

	/**
	* �A�j���[�V�����̕�ԕ��@
	*/
	enum class GltfInterpolation
	{
		step,		// ��ԑ�
		linear,		// ���`���
		cubicSpline,// 3���X�v���C�����	
	};

	/**
	* �A�j���[�V�����̃L�[�t���[��
	*/
	template<typename T>
	struct GltfKeyframe
	{
		float time;	// ����
		T value;	// �K�p����l
	};

	/**
	* �A�j���[�V�����̃`���l��
	*/
	template<typename T>
	struct GltfChannel
	{
		int targetNodeId;						// �l��K�p����m�[�hID
		GltfInterpolation interpolation;		// ��ԕ��@
		std::vector<GltfKeyframe<T>> keyframes;	// �L�[�t���[���z��
	};

	/**
	* �A�j���[�V����
	*/
	struct GltfAnimation
	{
		std::string name;		// �A�j���[�V������
		std::vector<GltfChannel<Vector3>> translations;	// ���s�ړ��`���l���̔z��
		std::vector<GltfChannel<Quaternion>> rotations;	// ��]�`���l���̔z��
		std::vector<GltfChannel<Vector3>> scales;		// �g��k���̃`���l���̔z��
		std::vector<int> staticNodes;	// �A�j���[�V�������Ȃ��m�[�hID�̔z��
		float totalTime = 0;
	};
	using GltfAnimationPtr = std::shared_ptr<GltfAnimation>;

	/**
	* �t�@�C��
	*/
	struct GltfFile
	{
		std::string name;							// �t�@�C����
		std::vector<GltfScene> scenes;				// �V�[���z��
		std::vector<GltfNode> nodes;				// �m�[�h�z��
		std::vector<GltfSkinn> skins;				// �X�L���z��
		std::vector<GltfMesh> meshes;				// ���b�V���z��
		std::vector<MaterialPtr> materials;		// �}�e���A���z��
		std::vector<GltfAnimationPtr> animations;	// �A�j���[�V����
		Matrix4x4 matRoot = Matrix4x4(1);			// ��{�p���s��
	};
	using GltfFilePtr = std::shared_ptr<GltfFile>;

	// �A�j���[�V�����p���W�ϊ��s��̔z��
	using GltfAnimationMatrices = std::vector<Matrix4x4>;

	// �`���l����̎w�肵�������̒l�����߂�
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode, const GltfAnimation* animation, float time);

	/**
	* @file glTF�t�@�C������ǂݍ��񂾃��b�V�����Ǘ�����N���X
	*/
	class GltfFileBuffer
	{
	public:

		// �R���X�g���N�^
		explicit GltfFileBuffer(size_t bufferCapacity, size_t maxMatrixCount);

		// �f�X�g���N�^
		~GltfFileBuffer() = default;

		/**
		* glTF�t�@�C���o�b�t�@���쐬
		*
		* @return �쐬����glTF�t�@�C���o�b�t�@
		*/
		static std::shared_ptr<GltfFileBuffer> Create(size_t bufferCapcity, size_t maxMatrixCount)
		{
			return std::make_shared<GltfFileBuffer>(bufferCapcity, maxMatrixCount);
		}

		/**
		* �t�@�C���̓ǂݍ���
		*
		* @return �ǂݍ���glTFFile
		*/
		GltfFilePtr Load(const char* filename);

		// �p���s��̔z��
		struct Range
		{
			GLintptr offset;
			size_t size;
		};

		// === �A�j���[�V�����̎p���s��o�b�t�@�̊Ǘ� === //
		void ClearAnimationBuffer();
		Range AddAnimationMatrices(const GltfAnimationMatrices& matBones);
		void UploadAnimationBuffer();
		void BindAnimationBuffer(GLuint bindingPoint, const Range& range);
		void UnbindAnimationBuffer(GLuint bindingPoint);


		// �e�N�X�`���쐬�R�[���o�b�N�^
		using TextureCallback = std::function<TexturePtr(const char*)>;

		// �e�N�X�`���쐬�R�[���o�b�N��ݒ肷��
		void SetTextureCallback(const TextureCallback& callback)
		{
			textureCallback = callback;
		}

	private:

		GltfFilePtr Parse(const char* text, const char* foldername);

	private:

		Rall::BufferObjectPtr buffer;			// bin�t�@�C����ǂݍ��ރo�b�t�@
		uint8_t* pBuffer = nullptr;		// �}�b�v���ꂽ�A�h���X
		GLsizeiptr curBufferSize = 0;	// �������ݍς݃f�[�^��
		MaterialPtr defaultMaterial;	// �}�e���A�����ݒ莞�Ɏg�p����}�e���A��

		// �t�@�C���Ǘ��p�̘A�z�z��
		std::unordered_map<std::string, GltfFilePtr> files;
		TextureCallback textureCallback;

		// �A�j���[�V�����̎p���s��o�b�t�@
		Rall::MappedBufferObjectPtr animationBuffer;
		GltfAnimationMatrices tmpAnimationBuffer;


	};
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* glTF���b�V����`�悷��
	*
	* @param mesh		�`�悷�郁�b�V��
	* @param materials	�`��Ɏg���}�e���A���z��
	* @param program	�`��v���O����
	*/
	void Draw(const GltfMesh& mesh, const std::vector<MaterialPtr>& materials, GLuint program);
}
#endif // !GLTFMESHBUFFER_H_INCLUDED
