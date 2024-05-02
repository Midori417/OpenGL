/**
* @file Texture.h
*/
#ifndef FFGENGINE_TEXTURE_H_INCLUDED
#define FFGENGINE_TEXTURE_H_INCLUDED
#include "Package/Glad.h"
#include "Object.h"

namespace FGEngine
{
	// 先行宣言
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* テクスチャ管理クラス
	*/
	class Texture : public Object
	{
	public:

		// filenameのテクスチャを作成するコンストラクタ
		explicit Texture(const std::string& name, GLuint object, int width, int height);

		// 空のテクスチャを作成するコンストラクタ
		explicit Texture(const std::string& name, int width, int height,
			GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);

		// デストラクタ
		~Texture();


		// コピーと代入を禁止
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	public:

		/**
		* テクスチャを読み込んで作成
		*
		* @param name		テクスチャの名前
		* @apram filename	テクスチャのファイル
		*
		* @return 作成したテクスチャポインター
		*/
		static std::shared_ptr<Texture> Create(const std::string& name, GLuint object, int width, int height);

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
		static std::shared_ptr<Texture> Create(const std::string& name, int width, int height,
			GLenum gpuFormat = GL_RGBA8, GLenum wrapMode = GL_CLAMP_TO_EDGE);

		/**
		* テクスチャの管理番号を取得
		*/
		operator GLuint() const 
		{
			return id;
		}

		/**
		* 幅を取得
		*/
		int GetWidth() const
		{
			return width;
		}
		/**
		*高さを取得
		*/
		int GetHeight() const
		{
			return height;
		}

	private:


		// テクスチャの管理番号
		GLuint id = 0;

		// テクスチャの幅
		int width = 0;

		// テクスチャの高さ
		int height = 0;

	};
}
#endif // !TEXTURE_H_INCLUDED
