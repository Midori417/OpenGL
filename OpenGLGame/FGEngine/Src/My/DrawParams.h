/**
* @file DrawParams.h
*/
#ifndef FGENGINE_DRAWPARAMS_H_INCLUDED
#define FGENGINE_DRAWPARAMS_H_INCLUDED
#include "Package/Glad.h"

namespace FGEngine::Rendering
{
	/**
	* 描画パラメータ
	*/
	struct DrawParams
	{
		// プリミティブの種類
		GLenum mode = GL_TRIANGLES;	

		// 描画するインデックスの数
		GLsizei count = 0;

		// 描画開始インデックスのバイトオフセット
		const void* indices = 0;

		// インデックス0となる頂点配列内の位置
		GLint baseVertex = 0;		

		// マテリアルインデックス
		int materialNo = -1;
	};
}

#endif // !FGENGINE_DRAWPARAMS_H_INCLUDED
