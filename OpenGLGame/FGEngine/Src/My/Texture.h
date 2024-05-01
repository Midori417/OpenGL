/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "glad/glad.h"
#include <string>
#include <memory>


/**
* テクスチャ管理クラス
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

	// filenameのテクスチャを作成するコンストラクタ
	explicit Texture(const char* filename, Usage usage = Usage::for3D);
	// 空のテクスチャを作成するコンストラクタ
	Texture(const char* name, int width, int height,
		GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);
	~Texture();

public:


	// コピーと代入を禁止
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


	// 管理番号を取得
	operator GLuint() const {
		return id;
	}
	GLuint GetId() const
	{
		return id;
	}

	// 幅と高さを取得
	int GetWidth() const {
		return width;
	}
	int GetHeight() const {
		return height;
	}

	// 画像のアスペクト比を取得
	float GetAspectRatio() const {
		return static_cast<float>(width) / static_cast<float>(height);
	}

	// 名前を取得
	const std::string& GetName() const {
		return name;
	}

private:

	std::string name;	// テクスチャ名
	GLuint id = 0;		// オブジェクトの管理番号
	int width = 0;		// テクスチャの幅
	int height = 0;		// テクスチャの高さ

};
using TexturePtr = std::shared_ptr<Texture>;

#endif // !TEXTURE_H_INCLUDED
