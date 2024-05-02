/**
* @file FrameBufferObject.cpp
*/
#include "FrameBufferObject.h"
#include "Debug.h"

namespace FGEngine::RenderingSystem
{
	/**
	* 既存のテクスチャからFBOを作成する
	* 
	* @param color カラーバッファ
	* @param depth 深度バッファ
	*/
	FrameBufferObject::FrameBufferObject(const TexturePtr& color, const TexturePtr& depth)
		: texColor(color), texDepth(depth)
	{
		glCreateFramebuffers(1, &id);

		// カラーバッファを設定
		if (color)
		{
			glNamedFramebufferTexture(id, GL_COLOR_ATTACHMENT0, *color, 0);
			widht = texColor->GetWidth();
			height = texColor->GetHeight();
		}
		else
		{
			// テクスチャを割り当てない
			glNamedFramebufferDrawBuffer(id, GL_NONE);
		}

		// 深度バッファを設定
		if (depth)
		{
			glNamedFramebufferTexture(id, GL_DEPTH_ATTACHMENT, *depth, 0);
			widht = texDepth->GetWidth();
			height = texDepth->GetHeight();
		}

		// FBOのエラーチェック
		if (glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glDeleteFramebuffers(1, &id);
			id = 0;
			texColor.reset();
			texDepth.reset();
			LOG_ERROR("FBOの作成に失敗");
			return;
		}

		// 作成成功
		LOG("FBO(width=%d, height=%d)を作成", widht, height);

	}

	/**
	* デストラクタ
	*/
	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &id);
	}

	/**
	* FraneBufferObjectを作成
	*
	* @param color カラーバッファ
	* @param depth 深度バッファ
	*
	* @return 作成したフレームバッファオブジェクトポインター
	*/
	FrameBufferObjectPtr FrameBufferObject::Create(const TexturePtr& color, const TexturePtr& depth)
	{
		return std::make_shared<FrameBufferObject>(color, depth);
	}

	/**
	* フレームバッファオブジェクトの管理番号を取得
	*/
	FrameBufferObject::operator GLuint() const
	{
		return id;
	}

	/**
	* 幅を取得
	*/
	int FrameBufferObject::GetWidth() const
	{
		return widht;
	}

	/**
	* 高さを取得
	*/
	int FrameBufferObject::GetHeight() const
	{
		return height;
	}

	/**
	* カラーテクスチャを取得
	*/
	const TexturePtr& FrameBufferObject::GetColorTexture() const
	{
		return texColor;
	}

	/**
	* 深度テクスチャを取得
	*/
	const TexturePtr& FrameBufferObject::GetDepthTexture() const
	{
		return texDepth;
	}
}