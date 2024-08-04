/**
* @file InputKey.h
*/
#ifndef FGENGINE_INPUTKEY_H_INCLUDED
#define FGENGINE_INPUTKEY_H_INCLUDED
#include <vector>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	// 先行宣言
	enum class KeyCode;

	/**
	* キーボード入力
	* 入力管理クラスのみ生成したいのでコンストラクタはprivate
	*/
	class InputKey
	{
		friend class InputManager;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		InputKey() = default;

	private:

		/**
		* キー入力を初期化
		* 
		* @retval 0		初期化成功
		* @retval 0以外	初期化失敗
		*/
		int Initialize();

		/**
		* キーボードの状態を更新
		*
		* @param window ウィンドウオブジェクト
		*/
		void Update(GLFWwindow* window);

	private:

		/**
		* キーが押されているかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押している
		* @retval false	押していない
		*/
		bool GetKey(KeyCode keyCode) const;

		/**
		* キーが上がったかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		bool GetKeyUp(KeyCode keyCode) const;

		/**
		* キーが下がったかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		bool GetKeyDown(KeyCode keyCode) const;

		/**
		* 何かしらのキーが押されているか取得
		* 
		* @retval true 押されている
		* @retval false 押されていない
		*/
		bool AnyKey() const;

	private:

		/**
		* キーの状態
		*/
		struct KeyState
		{
			// 前回のフレームに押されていたかの有無
			// true=押されていた : false=押されていない
			bool old = false;

			//	キーが下がったかの有無
			// true=下がった : false=下がっていない
			bool down = false;

			// キーが上がったかの有無
			// true=上がった : false=上がっていない
			bool up = false;

			// キーが押されているかの有無
			// true=押されている : false=押されていない
			bool on = false;
		};

		// キーの状態配列
		std::vector<KeyState> keyState;

		// 何かしらのキーが押されていたらtrue:何も押されていなければfasle
		bool isAnyKey = false;
	};
}

#endif // !FGENGINE_INPUTKEY_H_INCLUDED
