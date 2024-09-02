/**
* @file AssetManager.h
*/
#ifndef FGENGINE_ASSETMANAGER_H_INCLUDED
#define FGENGINE_ASSETMANAGER_H_INCLUDED
#include "FGEngine/SystemFrd.h"
#include "FGEngine/Singleton.h"
#include "FGEngine/UsingNames/UsingAsset.h"
#include "FGEngine/Asset/DefalutShader.h"
#include <unordered_map>

typedef unsigned int GLenum;

namespace FGEngine
{
	// ��s�錾
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* �A�Z�b�g�}�l�[�W���[
	*/
	class AssetManager : public Singleton<AssetManager>
	{
		friend MainSystem::EngineCore;
		friend Singleton<AssetManager>;
	private:	// �R���X�g���N�^

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		AssetManager() = default;

	private:

		/**
		* ���\�[�X�}�l�[�W���[��������
		*
		* @retval 0		����������
		* @retval 0�ȊO	���������s
		*/
		int Initialize();

	public:

		/**
		* Gltf�t�@�C�����擾
		*/
		GltfFileBuffer* GetGltfFileBuffer() const;

	public:		// �e�N�X�`��

		/**
		* tga�t�@�C����ǂݍ���
		*
		* @param name		�ۑ����閼�O
		* @param filename	Tga�t�@�C����
		*/
		void LoadTga(const std::string& name, const std::string& filename, GLenum fileterMode);
		void LoadTga(const std::string& name, const std::string& filename);

		/**
		* �e�N�X�`�����擾
		*
		* @param name �e�N�X�`���̖��O
		*
		* @return name�ɂ������e�N�X�`��
		*/
		TexturePtr GetTexture(const std::string& name);

	public:		// ���b�V��

		/**
		* OBJ�t�@�C����ǂݍ���
		*
		* @param name		�ۑ����閼�O
		* @param filename	Obj�t�@�C����
		*/
		void LoadObj(const std::string& name, const std::string& filename);

		/**
		* glTF�t�@�C����ǂݍ���
		*
		* @param name		�ۑ����閼�O
		* @param filename	Gltf�t�@�C����
		*/
		void LoadGlTF(const std::string& name, const std::string& filename);

		/**
		* �X�^�e�B�b�N���b�V�����擾
		*
		* @param name �X�^�e�B�b�N���b�V���̖��O
		*
		* @return name�ɂ������X�^�e�B�b�N���b�V��
		*/
		StaticMeshPtr GetStaticMesh(const std::string& name);

		/**
		* glTF�t�@�C�����擾
		*
		* @param name glTF�t�@�C���̖��O
		*
		* @return name�ɂ�����glTF�t�@�C��
		*/
		GltfFilePtr GetGltfFile(const std::string& name);

	public:		// �V�F�[�_

		/**
		* �V�F�[�_�t�@�C����ǂݍ���
		*
		* @param name		�V�F�[�_�̖��O
		* @param filenameVS �o�[�e�b�N�X�V�F�[�_�t�@�C��
		* @param filenameFS �t���O�����g�V�F�[�_�t�@�C��
		*/
		void LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

		/**
		* �V�F�[�_�[���擾
		*
		* @param name �V�F�[�_�[�̖��O
		*
		* @return name�ɂ������V�F�[�_
		*/
		ShaderPtr GetShader(const std::string& name);

		/**
		* �f�t�H���g�V�F�[�_�[���擾
		*
		* @param shader	�V�F�[�_�[
		*
		* @return shader�ɂ������V�F�[�_
		*/
		ShaderPtr GetShader(DefalutShader shader);

	private:

		// �e�N�X�`���L���b�V��
		std::unordered_map<std::string, TexturePtr> textureCache;

		// �V�F�[�_�L���b�V��
		std::unordered_map<std::string, ShaderPtr> shaderCache;

		// ���b�V���o�b�t�@
		MeshBufferPtr meshBuffer;

		// glTFFile�o�b�t�@
		GltfFileBufferPtr gltfFileBuffer;
	};

	/**
	* ���L�}�e���A���z��𕡐�
	*/
	std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
