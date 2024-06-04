/**
* @file MonoBehaviour.h
*/
#ifndef FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#define FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#include "Behaviour.h"

namespace FGEngine
{
	// 先行宣言
	class Collision;
	using CollisionPtr = std::shared_ptr<Collision>;

	/**
	* ゲームイベント基底コンポーネント
	*/
	class MonoBehaviour : public Behaviour
	{
	public:

		friend ObjectSystem::ObjectManager;

		// コンストラクタ・デストラクタ
		MonoBehaviour() = default;
		virtual ~MonoBehaviour() = default;

		// 生成時に実行
		virtual void Awake() {}

		// Updateが始める前に一度実行
		virtual void Start() {}

		// 毎フレーム実行
		virtual void Update() {}

		// Updateの後に実行
		virtual void LateUpdate() {}

		// オブジェクトを破壊時に実行
		virtual void OnDestory() {}

		// オブジェクトが有効・アクティブになった時に実行
		virtual void OnEnable() {}

		// オブジェクトが無効になった時に実行
		virtual void OnDisable() {}

		// 他のコリジョンに触れたときに実行
		virtual void OnCollisionEnter(const CollisionPtr other) {}

		// 他のコリジョンから離れたときに実行
		virtual void OnCollisionExit(const CollisionPtr other) {}

		// 他のコリジョンに触れ続けているときに実行
		virtual void OnCollisionStay(const CollisionPtr ohter) {}

		// (Trigger)他のコリジョンに触れたときに実行
		virtual void OnTriggerEnter(const CollisionPtr other) {}

		// (Trigger)他のコリジョンから離れたときに実行
		virtual void OnTriggerExit(const CollisionPtr other) {}

		// (Trigger)他のコリジョンに触れ続けているときに実行
		virtual void OnTriggerStay(const CollisionPtr ohter) {}

		// オブジェクト状態を設定する
		virtual void SetEnable(bool value)
		{
			enabled = value;
			if (enabled)
			{
				OnEnable();
			}
			else
			{
				OnDisable();
			}
		}

	private:

		// Startを実行したか
		bool isStart = false;
	};
	using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;
}
#endif // !FGENGINE_MONOBEHAVIOUR_H_INCLUDED
