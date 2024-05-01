/**
* @file FrameBufferObject.cpp
*/
#include "FrameBufferObject.h"
#include "Debug.h"

/**
* 既存のテクスチャからFBOを作成する
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
