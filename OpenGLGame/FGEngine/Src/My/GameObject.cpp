/**
* @file GameObject.cpp
*/
#include "GameObject.h"
#include <algorithm>

namespace FGEngine
{

	/**
	* デストラクタ
	*/
	GameObject::~GameObject()
	{
		// 死ぬ前に親子関係を解除する
		SetParent(nullptr);
		for (auto child : children) {
			child->parent = nullptr;
		}
	}

	/**
	* 最初のUpdateの直前で呼び出される
	*/
	void GameObject::Start()
	{
		for (auto& e : components) {
			if (!e->isStarted) {
				e->Start();
				e->isStarted = true;
			}
		}
	}

	/**
	* 毎フレーム一回呼び出す
	*
	* @param deltaTime	前回の更新からの経過時間
	*/
	void GameObject::Update()
	{
		for (auto& e : components) {
			e->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto& e : components) {
			e->LateUpdate();
		}
		// 破棄予定のコンポーネントを削除する
		RemoveDestroyedComponent();
	}

	/**
	* 衝突が起きたときに呼び出される
	*
	* @param self 衝突したコンポーネント(自分)
	* @param other 衝突したコンポーネント(相手)
	*/
	void GameObject::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
	{
		for (auto& e : components) {
			e->OnCollision(self, other);
		}
	}

	/**
	* 削除されたときに呼び出す
	*/
	void GameObject::OnDestroy()
	{
		for (auto& e : components) {
			e->OnDestroy();
		}
	}

	/**
	* 親オブジェクトを設定する
	*
	* @param parent 親にするゲームオブジェクト
	*/
	void GameObject::SetParent(GameObject* parent)
	{
		// 同じ親をしていされた場合は何もしない
		if (parent == this->parent) {
			return;
		}

		// 別の親がある場合その親との関係を解除する
		if (this->parent) {
			// 自分の位置を検索
			auto& c = this->parent->children;
			auto itr = std::find(c.begin(), c.end(), this);
			if (itr != c.end()) {
				c.erase(itr);	// 配列から自分を削除
			}
		}

		// 新たな親子関係を設定
		if (parent) {
			parent->children.push_back(this);
		}
		this->parent = parent;
	}

	/**
	* 親オブジェクトを設定する
	*
	* @param parent 親にするゲームオブジェクト
	*/
	void GameObject::SetParent(const GameObjectPtr& parent)
	{
		SetParent(parent.get());
	}

	/**
	* ゲームオブジェクトから削除予定のコンポーネントを削除する
	*/
	void GameObject::RemoveDestroyedComponent()
	{
		// コンポーネントを持っていなければ何もしない
		if (components.empty())
		{
			return;
		}

		// 破棄予定の有無でコンポーネントを分ける
		const auto iter = std::stable_partition(
			components.begin(), components.end(),
			[](const auto& p) {return !p->IsDestroyed(); });

		// 破棄予定のコンポーネントを別の配列に移動
		std::vector<ComponentPtr> destroyList(
			std::move_iterator(iter),
			std::move_iterator(components.end()));

		// 配列から移動済みコンポーネントを削除
		components.erase(iter, components.end());

		// コライダーはcollidersにも登録されているので、両方から削除する必要がある
		const auto iter2 = std::remove_if(
			colliders.begin(), colliders.end(),
			[](const auto& p) {return p->IsDestroyed(); });
		colliders.erase(iter2, colliders.end());

		// 破棄予定のコンポーネントのOnDestroyを実行
		for (auto& e : destroyList)
		{
			e->OnDestroy();
		}
	}// ここでdestoryListの寿命がおわり削除される
}