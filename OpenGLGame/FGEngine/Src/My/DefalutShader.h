/**
* @file DefalutShader.h
*/
#ifndef FGENGINE_DEFALUTSHADER_H_INCLUDED
#define FGENGINE_DEFALUTSHADER_H_INCLUDED

namespace FGEngine
{
	/**
	* 基礎シェーダリスト
	*/
	enum class DefalutShader
	{
		// 通常シェーダ
		Standard3D,

		// スケルタルメッシュシェーダ
		Skeletal3D,

		// 通常シャドウシェーダ
		Shadow3D,

		// スケルタルシャドウシェーダ
		ShadowSkeletal3D,

		// 何もないシェーダ
		Unlit,
	};
}

#endif // !FGENGINE_DEFALUTSHADERLIST_H_INCLUDED
