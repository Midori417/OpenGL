/**
* @file ResouceManager.cpp
*/
#include "ResouceManager.h"
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include "Debug.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "MeshBuffer.h"
#include "GltfFileBuffer.h"
#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)


namespace FGEngine::ResouceSystem
{
	/**
	* ���\�[�X�}�l�[�W���[��������
	* 
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int ResouceManager::Initialize()
	{
		// ���b�V���o�b�t�@���쐬
		this->meshBuffer = RenderingSystem::MeshBuffer::Create(32'000'000);
		// glTF�t�@�C���p�o�b�t�@��������
		const size_t maxAnimationModelCount = 64;	// �A�j���[�V�������郂�f����
		const size_t maxAnimationMatrixCount = 256;	// 1���f���̃{�[����
		gltfFileBuffer = RenderingSystem::GltfFileBuffer::Create(10'000'000, maxAnimationModelCount * maxAnimationMatrixCount);

		// �e�N�X�`���̓ǂݍ���
		LoadTga("white", "FGEngine/Res/Texture/white.tga");

		// �f�t�H���g���b�V����ǂݍ���
		LoadObj("Cube", "FGEngine/Res/Mesh/Cube/Cube.obj");
		LoadObj("Sphere", "FGEngine/Res/Mesh/Sphere/Sphere.obj");
		LoadObj("skySphere", "FGEngine/Res/Mesh/skySphere/sky_Sphere.obj");
		LoadObj("Plane", "FGEngine/Res/Mesh/Plane/Plane.obj");

		// �f�t�H���g�V�F�[�_�[�̓ǂݍ���
		LoadShader("Standard3D", "FGEngine/Res/Shader/standard3D.vert", "FGEngine/Res/Shader/standard3D.frag");
		LoadShader("Shadow3D", "FGEngine/Res/Shader/shadow3D.vert", "FGEngine/Res/Shader/shadow3D.frag");
		LoadShader("Unlit", "FGEngine/Res/Shader/unlit.vert", "FGEngine/Res/Shader/unlit.frag");
		LoadShader("Skeletal3D", "FGEngine/Res/Shader/skeletal3D.vert", "FGEngine/Res/Shader/standard3D.frag");
		LoadShader("ShadowSkeletal3D", "FGEngine/Res/Shader/shadowSkeletal3D.vert", "FGEngine/Res/Shader/shadow3D.frag");
		LoadShader("Particle", "FGEngine/Res/Shader/particle.vert", "FGEngine/Res/Shader/particle.frag");

		return 0;
	}
	/**
	* tga�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	Tga�t�@�C����
	*/
	void ResouceManager::LoadTga(const std::string& name, const std::string& filename, GLenum filterMode)
	{
		// ���łɓo�^����Ă��邽�ߓo�^�ł��Ȃ�
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			LOG_ERROR("(Texture)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());

			return;
		}

		// �ǂݍ��񂾃p�����[�^�Ńe�N�X�`�����쐬
		TexturePtr texture = Texture::Create(name, filename, Texture::TextureType::Obj, filterMode);
		if (!texture)
		{
			LOG_ERROR("(Texture)%s�̍쐬�Ɏ��s", name.c_str());
			return;
		}

		// �쐬�����e�N�X�`����z��ɓo�^
		LOG("(Texture)%s��o�^", name.c_str());
		textureCache.emplace(name, texture);
	}

	/**
	* OBJ�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	Obj�t�@�C����
	*/
	void ResouceManager::LoadObj(const std::string& name, const std::string& filename)
	{
		meshBuffer->LoadObj(name, filename);
	}

	/**
	* glTF�t�@�C����ǂݍ���
	* 
	* @param name		�ۑ����閼�O
	* @param filename	glTF�t�@�C����
	*/
	void ResouceManager::LoadGlTF(const std::string& name, const std::string& filename)
	{
		gltfFileBuffer->LoadGltf(name, filename);
	}

