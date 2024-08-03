/**
* @file Sprite.h
*/
#ifndef FGENGINE_SPRITE_H_INCLUDED
#define FGENGINE_SPRITE_H_INCLUDED
#include "VectorPoint.h"

namespace FGEngine
{
	/**
	* 図形に表示する範囲を表す構造体
	*/
	struct Texcoord
	{
		// テクスチャ座標
		Vector2 uv;

		// 図形の大きさ
		Vector2 size;
	};

	/**
	* 画像表示用データ(スプライト)を格納する構造体
	*/
	struct Sprite
	{
		// 画像を表示する座標
		Vector4 pos;

		// テクスチャ座標と大きさ
		Texcoord texcoord;
	};
}

#endif // !FGENGINE_SPRITE_H_INCLUDED
