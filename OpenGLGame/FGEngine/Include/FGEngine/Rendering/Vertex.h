/**
* @file Vertex.h
*/
#ifndef FGENGINE_VERTEX_H_INCLUDED
#define FGENGINE_VERTEX_H_INCLUDED
#include "FGEngine/Math/Math.h"

namespace FGEngine::RenderingSystem
{
	/**
	* 頂点データ形式
	*/
	struct Vertex
	{
		Vector3 position = Vector3::zero;
		Vector2 texcoord0 = Vector2::zero;
		Vector3 normal = Vector3(0, 0, -1);
		Vector4 tangent = Vector4(1, 0, 0, 1);
		Vector4 joints0 = Vector4::zero;
		Vector4 weights0 = Vector4::zero;
	};

}

#endif // !FGENGINE_VERTEX_H_INCLUDED
