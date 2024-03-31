/**
* @file GltfMesh.h
*/
#ifndef GLTFMESH_H_INCLUDED
#define GLTFMESH_H_INCLUDED
#include "Package/Glad.h"
#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include "VecMath.h"
#include "Texture.h"
#include "Material.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "MapBufferObjecth.h"


namespace FGEngine::Rendering
{

	/**
	* プリミティブデータ
	*/
	struct GltfPrimitive
	{
		GLenum mode = GL_TRIANGLES;	// プリミティブの種類
		GLsizei count = 0;			// 描画するインデックス数
		GLenum type = GL_UNSIGNED_SHORT;	// インデックスデータ型
		const GLvoid* indeices = 0;			// 描画開始インデックスのオフセット
		GLint baseVertex = 0;				// インデックス0番とみなされる頂点配列内の位置

		Rall::VertexArrayObjectPtr vao;	// プリミティブ用VAO
		size_t materialNo = -1;	// マテリアル番号
	};

	/**
	* メッシュデータ
	*/
	struct GltfMesh
	{
		std::string name;	// メッシュ名
		std::vector<GltfPrimitive> primitives;	// プリミティブ配列
	};

	/**
	*　スキン
	*/
	struct GltfSkinn
	{
		std::string name;	// スキン名

		// ジョイント(ボーン)データ
		struct Joint
		{
			int nodeId;						// ジョイント対応するノード番号
			Matrix4x4 matInverseBindPose;	// 逆バインドポーズ配列
		};
		std::vector<Joint> joints;	// ジョイント配列
	};

	/**
	* ノード
	*/
	struct GltfNode
	{
		std::string name;					// ノード名
		int mesh = -1;						// メッシュ番号
		int skin = -1;						// スキン番号
		GltfNode* parent = nullptr;			// 親ノード
		std::vector<GltfNode*> children;	// 子ノード配列
		Matrix4x4 matLocal = Matrix4x4(1);	// ローカル行列
		Matrix4x4 matGlobal = Matrix4x4(1);	// グローバル配列
	};

	/**
	* シーン
	*/
	struct GltfScene
	{
		std::vector<const GltfNode*> nodes;		// ノード配列
		std::vector<const GltfNode*> meshNodes;	// メッシュを持つノードのみの配列
	};

	/**
	* アニメーションの補間方法
	*/
	enum class GltfInterpolation
	{
		step,		// 補間足
		linear,		// 線形補間
		cubicSpline,// 3次スプライン補間	
	};

	/**
	* アニメーションのキーフレーム
	*/
	template<typename T>
	struct GltfKeyframe
	{
		float time;	// 時刻
		T value;	// 適用する値
	};

	/**
	* アニメーションのチャネル
	*/
	template<typename T>
	struct GltfChannel
	{
		int targetNodeId;						// 値を適用するノードID
		GltfInterpolation interpolation;		// 補間方法
		std::vector<GltfKeyframe<T>> keyframes;	// キーフレーム配列
	};

	/**
	* アニメーション
	*/
	struct GltfAnimation
	{
		std::string name;		// アニメーション名
		std::vector<GltfChannel<Vector3>> translations;	// 平行移動チャネルの配列
		std::vector<GltfChannel<Quaternion>> rotations;	// 回転チャネルの配列
		std::vector<GltfChannel<Vector3>> scales;		// 拡大縮小のチャネルの配列
		std::vector<int> staticNodes;	// アニメーションしないノードIDの配列
		float totalTime = 0;
	};
	using GltfAnimationPtr = std::shared_ptr<GltfAnimation>;

	/**
	* ファイル
	*/
	struct GltfFile
	{
		std::string name;							// ファイル名
		std::vector<GltfScene> scenes;				// シーン配列
		std::vector<GltfNode> nodes;				// ノード配列
		std::vector<GltfSkinn> skins;				// スキン配列
		std::vector<GltfMesh> meshes;				// メッシュ配列
		std::vector<MaterialPtr> materials;		// マテリアル配列
		std::vector<GltfAnimationPtr> animations;	// アニメーション
		Matrix4x4 matRoot = Matrix4x4(1);			// 基本姿勢行列
	};
	using GltfFilePtr = std::shared_ptr<GltfFile>;

	// アニメーション用座標変換行列の配列
	using GltfAnimationMatrices = std::vector<Matrix4x4>;

	// チャネル上の指定した時刻の値を求める
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode, const GltfAnimation* animation, float time);

	/**
	* @file glTFファイルから読み込んだメッシュを管理するクラス
	*/
	class GltfFileBuffer
	{
	public:

		// コンストラクタ
		explicit GltfFileBuffer(size_t bufferCapacity, size_t maxMatrixCount);

		// デストラクタ
		~GltfFileBuffer() = default;

		/**
		* glTFファイルバッファを作成
		*
		* @return 作成したglTFファイルバッファ
		*/
		static std::shared_ptr<GltfFileBuffer> Create(size_t bufferCapcity, size_t maxMatrixCount)
		{
			return std::make_shared<GltfFileBuffer>(bufferCapcity, maxMatrixCount);
		}

		/**
		* ファイルの読み込み
		*
		* @return 読み込んだglTFFile
		*/
		GltfFilePtr Load(const char* filename);

		// 姿勢行列の配列
		struct Range
		{
			GLintptr offset;
			size_t size;
		};

		// === アニメーションの姿勢行列バッファの管理 === //
		void ClearAnimationBuffer();
		Range AddAnimationMatrices(const GltfAnimationMatrices& matBones);
		void UploadAnimationBuffer();
		void BindAnimationBuffer(GLuint bindingPoint, const Range& range);
		void UnbindAnimationBuffer(GLuint bindingPoint);


		// テクスチャ作成コールバック型
		using TextureCallback = std::function<TexturePtr(const char*)>;

		// テクスチャ作成コールバックを設定する
		void SetTextureCallback(const TextureCallback& callback)
		{
			textureCallback = callback;
		}

	private:

		GltfFilePtr Parse(const char* text, const char* foldername);

	private:

		Rall::BufferObjectPtr buffer;			// binファイルを読み込むバッファ
		uint8_t* pBuffer = nullptr;		// マップされたアドレス
		GLsizeiptr curBufferSize = 0;	// 書き込み済みデータ数
		MaterialPtr defaultMaterial;	// マテリアル未設定時に使用するマテリアル

		// ファイル管理用の連想配列
		std::unordered_map<std::string, GltfFilePtr> files;
		TextureCallback textureCallback;

		// アニメーションの姿勢行列バッファ
		Rall::MappedBufferObjectPtr animationBuffer;
		GltfAnimationMatrices tmpAnimationBuffer;


	};
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* glTFメッシュを描画する
	*
	* @param mesh		描画するメッシュ
	* @param materials	描画に使うマテリアル配列
	* @param program	描画プログラム
	*/
	void Draw(const GltfMesh& mesh, const std::vector<MaterialPtr>& materials, GLuint program);
}
#endif // !GLTFMESHBUFFER_H_INCLUDED
