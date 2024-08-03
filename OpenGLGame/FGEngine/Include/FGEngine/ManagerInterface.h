/**
* @file ManagerInterface.h
*/
#ifndef FGENGINE_MANAGERINTERFACE_H_INCLUDED
#define FGENGINE_MANAGERINTERFACE_H_INCLUDED
#include <memory>

namespace FGEngine
{
	// 先行宣言
	class EngineCore;

	/**
	* マネージャーの基底クラス
	* このクラスが実体化しないためコンストラクタはprotected
	*/
	class ManagerInterface
	{
		friend EngineCore;
	protected:

		/**
		* デフォルトデストラクタ
		*/
		ManagerInterface() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~ManagerInterface() = default;

	public:

		/**
		* 初期化
		*
		* @retval 0		正常に初期化
		* @retval 0以外	エラー発生
		*/
		virtual int Initialize() { return 0; }

		/**
		* 状態の更新
		*/
		virtual void Update() {}

		/**
		* 終了
		*/
		virtual void Finaliz() {}
	};
	using ManagerInterfacePtr = std::shared_ptr<ManagerInterface>;
}

#endif // !FGENGINE_MANAGERINTERFACE_H_INCLUDED
