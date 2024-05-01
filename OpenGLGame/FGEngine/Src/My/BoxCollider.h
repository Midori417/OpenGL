/**
* @file BoxCollider.h
*/
#ifndef BOXCOLLIDER_H_INCLUDED
#define BOXCOLLIDER_H_INCLUDED

#include "Collider.h"
#include "Collision.h"

/**
* BOXコライダー
*/
class BoxCollider : public Collider
{
public:

	BoxCollider() = default;
	virtual ~BoxCollider() = default;

	// 図形の種類
	Type GetType() const override {
		return Type::Box;
	}

	// 座標を変更する
	void AddPosition(const Vector3& translate) override {
		box.position += translate;
	}

	// 座標変換したコライダーを取得する
	ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override {

		// 座標変換行列を分解
		Vector3 translate; // 未使用
		Vector3 scale;
		Matrix3x3 rotation;
		Decompose(transform, translate, scale, rotation);

		// 座標変換したコピーを作成
		auto p = std::make_shared<BoxCollider>();
		p->box.position = Vector3(transform * Vector4(box.position, 1));
		for (int i = 0; i < 3; ++i) {
			p->box.axis[i] = rotation * box.axis[i];	// 軸ベクトル
			p->box.scale[i] = box.scale[i] * scale[i];	// 拡大率
		}
		return p;
	}

	// 図形を取得する
	const Box& GetShape() const {
		return box;
	}

public:

	Box box = {
		{0,0,0},
		{{1,0,0}, {0,1,0}, {0,0,1}},
		{1,1,1}
	};
};
using BoxColliderPtr = std::shared_ptr<BoxCollider>;
#endif // !BOXCOLLIDER_H_INCLUDED
