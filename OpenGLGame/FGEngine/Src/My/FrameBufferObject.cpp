/**
* @file FrameBufferObject.cpp
*/
#include "FrameBufferObject.h"
#include "Debug.h"

namespace FGEngine::Rendering::Rall
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
		glCreateFramebuffers(1, &fbo);

		// カラーバッファを設定
		if (color)
		{
			glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, *color, 0);
			widht = texColor->GetWidth();
			height = texColor->GetHeight();
		}
		else
		{
			// テクスチャを割り当てない
			glNamedFramebufferDrawBuffer(fbo, GL_NONE);
		}

		// 深度バッファを設定
		if (depth)
		{
			glNamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, *depth, 0);
			widht = texDepth->GetWidth();
			height = texDepth->GetHeight();
		}

		// FBOのエラーチェック
		if (glCheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glDeleteFramebuffers(1, &fbo);
			fbo = 0;
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
		glDeleteFramebuffers(1, &fbo);
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
}