	/**
	* �V�F�[�_�t�@�C����ǂݍ���
	*
	* @param name		�V�F�[�_�̖��O
	* @param filenameVS �o�[�e�b�N�X�V�F�[�_�t�@�C��
	* @param filenameFS �t���O�����g�V�F�[�_�t�@�C��
	*/
	void ResouceManager::LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS,
		bool isNormal, bool isShadow, bool isLight, bool isUseLight)
	{
		// ���łɓo�^����Ă��邽�ߓo�^�ł��Ȃ�
		auto itr = shaderCache.find(name);
		if (itr != shaderCache.end())
		{
			LOG_ERROR("(Shader)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());
			return;
		}

		// �V�F�[�_���쐬
		auto shader = Shader::Create(name, filenameVS, filenameFS);
		if (!shader)
		{
			LOG_ERROR("(Shader)%s�̍쐬�Ɏ��s", name.c_str());
			return;
		}

		// �쐬�����V�F�[�_��z��ɓo�^����
		LOG("(Shader)%s��o�^", name.c_str());
		shaderCache.emplace(name, shader);
	}

	/**
	* �e�N�X�`�����擾
	*
	* @param name �e�N�X�`���̖��O
	*
	* @return name�ɂ������e�N�X�`��
	*/
	TexturePtr ResouceManager::GetTexture(const std::string& name)
	{
		// �L���b�V��������΁A�L���b�V�����ꂽ�e�N�X�`����Ԃ�
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			return itr->second;
		}

		LOG_ERROR("(Texture)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* �X�^�e�B�b�N���b�V�����擾
	*
	* @param name �X�^�e�B�b�N���b�V���̖��O
	*
	* @return name�ɂ������X�^�e�B�b�N���b�V��
	*/
	StaticMeshPtr ResouceManager::GetStaticMesh(const std::string& name)
	{
		return meshBuffer->GetStaticMesh(name);
	}

	/**
	* glTF�t�@�C�����擾
	*
	* @param name glTF�t�@�C���̖��O
	*
	* @return name�ɂ�����glTF�t�@�C��
	*/
	GltfFilePtr ResouceManager::GetGltfFile(const std::string& name)
	{
		return gltfFileBuffer->GetGltf(name);
	}

	/**
	* �V�F�[�_���擾
	* 
	* @param name �V�F�[�_�̖��O
	* 
	* @return name�ɂ������V�F�[�_
	*/
	ShaderPtr ResouceManager::GetShader(const std::string& name)
	{
		// �L���b�V��������΁A�L���b�V�����ꂽ�e�N�X�`����Ԃ�
		auto itr = shaderCache.find(name);
		if (itr != shaderCache.end())
		{
			return itr->second;
		}

		LOG_ERROR("(Shader)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* �f�t�H���g�V�F�[�_�[���擾
	*
	* @param shader	�V�F�[�_�[
	*
	* @return shader�ɂ������V�F�[�_
	*/
	ShaderPtr ResouceManager::GetShader(DefalutShader shader)
	{
		std::string name = "None";

		switch (shader)
		{
		case FGEngine::DefalutShader::Standard3D:
			name = "Standard3D";
			break;
		case FGEngine::DefalutShader::Skeletal3D:
			name = "Skeletal3D";
			break;
		case FGEngine::DefalutShader::Shadow3D:
			name = "Shadow3D";
			break;
		case FGEngine::DefalutShader::ShadowSkeletal3D:
			name = "ShadowSkeletal3D";
			break;
		case FGEngine::DefalutShader::Unlit:
			name = "Unlit";
			break;
		case FGEngine::DefalutShader::Particle:
			name = "Particle";
			break;
		default:
			break;
		}

		if (name == "None")
		{
			return nullptr;
		}

		return GetShader(name);
	}

	/**
	* ���L�}�e���A���𕡐�
	*/
	std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original)
	{
		if (!original)
		{
			return {};
		}

		MaterialList clone(original->materials.size());
		for (int i = 0; i < clone.size(); ++i)
		{
			clone[i] = std::make_shared<Material>(*original->materials[i]);
		}
		return clone;
	}
}