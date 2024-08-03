/**
* @file GameObject.cpp
*/
#include "GameObject.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* 削除予定のコンポーネントを削除
	*/
	void GameObject::DestroyComponent()
	{
		// コンポーネントを持っていなければ何もしない
		if (components.empty())
		{
			return;
		}

		// 破壊の有無でコンポーネントを分ける
		const auto iter = std::stable_partition(
			components.begin(), components.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });

		// 破棄するものがない
		if (iter == components.end())
		{
			return;
		}

		// コンポーネント配列から削除
		components.erase(iter, components.end());

		// コライダー配列からも削除する
		const auto iter2 = std::remove_if(
			colliders.begin(), colliders.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });

		// コライダー配列から削除
		colliders.erase(iter2, colliders.end());

		// モノビヘイビア配列から削除する
		const auto iter3 = std::stable_partition(
			monoBehaviours.begin(),monoBehaviours.end(),
			[](const auto& p) {return p->GetHideFlag() != HideFlag::Destory; });
		
		// 破棄のモノビヘイビアを別の配列に移動
		std::vector<MonoBehaviourPtr> destorylist(
			std::move_iterator(iter3),
			std::move_iterator(monoBehaviours.end()));

		// モノビヘイビア配列から削除
		monoBehaviours.erase(iter3, monoBehaviours.end());

		// 破棄のモノビヘイビアのOnDestroyを実行
		for (auto x : destorylist)
		{
			x->OnDestory();
		}

		// Transformが破棄予定なら削除
		if (transform->GetHideFlag() == HideFlag::Destory)
		{
			transform = nullptr;
		}

		// Rendererが破棄予定なら削除
		if (renderer->GetHideFlag() == HideFlag::Destory)
		{
			renderer = nullptr;
		}

		// Rigidbodyが破棄予定なら削除
		if (rigidbody->GetHideFlag() == HideFlag::Destory)
		{
			rigidbody = nullptr;
		}

	}
}