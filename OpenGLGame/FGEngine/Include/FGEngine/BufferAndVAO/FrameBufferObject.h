/**
* @file FrameBufferObject.h
*/
#ifndef FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#define FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#include "BufferAndVAOFrd.h"
#include "FGEngine/UsingNames/UsingAsset.h"

namespace FGEngine
{
	/**
	* フレームバッファ・オブジェクト(FBO)
	*/
	class FrameBufferObject
	{
	public:	// コンストラクタ・デストラクタ

		/**
		* 既存のテクスチャからFBOを作成する
		*
		* @param color カラーバッファ
		* @param depth 深度バッファ
		*/
		FrameBufferObject(const TexturePtr& color, const TexturePtr& depth);

		/**
		* デストラクタ
		*/
		~FrameBufferObject();

	public:	// 禁止事項

		// コピーを禁止
		FrameBufferObject(const FrameBufferObject&) = delete;

		// 代入を禁止
		FrameBufferObject& operator=(const FrameBufferObject&) = delete;

	public:

		/**
		* フレームバッファオブジェクトを作成
		* 
		* @param color カラーバッファ
		* @param depth 深度バッファ
		*
		* @return 作成したフレームバッファオブジェクトポインター
		*/
		static FrameBufferObjectPtr Create(const TexturePtr& color, const TexturePtr& depth);

	public:

		/**
		* 管理番号を取得
		*/
		operator GLuint() const;

		/**
		* 幅の取得
		*/
		int GetWidth() const;

		/**
		* 高さの取得
		*/
		int GetHeight() const;

		/**
		* カラーテクスチャを取得
		*/
		const TexturePtr& GetColorTexture() const;

		/**
		* 深度テクスチャを取得
		*/
		const TexturePtr& GetDepthTexture() const;

	private:

		// FBOの管理番号
		GLuint id;

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
