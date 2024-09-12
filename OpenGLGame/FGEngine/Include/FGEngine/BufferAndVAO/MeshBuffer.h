/**
* @file MeshBuffer.h
*/
#ifndef FGENGINE_MESHBUFFER_H_INCLUDED
#define FGENGINE_MESHBUFFER_H_INCLUDED
#include "BufferAndVAOFrd.h"
#include "FGEngine/UsingNames/UsingAsset.h"
#include <unordered_map>
#include <functional>
#include <string>

namespace FGEngine
{
	struct Vertex;
	struct DrawParams;
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;

	/**
	* 頂点データを管理するクラス
	*/
	class MeshBuffer
	{
	public:	// コンストラクタ・デストラクタ

		/**
		* コンストラクタ
		*
		* @param bufferSize 格納できる頂点データのサイズ(バイト数)
		*/
		MeshBuffer(size_t bufferSize);

		/**
		* デストラクタ
		*/
		~MeshBuffer();

	public:	// 禁止事項

		// コピーと代入を禁止
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

	public:

		/**
		* メッシュバッファを作成
		*
		* @param bufferSize	格納できる頂点データのサイズ(バイト数)
		*
		* @return 作成したメッシュバッファポインター
		*/
		static MeshBufferPtr Create(size_t bufferSize);

	public:

		/**
		* Objファイルの読み込み
		*
		* @param name 保存する名前
		* @param filename Objファイル名
		*/
		StaticMeshPtr LoadObj(const std::string& name, const std::string& filename);

	private:

		/**
		* 頂点データの追加
		*
		* @param vertices		GPUメモリにコピーする頂点データ配列
		* @param vertexBytes	verticesのバイト数
		* @param indices		GPUメモリににコピーするインデックスデータ配列
		* @param indexBytes		indciesのバイト数
		* @param mode			プリミティブの種類
		*/
		void AddVertexData(const void* vertices, size_t vertexBytes,
			const uint16_t* indices, size_t indexBytes,
			size_t stride, GLenum mode);
		void AddVertexData(const void* vertices, size_t vertexBytes,
			const uint16_t* indices, size_t indexBytes,
			size_t stride);

		/**
		* MTLファイルを読み込む
		*
		* @param foldername	OBJファイルのあるファルダ名
		* @param filename	MTLファイル名
		*
		* @return MTLファイルに含まれるマテリアルの配列
		*/
		MaterialList LoadMTL(const std::string& foldername, const char* filename);

		/**
		* メッシュ構築用の中間データ
		*/
		struct MeshData
		{
			std::vector<Vertex> vertices;	// 頂点データ
			std::vector<uint16_t> indices;	// インデックスデータ
			std::vector<DrawParams> drawParamsList; // 描画パラメータ配列
			MaterialList materials;
		};

		/**
		* OBJファイルをメッシュデータを変換する
		*
		* @param filename OBJファイル名
		*
		* @return filenameから作成したメッシュデータ
		*/
		MeshData CreateMeshDataFormObj(const std::string& filename);

	private:

		// 頂点データおよびインデックスデータ
		BufferObjectPtr buffer;

		// スタティックメッシュ頂点アトリビュート
		VertexArrayObjectPtr vao;

		// 描画パラメータ配列
		std::vector<DrawParams> drawParamsList;

		// バッファの使用済み容量(バイト)
		size_t usedBytes = 0;

		// マテリアル未設定時に使用するマテリアル
		MaterialPtr defaultMaterial;
	};

	/**
	* 描画パラメータは配列を描画する
	*
	* @param drawParamList	描画パラメータ配列
	* @param materials		マテリアル配列
	*/
	void Draw(const ShaderPtr& shader, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials);

	/**
	* スタティックメッシュを描画する
	*
	* @param mesh		スタティックメッシュ
	* @param materials	マテリアル配列
	*/
	void Draw(const ShaderPtr& shader, const StaticMesh& mesh, const MaterialList& materials);

	// 欠けている法線を補う
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE