/**
* @file Mesh.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include "MeshBuffer.h"
#include "Debug.h"
#include "Vertex.h"
#include "ResouceManager.h"
#include "ShaderLocationNum.h"

#include <numeric>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdio.h>

namespace FGEngine::RenderingSystem
{
	/**
	* コンストラクタ
	*/
	MeshBuffer::MeshBuffer(size_t bufferSize)
	{
		// バッファオブジェクトを作成
		buffer = BufferObject::Create(bufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);

		// VAOを作成
		vao = VertexArrayObject::Create();

		// VBOとIBOをVAOにバインド
		glBindVertexArray(*vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);

		// 頂点アトリビュートを設定
		vao->SetAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, position));
		vao->SetAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texcoord));
		vao->SetAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, normal));


		// スケルタルメッシュ用のVAOを作成
		vaoSkeletal = VertexArrayObject::Create();

		glBindVertexArray(*vaoSkeletal);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);

		vaoSkeletal->SetAttribute(0, 3, sizeof(SkeletalVertex), offsetof(SkeletalVertex, position));
		vaoSkeletal->SetAttribute(1, 2, sizeof(SkeletalVertex), offsetof(SkeletalVertex, texcoord));
		vaoSkeletal->SetAttribute(2, 3, sizeof(SkeletalVertex), offsetof(SkeletalVertex, normal));
		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, 4, GL_UNSIGNED_SHORT, sizeof(SkeletalVertex),
			reinterpret_cast<const void*>(offsetof(SkeletalVertex, joints)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(SkeletalVertex),
			reinterpret_cast<const void*>(offsetof(SkeletalVertex, weights)));

		// 誤った操作が行われないようにバインドを解除
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// スタティックメッシュの容量を予約
		meshes.reserve(1000);

		// 描画パラメータ配列の容量を確保
		drawParamsList.reserve(100);

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
	void MeshBuffer::AddVertexData(const void* vertices, size_t vertexBytes, const uint16_t* indices, size_t indexBytes, size_t stride, GLenum mode)
	{
		// 空き容量が足りていることを確認
		// 必要なバイト数が空きバイト数より大きい場合は追加できない
		const size_t totalBytes = vertexBytes + indexBytes;	// Byteの合計
		const size_t freeBytes = buffer->GetSize() - usedBytes; //　空き容量

		// 必要バイト > 空き容量
		if (totalBytes > freeBytes)
		{
			LOG_ERROR("容量が足りません(要求サイズ=%d, 使用量/最大容量=%d%d)", totalBytes, usedBytes, buffer->GetSize());
			return;
		}

		// 頂点データをGPUメモリにコピー
		GLuint tmp[2];
		// (作成するオブジェクト,番号を格納する配列)
		glCreateBuffers(2, tmp);
		// (バッファの管理番号、コピーするバイト数、コピーするデータのアドレス(メモリの確保の時はnullptr)、各種フラグ)
		glNamedBufferStorage(tmp[0], vertexBytes, vertices, 0);
		glNamedBufferStorage(tmp[1], indexBytes, indices, 0);
		// (コピー元のバッファの管理番号、コピー先バッファの管理番号、コピー元の読み取り開始位置、コピー先の書き込み開始位置、コピーするバイト数)
		glCopyNamedBufferSubData(tmp[0], *buffer, 0, usedBytes, vertexBytes);
		glCopyNamedBufferSubData(tmp[1], *buffer, 0, usedBytes + vertexBytes, indexBytes);
		// バッファを削除
		glDeleteBuffers(2, tmp);

		// 追加した図形の描画パラメータを作成
		DrawParams newParams;
		newParams.mode = mode;
		newParams.count = static_cast<GLsizei>(indexBytes / sizeof(uint16_t));
		// インデックスデータの位置（バイト数で指定）は頂点データの直後
		newParams.indices = reinterpret_cast<void*>(usedBytes + vertexBytes);
		//　頂点データの位置は頂点データ数で指定する
		newParams.baseVertex = static_cast<GLint>(usedBytes / stride);
		drawParamsList.push_back(newParams);

		// 次のデータ格納開始位置を計算
		/// std::lcm(数値その１、数値その２)最小公倍数
		constexpr size_t a = std::lcm(sizeof(SkeletalVertex),
			std::lcm(sizeof(uint16_t), sizeof(Vertex)));
		usedBytes += ((totalBytes + a - 1) / a) * a;

	}

	/**
	* OBJファイルを読み込む
	*
	* @param filename OBJファイル名
	*
	* @return filenameから作成したメッシュ
	*/
	void MeshBuffer::LoadObj(const std::string& name, const std::string& filename)
	{
		// OBJファイルからメッシュデータを作成
		MeshData meshData = CreateMeshDataFormObj(filename);
		if (meshData.vertices.empty())
		{
			return;	// 読み込みを失敗
		}

		// 変換したデータをバッファに追加
		AddVertexData(
			meshData.vertices.data(), meshData.vertices.size() * sizeof(Vertex),
			meshData.indices.data(), meshData.indices.size() * sizeof(uint16_t),
			sizeof(Vertex));

		// メッシュを作成
		auto pMesh = std::make_shared<StaticMesh>();

		pMesh->drawParamsList.swap(meshData.drawParamsList);
		pMesh->materials.swap(meshData.materials);
		pMesh->SetName(name);
		pMesh->vao = vao;
		meshes.emplace(name, pMesh);

		// AddVertexDataでコピーしたデータの位置を、描画パラメータに反映
		const intptr_t baseIndexOffset = reinterpret_cast<intptr_t>(drawParamsList.back().indices);
		const GLint baseVertex = drawParamsList.back().baseVertex;
		for (auto& e : pMesh->drawParamsList)
		{
			e.baseVertex = baseVertex;
			e.indices = reinterpret_cast<const void*>(baseIndexOffset + reinterpret_cast<intptr_t>(e.indices));
		}

		LOG("%sを読み込みました(頂点数=%d, インデックス数=%d)", filename.c_str(), meshData.vertices.size(), meshData.indices.size());
	}

	
	/**
	* すべての頂点データの削除
	*/
	void MeshBuffer::Clear()
	{
		usedBytes = 0;
		meshes.clear();
		drawParamsList.clear();
	}

	/**
	* スタティックメッシュを取得
	*
	* @param name スタティックメッシュの名前
	*
	* @return 名前がnameと一致するスタティックメッシュ
	*/
	StaticMeshPtr MeshBuffer::GetStaticMesh(const std::string& name) const
	{
		auto itr = meshes.find(name);
		if (itr != meshes.end())
		{
			return itr->second;
		}
		LOG_ERROR("(StaticMesh)%sは登録されていません", name.c_str());
		return nullptr;
	}

	/**
	* スケルタルメッシュを取得
	*
	* @param name スケルタルメッシュの名前
	*
	* @return 名前がnameと一致するスケルタルメッシュ
	*/
	SkeletalMeshPtr MeshBuffer::GetSkeletalMesh(const std::string& name) const
	{
		auto itr = skeletalMeshes.find(name);
		if (itr != skeletalMeshes.end()) 
		{
			return itr->second;
		}
		LOG_ERROR("(SkeltalMesh)%sは登録されていません", name.c_str());
		return nullptr;
	}

	/**
	* MTLファイルを読み込む
	*
	* @param foldername	OBJファイルのあるファルダ名
	* @param filename	MTLファイル名
	*
	* @return MTLファイルに含まれるマテリアルの配列
	*/
	std::vector<MaterialPtr> MeshBuffer::LoadMTL(const std::string& foldername, const char* filename)
	{
		// MTLファイルを開く
		const std::string fullpath = foldername + filename;
		std::ifstream file(fullpath);
		if (!file)
		{
			LOG_ERROR("%sを開けません", fullpath.c_str());
			return{};
		}

		// MTLファイルを解析する
		std::vector<MaterialPtr> materials;
		MaterialPtr pMaterial;
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			const char* p = line.c_str();

			// マテリアル定義の読み取りを試みる
			char name[1000] = { 0 };
			if (sscanf(line.data(), " newmtl %999s", name) == 1) 
			{
				pMaterial = std::make_shared<Material>();
				pMaterial->SetName(name);
				materials.push_back(pMaterial);
				continue;
			}

			// マテリアルが定義されていない場合は行を無視する
			if (!pMaterial)
			{
				continue;
			}

			// 基本色の読み取りを試みる
			if (sscanf(line.data(), " Kd %f %f %f",
				&pMaterial->color.r,
				&pMaterial->color.g,
				&pMaterial->color.b) == 3) {
				continue;
			}

			// 不透明度の読み取りを試みる
			if (sscanf(line.data(), " d %f", &pMaterial->color.a) == 1) 
			{
				continue;
			}

			// 基本色テクスチャ名の読み取りを試みる
			char texureName[1000] = { 0 };
			if (sscanf(line.data(), " map_Kd %999s", &texureName) == 1) 
			{
				const std::string filename = foldername + texureName;
				if (std::filesystem::exists(filename)) 
				{
					pMaterial->mainTexture = ResouceSystem::ResouceManager::GetInstance()->GetTexture(filename);
				}
				else
				{
					LOG_WARNINGS("%sを開けません", filename.c_str());
				}
				continue;
			}

			// 発光色の読み取りを試みる
			if (sscanf(line.data(), " Ke %f %f %f", &pMaterial->emissionColor.r,
				&pMaterial->emissionColor.g, &pMaterial->emissionColor.b) == 3)
			{
				continue;
			}

			// 発光色テクスチャ名の読みとりを試みる
			if (sscanf(line.data(), " map_Ke %999s", &texureName) == 1) 
			{
				const std::string filename = foldername + texureName;
				if (std::filesystem::exists(filename)) 
				{
					pMaterial->emissionTexture = ResouceSystem::ResouceManager::GetInstance()->GetTexture(filename);
				}
				else 
				{
					LOG_WARNINGS("%sを開けません", filename.c_str());
				}
				continue;
			}
		}

		// 読み込んだマテリアル配列を返す
		return materials;
	}

	/**
	* OBJファイルをメッシュデータを変換する
	*
	* @param filename OBJファイル名
	*
	* @return filenameから作成したメッシュデータ
	*/
	MeshBuffer::MeshData MeshBuffer::CreateMeshDataFormObj(const std::string& filename)
	{
		// OBJファイルを開く
		std::ifstream file(filename);
		if (!file)
		{
			LOG_ERROR("%sを開けません", filename);
			return {}; // 空のオブジェクトを返す
		}

		// フォルダ名を取得する
		std::string foldername(filename);
		{
			const size_t p = foldername.find_last_of("\\/");
			if (p != std::string::npos)
			{
				foldername.resize(p + 1);
			}
		}

		// OBJファイルを解析して、頂点データとインデックスデータを読み込む
		std::vector<Vector3> positions;
		std::vector<Vector2> texcoords;
		std::vector<Vector3> normals;
		struct IndexSet {
			int v = 0;
			int vt = 0;
			int vn = 0;
		};
		std::vector<IndexSet> faceIndexSet;

		positions.reserve(20'000);
		texcoords.reserve(20'000);
		normals.reserve(20'000);
		faceIndexSet.reserve(static_cast<std::vector<IndexSet, std::allocator<IndexSet>>::size_type>(20'000) * 3);

		// マテリアル
		std::vector<MaterialPtr> materials;
		materials.reserve(100);

		// マテリアルの使用範囲
		struct UseMaterial {
			std::string name;	// マテリアル名
			size_t startOffset;	// 割り当て範囲の先頭位置
		};
		std::vector<UseMaterial> usemtls;
		usemtls.reserve(100);

		// 仮データを追加(マテリアル指定がないファイル対策)
		usemtls.push_back({ std::string(), 0 });

		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			const char* p = line.c_str();

			// 頂点座標の読み取り試みる
			Vector3 v = Vector3::zero;
			// int sscanf(回世紀対象バッファ、書式指定文字列、データ格納先アドレス、 ...)
			//　戻り値実際に変換できた個数
			if (sscanf(p, " v %f %f %f", &v.x, &v.y, &v.z) == 3)
			{
				positions.push_back(v);
				continue; // 次の行に進む
			}

			// テクスチャ座標の読み取りを試みる
			Vector2 vt = Vector2::zero;
			if (sscanf(p, "vt %f %f", &vt.x, &vt.y) == 2)
			{
				texcoords.push_back(vt);
				continue; // 次の行に進む
			}

			// 法線の読み取りを試みる
			Vector3 vn = Vector3::zero;
			if (sscanf(p, " vn %f %f %f", &vn.x, &vn.y, &vn.z) == 3) {
				normals.push_back(vn);
				continue;
			}

			// 頂点座標+テクスチャ座標+法線
			IndexSet f0, f1, f2;
			int readByte = 0;
			if (sscanf(p, " f %u/%u/%u %u/%u/%u%n", &f0.v, &f0.vt, &f0.vn, &f1.v, &f1.vt, &f1.vn, &readByte) == 6) {
				p += readByte; // 読み取り位置の更新
				for (;;) {
					if (sscanf(p, " %u/%u/%u%n", &f2.v, &f2.vt, &f2.vn, &readByte) != 3) {
						break;
					}
					p += readByte; // 読み取り位置を更新
					faceIndexSet.push_back(f0);
					faceIndexSet.push_back(f1);
					faceIndexSet.push_back(f2);
					f1 = f2;	// 次の三角形のためにデータを移動
				}
				continue;
			}
			// 頂点座標+テクスチャ座標
			if (sscanf(p, " f %u/%u %u/%u%n", &f0.v, &f0.vt, &f1.v, &f1.vt, &readByte) == 4) {
				f0.vn = f1.vn = 0; // 法線なし
				p += readByte; // 読み取り位置更新
				for (;;) {
					if (sscanf(p, " %u/%u%n", &f2.v, &f2.vt, &readByte) != 2) {
						break;
					}
					f2.vn = 0; // 法線なし
					p += readByte;
					faceIndexSet.push_back(f0);
					faceIndexSet.push_back(f1);
					faceIndexSet.push_back(f2);
					f1 = f2;	// 次の三角形のためにデータを移動
				}
				continue;
			}

			// MTLファイルの読み込みを試みる
			char mtlFilename[1000];
			if (sscanf(line.data(), " mtllib %999s", mtlFilename) == 1) {
				const auto tmp = LoadMTL(foldername, mtlFilename);
				materials.insert(materials.end(), tmp.begin(), tmp.end());
				continue;
			}

			// 使用中のマテリアル名の読み取りを試みる
			char mtlName[1000];
			if (sscanf(line.data(), " usemtl %999s", mtlName) == 1) {
				usemtls.push_back({ mtlName, faceIndexSet.size() });
				continue;
			}
		}
		// 末尾に番兵を追加
		usemtls.push_back({ std::string(), faceIndexSet.size() });

		// OBJファイルのｆ構文とOpenGLの頂点インデックス配列の対応表
		std::unordered_map<uint64_t, uint16_t> indexMap;
		indexMap.reserve(10000);

		// 読み込んだデータを、OpenGLで使えるデータに変換
		MeshData meshData;
		std::vector<Vertex>& vertices = meshData.vertices;
		vertices.reserve(faceIndexSet.size());
		std::vector<uint16_t>& indices = meshData.indices;
		indices.reserve(faceIndexSet.size());
		for (int i = 0; i < faceIndexSet.size(); ++i) {
			const IndexSet& e = faceIndexSet[i];

			// f構文の値の64ビットの「キー」に変換]
			const uint64_t key = static_cast<uint64_t>(e.v) +
				(static_cast<uint64_t>(e.vt) << 20) + (static_cast<uint64_t>(e.vn) << 40);

			// 対応表にあるので既存の頂点インデックスを使う
			const auto itr = indexMap.find(key);
			if (itr != indexMap.end()) {
				// 対応表にあるので既存の頂点インデックスを使う
				indices.push_back(itr->second);
			}
			else {
				// 対応表にないので新しい頂点データを作成し、頂点配列に追加
				Vertex v;
				v.position = positions[e.v - 1];
				v.texcoord = texcoords[e.vt - 1];
				// 法線が設定されていない場合は0を設定(後で計算)
				if (e.vn == 0)
				{
					v.normal = Vector3::zero;
				}
				else
				{
					v.normal = normals[e.vn - 1];
				}
				vertices.push_back(v);

				// 新しい頂点データのインデックスを、頂点データ配列を追加
				const uint16_t index = static_cast<uint16_t>(vertices.size() - 1);
				indices.push_back(index);

				// キーと頂点インデックスのペアを対応表に追加
				indexMap.emplace(key, index);
			}
		}

		// 設定されていない法線を補う
		FillMissingNormals(vertices.data(), vertices.size(), indices.data(), indices.size());


		// データの位置を更新
		const void* indexOffset = 0;
		const GLint baseVertex = 0;

		// マテリアルに対応した描画パラメータを作成
		// 仮データと番兵以外のマテリアルがある場合、仮データを飛ばす
		size_t i = 0;
		if (usemtls.size() > 2) {
			i = 1;	// 仮データと番兵以外のマテリアルがある場合、仮データを飛ばす
		}
		for (; i < usemtls.size() - 1; ++i) {
			const UseMaterial& cur = usemtls[i];	// 使用中のマテリアル
			const UseMaterial& next = usemtls[i + 1]; // 次のマテリアル
			if (next.startOffset == cur.startOffset) {
				continue;	// インデックスデータがない場合は飛ばす
			}

			// 描画パラメータを作成
			DrawParams params;
			params.mode = GL_TRIANGLES;
			params.count = static_cast<GLsizei>(next.startOffset - cur.startOffset);
			params.indices = indexOffset;
			params.baseVertex = baseVertex;
			params.materialNo = 0;	// デフォルト値を設定
			for (int i = 0; i < materials.size(); ++i) {
				if (materials[i]->ToString() == cur.name) {
					params.materialNo = i;	// 名前と一致するマテリアルを設定
					break;
				}
			}
			meshData.drawParamsList.push_back(params);

			// インデックスオフセットを変更
			indexOffset = reinterpret_cast<void*>(reinterpret_cast<size_t>(indexOffset) + sizeof(uint16_t) * params.count);
		}

		// マテリアル配列が空の場合、デフォルトマテリアルを追加
		if (materials.empty()) {
			meshData.materials.push_back(std::make_shared<Material>());
		}
		else {
			meshData.materials.assign(materials.begin(), materials.end());
		}
		return meshData;
	}

	/**
	* 描画パラメータは配列を描画する
	*
	* @param drawParamList	描画パラメータ配列
	* @param materials		マテリアル配列
	*/
	void Draw(GLuint program, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials)
	{
		// シェーダプログラムを設定
		glUseProgram(program);
		for (const auto& e : drawParamsList)
		{
			// マテリアルを設定
			if (e.materialNo >= 0 && e.materialNo < materials.size())
			{
				// マテリアルを取得
				const Material& material = *materials[e.materialNo];

				// 色を設定
				if (glGetUniformLocation(program, "color") >= 0)
				{
					const Color color = material.color;
					glProgramUniform4fv(program, 100, 1, &color.r);
				}
				// 発光色を設定
				if (glGetUniformLocation(program, "emissionColor") >= 0)
				{
					const Color emissionColor = material.emissionColor;
					glProgramUniform4fv(program, 101, 1, &emissionColor.r);
				}
				// メインテクスチャを設定
				if (material.mainTexture)
				{
					const GLuint tex = *material.mainTexture;
					glBindTextures(0, 1, &tex);
				}
				// 発光テクスチャを設定
				if (material.emissionTexture)
				{
					const GLuint tex = *material.emissionTexture;
					glBindTextures(1, 1, &tex);
				}
				else
				{
					// テクスチャ1を未設定
					glBindTextures(1, 1, nullptr);
				}
				// 透明度カット
				if (glGetUniformLocation(program, "alphaCutoff") >= 0)
				{
					glProgramUniform1f(program, locAlphaCutoff, material.alphatCutOff);
				}
			}
			// 描画
			glDrawElementsBaseVertex(e.mode, e.count, GL_UNSIGNED_SHORT, e.indices, e.baseVertex);
		}
		// シェーダプログラムを解除
		glUseProgram(0);
	}

	/**
	* スタティックメッシュを描画する
	*
	* @param mesh		スタティックメッシュ
	* @param materials	マテリアル配列
	*/
	void Draw(GLuint program, const StaticMesh& mesh, const MaterialList& materials)
	{
		Draw(program, mesh.drawParamsList, materials);
	}


	/**
	* 欠けている法線を補う
	*
	* @param vertices		頂点配列
	* @param vertexCount	頂点配列の要素数
	* @param indices		インデックス配列
	* @param indexCount		インデックス配列の要素数
	*/
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount)
	{
		// 法線が設定されていない頂点を見つける
		std::vector<bool> missingNormals(vertexCount, false);
		for (int i = 0; i < vertexCount; ++i)
		{
			// 法線の長さが0の場合を「設定されていない」とみなす
			const Vector3& n = vertices[i].normal;
			if (n.x == 0 && n.y == 0 && n.z == 0) 
			{
				missingNormals[i] = true;
			}
		}

		// 法線を計算
		for (int i = 0; i < indexCount; i += 3)
		{
			//　面を構成する2辺a,b,を求める
			const int i0 = indices[i + 0];
			const int i1 = indices[i + 1];
			const int i2 = indices[i + 2];
			const Vector3& v0 = vertices[i0].position;
			const Vector3& v1 = vertices[i1].position;
			const Vector3& v2 = vertices[i2].position;
			const Vector3 a = v1 - v0;
			const Vector3 b = v2 - v0;

			// 法線を正規化して単位ベクトルにする
			const Vector3 c = Vector3::Cross(a, b);

			// 法線を正規化して単位ベクトルにする
			const Vector3 normal = c.Normalized();

			// 法線が設定されていない頂点にだけ法線を加算
			if (missingNormals[i0])
			{
				vertices[i0].normal += normal;
			}
			if (missingNormals[i1])
			{
				vertices[i1].normal += normal;
			}
			if (missingNormals[i2])
			{
				vertices[i2].normal += normal;
			}
		}
		// 法線を正規化
		for (int i = 0; i < vertexCount; ++i)
		{
			if (missingNormals[i])
			{
				Vector3& n = vertices[i].normal;
				n.Normalize();
			}
		}
	}
}