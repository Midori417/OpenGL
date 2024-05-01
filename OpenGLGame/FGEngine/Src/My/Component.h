/**
* @file Component.h
*/
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include <memory>

// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
class Component;
using ComponentPtr = std::shared_ptr<Component>;
class Transform;

/**
* コンポーネントの基底クラス
*/
class Component
{
	friend GameObject;
public:

	Component() = default;
	virtual ~Component() = default;

	// コンポーネントの所有者
	GameObject* GetGameObject() const {
		return gameObject;
	}

	// コンポーネントをゲームオブジェクトから削除する
	void Desotroy() {
		isDestroyed = true;
	}

	// コンポーネントが破棄予定か取得する trueだと破棄予定
	bool IsDestroyed() const {
		return isDestroyed;
	}

	// 自身の所有者のコンポーネントを取得
	template<class T>
	inline std::shared_ptr<T> GetComponent() const;

	// 親のコンポーネントを取得
	template<class T>
	inline std::shared_ptr<T> GetComponentParent() const;

	// 子供のコンポーネントを取得
	template<class T>
	inline std::shared_ptr<T> GetComponentChildren()const;

	// ゲームオブジェクトに追加されたときから呼び出される
	virtual void Awake() {}

	// 最初のUpdateの直前で呼び出される
	virtual void Start() {}

	// 毎フレーム一回呼び出される
	virtual void Update() {}

	// 毎フレーム一回呼び出される(Updateよりあと)
	virtual void LateUpdate() {}

	// 衝突が起きたときに呼び出される
	virtual void OnCollision(const ComponentPtr& slef, const ComponentPtr& other) {}

	// ゲームオブジェクトがエンジンが削除されるときの呼び出される
	virtual void OnDestroy() {}

public:

	Transform* transform = nullptr;

private:

	GameObject* gameObject = nullptr; // コンポーネントの所有者
	bool isActive = true;
	bool isStarted = false;		// Startが実行されたらtrueになる
	bool isDestroyed = false;	// Destroyが実行されたらtrueになる
};
#endif // !COMPONENT_H_INCLUDED
