/**
* @file GltfFileBuffer.cpp
*/
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"
#include "FGEngine/BufferAndVAO/MapBufferObjecth.h"
#include "FGEngine/BufferAndVAO/BufferObject.h"
#include "FGEngine/BufferAndVAO/VertexArrayObject.h"
#include "FGEngine/Rendering/Vertex.h"
#include "FGEngine/Asset/GltfFile.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/Asset/Material.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Math/Math.h"
#include "FGEngine/Math/Quaternion.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Debug.h"

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "FGEngine/Package/Nlohmann.h"
#include <fstream>
#include <filesystem>
#include <algorithm>

using json = nlohmann::json;

namespace FGEngine
{
	/**
	* バイナリデータ
	*/
	struct BinaryData
	{
		// GPUメモリ上のデータ開始オフセット
		GLsizeiptr offset;

		// GPUメモリに読み込んだデータ
		std::vector<char> bin;
	};
	using BinaryList = std::vector<BinaryData>;

	/**
	* ファイルを読み込む
	* 
	* @parma filename 読み込むファイル名
	* 
	* @retun 読み込んだデータ配列
	*/
	std::vector<char> ReadFile(const char* filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file)
		{
			LOG_WARNINGS("%sを開けません", filename);
			return {};
		}
		std::vector<char> buf(std::filesystem::file_size(filename));
		file.read(buf.data(), buf.size());
		return buf;
	}

	/**
	* 頂点アトリビュート番号
	*/
	enum AttribIndex
	{
		position,
		texcoord0,
		normal,
		tangent,
		joints0,
		weights0,
	};

	/**
	* 成分数を取得する
	*
	* @param accessor パラメータを持つアクセサ
	*
	* @return 成分の数
	*/
	int GetComponentCount(const json& accessor)
	{
		// 型名と成分数の対応表
		// VEC ベクトル MAT マトリクス
		static const struct {
			const char* type;	// 型の名前
			int componentCount;	// 成分数
		} componentCountList[] = {
			{ "SCALAR", 1 },
			{ "VEC2", 2 }, { "VEC3", 3 }, { "VEC4", 4 },
			{ "MAT2", 4 }, { "MAT3", 9 }, { "MAT4", 16 },
		};

		// 対応表から成分数を取得
		const std::string& type = accessor["type"].get<std::string>();
		for (const auto& e : componentCountList)
		{
			if (type == e.type)
			{
				return e.componentCount;
			}
		}
		LOG_WARNINGS("不明な型'%s'が指定されています", type.c_str());
		return 1;	// glTFの仕様通りなら、ここに来ることはないはず
	}

	/**
	* ストライド(次の要素までの距離)を取得する
	*
	* @parma accessor	アクセサ
	* @param bufferView	バッファビュー
	*
	* @return ストライド
	*/
	GLsizei GetByteStride(const json& accessor, const json& bufferView)
	{
		// byteStrideが定義されていたら、その値を返す
		const auto byteStride = bufferView.find("byteStride");
		if (byteStride != bufferView.end())
		{
			return byteStride->get<int>();
		}

		// bytteStrideが未定義の場合、要素1っ個分のサイズをストライドとする
		// 参考; glTF-2.0仕様 3.6.2.4. Data Alignment

		int componentSize = 1;	// 成分型のサイズ
		const int componentType = accessor["componentType"].get<int>();
		switch (componentType)
		{
		case GL_BYTE:
			componentSize = 1;
			break;
		case GL_UNSIGNED_BYTE:
			componentSize = 1;
			break;
		case GL_SHORT:
			componentSize = 2;
			break;
		case GL_UNSIGNED_SHORT:
			componentSize = 2;
			break;
		case GL_UNSIGNED_INT:
			componentSize = 4;
			break;
		case GL_FLOAT:
			componentSize = 4;
			break;
		default:
			LOG_WARNINGS("glTFの仕様にない型%dが使われています", componentType);
			break;
		}

		// ストライド = 成分型のサイズ * 成分数
		const int componentCount = GetComponentCount(accessor);
		return componentSize * componentCount;
	}

	/**
	* データの開始位置を取得する
	*
	* @param accessor	アクセサ
	* @param bufferView バッファビュー
	* @param binaryList バイナリデータ配列
	*
	* @reutrn データの開始位置
	*/
	GLsizeiptr GetBinaryDataOffset(const json& accessor, const json& bufferView, const BinaryList& binaryList)
	{
		const int bufferId = bufferView["buffer"].get<int>();
		const int byteOffset = accessor.value("byteOffset", 0);
		const int baseByteOffset = bufferView.value("byteOffset", 0);
		return binaryList[bufferId].offset + baseByteOffset + byteOffset;
	}

	/**
	* CPU側のデータのアドレスを取得する
	*
	* @param accessor		アクセサ
	* @param bufferViews	バッファビュー配列
	* @param binaryList		バイナリデータ配列
	*
	* @return データのアドレス
	*/
	const void* GetBinaryDataAddress(const json& accessor, const json& bufferViews, const BinaryList& binaryList)
	{
		const int bufferViewId = accessor["bufferView"].get<int>();
		const json& bufferView = bufferViews[bufferViewId];

		const int bufferId = bufferView["buffer"].get<int>();
		const int byteOffset = accessor.value("byteOffset", 0);
		const int baseByteOffset = bufferView.value("byteOffset", 0);
		return binaryList[bufferId].bin.data() + baseByteOffset + byteOffset;
	}

	/**
	* 頂点アトリビュートを設定する
	*
	* @retval true	頂点アトリビュートを設定した
	* @retval false	頂点アトリビュートのパラメータがなかった
	*/
	bool SetVertexAttribute(const GLuint index, const char* key, const json& attributes, const json& accessors, const json& bufferViews, const BinaryList& binaryList)
	{
		glEnableVertexAttribArray(index);	// 頂点アトリビュートを有効化
		const auto attribute = attributes.find(key);
		if (attribute != attributes.end())
		{
			// アクセサとバッファビューを取得
			const json& accessor = accessors[attribute->get<int>()];
			const int bufferViewId = accessor["bufferView"].get<int>();
			const json& bufferView = bufferViews[bufferViewId];

			// 頂点アトリビュートのパラメータを取得
			const GLint componentCount = GetComponentCount(accessor);
			const GLenum componentType = accessor["componentType"].get<int>();
			const GLboolean normalized = accessor.value("normalized", false);
			const GLsizei byteStride = GetByteStride(accessor, bufferView);
			const GLsizeiptr offset = GetBinaryDataOffset(accessor, bufferView, binaryList);

			// VAOに頂点アトリビュートを設定
			glVertexAttribPointer(index, componentCount, componentType,
				normalized, byteStride, reinterpret_cast<void*>(offset));

			return true;
		}
		return false;
	}

	/**
	* VAOにデフォルトの頂点アトリビュートを設定する
	*
	* @param index	設定先の頂点アトリビュート番号
	* @param size	データの要素数
	* @param offst	データの位置
	* @param vbo	頂点データを保持するVBO
	*/
	void SetDefaultAttribute(GLuint index, GLint size, GLuint offset, GLuint vbo)
	{
		glVertexAttribFormat(index, size, GL_FLOAT, GL_FALSE, offset);
		glVertexAttribBinding(index, index);
		glBindVertexBuffer(index, vbo, 0, 0);
	}

	/**
	* テクスチャを読み込む
	*
	* @param objectName  テクスチャ情報のキー文字列
	* @param gltf        glTFファイルのJSONオブジェクト
	* @param parent      テクスチャ情報を持つJSONオブジェクト
	* @param foldername  glTFファイルがあるフォルダ名
	* @param texDefault  テクスチャが作成できない場合に返すテクスチャ
	*
	* @return 読み込んだテクスチャ、またはtexDefault
	*/
	TexturePtr LoadTexture(const char* objectName, const json& gltf, const json& parent,
		const std::string& foldername, const TexturePtr& texDefault)
	{
		// テクスチャ情報を取得
		const auto textureInfo = parent.find(objectName);
		if (textureInfo == parent.end())
		{
			return texDefault;
		}

		// テクスチャ番号を取得
		const auto textures = gltf.find("textures");
		const int textureNo = textureInfo->at("index").get<int>();
		if (textures == gltf.end() || textureNo >= textures->size()) {
			return texDefault;
		}

		// イメージソース番号を取得
		const json& texture = textures->at(textureNo);
		const auto source = texture.find("source");
		if (source == texture.end())
		{
			return texDefault;
		}

		// イメージ番号を取得
		const auto images = gltf.find("images");
		const int imageNo = source->get<int>();
		if (images == gltf.end() || imageNo >= images->size())
		{
			return texDefault;
		}

		// ファイル名を取得
		const json& image = images->at(imageNo);
		const auto imageUri = image.find("uri");
		if (imageUri == image.end())
		{
			return texDefault;
		}

		// フォルダ名を追加し、拡張子をtgaに変更
		std::filesystem::path uri = imageUri->get<std::string>();
		std::filesystem::path filename = foldername;
		filename /= uri.parent_path();
		filename /= uri.stem();
		filename += ".tga";

		// テクスチャを読み込む
		return Texture::Create(filename.string(), filename.string(), Texture::TextureType::Gltf);
	}

	/**
	* JSONの配列データをVector3に変換する
	*
	* @param json 変換元となる配列データ
	*
	* @return jsonを変換してできたVector3の値
	*/
	Vector3 GetVector3(const json& json)
	{
		if (json.size() < 3)
		{
			return Vector3::zero;
		}

		return Vector3{
			json[0].get<float>(),
			json[1].get<float>(),
			json[2].get<float>()
		};
	}

	/**
	* JSONの配列データをクォータニオンに変換する
	*
	* @param json 変換元となる配列データ
	*
	* @return jsonを変換してできたクォータニオンの値
	*/
	Quaternion GetQuaternion(const json& json)
	{
		if (json.size() < 4)
		{
			return Quaternion{ 0,0,0,1 };
		}

		return Quaternion{
			json[0].get<float>(),
			json[1].get<float>(),
			json[2].get<float>(),
			json[3].get<float>()
		};
	}

	/**
	* JSONの配列データをMatrix4x4に変換する
	*
	* @param json 変換元となる配列データ
	*
	* @return jsonを変換してできたMatrix4x4の値
	*/
	Matrix4x4 GetMatrix4x4(const json& json)
	{
		if (json.size() < 16)
		{
			return Matrix4x4(1);
		}
		Matrix4x4 m;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				m(y, x) = json[y * 4 + x].get<float>();
			}
		}
		return m;
	}

	/**
	* ノードのローカル座標変換行列を計算する
	*
	* @param node glTFノード
	*
	* @return nodeのローカル座標変換行列
	*/
	Matrix4x4 GetLocalMatrix(const json& node)
	{
		// 行列データがある場合、行列データを読み取って返す
		const auto matrix = node.find("matrix");
		if (matrix != node.end())
		{
			return GetMatrix4x4(*matrix);
		}

		// 行列データない場合
		// スケール→回転→平行移動の順で適用した行列を返す
		Matrix4x4 result(1);
		const auto t = node.find("translation");
		if (t != node.end())
		{
			result.SetRow(3, Vector4(GetVector3(*t), 1));
		}
		const auto r = node.find("rotation");
		if (r != node.end())
		{
			result *= Matrix4x4(Quaternion::QuaternionToRotationMatrix(GetQuaternion(*r)));
		}
		const auto s = node.find("scale");
		if (s != node.end())
		{
			result *= Matrix4x4::Scale(GetVector3(*s));
		}
		return result;
	}

	/**
	* メッシュを持つノードをリストアップする
	*/
	void GetMeshNodeList(const GltfNode* node, std::vector<const GltfNode*>& list)
	{
		if (node->mesh >= 0)
		{
			list.push_back(node);
		}
		for (const GltfNode* child : node->children)
		{
			GetMeshNodeList(child, list);
		}
	}

	/**
	* アニメーションチャネルを作成する
	*
	* @param pTimes			時刻の配列のアドレス
	* @param pValues		値の配列のアドレス
	* @param inputCount		配列の要素数
	* @param targetNodeId	値の適用対象となるノードID
	* @param interp			補間方法
	*
	* @return 作成したアニメーションチャネル
	*/
	template<typename T>
	AnimationCurve<T> MakeAnimationChannel(const GLfloat* pTimes, const void* pValues, size_t inputCount, int targetNodeId, GltfInterpolation interp)
	{
		// 時刻と値の配列からキーフレーム配列を作成
		const T* pData = static_cast<const T*>(pValues);
		AnimationCurve<T> animationCurve;
		animationCurve.keyFrames.resize(inputCount);
		for (int i = 0; i < inputCount; ++i)
		{
			animationCurve.keyFrames[i] = { pTimes[i], pData[i] };
		}

		// 適用対象ノードIDと補間方法を設定
		animationCurve.targetNodeId = targetNodeId;
		animationCurve.interpolation = interp;

		return animationCurve;	// 作成したチャネルを返す
	}

	/**
	* チャネル上の指定した時刻の値を求める
	*
	* @param channel	対象のチャネル
	* @param time		値を求める時刻
	*
	* @return 時刻に対応する値
	*/
	template<typename T>
	T Interpolate(const AnimationCurve<T>& animationCurve, float time)
	{
		// time以上の時刻を持つ、最初のキーフレームを検索
		const auto curOrOver = std::lower_bound(
			animationCurve.keyFrames.begin(), animationCurve.keyFrames.end(), time,
			[](const KeyFrame<T>& keyframe, float time)
			{
				return keyframe.time < time;
			});

		// timeが先頭キーフレームの時刻と等しい場合、先頭キーフレームの値を返す
		if (curOrOver == animationCurve.keyFrames.begin())
		{
			return animationCurve.keyFrames.front().value;
		}

		// timeが末尾キーフレームの時刻より大きい場合、末尾キーフレームの値を返す
		if (curOrOver == animationCurve.keyFrames.end())
		{
			return animationCurve.keyFrames.front().value;
		}

		// timeが末尾キーフレームの時刻より大きい場合、末尾キーフレームの値を返す
		if (curOrOver == animationCurve.keyFrames.end())
		{
			return animationCurve.keyFrames.back().value;
		}

		// timeが先頭と末尾の間だった場合
		// キーフレーム間の時間おけるtimeの比率を計算し、比率によって補間した値を返す
		const auto prev = curOrOver - 1;	// ひとつ前の(time未満の時刻を待つ)キーフレーム
		const float frameTime = curOrOver->time - prev->time;
		const float t = Mathf::Clamp01((time - prev->time) / frameTime);

		// 注意:今は常に(球状)線形保管しているが、本来は補間方法によって処理を分けるべき
		if constexpr (std::is_same_v<T, Quaternion>)
		{
			return Quaternion::Slerp(prev->value, curOrOver->value, t);
		}
		else
		{
			return prev->value * (1 - t) + curOrOver->value * t;
		}
	}

	/**
	* アニメーション計算用の中間データ型
	*/
	struct NodeMatrix
	{
		Matrix4x4 m = Matrix4x4(1);	// 姿勢行列
		bool isCalculated = false;	// 計算済みフラグ
	};
	using NodeMatrices = std::vector<NodeMatrix>;

	/**
	* ノートのグローバル姿勢行列を計算する
	*/
	const Matrix4x4& CalcGlobalNodeMatrix(const std::vector<GltfNode>& nodes, const GltfNode& node, NodeMatrices& matrices)
	{
		const intptr_t currentNodeId = &node - &nodes[0];
		NodeMatrix& nodeMatrix = matrices[currentNodeId];

		// 「計算済み」の場合は自分の姿勢行列を返す
		if (nodeMatrix.isCalculated)
		{
			return nodeMatrix.m;
		}

		// 「計算済みでない」場合、親の姿勢行列を合成する
		if (node.parent)
		{
			// 親の行列を取得(再起呼び出し)
			const Matrix4x4& matParent = CalcGlobalNodeMatrix(nodes, *node.parent, matrices);

			// 親の姿勢行列を合成
			nodeMatrix.m = matParent * nodeMatrix.m;
		}

		// 「計算済み」にする
		nodeMatrix.isCalculated = true;

		// 自分の姿勢行列を返す
		return nodeMatrix.m;
	}

	/**
	* アニメーションを提要下姿勢行列を計算する
	*
	* @param file			meshNodeを所有するファイルオブジェクト
	* @param meshNode		メッシュを持つノード
	* @param animation		計算の元となるアニメーション
	* @param time			アニメーションの再生位置
	*
	* @return アニメーションを適用した姿勢行列の配列
	*/
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode, const AnimationClip* animation, float time)
	{
		GltfAnimationMatrices matBones;
		if (!file || !meshNode)
		{
			return matBones;
		}

		// アニメーションが設定されてない場合
		if (!animation)
		{
			// ノードのグローバル座標変換行列を使う
			size_t size = 1;
			if (meshNode->skin >= 0)
			{
				size = file->skins[meshNode->skin].joints.size();
			}
			matBones.resize(size, meshNode->matGlobal);

			return matBones;
		}

		// アニメーションが設定されている場合

		NodeMatrices matrices;
		const auto& nodes = file->nodes;
		matrices.resize(nodes.size());

		// アニメーションしないノーdpのローカル姿勢行列をを設定
		for (const auto e : animation->staticNodes)
		{
			matrices[e].m = nodes[e].matLocal;
		}

		// アニメーションするノードのローカル姿勢行列を計算
		// (拡大縮小→回転→平行移動の順で適用)
		for (const auto& e : animation->translations)
		{
			const Vector3 translation = Interpolate(e, time);
			matrices[e.targetNodeId].m = Matrix4x4::Translate(translation);
		}
		for (const auto& e : animation->rotations)
		{
			const Quaternion rotation = Interpolate(e, time);
			matrices[e.targetNodeId].m *= Matrix4x4(Quaternion::QuaternionToRotationMatrix(rotation));
		}
		for (const auto& e : animation->scales)
		{
			const Vector3 scale = Interpolate(e, time);
			matrices[e.targetNodeId].m *= Matrix4x4::Scale(scale);
		}

		// アニメーションを適用したグローバル姿勢行列を計算
		if (meshNode->skin >= 0)
		{
			for (const auto& joint : file->skins[meshNode->skin].joints)
			{
				CalcGlobalNodeMatrix(nodes, nodes[joint.nodeId], matrices);
			}
		}
		else
		{
			// ジョイントがないのでメッシュノードだけ計算
			CalcGlobalNodeMatrix(nodes, *meshNode, matrices);
		}

		// 逆バインドポーズ行列を合成
		if (meshNode->skin >= 0)
		{
			// glTFのjointsキーにはノード番号が格納されている
			// しかし、頂点データのJOINTS_n属性には「joints配列のインデックス」が格納されている
			// 実際に姿勢行列を使うのは頂点データなので、姿勢行列をjoints配列の順番で格納する
			const auto& joints = file->skins[meshNode->skin].joints;
			matBones.resize(joints.size());
			for (size_t i = 0; i < joints.size(); ++i)
			{
				const auto& joint = joints[i];
				matBones[i] = matrices[joint.nodeId].m * joint.matInverseBindPose;
			}
		}
		else
		{
			// ジョイントがないので逆バインドポーズ行列も存在しない
			const size_t nodeId = meshNode - &nodes[0];
			matBones.resize(1, matrices[nodeId].m);
		}
		return matBones;
	}
}

