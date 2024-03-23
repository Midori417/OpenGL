/**
* @file FrameBufferObject.h
*/
#ifndef FRAMEBUFFEROBJECT_H_INCLUDED
#define FRAMEBUFFEROBJECT_H_INCLUDED

#include "Package/Glad.h"
#include "Texture.h"

namespace FGEngine
{
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

		// 管理番号を取得
		operator GLuint() const
		{
			return fbo;
		}

		// 幅と高さを取得
		int GetWidth() const
		{
			return widht;
		}
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

		GLuint fbo;		// FBOの管理番号
		int widht = 0;	// FBOの幅
		int height = 0;	// FBOの高さ
		TexturePtr texColor;	// カラーテクスチャ
		TexturePtr texDepth;	// 深度テクスチャ
	};
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;
}
#endif // !FRAMEBUFFEROBJECT_H_INCLUDED
