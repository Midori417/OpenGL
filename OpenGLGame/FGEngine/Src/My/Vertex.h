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

	/**
	* スケルタルメッシュ頂点データ形式
	*/
	struct SkeletalVertex
	{
		Vector3 position = Vector3::zero;		// 頂点座標
		Vector2 texcoord = Vector2::zero;		// テクスチャ座標
		Vector3 normal = Vector3(0, 0, -1);		// 法線ベクトル
		Vector4 tangent = Vector4(1, 0, 0, 1);	// 線形空間
		Vector4 joints = Vector4::zero;			// ジョイント
		Vector4 weights = Vector4::zero;		// ウェイト
	};


}

#endif // !FGENGINE_VERTEX_H_INCLUDED