namespace FGEngine
{
	/**
	* コンストラクタ
	*
	* @param bufferSize 格納できる頂点データのサイズ(バイト数)
	* @param maxMatrixCount	アニメーション用SSBOに格納できる最大行列数
	*/
	GltfFileBuffer::GltfFileBuffer(size_t bufferSize, size_t maxMatrixCount)
	{
		// GPUメモリを確保し、書き込み専用としてマップする
		buffer = BufferObject::Create(bufferSize, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		pBuffer = static_cast<uint8_t*>(glMapNamedBuffer(*buffer, GL_WRITE_ONLY));

		// バッファの先頭にダミーデータを設定
		const Vertex defaultData;
		memcpy(pBuffer, &defaultData, sizeof(defaultData));
		curBufferSize = sizeof(defaultData);

		// アニメーションの姿勢行列用バッファを作成
		animationBuffer = MappedBufferObject::Create(maxMatrixCount * sizeof(Matrix4x4),
			GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
		tmpAnimationBuffer.reserve(maxMatrixCount);

		// デフォルトマテリアルを作成
		defaultMaterial = std::make_shared<Material>();
		defaultMaterial->name = "defaultMaterial";
		defaultMaterial->mainTexture = Texture::Create("defaultTexture", 4, 4);
		static const uint32_t img[4 * 4] = { // テクスチャデータ
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
		};
		glTextureSubImage2D(*defaultMaterial->mainTexture, 0, 0, 0,
			+4, 4, GL_BGRA, GL_UNSIGNED_BYTE, img);
	}

	/**
	* glTFFileBufferを作成
	*
	* @param bufferSize 格納できる頂点データのサイズ(バイト数)
	* @param maxMatrixCount	アニメーション用SSBOに格納できる最大行列数
	*
	* @return 作成したglTFFileBufferポインター
	*/
	GltfFileBufferPtr GltfFileBuffer::Create(size_t bufferSize, size_t maxMatrixCount)
	{
		return std::make_shared<GltfFileBuffer>(bufferSize, maxMatrixCount);
	}

	/**
	* glTFファイルの読み込み
	*
	* @parma name		保存したい名前
	* @parma filename	ファイルの名前
	*/
	GltfFilePtr GltfFileBuffer::LoadGltf(const std::string& name, const std::string& filename)
	{
		// glTFファイルを読み込む
		std::vector<char> buf = ReadFile(filename.c_str());
		if (buf.empty())
		{
			return nullptr;
		}
		buf.push_back('\0'); // テキスト終端を追加

		// フォルダ名を取り出す
		const std::string foldername = std::filesystem::path(filename.c_str()).parent_path().string() + '/';

		// JSONを解析
		auto p = Parse(buf.data(), foldername.c_str());
		if (!p)
		{
			LOG_ERROR("'%s'の読み込みに失敗しました", filename.c_str());
			return nullptr;
		}

		// 作成したファイルを連想配列に追加
		p->gltfFileBuffer = this;
		p->name = name;

		// 読み込んだファイル名とメッシュ名をデバッグ情報として出力
		LOG("%sを読み込みました", filename.c_str());
		for (size_t i = 0; i < p->meshes.size(); ++i)
		{
			LOG(R"(  meshes[%d]="%s")", i, p->meshes[i]->name.c_str());
		}

		for (size_t i = 0; i < p->animationClips.size(); ++i)
		{
			const std::string& name = p->animationClips[i]->name;
			const float time = p->animationClips[i]->totalTime;
			if (name.size() <= 0)
			{
				LOG(" animations[%d]=<NO NAME>", i);
			}
			else
			{
				LOG(R"( animations[%d]="%s"time=%f )", i, name.c_str(), time);
			}
		}

		return p;
	}

	/**
	* アニメーションメッシュの描画用データをすべて削除
	*/
	void GltfFileBuffer::ClearAnimationBuffer()
	{
		tmpAnimationBuffer.clear();
	}

	/**
	* アニメーションメッシュメッシュの描画用データを追加
	*
	* @param matBones SSBOに追加する姿勢行列の配列
	*
	* @return matBonesように割り当てられたSSBOの範囲
	*/
	AnimMatrixRange GltfFileBuffer::AddAnimationMatrices(const GltfAnimationMatrices& matBones)
	{
		const GLintptr offset = static_cast<GLintptr>(tmpAnimationBuffer.size() * sizeof(Matrix4x4));
		tmpAnimationBuffer.insert(tmpAnimationBuffer.end(), matBones.begin(), matBones.end());

		// SSBOのオフセットアライメント条件を満たすために256バイト境界(Matrix4x4の4個分)に配置する
		// 256はOpenGL仕様で許される最大値
		tmpAnimationBuffer.resize(((tmpAnimationBuffer.size() + 3) / 4) * 4);
		return { offset, matBones.size() * sizeof(Matrix4x4) };
	}

	/**
	* アニメーションメッシュの描画用データをGPUメモリにコピー
	*/
	void GltfFileBuffer::UploadAnimationBuffer()
	{
		if (tmpAnimationBuffer.empty())
		{
			return;	// 転送するデータがない場合は何もしない
		}
		animationBuffer->WaitSync();
		uint8_t* p = animationBuffer->GetMappedAddress();
		memcpy(p, tmpAnimationBuffer.data(), tmpAnimationBuffer.size() * sizeof(Matrix4x4));
	}

	/**
	* アニメーションメッシュの描画に使うSSBO領域に割り当てる
	*
	* @param bindingPoint	バインディングポイント
	* @param range			バインドする範囲
	*/
	void GltfFileBuffer::BindAnimationBuffer(GLuint bindingPoint, const AnimMatrixRange& range)
	{
		if (range.size > 0)
		{
			animationBuffer->Bind(bindingPoint, range.offset, range.size);
		}
	}

	/**
	* アニメーションメッシュの描画に使うSSBO両機の割り当てを解除する
	*
	* @param bindingPoint	バインディングポイント
	*/
	void GltfFileBuffer::UnbindAnimationBuffer(GLuint bindingPoint)
	{
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, bindingPoint, 0, 0, 0);
		animationBuffer->SwapBuffers();
	}

	/**
	* JSONテキストからGltfFileオブジェクトを作成する
	*
	* @param text		glTFのJOSNテキスト
	* @param foldernaem リソース読み込み用のフォルダ
	*
	* @retval nullptr以外	filenameから作成したファイルオブジェクト
	* @rtaval nullptr		読み込み失敗
	*/
	GltfFilePtr GltfFileBuffer::Parse(const char* text, const char* foldername)
	{
		// JSON解析
		json gltf = json::parse(text, nullptr, false);
		if (gltf.is_discarded())
		{
			LOG_ERROR("JSONの解析に失敗しました");
			return nullptr;
		}
		// バイナリファイルを読み込む
		const GLsizeiptr prevBufferSize = curBufferSize;
		const json& buffers = gltf["buffers"];
		BinaryList binaryList(buffers.size());
		for (size_t i = 0; i < buffers.size(); ++i)
		{
			const auto uri = buffers[i].find("uri");
			if (uri == buffers[i].end())
			{
				continue;
			}
			// ファイルを読み込む
			const std::string binPath = foldername + uri->get<std::string>();
			binaryList[i].bin = ReadFile(binPath.c_str());
			if (binaryList[i].bin.empty())
			{
				curBufferSize = prevBufferSize;	// 読み込んだデータをなったことにする
				return nullptr;	// バイナリファイルの読み込みに失敗
			}

			// バイナリデータをGPUメモリにコピー
			memcpy(pBuffer + curBufferSize, binaryList[i].bin.data(), binaryList[i].bin.size());

			// オフセットを更新
			binaryList[i].offset = curBufferSize;
			curBufferSize += binaryList[i].bin.size();
		}

		// ファイルオブジェクト作成
		GltfFilePtr file = std::make_shared<GltfFile>();

		// ルートノードの姿勢行列を取得
		const auto nodes = gltf.find("nodes");
		if (nodes != gltf.end())
		{
			const json& rootNode = nodes->at(0);
			const auto matrix = rootNode.find("matrix");
			if (matrix != rootNode.end())
			{
				if (matrix->size() >= 16)
				{
					for (int i = 0; i < 16; ++i)
					{
						file->matRoot(i / 4, i % 4) = matrix->at(i).get<float>();
					}
				}
			}
		}

		// メッシュを作成
		const json& accessors = gltf["accessors"];
		const json& bufferViews = gltf["bufferViews"];
		const json& meshes = gltf["meshes"];
		file->meshes.reserve(meshes.size());
		for (const json& jsonMesh : meshes)
		{
			// メッシュ名を取得
			StaticMeshPtr mesh = std::make_shared<StaticMesh>();
			mesh->name = jsonMesh.value("name", "<default>");

			// プリミティブを作成
			const json& primitives = jsonMesh["primitives"];
			mesh->drawParamsList.reserve(primitives.size());
			for (const json& jsonPrim : primitives)
			{
				// VAOを作成
				DrawParams prim;
				prim.vao = VertexArrayObject::Create();

				// VAOをOpenGLコンテキストに割り当てる
				prim.vao->Bind();

				// VBOとIBOを、OpenGLコンテキストとVAOの両方に割り当てる
				glBindBuffer(GL_ARRAY_BUFFER, *buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);

				// プリミティブのパラメータを取得
				{
					// プリミティブの種類
					prim.mode = jsonPrim.value("mode", GL_TRIANGLES);

					// インデックス数と型
					const int accessorId = jsonPrim["indices"].get<int>();
					const json& accessor = accessors[accessorId];
					prim.count = accessor["count"].get<int>();
					//prim.type = accessor["componentType"].get<int>();

					// インデックスデータの開始位置
					const int bufferViewId = accessor["bufferView"].get<int>();
					const json& bufferView = bufferViews[bufferViewId];
					prim.indices = reinterpret_cast<const void*>(
						GetBinaryDataOffset(accessor, bufferView, binaryList));
				}

				// 頂点アトリビュートを取得
				const json& attributes = jsonPrim["attributes"];

				// 頂点アトリビュート(頂点座標)を取得
				const bool hasPosition = SetVertexAttribute(AttribIndex::position, "POSITION", attributes,
					accessors, bufferViews, binaryList);
				if (!hasPosition)
				{
					SetDefaultAttribute(AttribIndex::position, 3, offsetof(Vertex, position), *buffer);
				}

				// 頂点アトリビュート(テクスチャ座標)を取得
				const bool hasTexcoord0 = SetVertexAttribute(AttribIndex::texcoord0, "TEXCOORD_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasTexcoord0)
				{
					SetDefaultAttribute(AttribIndex::texcoord0, 2, offsetof(Vertex, texcoord0), *buffer);
				}

				// 頂点アトリビュート(法線)を取得
				const bool hasNormal = SetVertexAttribute(AttribIndex::normal, "NORMAL", attributes,
					accessors, bufferViews, binaryList);
				if (!hasNormal)
				{
					SetDefaultAttribute(AttribIndex::normal, 3, offsetof(Vertex, normal), *buffer);
				}

				// 頂点アトリビュート(タンジェント)を取得
				//const bool hasTangent = SetVertexAttribute(AttribIndex::tangent, "TANGENT", attributes,
				//	accessors, bufferViews, binaryList);
				//if (!hasTangent)
				//{
				//	SetDefaultAttribute(AttribIndex::tangent, 4, offsetof(DefaultVertexData, tangent), *buffer);
				//}

				// 頂点アトリビュート(ジョイント番号)を取得
				const bool hasJoints = SetVertexAttribute(AttribIndex::joints0, "JOINTS_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasJoints)
				{
					SetDefaultAttribute(AttribIndex::joints0, 4, offsetof(Vertex, joints0), *buffer);
				}

				// 頂点アトリビュート(ジョイントウェイン)を取得
				const auto hasWeights = SetVertexAttribute(AttribIndex::weights0, "WEIGHTS_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasWeights)
				{
					SetDefaultAttribute(AttribIndex::weights0, 4, offsetof(Vertex, weights0), *buffer);
				}


				// プリミティブが使用するマテリアル番号を取得
				prim.materialNo = jsonPrim.value("material", 0);

				// VAO,VBO,IBOのOpenGLコンテキストへの割り当てを解除
				glBindVertexArray(0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// 作成したプリミティブを配列に追加
				mesh->drawParamsList.push_back(prim);
			}
			// 作成したメッシュオブジェクトを配列に追加
			file->meshes.push_back(mesh);
		}

		// マテリアルを作成
		const auto materials = gltf.find("materials");
		if (materials != gltf.end())
		{
			file->materials.reserve(materials->size());
			for (const json& material : *materials)
			{
				MaterialPtr m = std::make_shared<Material>();

				// 名前を設定
				m->name = material.value("name", std::string());

				// カラーを設定
				const auto pbr = material.find("pbrMetallicRoughness");
				if (pbr != material.end())
				{
					// マテリアルカラーを取得
					m->color = Color(1);
					const auto baseColorFactor = pbr->find("baseColorFactor");
					if (baseColorFactor != pbr->end())
					{
						for (int i = 0; i < baseColorFactor->size(); ++i) {
							m->color[i] = baseColorFactor->at(i).get<float>();
						}
					}

					// カラーテクスチャを読み込む
					m->mainTexture = LoadTexture("baseColorTexture", gltf, *pbr,
						foldername, defaultMaterial->mainTexture);
				} // if pbr

				// 法線テクスチャを読み込む
				m->normalTexture = LoadTexture("normalTexture", gltf, material, foldername, nullptr);

				// 作成したマテリアルを追加
				file->materials.push_back(m);
			}
		}

		// ノードを作成
		if (nodes != gltf.end())
		{
			file->nodes.resize(nodes->size());
			for (size_t i = 0; i < nodes->size(); ++i)
			{
				const json& node = nodes->at(i);
				GltfNode& n = file->nodes[i];
				n.name = node.value("name", std::string());
				n.mesh = node.value("mesh", -1);
				n.skin = node.value("skin", -1);

				// 子ノードを取得し、子ノードに対して親ノードを設定
				const auto children = node.find("children");
				if (children != node.end())
				{
					n.children.resize(children->size());
					for (int b = 0; b < children->size(); ++b)
					{
						const json& child = children->at(b);
						const int childId = child.get<int>();
						n.children[b] = &file->nodes[childId];	// 子ノードを追加
						n.children[b]->parent = &n;				// 親ノードを設定
					}
				}

				// ローカル座標変換行列を計算
				n.matLocal = GetLocalMatrix(node);
			}

			// 親をたどってグローバル座法変換行列を計算する
			for (GltfNode& e : file->nodes)
			{
				e.matGlobal = e.matLocal;
				const GltfNode* parent = e.parent;
				while (parent)
				{
					e.matGlobal = parent->matLocal * e.matGlobal;
					parent = parent->parent;
				}
			}
		}

		// シーンを作成
		const auto scenes = gltf.find("scenes");
		if (scenes != gltf.end())
		{
			// 各シーンに表示するノード配列を取得
			file->scenes.resize(scenes->size());
			for (size_t a = 0; a < scenes->size(); ++a)
			{
				const json& scene = scenes->at(a);
				const auto nodes = scene.find("nodes");
				if (nodes == scene.end())
				{
					continue;
				}
				GltfScene& s = file->scenes[a];
				s.nodes.resize(nodes->size());
				for (size_t b = 0; b < nodes->size(); ++b)
				{
					const int nodeId = nodes->at(b).get<int>();
					const GltfNode* n = &file->nodes[nodeId];
					s.nodes[b] = n;
					GetMeshNodeList(n, s.meshNodes);
				}
			}
		}

		// スキンを取得する
		const auto skins = gltf.find("skins");
		if (skins != gltf.end())
		{
			file->skins.resize(skins->size());
			for (size_t skinId = 0; skinId < skins->size(); ++skinId)
			{
				// スキン名を設定
				const json& skin = skins->at(skinId);
				GltfSkin& s = file->skins[skinId];
				s.name = skin.value("name", std::string());

				// 逆バインドポーズ行列のアドレスを取得
				const Matrix4x4* inverseBindMatrices = nullptr;
				const auto ibm = skin.find("inverseBindMatrices");
				if (ibm != skin.end())
				{
					const int ibmId = ibm->get<int>();
					inverseBindMatrices = static_cast<const Matrix4x4*>(
						GetBinaryDataAddress(accessors[ibmId], bufferViews, binaryList));
				}

				// 関節データを取得
				const json& joints = skin["joints"];
				s.joints.resize(joints.size());
				for (size_t jointId = 0; jointId < joints.size(); ++jointId)
				{
					auto& j = s.joints[jointId];
					j.nodeId = joints[jointId].get<int>();
					// 逆バインドポーズ行列が未指定の場合は単位行列を使う(glTF仕様 5.28.1)
					if (inverseBindMatrices)
					{
						j.matInverseBindPose = inverseBindMatrices[jointId];
					}
					else
					{
						j.matInverseBindPose = Matrix4x4(1);
					}
				}
			}
		}

		const auto animations = gltf.find("animations");
		if (animations != gltf.end())
		{
			file->animationClips.resize(animations->size());
			for (size_t animeId = 0; animeId < animations->size(); ++animeId)
			{
				// 名前を設定
				const json& animation = animations->at(animeId);
				AnimationClipPtr a = std::make_shared<AnimationClip>();
				a->name = animation.value("name", std::string());

				// チャネル配列の容量を予約
				// 一般的に、平行移動、回転、拡大縮小の３つはセットで指定するので
				// 各チャネル配列のサイズは「総チャネル / 3」になる可能性が高い
				// 安全のため、予約サイズが必ず1以上んあるように１を足している
				const json& channels = animation["channels"];
				const size_t predictedSize = channels.size() / 3 + 1;	// 予測サイズ
				a->translations.reserve(predictedSize);
				a->rotations.reserve(predictedSize);
				a->scales.reserve(predictedSize);

				// すべてのノードを「アニメーションなし」として登録
				a->staticNodes.resize(nodes->size());
				for (int i = 0; i < nodes->size(); ++i)
				{
					a->staticNodes[i] = i;
				}


				// チャネル配列を設定
				const json& samplers = animation["samplers"];
				a->totalTime = 0;
				for (const json& e : channels)
				{
					// 時刻の配列を取得
					const json& sampler = samplers[e["sampler"].get<int>()];
					const json& inputAccessor = accessors[sampler["input"].get<int>()];
					const GLfloat* pTimes = static_cast<const GLfloat*>(
						GetBinaryDataAddress(inputAccessor, bufferViews, binaryList));

					// 再生時間を計算
					a->totalTime = std::max(a->totalTime, inputAccessor["max"][0].get<float>());

					// 値の配列を取得
					const json& outputAccessor = accessors[sampler["output"].get<int>()];
					const void* pValue = GetBinaryDataAddress(outputAccessor, bufferViews, binaryList);

					// 補間方法を取得
					GltfInterpolation interp = GltfInterpolation::Linear;
					const json& target = e["target"];
					const std::string& interpolation = target.value("interpolation", std::string());
					if (interpolation == "LINEAR")
					{
						interp = GltfInterpolation::Linear;
					}
					else if (interpolation == "STEP")
					{
						interp = GltfInterpolation::None;
					}
					else if (interpolation == "CUBISPLINE")
					{
						interp = GltfInterpolation::CubicSpline;
					}

					// 時刻と値の配列からチャネルを作成し、pathに対応する配列に追加
					const int inputCount = inputAccessor["count"].get<int>();
					const int targetNodeId = target["node"].get<int>();
					const std::string& path = target["path"].get<std::string>();
					if (path == "translation")
					{
						a->translations.push_back(MakeAnimationChannel<Vector3>(
							pTimes, pValue, inputCount, targetNodeId, interp));
					}
					else if (path == "rotation")
					{
						a->rotations.push_back(MakeAnimationChannel<Quaternion>(
							pTimes, pValue, inputCount, targetNodeId, interp));
					}
					else if (path == "scale")
					{
						a->scales.push_back(MakeAnimationChannel<Vector3>(
							pTimes, pValue, inputCount, targetNodeId, interp));
					}
					a->staticNodes[targetNodeId] = -1;	// アニメーションあり
				}

				// 「アニメーションあり」をリストから削除する
				const auto itr = std::remove(a->staticNodes.begin(), a->staticNodes.end(), -1);
				a->staticNodes.erase(itr, a->staticNodes.end());
				a->staticNodes.shrink_to_fit();

				// アニメーションを設定
				file->animationClips[animeId] = a;
			}
		}

		// 作成したファイルを返す
		return file;
	}
}