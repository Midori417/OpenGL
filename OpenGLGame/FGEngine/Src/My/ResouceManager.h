/**
* @file ResouceManager.h
*/
#ifndef FGENGINE_RESOUCEMANAGER_H_INCLUDED
#define FGENGINE_RESOUCEMANAGER_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include "ShaderObject.h"
#include "ShapeType.h"
#include "DefalutShader.h"
#include <string>
#include <unordered_map>

namespace FGEngine
{
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;
	class StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	class SkeletalMesh;
	using SkeletalMeshPtr = std::shared_ptr<SkeletalMesh>;
	class ShaderObject;
	using ShaderObjectPtr = std::shared_ptr<ShaderObject>;
	class Material;
	using MaterialPtr = std::shared_ptr<Material>;


	namespace RenderingSystem
	{
		class MeshBuffer;
		using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
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

			std::unordered_map<std::string, ShaderObjectPtr>* GetShaderList()
			{
				return &shaderCache;
			}

		public:

			/**
			* tga�t�@�C����ǂݍ���
			* 
			* @param name		�e�N�X�`���̖��O
			* @param filename	Tga�t�@�C����
			*/
			void LoadTga(const std::string& name, const std::string& filename);

			/**
			* OBJ�t�@�C����ǂݍ���
			* 
			* @param name		���b�V���̖��O
			* @param filename	Obj�t�@�C����
			* @param meshData	�ڎ�̎��
			*/
			void LoadObj(const std::string& name, const std::string& filename);

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
			* �f�t�H���g�X�^�e�B�b�N���b�V�����擾
			* 
			* @param primitiveType	�v���~�e�B�u�̃^�C�v
			* 
			* @returun primitiveType�ɂ������X�^�e�B�b�N���b�V��
			*/
			StaticMeshPtr GetStaticMesh(ShapeType primitiveType);

			/**
			* �X�P���^�����b�V�����擾
			* 
			* @param name �X�P���^�����b�V���̖��O
			* 
			* @return name�ɂ������X�P���^�����b�V��
			*/
			SkeletalMeshPtr GetSkeltalMesh(const std::string& name);

			/**
			* �V�F�[�_�[���擾
			* 
			* @param name �V�F�[�_�[�̖��O
			* 
			* @return name�ɂ������V�F�[�_
			*/
			ShaderObjectPtr GetShader(const std::string& name);

			/**
			* �f�t�H���g�V�F�[�_�[���擾
			*
			* @param shader	�V�F�[�_�[
			*
			* @return shader�ɂ������V�F�[�_
			*/
			ShaderObjectPtr GetShader(DefalutShader shader);

		private:

			// �e�N�X�`���L���b�V��
			std::unordered_map<std::string, TexturePtr> textureCache;

			// �V�F�[�_�L���b�V��
			std::unordered_map<std::string, ShaderObjectPtr> shaderCache;

			// ���b�V���o�b�t�@
			RenderingSystem::MeshBufferPtr meshBuffer;
		};

		/**
		* ���L�}�e���A���z��𕡐�
		*/ 
		std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

	}
}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
