/**
* @file GameObject.h
*/
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "Renderer.h"
#include "Collision.h"
#include "Texture.h"
#include "VecMath.h"
#include "Color.h"

#include <string>
#include <vector>
#include <memory>
#include <type_traits>


// 先行宣言
class Engine;
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = std::vector<GameObjectPtr>;
class Transform;
using TransformPtr = std::shared_ptr<Transform>;

/**
* 描画の順序
*/
enum RenderQueue
{
	RenderQueue_geometry = 2000,	// 一般的な図形
	RenderQueue_transparent = 3000,	// 半透明な図形
	RenderQueue_overlay = 4000,		// UI、全画面エフェクト
	RenderQueue_max = 5000,			// キューの最大値
};

/**
* ゲームに登場する様々なオブジェクトの基本クラス
*/
class GameObject : public Object
{
	friend Engine;
public:

	GameObject() = default;
	virtual ~GameObject();

	// コピーと代入を禁止
	GameObject(GameObject&) = delete;
	GameObject& operator=(GameObject&) = delete;

	// === イベント制御 === //

	// 最初のUpdateの直前で呼び出される
	virtual void Start();

	// 毎フレーム一回呼び出す
	virtual void Update();

	virtual void LateUpdate();

	// 衝突したときに呼び出す
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other);

	// 削除されたときの呼び出す
	virtual void OnDestroy();

	// 親オブジェクトを取得する
	GameObject* GetParent() const {
		return parent;
	}

	// 親オブジェクトを設定する
	void SetParent(GameObject* parent);
	void SetParent(const GameObjectPtr& parent);

	// 子オブジェクトの数を取得する
	size_t GetChildCount() const {
		return children.size();
	}

	// 子オブジェクトを取得する
	GameObject* GetChild(size_t index)const {
		return children[index];
	}


	// ゲームオブジェクトにコンポーネントを追加する
	template<class T>
	std::shared_ptr<T> AddComponent() 
	{
		auto p = std::make_shared<T>();
		if constexpr (std::is_base_of_v<Collider, T>) {
			colliders.push_back(p);
		}
		if constexpr (std::is_base_of_v<Renderer, T>)
		{
			renderer = p;
		}
		if constexpr (std::is_base_of_v<Transform, T>)
		{
			transform = p;
		}
		p->gameObject = this;
		p->transform = transform.get();
		components.push_back(p);
		p->Awake();
		return p;
	}

	// コンポーネントを検索する
	template<class T>
	std::shared_ptr<T> GetComponent() const {
		for (auto& e : components) {
			// shared_ptrの場合はdynamic_castでなくdynamic_pointer_castを使う
			auto p = std::dynamic_pointer_cast<T>(e);
			if (p) {
				return p;
			}
		}
		return nullptr;
	}

	// 自分の親のオブジェクトのコンポーネントを検索
	template<class T>
	std::shared_ptr<T> GetComponentParent() const {
		if (parent == nullptr) {
			return nullptr; // 親がいない
		}
		return parent->GetComponent<T>();
	}


	// 自分の子供のオブジェクトのコンポーネントを検索
	template<class T>
	std::shared_ptr<T> GetComponenChildren() const {
		if (children.empty()) {
			return nullptr; // 子供がいない
		}
		for (auto x : children) {
			
			auto t = x->GetComponent<T>();
			// コンポーネントが見つかったら抜ける
			if (t != nullptr) {
				return t;
			}
		}
		return nullptr; // 見つからなかった
	}

	// ゲームオブジェクトから破棄予定のコンポーネントを削除する
	void RemoveDestroyedComponent();


public:

	std::string tag = "Untagged";			// タグ
	TransformPtr transform;
	RendererPtr renderer;
	int renderQueue = RenderQueue_geometry;	// 描画順
	bool isGrounded = false;			// 足場となる物体の上に載っているとtrue

private:

	Engine* engine = nullptr;				// エンジンのアドレス
	bool isActive = true;
	bool isDestroyed = false;				// 死亡フラグ
	GameObject* parent = nullptr;			// 親オブジェクト
	std::vector<GameObject*> children;		// 子オブジェクト
	std::vector<ComponentPtr> components;	// コンポーネント配列
	std::vector<ColliderPtr> colliders;	// コライダー配列

public:

	// ゲームエンジンを取得
	Engine* GetEngine() const 
	{
		return engine;
	}

	// ゲームオブジェクトをエンジンから削除する
	void Destory()
	{
		isDestroyed = true;
	}

	// ゲームオブジェクトが破棄されているかを取得 破棄されていたtrue
	bool IsDestroyed() const
	{
		return isDestroyed;
	}

};
#endif // !GAMEOBJECT_H_INCLUDED
