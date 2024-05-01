/**
* @file Renderer.h
*/
#ifndef COMPONENT_RENDERER_H_INCLUDED
#define COMPONENT_RENDERER_H_INCLUDED
#include "Component.h"
#include "VecMath.h"

// 先行宣言
class ProgramObject;

/**
* モデル形式
*/
enum class ModelFormat
{
	obj,			// OBJファイル
	gltfStatic,		// glTF(アニメーション無し)
	gltfAnimated	// glTF(アニメーションあり)
};

/**
* レンダラーコンポーネントの基底クラス
*/
class Renderer : public Component
{
public:
	enum class Type
	{
		Standard,
		Shadow
	};


	// コンストラクタ・デストラクタ
	Renderer() = default;
	virtual ~Renderer() = default;

	// モデル形式を取得
	virtual ModelFormat GetModelFormat() const = 0;

	virtual void PreDraw(){}
	virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const {}

public:

	//int renderQueue = RenderQueue_geometry;	// 描画順

};
using RendererPtr = std::shared_ptr<Renderer>;

#endif // !COMPONENT_RENDERER_H_INCLUDED
