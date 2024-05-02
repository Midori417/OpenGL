/**
* @file Vertex.h
*/
#ifndef FGENGINE_VERTEX_H_INCLUDED
#define FGENGINE_VERTEX_H_INCLUDED
#include "VectorPoint.h"

namespace FGEngine::RenderingSystem
{
	/**
	* 頂点データ形式
	*/
	struct Vertex
	{
		Vector3 position = Vector3::zero;	// 頂点座標
		Vector2 texcoord = Vector2::zero;	// テクスチャ座標
		Vector3 normal = Vector3(0,0,-1);	// 法線ベクトル
	};
}

#endif // !FGENGINE_VERTEX_H_INCLUDED
