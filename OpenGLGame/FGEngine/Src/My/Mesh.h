/**
* @file Mesh.h
*/
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Package/Glad.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "VecMath.h"
#include "Material.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace FGEngine
{
	// 先行宣言
	class MeshBuffer;
	using MeshBufferPtr = std::shared_ptr<MeshBuffer>;

	/**
	* 頂点データ形式
	*/
	struct Vertex
	{
		Vector3 position;	// 頂点座標
		Vector2 texcoord;	// テクスチャ座標
		Vector3 normal;	// 法線ベクトル
	};

	/**
	* 描画パラメータ
	*/
	struct DrawParams
	{
		GLenum mode = GL_TRIANGLES;	// プリミティブの種類
		GLsizei count = 0;			// 描画するインデックスの数
		const void* indices = 0;	// 描画開始インデックスのバイトオフセット
		GLint baseVertex = 0;		// インデックス0となる頂点配列内の位置

		int materialNo = -1;		// MaterialIndex
	};

	/**
	* 3Dモデル
	*/
	struct StaticMesh
	{
		std::string name;	// メッシュ名
		std::vector<DrawParams> drawParamsList;	// 描画パラメータ
		MaterialList materials;		// マテリアル配列
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	void Draw(const StaticMesh& mesh, GLuint program, const MaterialList& materials);

	// 共有マテリアル配列を複製
	inline MaterialList CloneMaterialList(const StaticMeshPtr& original) {
		MaterialList clone(original->materials.size());
		for (int i = 0; i < clone.size(); ++i) {
			clone[i] = std::make_shared<Material>(*original->materials[i]);
		}
		return clone;
	}


	/**
	* 頂点データを管理するクラス
	*/
	class MeshBuffer
	{
	public:

		MeshBuffer(size_t bufferSize);
		~MeshBuffer() = default;

		// コピーと代入を禁止
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;

		// テクスチャ作成コールバック型
		using TextureCallback = std::function<TexturePtr(const char*)>;

		// テクスチャ作成コールバックを設定する
		void SetTextureCallback(const TextureCallback& callback) {
			textureCallback = callback;
		}

		/**
		* メッシュバッファを作成
		*
		* @param bufferSize	格納できる頂点データのサイズ(バイト数)
		*/
		static MeshBufferPtr Create(size_t bufferSize) {
			return std::make_shared<MeshBuffer>(bufferSize);
		}

		// 頂点データの追加
		void AddVertexData(const Vertex* vertices, size_t vertexBytes, const uint16_t* indices, size_t indexBytes, GLenum mode = GL_TRIANGLES);

		// 既存の描画パラメータとテクスチャから新しいスタティックメッシュを作成する
		StaticMeshPtr CreateStaticMesh(const char* name, const DrawParams& params, const TexturePtr& texBaseColor);

		// すべての頂点データの削除
		void Clear();

		// 描画パラメータの取得
		inline const DrawParams& GetDrawParams(size_t index) const {
			return drawParamsList[index];
		}

		// 描画パラメータの数を取得
		size_t GetDrawParamsCount() const {
			return drawParamsList.size();
		}

		// VAOの取得
		VertexArrayObjectPtr GetVAO() const {
			return vao;
		}

		// スタティックメッシュの取得
		StaticMeshPtr GetStaticMesh(const char* name) const;

		// OBJファイルを読み込む
		StaticMeshPtr LoadObj(const char* filename);

	private:

		// MTLファイルを読み込む
		std::vector<MaterialPtr> LoadMTL(const std::string& foldername, const char* filename);

	private:

		std::unordered_map<std::string, StaticMeshPtr> meshes;
		std::vector<DrawParams> drawParamsList;	// 描画パラメータ配列
		VertexArrayObjectPtr vao;	// 頂点アトリビュート配列
		BufferObjectPtr buffer;		// 頂点データおよびインデックスデータ
		size_t usedBytes = 0;		// バッファの使用済み容量(バイト)
		TextureCallback textureCallback;	// テクスチャ作成コールバック
	};

	// 欠けている法線を補う
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount);
}
#endif // !MESH_H_INCLUDE
