/**
* @file Behaviour.h
*/
#ifndef FGENGINE_BEHAVIOUR_H_INCLUDED
#define FGENGINE_BEHAVIOUR_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* コンポーネントを有効無効機能を追加した基底クラス
	*/
	class Behaviour : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Behaviour() = default;
		virtual ~Behaviour() = default;

		// オブジェクト状態を設定する
		virtual void SetEnable(bool value)
		{
			enabled = value;
		}

		bool GetEnabled() const
		{
			return enabled;
		}


	protected:

		// 有効であれば更新され、無効であれば更新されません
		bool enabled = true;
	};
}

#endif // !FGENGINE_BEHAVIOUR_H_INCLUDED
