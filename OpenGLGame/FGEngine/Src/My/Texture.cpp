/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <vector>
#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

namespace FGEngine
{

	/**
	* コンストラクタ
	*
	* @param filename テクスチャファイル名
	*
	*/
	Texture::Texture(const std::string& name, GLuint object, int width, int height)
		: id(object), width(width), height(height)
	{		
		// 名前を設定
		this->SetName(name);
	}

	/**
	* 空のテクスチャを作成するコンストラクタ
	*
	* @param name		テクスチャ識別用の名前
	* @param widht		テクスチャの幅(ピクセル数)
	* @param height		テクスチャの高さ(ピクセル数)
	* @param gpuFormat	データ形式
	* @param wrapMode	ラップモード
	*/
	Texture::Texture(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
		: width(width), height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, gpuFormat, width, height);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, wrapMode);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, wrapMode);

		// 深度テクスチャの場合、シャドウマッピングのために比較モードを設定する
		switch (gpuFormat)
		{
		case GL_DEPTH_COMPONENT16:
		case GL_DEPTH_COMPONENT24:
		case GL_DEPTH_COMPONENT32:
		case GL_DEPTH_COMPONENT32F:
			glTextureParameteri(id, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
			break;
		default:
			break;
		}
		SetName(name);
	}

	/**
	* デストラクタ
	*/
	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	/**
	* テクスチャを読み込んで作成
	* 
	* @param name		テクスチャの名前
	* @apram filename	テクスチャのファイル
	* 
	* @return 作成したテクスチャポインター
	*/
	std::shared_ptr<Texture> Texture::Create(const std::string& name, GLuint object, int width, int height)
	{
		return std::make_shared<Texture>(name, object, width, height);
	}

	/**
	* 空のテクスチャを作成する
	* 
	* @param name		テクスチャ識別用の名前
	* @param widht		テクスチャの幅(ピクセル数)
	* @param height		テクスチャの高さ(ピクセル数)
	* @param gpuFormat	データ形式
	* @param wrapMode	ラップモード
	* 
	* @return 作成したテクスチャポインター
	*/
	std::shared_ptr<Texture> Texture::Create(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
	{
		return std::make_shared<Texture>(name, width, height, gpuFormat, wrapMode);
	}
}