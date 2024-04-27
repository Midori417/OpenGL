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

			std::unordered_map<std::string, ShaderObjectPtr>* GetShaderList()
			{
				return &shaderCache;
			}

		public:

			/**
			* tgaファイルを読み込む
			* 
			* @param name		テクスチャの名前
			* @param filename	Tgaファイル名
			*/
			void LoadTga(const std::string& name, const std::string& filename);

			/**
			* OBJファイルを読み込む
			* 
			* @param name		メッシュの名前
			* @param filename	Objファイル名
			* @param meshData	目主の種類
			*/
			void LoadObj(const std::string& name, const std::string& filename);

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
			* デフォルトスタティックメッシュを取得
			* 
			* @param primitiveType	プリミティブのタイプ
			* 
			* @returun primitiveTypeにあったスタティックメッシュ
			*/
			StaticMeshPtr GetStaticMesh(ShapeType primitiveType);

			/**
			* スケルタルメッシュを取得
			* 
			* @param name スケルタルメッシュの名前
			* 
			* @return nameにあったスケルタルメッシュ
			*/
			SkeletalMeshPtr GetSkeltalMesh(const std::string& name);

			/**
			* シェーダーを取得
			* 
			* @param name シェーダーの名前
			* 
			* @return nameにあったシェーダ
			*/
			ShaderObjectPtr GetShader(const std::string& name);

			/**
			* デフォルトシェーダーを取得
			*
			* @param shader	シェーダー
			*
			* @return shaderにあったシェーダ
			*/
			ShaderObjectPtr GetShader(DefalutShader shader);

		private:

			// テクスチャキャッシュ
			std::unordered_map<std::string, TexturePtr> textureCache;

			// シェーダキャッシュ
			std::unordered_map<std::string, ShaderObjectPtr> shaderCache;

			// メッシュバッファ
			RenderingSystem::MeshBufferPtr meshBuffer;
		};

		/**
		* 共有マテリアル配列を複製
		*/ 
		std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

	}
}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
