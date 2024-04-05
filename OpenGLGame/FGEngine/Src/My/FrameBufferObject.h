/**
* @file FrameBufferObject.h
*/
#ifndef FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#define FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include "Texture.h"

namespace FGEngine::Rendering
{
	// 先行宣言
	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;


	/**
	* フレームバッファ・オブジェクト(FBO)
	*/
	class FrameBufferObject
	{
	public:

		// テクスチャからFBOを作成するコンストラクタ
		FrameBufferObject(const TexturePtr& color, const TexturePtr& depth);
		~FrameBufferObject();

		// コピーと代入を禁止
		FrameBufferObject(const FrameBufferObject&) = delete;
		FrameBufferObject& operator=(const FrameBufferObject&) = delete;

		/**
		* フレームバッファオブジェクトを作成
		* 
		* @param color カラーバッファ
		* @param depth 深度バッファ
		*
		* @return 作成したフレームバッファオブジェクトポインター
		*/
		static FrameBufferObjectPtr Create(const TexturePtr& color, const TexturePtr& depth);

		/**
		* 管理番号を取得
		*/
		operator GLuint() const
		{
			return fbo;
		}

		/**
		* 幅の取得
		*/
		int GetWidth() const
		{
			return widht;
		}

		/**
		* 高さの取得
		*/
		int GetHeight() const
		{
			return height;
		}

		// テクスチャを取得
		const TexturePtr& GetColorTexture() const
		{
			return texColor;
		}
		const TexturePtr& GetDepthTexture() const
		{
			return texDepth;
		}

	private:

		// FBOの管理番号
		GLuint fbo;

		// FBOの幅
		int widht = 0;

		// FBOの高さ
		int height = 0;

		// カラーテクスチャ
		TexturePtr texColor;

		// 深度テクスチャ
		TexturePtr texDepth;
	};
}
#endif // !FRAMEBUFFEROBJECT_H_INCLUDED
