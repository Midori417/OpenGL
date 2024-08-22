/**
* @file GameObject.cpp
*/
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Renderer.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/AudioSource.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* ゲームオブジェクトの状態を取得
	*/
	GameObjectState GameObject::GetState() const
	{
		return state;
	}

	/**
	* シーンを取得
	*/
	Scene* GameObject::GetScene() const
	{
		return ownerScene;
	}

	/**
	* トランスフォームコンポーネントを取得
	*/
	TransformPtr GameObject::GetTransform() const
	{
		return transform;
	}

	/**
	* ゲームオブジェクトを破棄する
	*
	* @param destroyTime 破棄までの時間
	*/
	void GameObject::Destroy(float destroyTime)
	{
		// 引数の破棄時間が0秒いかなら状態を破棄にする
		if (destroyTime <= 0)
		{
			state = GameObjectState::Destory;
			return;
		}

		// すでに破棄なら何もしない
		if (state == GameObjectState::Destory)
		{
			return;
		}

		// 破棄待ちじゃなければ破棄時間を代入する
		if (state != GameObjectState::DestroyTime)
		{
			// 状態を破棄待ちにする
			state = GameObjectState::DestroyTime;
			// 破棄時間を設定
			this->destroyTime = destroyTime;
		}
	}

	/**
	* クローンしたゲームオブジェクトを取得する
	*/
	GameObjectPtr GameObject::CloneGameObject(const GameObjectPtr& object, const TransformPtr& transform)
	{
		auto p = std::make_shared<GameObject>();

		p->isActive = object->isActive;
		p->name = object->name + "Clone";
		p->tag = object->tag;

		// クローンするトランスフォームがなければobjectのトランスフォームをクローンするする
		if (transform != nullptr)
		{
			// クローンもとにトランスフォームコンポーネントがあれば
			if (object->transform)
			{
				ComponentPtr clone = object->transform->Clone();
				clone->ownerObject = p;
				p->transform = std::dynamic_pointer_cast<Transform>(clone);
			}
		}
		else
		{
			ComponentPtr clone = transform->Clone();
			clone->ownerObject = p;
			p->transform = std::dynamic_pointer_cast<Transform>(clone);
		}
		// クローンもとにレンダラーコンポーネントがあれば
		if (object->renderer)
		{
			ComponentPtr clone = object->renderer->Clone();
			clone->ownerObject = p;
			p->renderer = std::dynamic_pointer_cast<Renderer>(clone);
		}
		// クローンもとにリジッドボディコンポーネントがあれば
		if (object->rigidbody)
		{
			ComponentPtr clone = object->rigidbody->Clone();
			clone->ownerObject = p;
			p->rigidbody = std::dynamic_pointer_cast<Rigidbody>(clone);
		}
		// クローンもとにアニメータコンポーネントがあれば
		if (object->animator)
		{
			ComponentPtr clone = object->animator->Clone();
			clone->ownerObject = p;
			p->animator = std::dynamic_pointer_cast<Animator>(clone);
		}
		// クローン元にImguiコンポーネントがあれば
		if (object->imGuiLayout)
		{
			ComponentPtr clone = object->imGuiLayout->Clone();
			clone->ownerObject = p;
			p->imGuiLayout = std::dynamic_pointer_cast<UI::ImGuiLayout>(clone);
		}
		// クローンもとにカメラコンポーネントがあれば
		if (object->camera)
		{
			ComponentPtr clone = object->camera->Clone();
			clone->ownerObject = p;
			p->camera = std::dynamic_pointer_cast<Camera>(clone);
		}
		// クローンもとにコライダーコンポーネントがあれば
		if (!object->colliders.empty())
		{
			for (auto& x : object->colliders)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->colliders.push_back(std::dynamic_pointer_cast<Collider>(clone));
			}
		}
		// クローンもとにゲームイベントコンポーネントがあれば
		if (!object->gameEvents.empty())
		{
			for (auto& x : object->gameEvents)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->gameEvents.push_back(std::dynamic_pointer_cast<GameEvent>(clone));
			}
		}
		// クローンもとにオウディオソースコンポーネントがあれば
		if (!object->audioSources.empty())
		{
			for (auto& x : object->audioSources)
			{
				ComponentPtr clone = x->Clone();
				clone->ownerObject = p;
				p->audioSources.push_back(std::dynamic_pointer_cast<AudioSource>(clone));
			}
		}

		return p;
	}

	/**
	* 削除予定のコンポーネントを削除
	*/
	void GameObject::DestroyComponent()
	{

	}
}