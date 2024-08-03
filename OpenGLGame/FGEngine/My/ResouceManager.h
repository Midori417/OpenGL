/**
* @file ResouceManager.h
*/
#ifndef FGENGINE_RESOUCEMANAGER_H_INCLUDED
#define FGENGINE_RESOUCEMANAGER_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include "Shader.h"
#include "DefalutShader.h"
#include <string>
#include <unordered_map>

namespace FGEngine
{
	// ��s�錾
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;
	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;

	namespace RenderingSystem
	{
		class MeshBuffer;
		using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
		class GltfFileBuffer;
		using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;
	}

	namespace ResouceSystem
	{
		/**
		* ���\�[�X�}�l�[�W���[
		*/
		class ResouceManager : public Singleton<ResouceManager>
		{
		private:

			friend MainSystem::EngineCore;
			friend RenderingSystem::RenderingEngine;
			friend Singleton<ResouceManager>;
			friend ObjectSystem::ObjectManager;

			// �R���X�g���N�^
			ResouceManager() = default;

			/**
			* ���\�[�X�}�l�[�W���[��������
			* 
			* @retval 0		����������
			* @retval 0�ȊO	���������s
			*/
			int Initialize();

		public:

			/**
			* tga�t�@�C����ǂݍ���
			* 
			* @param name		�ۑ����閼�O
			* @param filename	Tga�t�@�C����
			*/
			void LoadTga(const std::string& name, const std::string& filename, GLenum fileterMode = GL_NEAREST);

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
			* �V�F�[�_�t�@�C����ǂݍ���
			* 
			* @param name		�V�F�[�_�̖��O
			* @param filenameVS �o�[�e�b�N�X�V�F�[�_�t�@�C��
			* @param filenameFS �t���O�����g�V�F�[�_�t�@�C��
			*/
			void LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS,
				bool isNormal = false, bool isShadow = false, bool isLight = false, bool isUseLight = false);

			/**
			* �e�N�X�`�����擾
			* 
			* @param name �e�N�X�`���̖��O
			* 
			* @return name�ɂ������e�N�X�`��
			*/
			TexturePtr GetTexture(const std::string& name);

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
			RenderingSystem::MeshBufferPtr meshBuffer;

			// glTFFile�o�b�t�@
			RenderingSystem::GltfFileBufferPtr gltfFileBuffer;
		};

		/**
		* ���L�}�e���A���z��𕡐�
		*/ 
		std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

	}
}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
