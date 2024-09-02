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
	// 先行宣言
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* アセットマネージャー
	*/
	class AssetManager : public Singleton<AssetManager>
	{
		friend MainSystem::EngineCore;
		friend Singleton<AssetManager>;
	private:	// コンストラクタ

		/**
		* デフォルトコンストラクタ
		*/
		AssetManager() = default;

	private:

		/**
		* リソースマネージャーを初期化
		*
		* @retval 0		初期化成功
		* @retval 0以外	初期化失敗
		*/
		int Initialize();

	public:

		/**
		* Gltfファイルを取得
		*/
		GltfFileBuffer* GetGltfFileBuffer() const;

	public:		// テクスチャ

		/**
		* tgaファイルを読み込む
		*
		* @param name		保存する名前
		* @param filename	Tgaファイル名
		*/
		void LoadTga(const std::string& name, const std::string& filename, GLenum fileterMode);
		void LoadTga(const std::string& name, const std::string& filename);

		/**
		* テクスチャを取得
		*
		* @param name テクスチャの名前
		*
		* @return nameにあったテクスチャ
		*/
		TexturePtr GetTexture(const std::string& name);

	public:		// メッシュ

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

	public:		// シェーダ

		/**
		* シェーダファイルを読み込む
		*
		* @param name		シェーダの名前
		* @param filenameVS バーテックスシェーダファイル
		* @param filenameFS フラグメントシェーダファイル
		*/
		void LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS);

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
		MeshBufferPtr meshBuffer;

		// glTFFileバッファ
		GltfFileBufferPtr gltfFileBuffer;
	};

	/**
	* 共有マテリアル配列を複製
	*/
	std::vector<MaterialPtr> CloneMaterialList(const StaticMeshPtr& original);

}

#endif // !FGENGINE_ASSETMANAGER_H_INCLUDED
