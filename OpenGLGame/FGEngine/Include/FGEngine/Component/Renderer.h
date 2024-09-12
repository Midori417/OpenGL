/**
* @file Renderer.h
*/
#ifndef FGENGINE_RENDERER_H_INCLUDED
#define FGENGINE_RENDERER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;

	/**
	* 描画の順序
	*/
	enum RenderQueue
	{
		RenderQueue_geometry = 2000,	// 一般的な図形
		RenderQueue_transparent = 3000,	// 半透明な図形
		RenderQueue_overlay = 4000,		// UI、全画面エフェクト
		RenderQueue_max = 5000,			// キューの最大値
	};

	enum class DrawType
	{
		normal,
		shadow
	};

	/**
	* 描画コンポーネントの基底クラス
	*/
	class Renderer : public Component
	{
		friend class RenderingEngine;
	public:

		// コンストラクタ・デストラクタ
		Renderer() = default;
		virtual ~Renderer() = default;

	protected:

		/**
		* 描画の前処理
		*/
		virtual void PreDraw(){}

		/**
		* 描画
		* 
		* @param 描画のタイプ
		*/
		virtual void Draw(DrawType drawType) const{}

	public:

		// 描画するするかの有無
		bool enabled = true;

		// レンダーキュー
		int renderQueue = RenderQueue_geometry;

		// シェーダ
		ShaderPtr shader;

		// 影シェーダ
		ShaderPtr shadowShader;
	};
	using RendererPtr = std::shared_ptr<Renderer>;
}

#endif // !FGENGINE_RENDERER_H_INCLUDED
