/**
* @file MapRangeLimit.h
*/
#ifndef MAPRANGELIMIT_H_INCLUDED
#define MAPRANGELIMIT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/UsingNames/UsingAsset.h"
using namespace FGEngine;

/**
* マップ範囲制限
*/
class MapRangeLimit : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	MapRangeLimit() = default;

private:

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* コンポーネントのクローンを作成する
	* 
	* @return 作成したクローン
	*/
	virtual ComponentPtr Clone() const override;

private:

	/**
	* 壁を作成
	*/
	void CreateMapWall(const Vector2& pos, const Vector2& size);

public:

	StaticMeshPtr mesh;
	ShaderPtr shader;
	MaterialPtr material;

	// 範囲制限の大きさ
	Vector2 mapSize = Vector2::one;
};


#endif // !MAPRANGELIMIT_H_INCLUDED