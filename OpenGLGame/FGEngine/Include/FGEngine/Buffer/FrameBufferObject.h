/**
* @file FrameBufferObject.h
*/
#ifndef FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#define FGENGINE_FRAMEBUFFEROBJECT_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include "FGEngine/Asset/Texture.h"

namespace FGEngine
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
