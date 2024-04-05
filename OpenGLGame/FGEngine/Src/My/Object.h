/**
* @file Object.h
*/
#ifndef FGENGINE_OBJECT_H_INCLUDED
#define FGENGINE_OBJECT_H_INCLUDED
#include <memory>
#include <vector>
#include <string>
#include "SystemFrd.h"
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Quaternion.h"

namespace FGEngine
{
	// 先行宣言
	class Object;
	using ObjectPtr = std::shared_ptr<Object>;
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;

	/**
	* すべてのオブジェクトの基底クラス
	*/
	class Object
	{
	public:
		
		friend ObjectSystem::ObjectManager;
		
		// コンストラクタ・デストラクタ
		Object() = default;
		virtual ~Object() = default;

		/**
		* オブジェクトの名前を取得する
		*/
		std::string ToString() const;

		/**
		* オブジェクトの名前を設定する
		*
		* @param value 設定する名前
		*/
		void SetName(const std::string& value);


		/**
		* オブジェクトの状態
		*/
		enum class HideFlag
		{
			None,		// 通常
			Destory,	// 破壊
		};

		/**
		* オブジェクトの状態を取得する
		*/
		HideFlag GetHideFlag() const;


		/**
		* オブジェクトを生成する
		*/
		template<typename T>
		std::shared_ptr<T> Instantate(const std::string& name);

		/**
		* ゲームオブジェクトを生成する
		*/
		GameObjectPtr Instantate(const std::string& name);
		GameObjectPtr Instantate(const std::string& name, const Transform& transform);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* オブジェクトの状態を破壊予定にする
		*
		* @param obj 破棄予定にするオブジェクト
		* @parma t	破壊される時間
		*/
		void Destory(ObjectPtr obj, float t = 0);

		/**
		* 破棄予定か取得
		* 
		* @return true 破棄予定
		* @return false 破棄予定じゃない
		*/
		bool IsDestroyed() const
		{
			return isDestroyed;
		}

	private:

		// オブジェクトの名前
		std::string name;

		// 破壊予定か
		bool isDestroyed;

		// オブジェクトの状態
		HideFlag hideFlag = HideFlag::None;

		// 破壊時間
		float destroyTime = 0;
	};
	using ObjectList = std::vector<ObjectPtr>;
}
#endif // !OBJECT_H_INCLUDED
