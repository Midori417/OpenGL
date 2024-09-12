/**
* @file Component.h
*/
#ifndef FGENGINE_COMPONENT_H_INCLUDED
#define FGENGINE_COMPONENT_H_INCLUDED
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingMath.h"
#include "FGEngine/UsingNames/UsingScene.h"
#include <string>

namespace FGEngine
{
	/**
	* コンポーネントの基底クラス
	*/
	class Component
	{
		friend GameObject;
	protected:	// このクラスは実体化しない

		/**
		* デフォルトコンストラクタ
		*/
		Component() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~Component() = default;

	public:

		/**
		* 自身を所有しているオブジェクトを取得
		*/
		GameObjectPtr OwnerObject() const;

		/**
		* トランスフォームを取得
		*/
		TransformPtr GetTransform() const;

		/**
		* Tagを取得
		*/
		std::string GetTag() const;

		/**
		* T型のコンポーネントを取得
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* 破棄予定か取得
		*
		* @return true 破棄予定
		* @return false 破棄予定じゃない
		*/
		bool IsDestroyed() const;

	public:	// オブジェクトの生成

		/**
		* typeにあったオブジェクトを生成する
		*
		* @param type 生成したいオブジェクトのタイプ
		* namespace CreateObjectから選択推奨
		*
		* @return 生成したオブジェクト
		*/
		GameObjectPtr Instantate(const std::string& type);

		/**
		* typeにあったオブジェクトを生成する
		*
		* @param type 生成したいオブジェクトのタイプ
		* namespace CreateObjectから選択推奨
		* @param position 位置
		* @param rotation 回転
		*
		* @return 生成したオブジェクト
		*/
		GameObjectPtr Instantate(const std::string& type, const Vector3& position, const Quaternion& rotation);

		/**
		* gameObjectのクローンを作成
		* 
		* @param gameObject クローンもとのゲームオブジェクト
		* 
		* @return 生成したゲームオブジェクト
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject);

		/**
		* gameObjectのクローンを作成
		*
		* @param gameObject クローン元のゲームオブジェクト
		* @param transform	クローンするトランスフォーム
		*
		* @return 作成したゲームオブジェクト
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject, const TransformPtr& tranform);

		/**
		* gameObjectのクローンを作成
		*
		* @param gameObject クローン元のゲームオブジェクト
		* @param position	クローンした時の位置
		* @param rotation	クローンした時の回転
		*
		* @return 作成したゲームオブジェクト
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation);

	protected:

		/**
		* コンポーネントのクローンを作成する
		*/
		virtual ComponentPtr Clone() const = 0;

	private:

		// コンポーネントの所有オブジェクト
		std::weak_ptr<GameObject> ownerObject;

		// trueなら破壊予定
		bool isDestroyed = false;
	};
}
#endif // !FGENGINE_COMPONENT_H_INCLUDED