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
	* リソースマネージャーを初期化
	* 
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int ResouceManager::Initialize()
	{
		// メッシュバッファを作成
		this->meshBuffer = RenderingSystem::MeshBuffer::Create(32'000'000);
		// glTFファイル用バッファを初期化
		const size_t maxAnimationModelCount = 64;	// アニメーションするモデル数
		const size_t maxAnimationMatrixCount = 256;	// 1モデルのボーン数
		gltfFileBuffer = RenderingSystem::GltfFileBuffer::Create(10'000'000, maxAnimationModelCount * maxAnimationMatrixCount);

		// テクスチャの読み込み
		LoadTga("white", "FGEngine/Res/Texture/white.tga");

		// デフォルトメッシュを読み込み
		LoadObj("Cube", "FGEngine/Res/Mesh/Cube/Cube.obj");
		LoadObj("Sphere", "FGEngine/Res/Mesh/Sphere/Sphere.obj");
		LoadObj("skySphere", "FGEngine/Res/Mesh/skySphere/sky_Sphere.obj");
		LoadObj("Plane", "FGEngine/Res/Mesh/Plane/Plane.obj");

		// デフォルトシェーダーの読み込み
		LoadShader("Standard3D", "FGEngine/Res/Shader/standard3D.vert", "FGEngine/Res/Shader/standard3D.frag");
		LoadShader("Shadow3D", "FGEngine/Res/Shader/shadow3D.vert", "FGEngine/Res/Shader/shadow3D.frag");
		LoadShader("Unlit", "FGEngine/Res/Shader/unlit.vert", "FGEngine/Res/Shader/unlit.frag");
		LoadShader("Skeletal3D", "FGEngine/Res/Shader/skeletal3D.vert", "FGEngine/Res/Shader/standard3D.frag");
		LoadShader("ShadowSkeletal3D", "FGEngine/Res/Shader/shadowSkeletal3D.vert", "FGEngine/Res/Shader/shadow3D.frag");
		LoadShader("Particle", "FGEngine/Res/Shader/particle.vert", "FGEngine/Res/Shader/particle.frag");

		return 0;
	}
	/**
	* tgaファイルを読み込む
	*
	* @param name		保存する名前
	* @param filename	Tgaファイル名
	*/
	void ResouceManager::LoadTga(const std::string& name, const std::string& filename, GLenum filterMode)
	{
		// すでに登録されているため登録できない
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			LOG_ERROR("(Texture)%sはすでに登録されているため登録できません", name.c_str());

			return;
		}

		// 読み込んだパラメータでテクスチャを作成
		TexturePtr texture = Texture::Create(name, filename, Texture::TextureType::Obj, filterMode);
		if (!texture)
		{
			LOG_ERROR("(Texture)%sの作成に失敗", name.c_str());
			return;
		}

		// 作成したテクスチャを配列に登録
		LOG("(Texture)%sを登録", name.c_str());
		textureCache.emplace(name, texture);
	}

	/**
	* OBJファイルを読み込む
	*
	* @param name		保存する名前
	* @param filename	Objファイル名
	*/
	void ResouceManager::LoadObj(const std::string& name, const std::string& filename)
	{
		meshBuffer->LoadObj(name, filename);
	}

	/**
	* glTFファイルを読み込む
	* 
	* @param name		保存する名前
	* @param filename	glTFファイル名
	*/
	void ResouceManager::LoadGlTF(const std::string& name, const std::string& filename)
	{
		gltfFileBuffer->LoadGltf(name, filename);
	}

	/**
	* シェーダファイルを読み込む
	*
	* @param name		シェーダの名前
	* @param filenameVS バーテックスシェーダファイル
	* @param filenameFS フラグメントシェーダファイル
	*/
	void ResouceManager::LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS,
		bool isNormal, bool isShadow, bool isLight, bool isUseLight)
	{
		// すでに登録されているため登録できない
		auto itr = shaderCache.find(name);
		if (itr != shaderCache.end())
		{
			LOG_ERROR("(Shader)%sはすでに登録されているため登録できません", name.c_str());
			return;
		}

		// シェーダを作成
		auto shader = Shader::Create(name, filenameVS, filenameFS);
		if (!shader)
		{
			LOG_ERROR("(Shader)%sの作成に失敗", name.c_str());
			return;
		}

		// 作成したシェーダを配列に登録する
		LOG("(Shader)%sを登録", name.c_str());
		shaderCache.emplace(name, shader);
	}

	/**
	* テクスチャを取得
	*
	* @param name テクスチャの名前
	*
	* @return nameにあったテクスチャ
	*/
	TexturePtr ResouceManager::GetTexture(const std::string& name)
	{
		// キャッシュがあれば、キャッシュされたテクスチャを返す
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			return itr->second;
		}

		LOG_ERROR("(Texture)%sは登録されていません", name.c_str());
		return nullptr;
	}

	/**
	* スタティックメッシュを取得
	*
	* @param name スタティックメッシュの名前
	*
	* @return nameにあったスタティックメッシュ
	*/
	StaticMeshPtr ResouceManager::GetStaticMesh(const std::string& name)
	{
		return meshBuffer->GetStaticMesh(name);
	}

	/**
	* glTFファイルを取得
	*
	* @param name glTFファイルの名前
	*
	* @return nameにあったglTFファイル
	*/
	GltfFilePtr ResouceManager::GetGltfFile(const std::string& name)
	{
		return gltfFileBuffer->GetGltf(name);
	}

	/**
	* シェーダを取得
	* 
	* @param name シェーダの名前
	* 
	* @return nameにあったシェーダ
	*/
	ShaderPtr ResouceManager::GetShader(const std::string& name)
	{
		// キャッシュがあれば、キャッシュされたテクスチャを返す
		auto itr = shaderCache.find(name);
		if (itr != shaderCache.end())
		{
			return itr->second;
		}

		LOG_ERROR("(Shader)%sは登録されていません", name.c_str());
		return nullptr;
	}

	/**
	* デフォルトシェーダーを取得
	*
	* @param shader	シェーダー
	*
	* @return shaderにあったシェーダ
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
	* 共有マテリアルを複製
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