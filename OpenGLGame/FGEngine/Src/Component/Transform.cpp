/**
* @file Transform.cpp
*/
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* 前方ベクトルを取得
	*/
	Vector3 Transform::Forward() const
	{
		auto foward = rotation * Vector3::forward;
		return Vector3::Normalize(foward);
	}

	/**
	* 右方ベクトルを取得
	*/
	Vector3 Transform::Right() const
	{
		auto right = rotation * Vector3::right;
		return Vector3::Normalize(right);
	}

	/**
	* 上方ベクトルを取得
	*/
	Vector3 Transform::Up() const
	{
		auto up = rotation * Vector3::up;
		return Vector3::Normalize(up);
	}
	
	/**
	* 位置と回転を設定する
	*
	* @param pos 位置
	* @param rot 回転
	*/
	void Transform::SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
	{
		position = pos;
		rotation = rot;
	}

	/**
	* translationの方向と距離に移動する
	*
	* @param translation 移動する方向と距離
	*/
	void Transform::Translate(const Vector3& translation)
	{
		position += translation;
	}

	/**
	* オイラー角を取得
	*/
	Vector3 Transform::GetEulerAngle() const
	{
		return Quaternion::EulerAngle(rotation);
	}

	/**
	* 現在の角度からeuler加算する
	*
	* @param euler 回転量(オイラー角)
	*/
	void Transform::Rotate(const Vector3& eulers)
	{
		rotation = Quaternion::Euler(eulers) * rotation;
	}

	/**
	* 対象のTransformを設定し、その方向へ向く
	*
	* @param target		向ける対象オブジェクトのTransform
	* @param worldUp	上方ベクトル
	*/
	void Transform::LookAt(const Transform* target, const Vector3& worldUp)
	{
		// ワールド座標系における始点座標系のXYZの向きを計算
		const Vector3 axisZ = Vector3::Normalize(-Vector3(position - target->position));
		const Vector3 axisX = Vector3::Normalize(Vector3::Cross(worldUp, axisZ));
		const Vector3 axisY = Vector3::Normalize(Vector3::Cross(axisZ, axisX));

		// 座標を軸ベクトルに投影するように行列を設定
		Matrix4x4 m;
		m.SetRow(0, Vector4{ axisX.x, axisY.x, axisZ.x, 0 });
		m.SetRow(1, Vector4{ axisX.y, axisY.y, axisZ.y, 0 });
		m.SetRow(2, Vector4{ axisX.z, axisY.z, axisZ.z, 0 });

		// eyeが原点になるように、eyeを各軸に射影して平行移動量を計算
		m.SetRow(3, Vector4{ -Vector3::Dot(axisX, position), -Vector3::Dot(axisY, position), -Vector3::Dot(axisZ, position), 1 });

		rotation = Quaternion::RotationMatrixToQuaternion(Matrix3x3(m));

	}

	/**
	* 対象のTransformを設定し、その方向へ向く
	*
	* @param target		向ける対象オブジェクトのTransform
	* @param worldUp	上方ベクトル
	*/
	void Transform::LookAt(const TransformPtr target, const Vector3& worldUp)
	{
		LookAt(target.get(), worldUp);
	}

	/**
	* 親Transformを設定する
	*
	* @param parent 設定する親のTransform
	*/
	void Transform::SetParent(const TransformPtr parent)
	{
		// 同じ親を指定していたら何もしない
		if (this->parent.lock() == parent)
		{
			return;
		}

		// 別の親が指定された場合今の親と関係を解除する
		auto par = this->parent.lock();
		if (par)
		{
			// 自分の位置を検索
			auto itr = std::find_if(par->childrens.begin(), par->childrens.end(),
				[this](const std::weak_ptr<Transform>& child) {
					return child.lock() == this->GetTransform();
				});

			// 親の子供配列の中の自分との関係を各除する
			if (itr != par->childrens.end())
			{
				par->childrens.erase(itr);
			}
		}

		// 新たな親子関係を設定
		if (parent)
		{
			parent->childrens.push_back(GetTransform());
		}
		this->parent = parent;
	}

	/**
	* 親Transformを取得する
	*/
	TransformPtr Transform::GetParent() const
	{
		auto ptr = parent.lock();
		if (!ptr)
		{
			return nullptr;
		}
		return ptr;
	}

	/**
	* 子オブジェクトの数を取得する
	*/
	size_t Transform::GetChildrenCount() const
	{
		return childrens.size();
	}

	/**
	* indexから子のTransformを取得する
	*
	* @param 子Transformのindex
	*/
	TransformPtr Transform::GetChildren(size_t index) const
	{
		return childrens[index].lock();
	}

	/**
	* 全ての子オブジェクトを切り離す
	*/
	void Transform::AllChildrenPurge()
	{
		childrens.clear();
	}

	/**
	* ローカル座標行列を取得
	*/
	Matrix4x4 Transform::GetLocalTransformMatrix() const
	{
		return localTransformMatrix;
	}

	/**
	* ワールド座標行列を取得
	*/
	Matrix4x4 Transform::GetWorldTransformMatrix() const
	{
		return worldTransformMatrix;
	}

	/**
	* 法線行列を取得
	*/
	Matrix3x3 Transform::GetNormalMatrix() const
	{
		return normalMatrix;
	}

	/**
	* 
	*/
	ComponentPtr Transform::Clone() const
	{
		TransformPtr p = std::make_shared<Transform>();

		p->position = this->position;
		p->rotation = this->rotation;
		p->scale = this->scale;

		p->localTransformMatrix = this->localTransformMatrix;
		p->worldTransformMatrix = this->worldTransformMatrix;
		p->normalMatrix = this->normalMatrix;

		p->parent = this->parent;

		return p;
	}

	/**
	* ローカル座標行列を更新
	*/
	void Transform::LocalTransformUpdate()
	{
		auto pos = Matrix4x4::Translate(Vector3(position.x, position.y, -position.z));
		auto rot = Quaternion::QuaternionToRotationMatrix(Quaternion(-rotation.x, -rotation.y, rotation.z, rotation.w));
		auto s = Matrix4x4::Scale(scale);
		localTransformMatrix = pos * Matrix4x4(rot) * s;
		normalMatrix = (rot);
	}

}