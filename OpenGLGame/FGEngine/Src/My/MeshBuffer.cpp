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
	* �R���X�g���N�^
	*/
	MeshBuffer::MeshBuffer(size_t bufferSize)
	{
		// �o�b�t�@�I�u�W�F�N�g���쐬
		buffer = BufferObject::Create(bufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);

		// VAO���쐬
		vao = VertexArrayObject::Create();

		// VBO��IBO��VAO�Ƀo�C���h
		glBindVertexArray(*vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);

		// ���_�A�g���r���[�g��ݒ�
		vao->SetAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, position));
		vao->SetAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texcoord));
		vao->SetAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, normal));


		// �X�P���^�����b�V���p��VAO���쐬
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

		// ��������삪�s���Ȃ��悤�Ƀo�C���h������
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// �X�^�e�B�b�N���b�V���̗e�ʂ�\��
		meshes.reserve(1000);

		// �`��p�����[�^�z��̗e�ʂ��m��
		drawParamsList.reserve(100);

	}

	/**
	* ���_�f�[�^�̒ǉ�
	*
	* @param vertices		GPU�������ɃR�s�[���钸�_�f�[�^�z��
	* @param vertexBytes	vertices�̃o�C�g��
	* @param indices		GPU�������ɂɃR�s�[����C���f�b�N�X�f�[�^�z��
	* @param indexBytes		indcies�̃o�C�g��
	* @param mode			�v���~�e�B�u�̎��
	*/
	void MeshBuffer::AddVertexData(const void* vertices, size_t vertexBytes, const uint16_t* indices, size_t indexBytes, size_t stride, GLenum mode)
	{
		// �󂫗e�ʂ�����Ă��邱�Ƃ��m�F
		// �K�v�ȃo�C�g�����󂫃o�C�g�����傫���ꍇ�͒ǉ��ł��Ȃ�
		const size_t totalBytes = vertexBytes + indexBytes;	// Byte�̍��v
		const size_t freeBytes = buffer->GetSize() - usedBytes; //�@�󂫗e��

		// �K�v�o�C�g > �󂫗e��
		if (totalBytes > freeBytes)
		{
			LOG_ERROR("�e�ʂ�����܂���(�v���T�C�Y=%d, �g�p��/�ő�e��=%d%d)", totalBytes, usedBytes, buffer->GetSize());
			return;
		}

		// ���_�f�[�^��GPU�������ɃR�s�[
		GLuint tmp[2];
		// (�쐬����I�u�W�F�N�g,�ԍ����i�[����z��)
		glCreateBuffers(2, tmp);
		// (�o�b�t�@�̊Ǘ��ԍ��A�R�s�[����o�C�g���A�R�s�[����f�[�^�̃A�h���X(�������̊m�ۂ̎���nullptr)�A�e��t���O)
		glNamedBufferStorage(tmp[0], vertexBytes, vertices, 0);
		glNamedBufferStorage(tmp[1], indexBytes, indices, 0);
		// (�R�s�[���̃o�b�t�@�̊Ǘ��ԍ��A�R�s�[��o�b�t�@�̊Ǘ��ԍ��A�R�s�[���̓ǂݎ��J�n�ʒu�A�R�s�[��̏������݊J�n�ʒu�A�R�s�[����o�C�g��)
		glCopyNamedBufferSubData(tmp[0], *buffer, 0, usedBytes, vertexBytes);
		glCopyNamedBufferSubData(tmp[1], *buffer, 0, usedBytes + vertexBytes, indexBytes);
		// �o�b�t�@���폜
		glDeleteBuffers(2, tmp);

		// �ǉ������}�`�̕`��p�����[�^���쐬
		DrawParams newParams;
		newParams.mode = mode;
		newParams.count = static_cast<GLsizei>(indexBytes / sizeof(uint16_t));
		// �C���f�b�N�X�f�[�^�̈ʒu�i�o�C�g���Ŏw��j�͒��_�f�[�^�̒���
		newParams.indices = reinterpret_cast<void*>(usedBytes + vertexBytes);
		//�@���_�f�[�^�̈ʒu�͒��_�f�[�^���Ŏw�肷��
		newParams.baseVertex = static_cast<GLint>(usedBytes / stride);
		drawParamsList.push_back(newParams);

		// ���̃f�[�^�i�[�J�n�ʒu���v�Z
		/// std::lcm(���l���̂P�A���l���̂Q)�ŏ����{��
		constexpr size_t a = std::lcm(sizeof(SkeletalVertex),
			std::lcm(sizeof(uint16_t), sizeof(Vertex)));
		usedBytes += ((totalBytes + a - 1) / a) * a;

	}

	/**
	* OBJ�t�@�C����ǂݍ���
	*
	* @param filename OBJ�t�@�C����
	*
	* @return filename����쐬�������b�V��
	*/
	void MeshBuffer::LoadObj(const std::string& name, const std::string& filename)
	{
		// OBJ�t�@�C�����烁�b�V���f�[�^���쐬
		MeshData meshData = CreateMeshDataFormObj(filename);
		if (meshData.vertices.empty())
		{
			return;	// �ǂݍ��݂����s
		}

		// �ϊ������f�[�^���o�b�t�@�ɒǉ�
		AddVertexData(
			meshData.vertices.data(), meshData.vertices.size() * sizeof(Vertex),
			meshData.indices.data(), meshData.indices.size() * sizeof(uint16_t),
			sizeof(Vertex));

		// ���b�V�����쐬
		auto pMesh = std::make_shared<StaticMesh>();

		pMesh->drawParamsList.swap(meshData.drawParamsList);
		pMesh->materials.swap(meshData.materials);
		pMesh->SetName(name);
		pMesh->vao = vao;
		meshes.emplace(name, pMesh);

		// AddVertexData�ŃR�s�[�����f�[�^�̈ʒu���A�`��p�����[�^�ɔ��f
		const intptr_t baseIndexOffset = reinterpret_cast<intptr_t>(drawParamsList.back().indices);
		const GLint baseVertex = drawParamsList.back().baseVertex;
		for (auto& e : pMesh->drawParamsList)
		{
			e.baseVertex = baseVertex;
			e.indices = reinterpret_cast<const void*>(baseIndexOffset + reinterpret_cast<intptr_t>(e.indices));
		}

		LOG("%s��ǂݍ��݂܂���(���_��=%d, �C���f�b�N�X��=%d)", filename.c_str(), meshData.vertices.size(), meshData.indices.size());
	}

	
	/**
	* ���ׂĂ̒��_�f�[�^�̍폜
	*/
	void MeshBuffer::Clear()
	{
		usedBytes = 0;
		meshes.clear();
		drawParamsList.clear();
	}

	/**
	* �X�^�e�B�b�N���b�V�����擾
	*
	* @param name �X�^�e�B�b�N���b�V���̖��O
	*
	* @return ���O��name�ƈ�v����X�^�e�B�b�N���b�V��
	*/
	StaticMeshPtr MeshBuffer::GetStaticMesh(const std::string& name) const
	{
		auto itr = meshes.find(name);
		if (itr != meshes.end())
		{
			return itr->second;
		}
		LOG_ERROR("(StaticMesh)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* �X�P���^�����b�V�����擾
	*
	* @param name �X�P���^�����b�V���̖��O
	*
	* @return ���O��name�ƈ�v����X�P���^�����b�V��
	*/
	SkeletalMeshPtr MeshBuffer::GetSkeletalMesh(const std::string& name) const
	{
		auto itr = skeletalMeshes.find(name);
		if (itr != skeletalMeshes.end()) 
		{
			return itr->second;
		}
		LOG_ERROR("(SkeltalMesh)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* MTL�t�@�C����ǂݍ���
	*
	* @param foldername	OBJ�t�@�C���̂���t�@���_��
	* @param filename	MTL�t�@�C����
	*
	* @return MTL�t�@�C���Ɋ܂܂��}�e���A���̔z��
	*/
	std::vector<MaterialPtr> MeshBuffer::LoadMTL(const std::string& foldername, const char* filename)
	{
		// MTL�t�@�C�����J��
		const std::string fullpath = foldername + filename;
		std::ifstream file(fullpath);
		if (!file)
		{
			LOG_ERROR("%s���J���܂���", fullpath.c_str());
			return{};
		}

		// MTL�t�@�C������͂���
		std::vector<MaterialPtr> materials;
		MaterialPtr pMaterial;
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			const char* p = line.c_str();

			// �}�e���A����`�̓ǂݎ������݂�
			char name[1000] = { 0 };
			if (sscanf(line.data(), " newmtl %999s", name) == 1) 
			{
				pMaterial = std::make_shared<Material>();
				pMaterial->SetName(name);
				materials.push_back(pMaterial);
				continue;
			}

			// �}�e���A������`����Ă��Ȃ��ꍇ�͍s�𖳎�����
			if (!pMaterial)
			{
				continue;
			}

			// ��{�F�̓ǂݎ������݂�
			if (sscanf(line.data(), " Kd %f %f %f",
				&pMaterial->color.r,
				&pMaterial->color.g,
				&pMaterial->color.b) == 3) {
				continue;
			}

			// �s�����x�̓ǂݎ������݂�
			if (sscanf(line.data(), " d %f", &pMaterial->color.a) == 1) 
			{
				continue;
			}

			// ��{�F�e�N�X�`�����̓ǂݎ������݂�
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
					LOG_WARNINGS("%s���J���܂���", filename.c_str());
				}
				continue;
			}

			// �����F�̓ǂݎ������݂�
			if (sscanf(line.data(), " Ke %f %f %f", &pMaterial->emissionColor.r,
				&pMaterial->emissionColor.g, &pMaterial->emissionColor.b) == 3)
			{
				continue;
			}

			// �����F�e�N�X�`�����̓ǂ݂Ƃ�����݂�
			if (sscanf(line.data(), " map_Ke %999s", &texureName) == 1) 
			{
				const std::string filename = foldername + texureName;
				if (std::filesystem::exists(filename)) 
				{
					pMaterial->emissionTexture = ResouceSystem::ResouceManager::GetInstance()->GetTexture(filename);
				}
				else 
				{
					LOG_WARNINGS("%s���J���܂���", filename.c_str());
				}
				continue;
			}
		}

		// �ǂݍ��񂾃}�e���A���z���Ԃ�
		return materials;
	}

	/**
	* OBJ�t�@�C�������b�V���f�[�^��ϊ�����
	*
	* @param filename OBJ�t�@�C����
	*
	* @return filename����쐬�������b�V���f�[�^
	*/
	MeshBuffer::MeshData MeshBuffer::CreateMeshDataFormObj(const std::string& filename)
	{
		// OBJ�t�@�C�����J��
		std::ifstream file(filename);
		if (!file)
		{
			LOG_ERROR("%s���J���܂���", filename);
			return {}; // ��̃I�u�W�F�N�g��Ԃ�
		}

		// �t�H���_�����擾����
		std::string foldername(filename);
		{
			const size_t p = foldername.find_last_of("\\/");
			if (p != std::string::npos)
			{
				foldername.resize(p + 1);
			}
		}

		// OBJ�t�@�C������͂��āA���_�f�[�^�ƃC���f�b�N�X�f�[�^��ǂݍ���
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

		// �}�e���A��
		std::vector<MaterialPtr> materials;
		materials.reserve(100);

		// �}�e���A���̎g�p�͈�
		struct UseMaterial {
			std::string name;	// �}�e���A����
			size_t startOffset;	// ���蓖�Ĕ͈͂̐擪�ʒu
		};
		std::vector<UseMaterial> usemtls;
		usemtls.reserve(100);

		// ���f�[�^��ǉ�(�}�e���A���w�肪�Ȃ��t�@�C���΍�)
		usemtls.push_back({ std::string(), 0 });

		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			const char* p = line.c_str();

			// ���_���W�̓ǂݎ�莎�݂�
			Vector3 v = Vector3::zero;
			// int sscanf(�񐢋I�Ώۃo�b�t�@�A�����w�蕶����A�f�[�^�i�[��A�h���X�A ...)
			//�@�߂�l���ۂɕϊ��ł�����
			if (sscanf(p, " v %f %f %f", &v.x, &v.y, &v.z) == 3)
			{
				positions.push_back(v);
				continue; // ���̍s�ɐi��
			}

			// �e�N�X�`�����W�̓ǂݎ������݂�
			Vector2 vt = Vector2::zero;
			if (sscanf(p, "vt %f %f", &vt.x, &vt.y) == 2)
			{
				texcoords.push_back(vt);
				continue; // ���̍s�ɐi��
			}

			// �@���̓ǂݎ������݂�
			Vector3 vn = Vector3::zero;
			if (sscanf(p, " vn %f %f %f", &vn.x, &vn.y, &vn.z) == 3) {
				normals.push_back(vn);
				continue;
			}

			// ���_���W+�e�N�X�`�����W+�@��
			IndexSet f0, f1, f2;
			int readByte = 0;
			if (sscanf(p, " f %u/%u/%u %u/%u/%u%n", &f0.v, &f0.vt, &f0.vn, &f1.v, &f1.vt, &f1.vn, &readByte) == 6) {
				p += readByte; // �ǂݎ��ʒu�̍X�V
				for (;;) {
					if (sscanf(p, " %u/%u/%u%n", &f2.v, &f2.vt, &f2.vn, &readByte) != 3) {
						break;
					}
					p += readByte; // �ǂݎ��ʒu���X�V
					faceIndexSet.push_back(f0);
					faceIndexSet.push_back(f1);
					faceIndexSet.push_back(f2);
					f1 = f2;	// ���̎O�p�`�̂��߂Ƀf�[�^���ړ�
				}
				continue;
			}
			// ���_���W+�e�N�X�`�����W
			if (sscanf(p, " f %u/%u %u/%u%n", &f0.v, &f0.vt, &f1.v, &f1.vt, &readByte) == 4) {
				f0.vn = f1.vn = 0; // �@���Ȃ�
				p += readByte; // �ǂݎ��ʒu�X�V
				for (;;) {
					if (sscanf(p, " %u/%u%n", &f2.v, &f2.vt, &readByte) != 2) {
						break;
					}
					f2.vn = 0; // �@���Ȃ�
					p += readByte;
					faceIndexSet.push_back(f0);
					faceIndexSet.push_back(f1);
					faceIndexSet.push_back(f2);
					f1 = f2;	// ���̎O�p�`�̂��߂Ƀf�[�^���ړ�
				}
				continue;
			}

			// MTL�t�@�C���̓ǂݍ��݂����݂�
			char mtlFilename[1000];
			if (sscanf(line.data(), " mtllib %999s", mtlFilename) == 1) {
				const auto tmp = LoadMTL(foldername, mtlFilename);
				materials.insert(materials.end(), tmp.begin(), tmp.end());
				continue;
			}

			// �g�p���̃}�e���A�����̓ǂݎ������݂�
			char mtlName[1000];
			if (sscanf(line.data(), " usemtl %999s", mtlName) == 1) {
				usemtls.push_back({ mtlName, faceIndexSet.size() });
				continue;
			}
		}
		// �����ɔԕ���ǉ�
		usemtls.push_back({ std::string(), faceIndexSet.size() });

		// OBJ�t�@�C���̂��\����OpenGL�̒��_�C���f�b�N�X�z��̑Ή��\
		std::unordered_map<uint64_t, uint16_t> indexMap;
		indexMap.reserve(10000);

		// �ǂݍ��񂾃f�[�^���AOpenGL�Ŏg����f�[�^�ɕϊ�
		MeshData meshData;
		std::vector<Vertex>& vertices = meshData.vertices;
		vertices.reserve(faceIndexSet.size());
		std::vector<uint16_t>& indices = meshData.indices;
		indices.reserve(faceIndexSet.size());
		for (int i = 0; i < faceIndexSet.size(); ++i) {
			const IndexSet& e = faceIndexSet[i];

			// f�\���̒l��64�r�b�g�́u�L�[�v�ɕϊ�]
			const uint64_t key = static_cast<uint64_t>(e.v) +
				(static_cast<uint64_t>(e.vt) << 20) + (static_cast<uint64_t>(e.vn) << 40);

			// �Ή��\�ɂ���̂Ŋ����̒��_�C���f�b�N�X���g��
			const auto itr = indexMap.find(key);
			if (itr != indexMap.end()) {
				// �Ή��\�ɂ���̂Ŋ����̒��_�C���f�b�N�X���g��
				indices.push_back(itr->second);
			}
			else {
				// �Ή��\�ɂȂ��̂ŐV�������_�f�[�^���쐬���A���_�z��ɒǉ�
				Vertex v;
				v.position = positions[e.v - 1];
				v.texcoord = texcoords[e.vt - 1];
				// �@�����ݒ肳��Ă��Ȃ��ꍇ��0��ݒ�(��Ōv�Z)
				if (e.vn == 0)
				{
					v.normal = Vector3::zero;
				}
				else
				{
					v.normal = normals[e.vn - 1];
				}
				vertices.push_back(v);

				// �V�������_�f�[�^�̃C���f�b�N�X���A���_�f�[�^�z���ǉ�
				const uint16_t index = static_cast<uint16_t>(vertices.size() - 1);
				indices.push_back(index);

				// �L�[�ƒ��_�C���f�b�N�X�̃y�A��Ή��\�ɒǉ�
				indexMap.emplace(key, index);
			}
		}

		// �ݒ肳��Ă��Ȃ��@����₤
		FillMissingNormals(vertices.data(), vertices.size(), indices.data(), indices.size());


		// �f�[�^�̈ʒu���X�V
		const void* indexOffset = 0;
		const GLint baseVertex = 0;

		// �}�e���A���ɑΉ������`��p�����[�^���쐬
		// ���f�[�^�Ɣԕ��ȊO�̃}�e���A��������ꍇ�A���f�[�^���΂�
		size_t i = 0;
		if (usemtls.size() > 2) {
			i = 1;	// ���f�[�^�Ɣԕ��ȊO�̃}�e���A��������ꍇ�A���f�[�^���΂�
		}
		for (; i < usemtls.size() - 1; ++i) {
			const UseMaterial& cur = usemtls[i];	// �g�p���̃}�e���A��
			const UseMaterial& next = usemtls[i + 1]; // ���̃}�e���A��
			if (next.startOffset == cur.startOffset) {
				continue;	// �C���f�b�N�X�f�[�^���Ȃ��ꍇ�͔�΂�
			}

			// �`��p�����[�^���쐬
			DrawParams params;
			params.mode = GL_TRIANGLES;
			params.count = static_cast<GLsizei>(next.startOffset - cur.startOffset);
			params.indices = indexOffset;
			params.baseVertex = baseVertex;
			params.materialNo = 0;	// �f�t�H���g�l��ݒ�
			for (int i = 0; i < materials.size(); ++i) {
				if (materials[i]->ToString() == cur.name) {
					params.materialNo = i;	// ���O�ƈ�v����}�e���A����ݒ�
					break;
				}
			}
			meshData.drawParamsList.push_back(params);

			// �C���f�b�N�X�I�t�Z�b�g��ύX
			indexOffset = reinterpret_cast<void*>(reinterpret_cast<size_t>(indexOffset) + sizeof(uint16_t) * params.count);
		}

		// �}�e���A���z�񂪋�̏ꍇ�A�f�t�H���g�}�e���A����ǉ�
		if (materials.empty()) {
			meshData.materials.push_back(std::make_shared<Material>());
		}
		else {
			meshData.materials.assign(materials.begin(), materials.end());
		}
		return meshData;
	}

	/**
	* �`��p�����[�^�͔z���`�悷��
	*
	* @param drawParamList	�`��p�����[�^�z��
	* @param materials		�}�e���A���z��
	*/
	void Draw(GLuint program, const std::vector<DrawParams>& drawParamsList, const MaterialList& materials)
	{
		// �V�F�[�_�v���O������ݒ�
		glUseProgram(program);
		for (const auto& e : drawParamsList)
		{
			// �}�e���A����ݒ�
			if (e.materialNo >= 0 && e.materialNo < materials.size())
			{
				// �}�e���A�����擾
				const Material& material = *materials[e.materialNo];

				// �F��ݒ�
				if (glGetUniformLocation(program, "color") >= 0)
				{
					const Color color = material.color;
					glProgramUniform4fv(program, 100, 1, &color.r);
				}
				// �����F��ݒ�
				if (glGetUniformLocation(program, "emissionColor") >= 0)
				{
					const Color emissionColor = material.emissionColor;
					glProgramUniform4fv(program, 101, 1, &emissionColor.r);
				}
				// ���C���e�N�X�`����ݒ�
				if (material.mainTexture)
				{
					const GLuint tex = *material.mainTexture;
					glBindTextures(0, 1, &tex);
				}
				// �����e�N�X�`����ݒ�
				if (material.emissionTexture)
				{
					const GLuint tex = *material.emissionTexture;
					glBindTextures(1, 1, &tex);
				}
				else
				{
					// �e�N�X�`��1�𖢐ݒ�
					glBindTextures(1, 1, nullptr);
				}
				// �����x�J�b�g
				if (glGetUniformLocation(program, "alphaCutoff") >= 0)
				{
					glProgramUniform1f(program, locAlphaCutoff, material.alphatCutOff);
				}
			}
			// �`��
			glDrawElementsBaseVertex(e.mode, e.count, GL_UNSIGNED_SHORT, e.indices, e.baseVertex);
		}
		// �V�F�[�_�v���O����������
		glUseProgram(0);
	}

	/**
	* �X�^�e�B�b�N���b�V����`�悷��
	*
	* @param mesh		�X�^�e�B�b�N���b�V��
	* @param materials	�}�e���A���z��
	*/
	void Draw(GLuint program, const StaticMesh& mesh, const MaterialList& materials)
	{
		Draw(program, mesh.drawParamsList, materials);
	}


	/**
	* �����Ă���@����₤
	*
	* @param vertices		���_�z��
	* @param vertexCount	���_�z��̗v�f��
	* @param indices		�C���f�b�N�X�z��
	* @param indexCount		�C���f�b�N�X�z��̗v�f��
	*/
	void FillMissingNormals(Vertex* vertices, size_t vertexCount, const uint16_t* indices, size_t indexCount)
	{
		// �@�����ݒ肳��Ă��Ȃ����_��������
		std::vector<bool> missingNormals(vertexCount, false);
		for (int i = 0; i < vertexCount; ++i)
		{
			// �@���̒�����0�̏ꍇ���u�ݒ肳��Ă��Ȃ��v�Ƃ݂Ȃ�
			const Vector3& n = vertices[i].normal;
			if (n.x == 0 && n.y == 0 && n.z == 0) 
			{
				missingNormals[i] = true;
			}
		}

		// �@�����v�Z
		for (int i = 0; i < indexCount; i += 3)
		{
			//�@�ʂ��\������2��a,b,�����߂�
			const int i0 = indices[i + 0];
			const int i1 = indices[i + 1];
			const int i2 = indices[i + 2];
			const Vector3& v0 = vertices[i0].position;
			const Vector3& v1 = vertices[i1].position;
			const Vector3& v2 = vertices[i2].position;
			const Vector3 a = v1 - v0;
			const Vector3 b = v2 - v0;

			// �@���𐳋K�����ĒP�ʃx�N�g���ɂ���
			const Vector3 c = Vector3::Cross(a, b);

			// �@���𐳋K�����ĒP�ʃx�N�g���ɂ���
			const Vector3 normal = c.Normalized();

			// �@�����ݒ肳��Ă��Ȃ����_�ɂ����@�������Z
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
		// �@���𐳋K��
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