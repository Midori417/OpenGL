/**
* @file GltfMesh.cpp
*/
#include "GltfMesh.h"
#include "Texture.h"
#include "BufferObject.h"
#include "MapBufferObjecth.h"
#include "VertexArrayObject.h"

#include "Debug.h"
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "Package/Nlohmann.h"
#include <fstream>
#include <filesystem>
#include <algorithm>

using json = nlohmann::json;
using namespace FGEngine::Rendering::Rall;

namespace FGEngine::Rendering
{
	/**
	* �o�C�i���f�[�^
	*/
	struct BinaryData
	{
		GLsizeiptr offset;		// GPU��������̃f�[�^�J�n�I�t�Z�b�g
		std::vector<char> bin;	// CPU�������ɓǂݍ��񂾃f�[�^
	};
	using BinaryList = std::vector<BinaryData>;

	/**
	* �t�@�C����ǂݍ���
	*
	* @param filename �ǂݍ��ރt�@�C����
	*
	* @return �ǂݍ��񂾃f�[�^�z��
	*/
	std::vector<char> ReadFile(const char* filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file)
		{
			LOG_WARNINGS("%s���J���܂���", filename);
			return {};
		}
		std::vector<char> buf(std::filesystem::file_size(filename));
		file.read(buf.data(), buf.size());
		return buf;
	}

	/**
	* ���_�A�g���r���[�g�ԍ�
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
	* �K�v�Ȓ��_�f�[�^�v�f���v���~�e�B�u�ɑ��݂��Ȃ��ꍇ�Ɏg���f�[�^
	*/
	struct SkeletalVertex
	{
		Vector3 position = Vector3::zero;
		Vector2 texcoord0 = Vector2::zero;
		Vector3 normal = Vector3(0, 0, -1);
		Vector4 tangent = Vector4(1, 0, 0, 1);
		Vector4 joints0 = Vector4::zero;
		Vector4 weights0 = Vector4::zero;
	};

	/**
	* ���������擾����
	*
	* @param accessor �p�����[�^�����A�N�Z�T
	*
	* @return �����̐�
	*/
	int GetComponentCount(const json& accessor)
	{
		// �^���Ɛ������̑Ή��\
		// VEC �x�N�g�� MAT �}�g���N�X
		static const struct {
			const char* type;	// �^�̖��O
			int componentCount;	// ������
		} componentCountList[] = {
			{ "SCALAR", 1 },
			{ "VEC2", 2 }, { "VEC3", 3 }, { "VEC4", 4 },
			{ "MAT2", 4 }, { "MAT3", 9 }, { "MAT4", 16 },
		};

		// �Ή��\���琬�������擾
		const std::string& type = accessor["type"].get<std::string>();
		for (const auto& e : componentCountList)
		{
			if (type == e.type)
			{
				return e.componentCount;
			}
		}
		LOG_WARNINGS("�s���Ȍ^'%s'���w�肳��Ă��܂�", type.c_str());
		return 1;	// glTF�̎d�l�ʂ�Ȃ�A�����ɗ��邱�Ƃ͂Ȃ��͂�
	}

	/**
	* �X�g���C�h(���̗v�f�܂ł̋���)���擾����
	*
	* @parma accessor	�A�N�Z�T
	* @param bufferView	�o�b�t�@�r���[
	*
	* @return �X�g���C�h
	*/
	GLsizei GetByteStride(const json& accessor, const json& bufferView)
	{
		// byteStride����`����Ă�����A���̒l��Ԃ�
		const auto byteStride = bufferView.find("byteStride");
		if (byteStride != bufferView.end())
		{
			return byteStride->get<int>();
		}

		// bytteStride������`�̏ꍇ�A�v�f1�����̃T�C�Y���X�g���C�h�Ƃ���
		// �Q�l; glTF-2.0�d�l 3.6.2.4. Data Alignment

		int componentSize = 1;	// �����^�̃T�C�Y
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
			LOG_WARNINGS("glTF�̎d�l�ɂȂ��^%d���g���Ă��܂�", componentType);
			break;
		}

		// �X�g���C�h = �����^�̃T�C�Y * ������
		const int componentCount = GetComponentCount(accessor);
		return componentSize * componentCount;
	}

	/**
	* �f�[�^�̊J�n�ʒu���擾����
	*
	* @param accessor	�A�N�Z�T
	* @param bufferView �o�b�t�@�r���[
	* @param binaryList �o�C�i���f�[�^�z��
	*
	* @reutrn �f�[�^�̊J�n�ʒu
	*/
	GLsizeiptr GetBinaryDataOffset(const json& accessor, const json& bufferView, const BinaryList& binaryList)
	{
		const int bufferId = bufferView["buffer"].get<int>();
		const int byteOffset = accessor.value("byteOffset", 0);
		const int baseByteOffset = bufferView.value("byteOffset", 0);
		return binaryList[bufferId].offset + baseByteOffset + byteOffset;
	}

	/**
	* CPU���̃f�[�^�̃A�h���X���擾����
	*
	* @param accessor		�A�N�Z�T
	* @param bufferViews	�o�b�t�@�r���[�z��
	* @param binaryList		�o�C�i���f�[�^�z��
	*
	* @return �f�[�^�̃A�h���X
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
	* ���_�A�g���r���[�g��ݒ肷��
	*
	* @retval true	���_�A�g���r���[�g��ݒ肵��
	* @retval false	���_�A�g���r���[�g�̃p�����[�^���Ȃ�����
	*/
	bool SetVertexAttribute(const GLuint index, const char* key, const json& attributes, const json& accessors, const json& bufferViews, const BinaryList& binaryList)
	{
		glEnableVertexAttribArray(index);	// ���_�A�g���r���[�g��L����
		const auto attribute = attributes.find(key);
		if (attribute != attributes.end())
		{
			// �A�N�Z�T�ƃo�b�t�@�r���[���擾
			const json& accessor = accessors[attribute->get<int>()];
			const int bufferViewId = accessor["bufferView"].get<int>();
			const json& bufferView = bufferViews[bufferViewId];

			// ���_�A�g���r���[�g�̃p�����[�^���擾
			const GLint componentCount = GetComponentCount(accessor);
			const GLenum componentType = accessor["componentType"].get<int>();
			const GLboolean normalized = accessor.value("normalized", false);
			const GLsizei byteStride = GetByteStride(accessor, bufferView);
			const GLsizeiptr offset = GetBinaryDataOffset(accessor, bufferView, binaryList);

			// VAO�ɒ��_�A�g���r���[�g��ݒ�
			glVertexAttribPointer(index, componentCount, componentType,
				normalized, byteStride, reinterpret_cast<void*>(offset));

			return true;
		}
		return false;
	}

	/**
	* VAO�Ƀf�t�H���g�̒��_�A�g���r���[�g��ݒ肷��
	*
	* @param index	�ݒ��̒��_�A�g���r���[�g�ԍ�
	* @param size	�f�[�^�̗v�f��
	* @param offst	�f�[�^�̈ʒu
	* @param vbo	���_�f�[�^��ێ�����VBO
	*/
	void SetDefaultAttribute(GLuint index, GLint size, GLuint offset, GLuint vbo)
	{
		glVertexAttribFormat(index, size, GL_FLOAT, GL_FALSE, offset);
		glVertexAttribBinding(index, index);
		glBindVertexBuffer(index, vbo, 0, 0);
	}

	/**
	* �e�N�X�`����ǂݍ���
	*
	* @param objectName  �e�N�X�`�����̃L�[������
	* @param gltf        glTF�t�@�C����JSON�I�u�W�F�N�g
	* @param parent      �e�N�X�`����������JSON�I�u�W�F�N�g
	* @param foldername  glTF�t�@�C��������t�H���_��
	* @param texDefault  �e�N�X�`�����쐬�ł��Ȃ��ꍇ�ɕԂ��e�N�X�`��
	*
	* @return �ǂݍ��񂾃e�N�X�`���A�܂���texDefault
	*/
	TexturePtr LoadTexture(const char* objectName, const json& gltf, const json& parent,
		const std::string& foldername, const TexturePtr& texDefault)
	{
		// �e�N�X�`�������擾
		const auto textureInfo = parent.find(objectName);
		if (textureInfo == parent.end())
		{
			return texDefault;
		}

		// �e�N�X�`���ԍ����擾
		const auto textures = gltf.find("textures");
		const int textureNo = textureInfo->at("index").get<int>();
		if (textures == gltf.end() || textureNo >= textures->size()) {
			return texDefault;
		}

		// �C���[�W�\�[�X�ԍ����擾
		const json& texture = textures->at(textureNo);
		const auto source = texture.find("source");
		if (source == texture.end())
		{
			return texDefault;
		}

		// �C���[�W�ԍ����擾
		const auto images = gltf.find("images");
		const int imageNo = source->get<int>();
		if (images == gltf.end() || imageNo >= images->size())
		{
			return texDefault;
		}

		// �t�@�C�������擾
		const json& image = images->at(imageNo);
		const auto imageUri = image.find("uri");
		if (imageUri == image.end())
		{
			return texDefault;
		}

		// �t�H���_����ǉ����A�g���q��tga�ɕύX
		std::filesystem::path uri = imageUri->get<std::string>();
		std::filesystem::path filename = foldername;
		filename /= uri.parent_path();
		filename /= uri.stem();
		filename += ".tga";


		// �e�N�X�`����ǂݍ���
		return Texture::Create(filename.string(), Texture::Usage::forGltf);
	}

	/**
	* JSON�̔z��f�[�^��Vector3�ɕϊ�����
	*
	* @param json �ϊ����ƂȂ�z��f�[�^
	*
	* @return json��ϊ����Ăł���Vector3�̒l
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
	* JSON�̔z��f�[�^���N�H�[�^�j�I���ɕϊ�����
	*
	* @param json �ϊ����ƂȂ�z��f�[�^
	*
	* @return json��ϊ����Ăł����N�H�[�^�j�I���̒l
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
	* JSON�̔z��f�[�^��Matrix4x4�ɕϊ�����
	*
	* @param json �ϊ����ƂȂ�z��f�[�^
	*
	* @return json��ϊ����Ăł���Matrix4x4�̒l
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
				m[y][x] = json[y * 4 + x].get<float>();
			}
		}
		return m;
	}

	/**
	* �m�[�h�̃��[�J�����W�ϊ��s����v�Z����
	*
	* @param node glTF�m�[�h
	*
	* @return node�̃��[�J�����W�ϊ��s��
	*/
	Matrix4x4 GetLocalMatrix(const json& node)
	{
		// �s��f�[�^������ꍇ�A�s��f�[�^��ǂݎ���ĕԂ�
		const auto matrix = node.find("matrix");
		if (matrix != node.end())
		{
			return GetMatrix4x4(*matrix);
		}

		// �s��f�[�^�Ȃ��ꍇ
		// �X�P�[������]�����s�ړ��̏��œK�p�����s���Ԃ�
		Matrix4x4 result(1);
		const auto t = node.find("translation");
		if (t != node.end())
		{
			result[3] = Vector4(GetVector3(*t), 1);
		}
		const auto r = node.find("rotation");
		if (r != node.end())
		{
			result *= Quaternion::Matrix4x4Cast(GetQuaternion(*r));
		}
		const auto s = node.find("scale");
		if (s != node.end())
		{
			result *= Matrix4x4::Scale(GetVector3(*s));
		}
		return result;
	}

	/**
	* ���b�V�������m�[�h�����X�g�A�b�v����
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
	* �A�j���[�V�����`���l�����쐬����
	*
	* @param pTimes			�����̔z��̃A�h���X
	* @param pValues		�l�̔z��̃A�h���X
	* @param inputCount		�z��̗v�f��
	* @param targetNodeId	�l�̓K�p�ΏۂƂȂ�m�[�hID
	* @param interp			��ԕ��@
	*
	* @return �쐬�����A�j���[�V�����`���l��
	*/
	template<typename T>
	GltfChannel<T> MakeAnimationChannel(const GLfloat* pTimes, const void* pValues, size_t inputCount, int targetNodeId, GltfInterpolation interp)
	{
		// �����ƒl�̔z�񂩂�L�[�t���[���z����쐬
		const T* pData = static_cast<const T*>(pValues);
		GltfChannel<T> channel;
		channel.keyframes.resize(inputCount);
		for (int i = 0; i < inputCount; ++i)
		{
			channel.keyframes[i] = { pTimes[i], pData[i] };
		}

		// �K�p�Ώۃm�[�hID�ƕ�ԕ��@��ݒ�
		channel.targetNodeId = targetNodeId;
		channel.interpolation = interp;

		return channel;	// �쐬�����`���l����Ԃ�
	}

	/**
	* �`���l����̎w�肵�������̒l�����߂�
	*
	* @param channel	�Ώۂ̃`���l��
	* @param time		�l�����߂鎞��
	*
	* @return �����ɑΉ�����l
	*/
	template<typename T>
	T Interpolate(const GltfChannel<T>& channel, float time)
	{
		// time�ȏ�̎��������A�ŏ��̃L�[�t���[��������
		const auto curOrOver = std::lower_bound(
			channel.keyframes.begin(), channel.keyframes.end(), time,
			[](const GltfKeyframe<T>& keyframe, float time)
			{
				return keyframe.time < time;
			});

		// time���擪�L�[�t���[���̎����Ɠ������ꍇ�A�擪�L�[�t���[���̒l��Ԃ�
		if (curOrOver == channel.keyframes.begin())
		{
			return channel.keyframes.front().value;
		}

		// time�������L�[�t���[���̎������傫���ꍇ�A�����L�[�t���[���̒l��Ԃ�
		if (curOrOver == channel.keyframes.end())
		{
			return channel.keyframes.front().value;
		}

		// time�������L�[�t���[���̎������傫���ꍇ�A�����L�[�t���[���̒l��Ԃ�
		if (curOrOver == channel.keyframes.end())
		{
			return channel.keyframes.back().value;
		}

		// time���擪�Ɩ����̊Ԃ������ꍇ
		// �L�[�t���[���Ԃ̎��Ԃ�����time�̔䗦���v�Z���A�䗦�ɂ���ĕ�Ԃ����l��Ԃ�
		const auto prev = curOrOver - 1;	// �ЂƂO��(time�����̎�����҂�)�L�[�t���[��
		const float frameTime = curOrOver->time - prev->time;
		const float t = Mathf::Clamp01((time - prev->time) / frameTime);

		// ����:���͏��(����)���`�ۊǂ��Ă��邪�A�{���͕�ԕ��@�ɂ���ď����𕪂���ׂ�
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
	* �A�j���[�V�����v�Z�p�̒��ԃf�[�^�^
	*/
	struct NodeMatrix
	{
		Matrix4x4 m = Matrix4x4(1);	// �p���s��
		bool isCalculated = false;	// �v�Z�ς݃t���O
	};
	using NodeMatrices = std::vector<NodeMatrix>;

	/**
	* �m�[�g�̃O���[�o���p���s����v�Z����
	*/
	const Matrix4x4& CalcGlobalNodeMatrix(const std::vector<GltfNode>& nodes, const GltfNode& node, NodeMatrices& matrices)
	{
		const intptr_t currentNodeId = &node - &nodes[0];
		NodeMatrix& nodeMatrix = matrices[currentNodeId];

		// �u�v�Z�ς݁v�̏ꍇ�͎����̎p���s���Ԃ�
		if (nodeMatrix.isCalculated)
		{
			return nodeMatrix.m;
		}

		// �u�v�Z�ς݂łȂ��v�ꍇ�A�e�̎p���s�����������
		if (node.parent)
		{
			// �e�̍s����擾(�ċN�Ăяo��)
			const Matrix4x4& matParent = CalcGlobalNodeMatrix(nodes, *node.parent, matrices);

			// �e�̎p���s�������
			nodeMatrix.m = matParent * nodeMatrix.m;
		}

		// �u�v�Z�ς݁v�ɂ���
		nodeMatrix.isCalculated = true;

		// �����̎p���s���Ԃ�
		return nodeMatrix.m;
	}

	/**
	* �A�j���[�V�������v���p���s����v�Z����
	*
	* @param file			meshNode�����L����t�@�C���I�u�W�F�N�g
	* @param meshNode		���b�V�������m�[�h
	* @param animation		�v�Z�̌��ƂȂ�A�j���[�V����
	* @param time			�A�j���[�V�����̍Đ��ʒu
	*
	* @return �A�j���[�V������K�p�����p���s��̔z��
	*/
	GltfAnimationMatrices CalcAnimationMatrices(const GltfFilePtr& file, const GltfNode* meshNode, const GltfAnimation* animation, float time)
	{
		GltfAnimationMatrices matBones;
		if (!file || !meshNode)
		{
			return matBones;
		}

		// �A�j���[�V�������ݒ肳��ĂȂ��ꍇ
		if (!animation)
		{
			// �m�[�h�̃O���[�o�����W�ϊ��s����g��
			size_t size = 1;
			if (meshNode->skin >= 0)
			{
				size = file->skins[meshNode->skin].joints.size();
			}
			matBones.resize(size, meshNode->matGlobal);

			return matBones;
		}

		// �A�j���[�V�������ݒ肳��Ă���ꍇ

		NodeMatrices matrices;
		const auto& nodes = file->nodes;
		matrices.resize(nodes.size());

		// �A�j���[�V�������Ȃ��m�[dp�̃��[�J���p���s�����ݒ�
		for (const auto e : animation->staticNodes)
		{
			matrices[e].m = nodes[e].matLocal;
		}

		// �A�j���[�V��������m�[�h�̃��[�J���p���s����v�Z
		// (�g��k������]�����s�ړ��̏��œK�p)
		for (const auto& e : animation->translations)
		{
			const Vector3 translation = Interpolate(e, time);
			matrices[e.targetNodeId].m = Matrix4x4::Translate(translation);
		}
		for (const auto& e : animation->rotations)
		{
			const Quaternion rotation = Interpolate(e, time);
			matrices[e.targetNodeId].m *= Quaternion::Matrix4x4Cast(rotation);
		}
		for (const auto& e : animation->scales)
		{
			const Vector3 scale = Interpolate(e, time);
			matrices[e.targetNodeId].m *= Matrix4x4::Scale(scale);
		}

		// �A�j���[�V������K�p�����O���[�o���p���s����v�Z
		if (meshNode->skin >= 0)
		{
			for (const auto& joint : file->skins[meshNode->skin].joints)
			{
				CalcGlobalNodeMatrix(nodes, nodes[joint.nodeId], matrices);
			}
		}
		else
		{
			// �W���C���g���Ȃ��̂Ń��b�V���m�[�h�����v�Z
			CalcGlobalNodeMatrix(nodes, *meshNode, matrices);
		}

		// �t�o�C���h�|�[�Y�s�������
		if (meshNode->skin >= 0)
		{
			// glTF��joints�L�[�ɂ̓m�[�h�ԍ����i�[����Ă���
			// �������A���_�f�[�^��JOINTS_n�����ɂ́ujoints�z��̃C���f�b�N�X�v���i�[����Ă���
			// ���ۂɎp���s����g���̂͒��_�f�[�^�Ȃ̂ŁA�p���s���joints�z��̏��ԂŊi�[����
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
			// �W���C���g���Ȃ��̂ŋt�o�C���h�|�[�Y�s������݂��Ȃ�
			const size_t nodeId = meshNode - &nodes[0];
			matBones.resize(1, matrices[nodeId].m);
		}

		return matBones;

	}

	/**
	* �R���X�g���N�^
	*
	* @param bufferCapcity	�t�@�C���i�[�p�o�b�t�@�̍ő�o�C�g��
	* @param maxMatrixCount	�A�j���[�V�����pSSBO�Ɋi�[�ł���ő�s��
	*/
	GltfFileBuffer::GltfFileBuffer(size_t bufferCapacity, size_t maxMatrixCount)
	{
		// GPU���������m�ۂ��A�������ݐ�p�Ƃ��ă}�b�v����
		buffer = BufferObject::Create(bufferCapacity, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		pBuffer = static_cast<uint8_t*>(glMapNamedBuffer(*buffer, GL_WRITE_ONLY));

		// �o�b�t�@�̐擪�Ƀ_�~�[�f�[�^��ݒ�
		const SkeletalVertex defaultData;
		memcpy(pBuffer, &defaultData, sizeof(defaultData));
		curBufferSize = sizeof(defaultData);

		// �A�j���[�V�����̎p���s��p�o�b�t�@���쐬
		animationBuffer = Rall::MappedBufferObject::Create(maxMatrixCount * sizeof(Matrix4x4),
			GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
		tmpAnimationBuffer.reserve(maxMatrixCount);

		// �f�t�H���g�}�e���A�����쐬
		defaultMaterial = std::make_shared<Material>();
		defaultMaterial->SetName("defaultMaterial");
		defaultMaterial->mainTexture = Texture::Create("defaultTexture", 4, 4);
		static const uint32_t img[4 * 4] = { // �e�N�X�`���f�[�^
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
			0xffff'ffff, 0xffff'ffff, 0xffff'ffff, 0xffff'ffff,
		};
		glTextureSubImage2D(*defaultMaterial->mainTexture, 0, 0, 0,
			+4, 4, GL_BGRA, GL_UNSIGNED_BYTE, img);
	}

	/**
	* �A�j���[�V�������b�V���̕`��p�f�[�^�����ׂč폜
	*
	* �t���[���̍ŏ��ɌĂяo������
	*/
	void GltfFileBuffer::ClearAnimationBuffer()
	{
		tmpAnimationBuffer.clear();
	}

	/**
	* �A�j���[�V�������b�V���̕`��p�f�[�^��ǉ�
	*
	* @param matBones SSBO�ɒǉ�����p���s��̔z��
	*
	* @return matBones�悤�Ɋ��蓖�Ă�ꂽSSBO�͈̔�
	*/
	GltfFileBuffer::Range GltfFileBuffer::AddAnimationMatrices(const GltfAnimationMatrices& matBones)
	{
		const GLintptr offset = static_cast<GLintptr>(tmpAnimationBuffer.size() * sizeof(Matrix4x4));
		tmpAnimationBuffer.insert(tmpAnimationBuffer.end(), matBones.begin(), matBones.end());

		// SSBO�̃I�t�Z�b�g�A���C�����g�����𖞂������߂�256�o�C�g���E(Matrix4x4��4��)�ɔz�u����
		// 256��OpenGL�d�l�ŋ������ő�l
		tmpAnimationBuffer.resize(((tmpAnimationBuffer.size() + 3) / 4) * 4);
		return { offset, matBones.size() * sizeof(Matrix4x4) };
	}

	/**
	*�A�j���[�V�������b�V���̕`��p�f�[�^��GPU�������ɃR�s�[
	*/
	void GltfFileBuffer::UploadAnimationBuffer()
	{
		if (tmpAnimationBuffer.empty())
		{
			return;	// �]������f�[�^���Ȃ��ꍇ�͉������Ȃ�
		}
		animationBuffer->WaitSync();
		uint8_t* p = animationBuffer->GetMappedAddress();
		memcpy(p, tmpAnimationBuffer.data(), tmpAnimationBuffer.size() * sizeof(Matrix4x4));
		animationBuffer->SwapBuffers();
	}

	/**
	* �A�j���[�V�������b�V���̕`��Ɏg��SSBO�̈�Ɋ��蓖�Ă�
	*
	* @param bindingPoint	�o�C���f�B���O�|�C���g
	* @param range			�o�C���h����͈�
	*/
	void GltfFileBuffer::BindAnimationBuffer(GLuint bindingPoint, const Range& range)
	{
		if (range.size > 0)
		{
			animationBuffer->Bind(bindingPoint, range.offset, range.size);
		}
	}

	/**
	* �A�j���[�V�������b�V���̕`��Ɏg��SSBO���@�̊��蓖�Ă���������
	*/
	void GltfFileBuffer::UnbindAnimationBuffer(GLuint bindingPoint)
	{
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, bindingPoint, 0, 0, 0);
	}

	/**
	* glTF�t�@�C������GltfFile�I�u�W�F�N�g���쐬����
	*
	* @parma filename glTF�t�@�C����
	*
	* @retaval nullptr�ȊO	filename����쐬�����t�@�C���I�u�W�F�N�g
	* @retaval nullptr		�ǂݍ��ݎ��s
	*/
	GltfFilePtr GltfFileBuffer::Load(const char* filename)
	{
		// �ȑO�ɓǂݍ��񂾃t�@�C���Ȃ�A�쐬�ς݂̃t�@�C����Ԃ�
		auto itr = files.find(filename);
		if (itr != files.end())
		{
			return itr->second;
		}

		// glTF�t�@�C����ǂݍ���
		std::vector<char> buf = ReadFile(filename);
		if (buf.empty())
		{
			return nullptr;
		}
		buf.push_back('\0'); // �e�L�X�g�I�[��ǉ�

		// �t�H���_�������o��
		const std::string foldername =
			std::filesystem::path(filename).parent_path().string() + '/';

		// JSON�����
		auto p = Parse(buf.data(), foldername.c_str());
		if (!p)
		{
			LOG_ERROR("'%s'�̓ǂݍ��݂Ɏ��s���܂���", filename);
			return p;
		}

		// �쐬�����t�@�C����A�z�z��ɒǉ�
		p->name = filename;
		files.emplace(filename, p);

		// �ǂݍ��񂾃t�@�C�����ƃ��b�V�������f�o�b�O���Ƃ��ďo��
		LOG("%s��ǂݍ��݂܂���", filename);
		for (size_t i = 0; i < p->meshes.size(); ++i)
		{
			LOG(R"(  meshes[%d]="%s")", i, p->meshes[i].name.c_str());
		}

		for (size_t i = 0; i < p->animations.size(); ++i)
		{
			const std::string& name = p->animations[i]->name;
			if (name.size() <= 0)
			{
				LOG(" animations[%d]=<NO NAME>", i);
			}
			else
			{
				LOG(R"( animations[%d]="%s")", i, name.c_str());
			}
		}
		return p;
	}

	/**
	* JSON�e�L�X�g����GltfFile�I�u�W�F�N�g���쐬����
	*
	* @param text		glTF��JOSN�e�L�X�g
	* @param foldernaem ���\�[�X�ǂݍ��ݗp�̃t�H���_
	*
	* @retval nullptr�ȊO	filename����쐬�����t�@�C���I�u�W�F�N�g
	* @rtaval nullptr		�ǂݍ��ݎ��s
	*/
	GltfFilePtr GltfFileBuffer::Parse(const char* text, const char* foldername)
	{
		// JSON���
		json gltf = json::parse(text, nullptr, false);
		if (gltf.is_discarded())
		{
			LOG_ERROR("JSON�̉�͂Ɏ��s���܂���");
			return nullptr;
		}
		// �o�C�i���t�@�C����ǂݍ���
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
			// �t�@�C����ǂݍ���
			const std::string binPath = foldername + uri->get<std::string>();
			binaryList[i].bin = ReadFile(binPath.c_str());
			if (binaryList[i].bin.empty())
			{
				curBufferSize = prevBufferSize;	// �ǂݍ��񂾃f�[�^���Ȃ������Ƃɂ���
				return nullptr;	// �o�C�i���t�@�C���̓ǂݍ��݂Ɏ��s
			}

			// �o�C�i���f�[�^��GPU�������ɃR�s�[
			memcpy(pBuffer + curBufferSize, binaryList[i].bin.data(), binaryList[i].bin.size());

			// �I�t�Z�b�g���X�V
			binaryList[i].offset = curBufferSize;
			curBufferSize += binaryList[i].bin.size();
		}

		// �t�@�C���I�u�W�F�N�g�쐬
		GltfFilePtr file = std::make_shared<GltfFile>();

		// ���[�g�m�[�h�̎p���s����擾
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
						file->matRoot[i / 4][i % 4] = matrix->at(i).get<float>();
					}
				}
			}
		}

		// ���b�V�����쐬
		const json& accessors = gltf["accessors"];
		const json& bufferViews = gltf["bufferViews"];
		const json& meshes = gltf["meshes"];
		file->meshes.reserve(meshes.size());
		for (const json& jsonMesh : meshes)
		{
			// ���b�V�������擾
			GltfMesh mesh;
			mesh.name = jsonMesh.value("name", "<default>");

			// �v���~�e�B�u���쐬
			const json& primitives = jsonMesh["primitives"];
			mesh.primitives.reserve(primitives.size());
			for (const json& jsonPrim : primitives)
			{
				// VAO���쐬
				GltfPrimitive prim;
				prim.vao = std::make_shared<VertexArrayObject>();

				// VAO��OpenGL�R���e�L�X�g�Ɋ��蓖�Ă�
				glBindVertexArray(*prim.vao);

				// VBO��IBO���AOpenGL�R���e�L�X�g��VAO�̗����Ɋ��蓖�Ă�
				glBindBuffer(GL_ARRAY_BUFFER, *buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);

				// �v���~�e�B�u�̃p�����[�^���擾
				{
					// �v���~�e�B�u�̎��
					prim.mode = jsonPrim.value("mode", GL_TRIANGLES);

					// �C���f�b�N�X���ƌ^
					const int accessorId = jsonPrim["indices"].get<int>();
					const json& accessor = accessors[accessorId];
					prim.count = accessor["count"].get<int>();
					prim.type = accessor["componentType"].get<int>();

					// �C���f�b�N�X�f�[�^�̊J�n�ʒu
					const int bufferViewId = accessor["bufferView"].get<int>();
					const json& bufferView = bufferViews[bufferViewId];
					prim.indeices = reinterpret_cast<const GLvoid*>(
						GetBinaryDataOffset(accessor, bufferView, binaryList));
				}

				// ���_�A�g���r���[�g���擾
				const json& attributes = jsonPrim["attributes"];

				// ���_�A�g���r���[�g(���_���W)���擾
				const bool hasPosition = SetVertexAttribute(AttribIndex::position, "POSITION", attributes,
					accessors, bufferViews, binaryList);
				if (!hasPosition)
				{
					SetDefaultAttribute(AttribIndex::position, 3, offsetof(SkeletalVertex, position), *buffer);
				}

				// ���_�A�g���r���[�g(�e�N�X�`�����W)���擾
				const bool hasTexcoord0 = SetVertexAttribute(AttribIndex::texcoord0, "TEXCOORD_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasTexcoord0)
				{
					SetDefaultAttribute(AttribIndex::texcoord0, 2, offsetof(SkeletalVertex, texcoord0), *buffer);
				}

				// ���_�A�g���r���[�g(�@��)���擾
				const bool hasNormal = SetVertexAttribute(AttribIndex::normal, "NORMAL", attributes,
					accessors, bufferViews, binaryList);
				if (!hasNormal)
				{
					SetDefaultAttribute(AttribIndex::normal, 3, offsetof(SkeletalVertex, normal), *buffer);
				}

				// ���_�A�g���r���[�g(�^���W�F���g)���擾
				//const bool hasTangent = SetVertexAttribute(AttribIndex::tangent, "TANGENT", attributes,
				//	accessors, bufferViews, binaryList);
				//if (!hasTangent)
				//{
				//	SetDefaultAttribute(AttribIndex::tangent, 4, offsetof(DefaultVertexData, tangent), *buffer);
				//}

				// ���_�A�g���r���[�g(�W���C���g�ԍ�)���擾
				const bool hasJoints = SetVertexAttribute(AttribIndex::joints0, "JOINTS_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasJoints)
				{
					SetDefaultAttribute(AttribIndex::joints0, 4, offsetof(SkeletalVertex, joints0), *buffer);
				}

				// ���_�A�g���r���[�g(�W���C���g�E�F�C��)���擾
				const auto hasWeights = SetVertexAttribute(AttribIndex::weights0, "WEIGHTS_0", attributes,
					accessors, bufferViews, binaryList);
				if (!hasWeights)
				{
					SetDefaultAttribute(AttribIndex::weights0, 4, offsetof(SkeletalVertex, weights0), *buffer);
				}


				// �v���~�e�B�u���g�p����}�e���A���ԍ����擾
				prim.materialNo = jsonPrim.value("material", 0);

				// VAO,VBO,IBO��OpenGL�R���e�L�X�g�ւ̊��蓖�Ă�����
				glBindVertexArray(0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// �쐬�����v���~�e�B�u��z��ɒǉ�
				mesh.primitives.push_back(prim);
			}
			// �쐬�������b�V���I�u�W�F�N�g��z��ɒǉ�
			file->meshes.push_back(mesh);
		}

		// �}�e���A�����쐬
		const auto materials = gltf.find("materials");
		if (materials != gltf.end())
		{
			file->materials.reserve(materials->size());
			for (const json& material : *materials)
			{
				MaterialPtr m = std::make_shared<Material>();

				// ���O��ݒ�
				m->SetName(material.value("name", std::string()));

				// �J���[��ݒ�
				const auto pbr = material.find("pbrMetallicRoughness");
				if (pbr != material.end())
				{
					// �}�e���A���J���[���擾
					m->color = Color::white;
					const auto baseColorFactor = pbr->find("baseColorFactor");
					if (baseColorFactor != pbr->end())
					{
						for (int i = 0; i < baseColorFactor->size(); ++i) {
							m->color[i] = baseColorFactor->at(i).get<float>();
						}
					}

					// �J���[�e�N�X�`����ǂݍ���
					m->mainTexture = LoadTexture("baseColorTexture", gltf, *pbr,
						foldername, defaultMaterial->mainTexture);
				} // if pbr

				// �@���e�N�X�`����ǂݍ���
				m->normalTexture = LoadTexture("normalTexture", gltf, material, foldername, nullptr);

				// �쐬�����}�e���A����ǉ�
				file->materials.push_back(m);
			}
		}

		// �m�[�h���쐬
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

				// �q�m�[�h���擾���A�q�m�[�h�ɑ΂��Đe�m�[�h��ݒ�
				const auto children = node.find("children");
				if (children != node.end())
				{
					n.children.resize(children->size());
					for (int b = 0; b < children->size(); ++b)
					{
						const json& child = children->at(b);
						const int childId = child.get<int>();
						n.children[b] = &file->nodes[childId];	// �q�m�[�h��ǉ�
						n.children[b]->parent = &n;				// �e�m�[�h��ݒ�
					}
				}

				// ���[�J�����W�ϊ��s����v�Z
				n.matLocal = GetLocalMatrix(node);
			}

			// �e�����ǂ��ăO���[�o�����@�ϊ��s����v�Z����
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

		// �V�[�����쐬
		const auto scenes = gltf.find("scenes");
		if (scenes != gltf.end())
		{
			// �e�V�[���ɕ\������m�[�h�z����擾
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

		// �X�L�����擾����
		const auto skins = gltf.find("skins");
		if (skins != gltf.end())
		{
			file->skins.resize(skins->size());
			for (size_t skinId = 0; skinId < skins->size(); ++skinId)
			{
				// �X�L������ݒ�
				const json& skin = skins->at(skinId);
				GltfSkinn& s = file->skins[skinId];
				s.name = skin.value("name", std::string());

				// �t�o�C���h�|�[�Y�s��̃A�h���X���擾
				const Matrix4x4* inverseBindMatrices = nullptr;
				const auto ibm = skin.find("inverseBindMatrices");
				if (ibm != skin.end())
				{
					const int ibmId = ibm->get<int>();
					inverseBindMatrices = static_cast<const Matrix4x4*>(
						GetBinaryDataAddress(accessors[ibmId], bufferViews, binaryList));
				}

				// �֐߃f�[�^���擾
				const json& joints = skin["joints"];
				s.joints.resize(joints.size());
				for (size_t jointId = 0; jointId < joints.size(); ++jointId)
				{
					auto& j = s.joints[jointId];
					j.nodeId = joints[jointId].get<int>();
					// �t�o�C���h�|�[�Y�s�񂪖��w��̏ꍇ�͒P�ʍs����g��(glTF�d�l 5.28.1)
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
			file->animations.resize(animations->size());
			for (size_t animeId = 0; animeId < animations->size(); ++animeId)
			{
				// ���O��ݒ�
				const json& animation = animations->at(animeId);
				GltfAnimationPtr a = std::make_shared<GltfAnimation>();
				a->name = animation.value("name", std::string());

				// �`���l���z��̗e�ʂ�\��
				// ��ʓI�ɁA���s�ړ��A��]�A�g��k���̂R�̓Z�b�g�Ŏw�肷��̂�
				// �e�`���l���z��̃T�C�Y�́u���`���l�� / 3�v�ɂȂ�\��������
				// ���S�̂��߁A�\��T�C�Y���K��1�ȏ�񂠂�悤�ɂP�𑫂��Ă���
				const json& channels = animation["channels"];
				const size_t predictedSize = channels.size() / 3 + 1;	// �\���T�C�Y
				a->translations.reserve(predictedSize);
				a->rotations.reserve(predictedSize);
				a->scales.reserve(predictedSize);

				// ���ׂẴm�[�h���u�A�j���[�V�����Ȃ��v�Ƃ��ēo�^
				a->staticNodes.resize(nodes->size());
				for (int i = 0; i < nodes->size(); ++i)
				{
					a->staticNodes[i] = i;
				}


				// �`���l���z���ݒ�
				const json& samplers = animation["samplers"];
				a->totalTime = 0;
				for (const json& e : channels)
				{
					// �����̔z����擾
					const json& sampler = samplers[e["sampler"].get<int>()];
					const json& inputAccessor = accessors[sampler["input"].get<int>()];
					const GLfloat* pTimes = static_cast<const GLfloat*>(
						GetBinaryDataAddress(inputAccessor, bufferViews, binaryList));

					// �Đ����Ԃ��v�Z
					a->totalTime = std::max(a->totalTime, inputAccessor["max"][0].get<float>());

					// �l�̔z����擾
					const json& outputAccessor = accessors[sampler["output"].get<int>()];
					const void* pValue = GetBinaryDataAddress(outputAccessor, bufferViews, binaryList);

					// ��ԕ��@���擾
					GltfInterpolation interp = GltfInterpolation::linear;
					const json& target = e["target"];
					const std::string& interpolation = target.value("interpolation", std::string());
					if (interpolation == "LINEAR")
					{
						interp = GltfInterpolation::linear;
					}
					else if (interpolation == "STEP")
					{
						interp = GltfInterpolation::step;
					}
					else if (interpolation == "CUBISPLINE")
					{
						interp = GltfInterpolation::cubicSpline;
					}

					// �����ƒl�̔z�񂩂�`���l�����쐬���Apath�ɑΉ�����z��ɒǉ�
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
					a->staticNodes[targetNodeId] = -1;	// �A�j���[�V��������
				}

				// �u�A�j���[�V��������v�����X�g����폜����
				const auto itr = std::remove(a->staticNodes.begin(), a->staticNodes.end(), -1);
				a->staticNodes.erase(itr, a->staticNodes.end());
				a->staticNodes.shrink_to_fit();

				// �A�j���[�V������ݒ�
				file->animations[animeId] = a;
			}
		}

		// �쐬�����t�@�C����Ԃ�
		return file;
	}

	/**
	* glTF���b�V����`�悷��
	*
	* @param mesh		�`�悷�郁�b�V��
	* @param materials	�`��Ɏg���}�e���A���z��
	* @param program	�`��v���O����
	*/
	void Draw(const GltfMesh& mesh, const std::vector<MaterialPtr>& materials, GLuint program)
	{
		// ���ׂẴv���~�e�B�u��`��
		for (const auto& prim : mesh.primitives)
		{
			// �}�e���A����ݒ�
			if (prim.materialNo >= 0 && prim.materialNo < materials.size())
			{
				const Material& material = *materials[prim.materialNo];

				// �X�؃L�����p�����[�^���v�Z
				const float a = 1.0f - material.rouhness;
				const float specularPower = (a * a) * 999 + 1;
				const float normalizeFactor = (specularPower + 8) / (8 * Mathf::PI);
				bool hasUnifomColor = false;
				if (program)
				{
					hasUnifomColor = glGetUniformLocation(program, "color") >= 0;
				}
				if (hasUnifomColor)
				{
					glProgramUniform4fv(program, 100, 1, &material.color.r);
					//glProgramUniform2f(program, 103, specularPower, normalizeFactor);
				}
				// OpenGL�R���e�L�X�g�Ƀe�N�X�`�������蓖�Ă�
				if (material.mainTexture)
				{
					GLuint tex = 0;
					tex = *material.mainTexture;
					glBindTextures(0, 1, &tex);
				}
				if (material.normalTexture)
				{
					GLuint tex = 0;
					tex = *material.normalTexture;
					// �V�F�[�_�ɖ@���}�b�v��Ή������������
					//glBindTextures(0, 1, &tex);
				}
			}
			glBindVertexArray(*prim.vao);
			glDrawElements(prim.mode, prim.count, prim.type, prim.indeices);
		}

		// OpenGL�R���e�L�X�g�ւ̊��蓖�Ă�����
		glBindVertexArray(0);
		glBindTextures(0, 1, nullptr);
		//glBindTextures(0, 1, nullptr);
	}
}
