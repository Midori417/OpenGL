/**
* @file Texture.h
*/
#ifndef FFGENGINE_TEXTURE_H_INCLUDED
#define FFGENGINE_TEXTURE_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>
#include "Vector2.h"

namespace FGEngine
{
	// 先行宣言
	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	/**
	* テクスチャ管理クラス
	*/
	class Texture
	{
	public:

		/**
		* テクスチャのタイプ
		*/
		enum class TextureType
		{
			// Obj
			Obj,

			// Gltf
			Gltf,
		};

		// filenameのテクスチャを作成するコンストラクタ
		explicit Texture(const std::string& name, const std::string& filename, TextureType type = TextureType::Obj,
			GLenum filterMode = GL_NEAREST);

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
		* @param filename	テクスチャのファイル
		* @param type		テクスチャのタイプ
		* 
		* @return 作成したテクスチャポインター
		*/
		static std::shared_ptr<Texture> Create(const std::string& name, const std::string& filename, 
			TextureType type = TextureType::Obj, GLenum filterMode = GL_NEAREST);

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

		Vector2 GetSize() const
		{
			return Vector2(static_cast<float>(width), static_cast<float>(height));
		}

		/**
		* テクスチャの名前を取得
		*/
		std::string ToString() const
		{
			return name;
		}

	private:

		// テクスチャの名前
		std::string name;

		// テクスチャの管理番号
		GLuint id = 0;

		// テクスチャの幅
		int width = 0;

		// テクスチャの高さ
		int height = 0;

	};
}
#endif // !TEXTURE_H_INCLUDED
