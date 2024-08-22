/**
* @file GltfFileBuffer.h
*/
#ifndef FGENGINE_GLTFFILEBUFFER_H_INCLUDED
#define FGENGINE_GLTFFILEBUFFER_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include "FGEngine/Math//Matrix4x4.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace FGEngine
{
	// 先行宣言
	struct GltfNode;
	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;
	struct AnimationClip;

	// アニメーション用座標変換行列の配列
	using GltfAnimationMatrices = std::vector<Matrix4x4>;
	struct AnimMatrixRange;

	/**
	* アニメーションの姿勢行列を計算する
	*
	* @param file			meshNodeを所有するファイルオブジェクト
	* @param meshNode		メッシュを持つノード
	* @param animation		計算の元となるアニメーション
	* @param time			アニメーションの再生位置
	*
	* @return アニメーションを適用した姿勢行列の配列
	*/
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode,
		const AnimationClip* animation, float time);

	/**
	* 二つのアニメーションの姿勢行列を補間する
	*
	* @param file
	* @param nextAnimation
	* @param currentAnimation
	*/
	GltfAnimationMatrices InterpolationAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode,
		const AnimationClip* currentAnimation, float time, const AnimationClip* nextAnimation);

	class BufferObject;
	using BufferObjectPtr = std::shared_ptr<BufferObject>;
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	/**
	* glTFファイルを管理するクラス
	*/
	class GltfFileBuffer
	{
	public:

		/**
		* コンストラクタ
		*
		* @param bufferSize 格納できる頂点データのサイズ(バイト数)
		* @param maxMatrixCount	アニメーション用SSBOに格納できる最大行列数
		*/
		GltfFileBuffer(size_t bufferSize, size_t maxMatrixCount);

		// デストラクタ
		~GltfFileBuffer();

		/**
		* glTFFileBufferを作成
		*
		* @param bufferSize 格納できる頂点データのサイズ(バイト数)
		* @param maxMatrixCount	アニメーション用SSBOに格納できる最大行列数
		*
		* @return 作成したglTFFileBufferポインター
		*/
		static GltfFileBufferPtr Create(size_t bufferSize, size_t maxMatrixCount);

		/**
		* glTFファイルの読み込み
		*
		* @parma name		保存したい名前
		* @parma filename	ファイルの名前
		*/
		void LoadGltf(const std::string& name, const std::string& filename);

		/**
		* glTFファイルを取得
		*
		* @parma name		取得したいglTFファイルの名前
		*
		* @return glTFファイルポインター
		*/
		GltfFilePtr GetGltf(const std::string& name);

		/**
		* アニメーションメッシュの描画用データをすべて削除
		*/
		void ClearAnimationBuffer();

		/**
		* アニメーションメッシュメッシュの描画用データを追加
		*
		* @param matBones SSBOに追加する姿勢行列の配列
		*
		* @return matBonesように割り当てられたSSBOの範囲
		*/
		AnimMatrixRange AddAnimationMatrices(const GltfAnimationMatrices& matBones);

		/**
		* アニメーションメッシュの描画用データをGPUメモリにコピー
		*/
		void UploadAnimationBuffer();

		/**
		* アニメーションメッシュの描画に使うSSBO領域に割り当てる
		*
		* @param bindingPoint	バインディングポイント
		* @param range			バインドする範囲
		*/
		void BindAnimationBuffer(GLuint bindingPoint, const AnimMatrixRange& range);

		/**
		* アニメーションメッシュの描画に使うSSBO両機の割り当てを解除する
		*
		* @param bindingPoint	バインディングポイント
		*/
		void UnbindAnimationBuffer(GLuint bindingPoint);

	private:

		/**
		* JSONテキストからGltfFileオブジェクトを作成する
		*
		* @param text		glTFのJOSNテキスト
		* @param foldernaem リソース読み込み用のフォルダ
		*
		* @retval nullptr以外	filenameから作成したファイルオブジェクト
		* @rtaval nullptr		読み込み失敗
		*/
		GltfFilePtr Parse(const char* text, const char* foldername);

	private:

		// binファイルを読み込みバッファ
		BufferObjectPtr buffer;

		// マップされたアドレス
		uint8_t* pBuffer = nullptr;

		// 書き込み済みデータ数
		GLsizeiptr curBufferSize = 0;

		// マテリアル未設定時に使用するマテリアル
		MaterialPtr defaultMaterial;

		// glTFファイル配列
		std::unordered_map<std::string, GltfFilePtr> glTFfiles;

		// アニメーションの姿勢行列バッファ
		MappedBufferObjectPtr animationBuffer;

		GltfAnimationMatrices tmpAnimationBuffer;
	};
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;
}

#endif // !FGENGINE_GLTFFILEBUFFER_H_INCLUDED
