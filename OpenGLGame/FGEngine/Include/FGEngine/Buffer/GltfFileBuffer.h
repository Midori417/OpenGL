/**
* @file GltfFileBuffer.h
*/
#ifndef FGENGINE_GLTFFILEBUFFER_H_INCLUDED
#define FGENGINE_GLTFFILEBUFFER_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include "FGEngine/Math//Matrix4x4.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace FGEngine
{
	// ��s�錾
	struct GltfNode;
	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	struct AnimationClip;

	// �A�j���[�V�����p���W�ϊ��s��̔z��
	using GltfAnimationMatrices = std::vector<Matrix4x4>;
	struct AnimMatrixRange;

	/**
	* �A�j���[�V�����̎p���s����v�Z����
	*
	* @param file			meshNode�����L����t�@�C���I�u�W�F�N�g
	* @param meshNode		���b�V�������m�[�h
	* @param animation		�v�Z�̌��ƂȂ�A�j���[�V����
	* @param time			�A�j���[�V�����̍Đ��ʒu
	*
	* @return �A�j���[�V������K�p�����p���s��̔z��
	*/
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode,
		const AnimationClip* animation, float time);

	/**
	* ��̃A�j���[�V�����̎p���s����Ԃ���
	*
	* @param file
	* @param nextAnimation
	* @param currentAnimation
	*/
	GltfAnimationMatrices InterpolationAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode,
		const AnimationClip* currentAnimation, float time, const AnimationClip* nextAnimation);

	class BufferObject;
	using BufferObjectPtr = std::shared_ptr<BufferObject>;
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* glTF�t�@�C�����Ǘ�����N���X
	*/
	class GltfFileBuffer
	{
	public:

		/**
		* �R���X�g���N�^
		*
		* @param bufferSize �i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		* @param maxMatrixCount	�A�j���[�V�����pSSBO�Ɋi�[�ł���ő�s��
		*/
		GltfFileBuffer(size_t bufferSize, size_t maxMatrixCount);

		// �f�X�g���N�^
		~GltfFileBuffer();

		/**
		* glTFFileBuffer���쐬
		*
		* @param bufferSize �i�[�ł��钸�_�f�[�^�̃T�C�Y(�o�C�g��)
		* @param maxMatrixCount	�A�j���[�V�����pSSBO�Ɋi�[�ł���ő�s��
		*
		* @return �쐬����glTFFileBuffer�|�C���^�[
		*/
		static GltfFileBufferPtr Create(size_t bufferSize, size_t maxMatrixCount);

		/**
		* glTF�t�@�C���̓ǂݍ���
		*
		* @parma name		�ۑ����������O
		* @parma filename	�t�@�C���̖��O
		*/
		void LoadGltf(const std::string& name, const std::string& filename);

		/**
		* glTF�t�@�C�����擾
		*
		* @parma name		�擾������glTF�t�@�C���̖��O
		*
		* @return glTF�t�@�C���|�C���^�[
		*/
		GltfFilePtr GetGltf(const std::string& name);

		/**
		* �A�j���[�V�������b�V���̕`��p�f�[�^�����ׂč폜
		*/
		void ClearAnimationBuffer();

		/**
		* �A�j���[�V�������b�V�����b�V���̕`��p�f�[�^��ǉ�
		*
		* @param matBones SSBO�ɒǉ�����p���s��̔z��
		*
		* @return matBones�悤�Ɋ��蓖�Ă�ꂽSSBO�͈̔�
		*/
		AnimMatrixRange AddAnimationMatrices(const GltfAnimationMatrices& matBones);

		/**
		* �A�j���[�V�������b�V���̕`��p�f�[�^��GPU�������ɃR�s�[
		*/
		void UploadAnimationBuffer();

		/**
		* �A�j���[�V�������b�V���̕`��Ɏg��SSBO�̈�Ɋ��蓖�Ă�
		*
		* @param bindingPoint	�o�C���f�B���O�|�C���g
		* @param range			�o�C���h����͈�
		*/
		void BindAnimationBuffer(GLuint bindingPoint, const AnimMatrixRange& range);

		/**
		* �A�j���[�V�������b�V���̕`��Ɏg��SSBO���@�̊��蓖�Ă���������
		*
		* @param bindingPoint	�o�C���f�B���O�|�C���g
		*/
		void UnbindAnimationBuffer(GLuint bindingPoint);

	private:

		/**
		* JSON�e�L�X�g����GltfFile�I�u�W�F�N�g���쐬����
		*
		* @param text		glTF��JOSN�e�L�X�g
		* @param foldernaem ���\�[�X�ǂݍ��ݗp�̃t�H���_
		*
		* @retval nullptr�ȊO	filename����쐬�����t�@�C���I�u�W�F�N�g
		* @rtaval nullptr		�ǂݍ��ݎ��s
		*/
		GltfFilePtr Parse(const char* text, const char* foldername);

	private:

		// bin�t�@�C����ǂݍ��݃o�b�t�@
		BufferObjectPtr buffer;

		// �}�b�v���ꂽ�A�h���X
		uint8_t* pBuffer = nullptr;

		// �������ݍς݃f�[�^��
		GLsizeiptr curBufferSize = 0;

		// �}�e���A�����ݒ莞�Ɏg�p����}�e���A��
		MaterialPtr defaultMaterial;

		// glTF�t�@�C���z��
		std::unordered_map<std::string, GltfFilePtr> glTFfiles;

		// �A�j���[�V�����̎p���s��o�b�t�@
		MappedBufferObjectPtr animationBuffer;

		GltfAnimationMatrices tmpAnimationBuffer;
	};
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;
}

#endif // !FGENGINE_GLTFFILEBUFFER_H_INCLUDED
