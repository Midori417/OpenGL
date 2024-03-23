/**
* @file Object.h
*/
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <memory>
#include <vector>
#include <string>
#include "VecMath.h"

namespace FGEngine
{
	// 先行宣言
	class Object;
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
		GameObjectPtr Instantate(const std::string& name, const TransformPtr& transform);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* オブジェクトの状態を破壊予定にする
		*
		* @param obj 破棄予定にするオブジェクト
		* @parma t	破壊される時間
		*/
		void Destory(Object* obj, float t = 0);

		/**
		* 破棄予定か取得
		* 
		* @return true 破棄予定
		* @return false 破棄予定じゃない
		*/
		bool IsDestroyed() const
		{
			return isDestoryed;
		}

	private:

		std::string name;	// オブジェクトの名前
		bool isDestoryed;	// 破壊予定か
		float destoryTime = 0;	// 破壊時間
		HideFlag hideFlag = HideFlag::None;	// オブジェクトの状態

	};
	using ObjectPtr = std::shared_ptr<Object>;
	using ObjectList = std::vector<ObjectPtr>;
}
#endif // !OBJECT_H_INCLUDED
