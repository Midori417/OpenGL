/**
* @file MeshBuffer.h
*/
#ifndef FGENGINE_MESHBUFFER_H_INCLUDED
#define FGENGINE_MESHBUFFER_H_INCLUDED

#include "Package/Glad.h"
#include "Mesh.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "Material.h"
#include <unordered_map>
#include <functional>

namespace FGEngine::RenderingSystem
{
	// 先行宣言
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	struct Vertex;

	/**
	* 頂点データを管理するクラス
	*/
	class MeshBuffer
	{
	public:

		// コンストラクタ・デストラクタ
		MeshBuffer(size_t bufferSize);
		~MeshBuffer() = default;

		// コピーと代入を禁止
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

		/**
		* メッシュバッファを作成
		*
		* @param bufferSize	格納できる頂点データのサイズ(バイト数)
		*/
		static MeshBufferPtr Create(size_t bufferSize)
		{
			return std::make_shared<MeshBuffer>(bufferSize);
		}

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
			size_t stride, GLenum mode = GL_TRIANGLES);

		/**
		* すべての頂点データの削除
		*/
		void Clear();

		/**
		* Objファイルの読み込み
		*
		* @param name 保存する名前
		* @param filename Objファイルの位置
		*/
		void LoadObj(const std::string& name, const std::string& filename);


		/**
		* スタティックメッシュの取得
		* 
		* @param name 取得したいスタティックメッシュの名前
		* 
		* @param nameに対応したスケルタルメッシュ
		*/
		StaticMeshPtr GetStaticMesh(const std::string& name) const;

		/**
		* スケルタルメッシュの取得
		* 
		* @param name 取得したいスケルタルメッシュの名前
		* 
		* @return nameに対応したスケルタルメッシュ
		*/
		SkeletalMeshPtr GetSkeletalMesh(const std::string& name) const;

		/**
		* VAOの取得
		*/
		VertexArrayObjectPtr GetVAO() const
		{
			return vao;
		}

		/**
		* SkeletalVAOの取得
		* */
		VertexArrayObjectPtr GetSkeletalVAO() const
		{
			return vaoSkeletal;
		}

	private:

		/**
		* MTLファイルを読み込む
		*
		* @param foldername	OBJファイルのあるファルダ名
		* @param filename	MTLファイル名
		*
		* @return MTLファイルに含まれるマテリアルの配列
		*/
		std::vector<MaterialPtr> LoadMTL(const std::string& foldername, const char* filename);

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

		//スケルタルメッシュ頂点アトリビュート
		VertexArrayObjectPtr vaoSkeletal;

		// スタティックメッシュ配列
		std::unordered_map<std::string, StaticMeshPtr> meshes;

		// スケルタルメッシュ配列
		std::unordered_map<std::string, SkeletalMeshPtr> skeletalMeshes;

		// 描画パラメータ配列
		std::vector<DrawParams> drawParamsList;

		// バッファの使用済み容量(バイト)
		size_t usedBytes = 0;

	};

	/**
	* 描画パラメータは配列を描画する
	* 
	* @param drawParamList	描画パラメータ配列
	* @param materials		マテリアル配列
	*/
	void Draw(GLuint program, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials);

	/**
	* スタティックメッシュを描画する
	* 
	* @param mesh		スタティックメッシュ
	* @param materials	マテリアル配列
	*/
	void Draw(GLuint program, const StaticMesh& mesh, const MaterialList& materials);

	// 欠けている法線を補う
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE