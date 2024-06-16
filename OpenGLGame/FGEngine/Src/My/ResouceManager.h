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
	// 先行宣言
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
		* リソースマネージャー
		*/
		class ResouceManager : public Singleton<ResouceManager>
		{
		private:

			friend MainSystem::EngineCore;
			friend RenderingSystem::RenderingEngine;
			friend Singleton<ResouceManager>;
			friend ObjectSystem::ObjectManager;

			// コンストラクタ
			ResouceManager() = default;

			/**
			* リソースマネージャーを初期化
			* 
			* @retval 0		初期化成功
			* @retval 0以外	初期化失敗
			*/
			int Initialize();

		public:

			/**
			* tgaファイルを読み込む
			* 
			* @param name		保存する名前
			* @param filename	Tgaファイル名
			*/
			void LoadTga(const std::string& name, const std::string& filename, GLenum fileterMode = GL_NEAREST);

			/**
			* OBJファイルを読み込む
			* 
			* @param name		保存する名前
			* @param filename	Objファイル名
			*/
			void LoadObj(const std::string& name, const std::string& filename);

			/**
			* glTFファイルを読み込む
			* 
			* @param name		保存する名前
			* @param filename	Gltfファイル名
			*/
			void LoadGlTF(const std::string& name, const std::string& filename);

			/**
			* シェーダファイルを読み込む
			* 
			* @param name		シェーダの名前
			* @param filenameVS バーテックスシェーダファイル
			* @param filenameFS フラグメントシェーダファイル
			*/
			void LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS,
				bool isNormal = false, bool isShadow = false, bool isLight = false, bool isUseLight = false);

			/**
			* テクスチャを取得
			* 
			* @param name テクスチャの名前
			* 
			* @return nameにあったテクスチャ
			*/
			TexturePtr GetTexture(const std::string& name);

			/**
			* スタティックメッシュを取得
			* 
			* @param name スタティックメッシュの名前
			* 
			* @return nameにあったスタティックメッシュ
			*/
			StaticMeshPtr GetStaticMesh(const std::string& name);

			/**
			* glTFファイルを取得
			* 
			* @param name glTFファイルの名前
			* 
			* @return nameにあったglTFファイル
			*/
			GltfFilePtr GetGltfFile(const std::string& name);

			/**
			* シェーダーを取得
			* 
			* @param name シェーダーの名前
			* 
			* @return nameにあったシェーダ
			*/
			ShaderPtr GetShader(const std::string& name);

			/**
			* デフォルトシェーダーを取得
			*
			* @param shader	シェーダー
			*
			* @return shaderにあったシェーダ
			*/
			ShaderPtr GetShader(DefalutShader shader);


		private:

			// テクスチャキャッシュ
			std::unordered_map<std::string, TexturePtr> textureCache;

			// シェーダキャッシュ
			std::unordered_map<std::string, ShaderPtr> shaderCache;

			// メッシュバッファ
			RenderingSystem::MeshBufferPtr meshBuffer;

			// glTFFileバッファ
			RenderingSystem::GltfFileBufferPtr gltfFileBuffer;
		};

		/**
		* 共有マテリアル配列を複製
		*/ 
		std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

	}
}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
