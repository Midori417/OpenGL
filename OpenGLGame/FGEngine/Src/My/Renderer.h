/**
* @file Renderer.h
*/
#ifndef FGENGINE_RENDERER_H_INCLUDED
#define FGENGINE_RENDERER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* 描画コンポーネントの基底クラス
	*/
	class Renderer : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Renderer() = default;
		virtual ~Renderer() = default;

	public:

		// 描画するするかの有無
		bool enabled = true;
	};
	using RendererPtr = std::shared_ptr<Renderer>;
}

#endif // !FGENGINE_RENDERER_H_INCLUDED
