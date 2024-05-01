/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "glad/glad.h"
#include <string>
#include <memory>


/**
* �e�N�X�`���Ǘ��N���X
*/
class Texture
{
	friend class Engine;
public:

	enum class Usage
	{
		for3D,
		forGltf
	};

	// filename�̃e�N�X�`�����쐬����R���X�g���N�^
	explicit Texture(const char* filename, Usage usage = Usage::for3D);
	// ��̃e�N�X�`�����쐬����R���X�g���N�^
	Texture(const char* name, int width, int height,
		GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);
	~Texture();

public:


	// �R�s�[�Ƒ�����֎~
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	static std::shared_ptr<Texture> Create(const char* filename, Usage usage = Usage::for3D)
	{
		return std::make_shared<Texture>(filename, usage);
	}
	static std::shared_ptr<Texture> Create(const std::string& filename , Usage usage = Usage::for3D)
	{
		return std::make_shared<Texture>(filename.c_str(), usage);
	}
	static std::shared_ptr<Texture> Create(const char* name, int width, int height,
		GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE)
	{
		return std::make_shared<Texture>(name, width, height, gpuFormat, wrapMode);
	}


	// �Ǘ��ԍ����擾
	operator GLuint() const {
		return id;
	}
	GLuint GetId() const
	{
		return id;
	}

	// ���ƍ������擾
	int GetWidth() const {
		return width;
	}
	int GetHeight() const {
		return height;
	}

	// �摜�̃A�X�y�N�g����擾
	float GetAspectRatio() const {
		return static_cast<float>(width) / static_cast<float>(height);
	}

	// ���O���擾
	const std::string& GetName() const {
		return name;
	}

private:

	std::string name;	// �e�N�X�`����
	GLuint id = 0;		// �I�u�W�F�N�g�̊Ǘ��ԍ�
	int width = 0;		// �e�N�X�`���̕�
	int height = 0;		// �e�N�X�`���̍���

};
using TexturePtr = std::shared_ptr<Texture>;

#endif // !TEXTURE_H_INCLUDED
