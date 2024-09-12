/**
* @file AssetManager.cpp
*/
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Debug.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"

#include "FGEngine/GameObject.h"

#include "FGEngine/Package/Glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	std::unordered_map<std::string, TexturePtr> AssetManager::textureCache;
	std::unordered_map<std::string, StaticMeshPtr> AssetManager::staticMeshCache;
	std::unordered_map<std::string, GltfFilePtr> AssetManager::gltfFileCache;
	std::unordered_map<std::string, ShaderPtr> AssetManager::shaderCache;
	std::unordered_map<std::string, GameObjectPtr> AssetManager::gameObjectChache;
	MeshBufferPtr AssetManager::meshBuffer;
	GltfFileBufferPtr AssetManager::gltfFileBuffer;

	/**
	* ���\�[�X�}�l�[�W���[��������
	*
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int AssetManager::Initialize()
	{
		// ���b�V���o�b�t�@���쐬
		this->meshBuffer = MeshBuffer::Create(32'000'000);
		// glTF�t�@�C���p�o�b�t�@��������
		const size_t maxAnimationModelCount = 64;	// �A�j���[�V�������郂�f����
		const size_t maxAnimationMatrixCount = 256;	// 1���f���̃{�[����
		gltfFileBuffer = GltfFileBuffer::Create(10'000'000, maxAnimationModelCount * maxAnimationMatrixCount);

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
	* �A�Z�b�g�}�l�[�W���[�̏I������
	*/
	void AssetManager::Fainalize()
	{
		textureCache.clear();
		staticMeshCache.clear();
		gltfFileCache.clear();
		shaderCache.clear();
		gameObjectChache.clear();
	}

	/**
	* Gltf�t�@�C�����擾
	*/
	GltfFileBuffer* AssetManager::GetGltfFileBuffer() const
	{
		return gltfFileBuffer.get();
	}

#pragma region Texture

	/**
	* tga�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	Tga�t�@�C����
	*/
	void AssetManager::LoadTga(const std::string& name, const std::string& filename, GLenum filterMode)
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
	* tga�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	Tga�t�@�C����
	*/
	void AssetManager::LoadTga(const std::string& name, const std::string& filename)
	{
		LoadTga(name, filename, GL_NEAREST);
	}

	/**
	* �e�N�X�`�����擾
	*
	* @param name �e�N�X�`���̖��O
	*
	* @return name�ɂ������e�N�X�`��
	*/
	TexturePtr AssetManager::GetTexture(const std::string& name)
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

#pragma endregion

#pragma region Mesh

	/**
	* OBJ�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	Obj�t�@�C����
	*/
	void AssetManager::LoadObj(const std::string& name, const std::string& filename)
	{
		// meshBuffer����������Ă��Ȃ�
		if (!meshBuffer)
		{
			return;
		}

		auto itr = staticMeshCache.find(name);
		if (itr != staticMeshCache.end())
		{
			LOG_ERROR("(StaticMesh)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());
			return;
		}

		// ���b�V����ǂݍ���
		auto mesh = meshBuffer->LoadObj(name, filename);

		// �o�^
		staticMeshCache.emplace(name, mesh);
	}

	/**
	* glTF�t�@�C����ǂݍ���
	*
	* @param name		�ۑ����閼�O
	* @param filename	glTF�t�@�C����
	*/
	void AssetManager::LoadGlTF(const std::string& name, const std::string& filename)
	{
		// glTFFile�o�b�t�@����������Ă��Ȃ�
		if (!gltfFileBuffer)
		{
			return;
		}

		auto itr = gltfFileCache.find(name);
		if (itr != gltfFileCache.end())
		{
			LOG_ERROR("(GltfFile)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());
			return;
		}

		// ���b�V����ǂݍ���
		auto gltfFile = gltfFileBuffer->LoadGltf(name, filename);

		// �o�^
		gltfFileCache.emplace(name, gltfFile);
	}

	/**
	* �X�^�e�B�b�N���b�V�����擾
	*
	* @param name �X�^�e�B�b�N���b�V���̖��O
	*
	* @return name�ɂ������X�^�e�B�b�N���b�V��
	*/
	StaticMeshPtr AssetManager::GetStaticMesh(const std::string& name)
	{
		auto itr = staticMeshCache.find(name);
		if (itr != staticMeshCache.end())
		{
			return itr->second;
		}
		LOG_ERROR("(StaticMesh)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* glTF�t�@�C�����擾
	*
	* @param name glTF�t�@�C���̖��O
	*
	* @return name�ɂ�����glTF�t�@�C��
	*/
	GltfFilePtr AssetManager::GetGltfFile(const std::string& name)
	{
		auto itr = gltfFileCache.find(name);
		if (itr != gltfFileCache.end())
		{
			return itr->second;
		}
		LOG_ERROR("(glTFFile)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

#pragma endregion

#pragma region Shader

	/**
	* �V�F�[�_�t�@�C����ǂݍ���
	*
	* @param name		�V�F�[�_�̖��O
	* @param filenameVS �o�[�e�b�N�X�V�F�[�_�t�@�C��
	* @param filenameFS �t���O�����g�V�F�[�_�t�@�C��
	*/
	void AssetManager::LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
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
	* �V�F�[�_���擾
	*
	* @param name �V�F�[�_�̖��O
	*
	* @return name�ɂ������V�F�[�_
	*/
	ShaderPtr AssetManager::GetShader(const std::string& name)
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
	ShaderPtr AssetManager::GetShader(DefalutShader shader)
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

#pragma endregion

#pragma region GameObject

	/**
	* �Q�[���I�u�W�F�N�g��ǂݍ���
	*
	* @param object �ǂݍ��ރQ�[���I�u�W�F�N�g
	*/
	void AssetManager::LoadGameObject(const GameObjectPtr& object)
	{
		if (!object)
		{
			return;
		}

		auto itr = gameObjectChache.find(object->name);
		if (gameObjectChache.end() != itr)
		{
			return;
		}

		// �I�u�W�F�N�g�̓o�^
		gameObjectChache.emplace(object->name, object);
	}

	/**
	* �Q�[���I�u�W�F�N�g���擾����
	*
	* @param name �I�u�W�F�N�g�̖��O
	*/
	GameObjectPtr AssetManager::GetGameObjet(const std::string& name)
	{
		auto itr = gameObjectChache.find(name);
		if (itr != gameObjectChache.end())
		{
			itr->second;
		}

		return nullptr;
	}

#pragma endregion

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