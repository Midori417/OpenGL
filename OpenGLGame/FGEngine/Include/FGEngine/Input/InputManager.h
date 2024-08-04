/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/ManagerInterface.h"
#include "KeyCode.h"
#include "MouseButton.h"
#include <unordered_map>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	// 先行宣言
	struct Vector2;
	class InputKey;
	class InputMouse;

	/**
	* インプットマネージャー
	* 入力デバイス管理クラス
	*/
	class InputManager : public ManagerInterface, public Singleton<InputManager>
	{
		friend Singleton<InputManager>;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		InputManager() = default;

	private:

		/**
		* インプットマネージャーを初期化
		* 
		* @retval 0		正常に初期化
		* @retval 0以外	エラー発生
		*/
		virtual int Initialize() override;

		/**
		* インプットマネージャーの状態を更新
		*/
		virtual void Update() override;

		/**
		* キーボードデバイスを取得
		*/
		static std::shared_ptr<InputKey> GetInputKey();

		/**
		* マウスデバイスを取得
		*/
		static std::shared_ptr<InputMouse> GetInputMouse();

	public:

		/**
		* キーが押されているかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押している
		* @retval false	押していない
		*/
		static bool GetKey(KeyCode keyCode);

		/**
		* キーが上がったかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		static bool GetKeyUp(KeyCode keyCode);

		/**
		* キーが下がったかを取得
		*
		* @param keyCode 対応しているキー
		*
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		static bool GetKeyDown(KeyCode keyCode);

		/**
		* 何かしらのキーが押されているか取得
		*
		* @retval true 押されている
		* @retval false 押されていない
		*/
		static bool AnyKey();

	public:

		/**
		* マウスの位置を取得
		*/
		static Vector2 GetMousePosition();

		/**
		* マウスのボタンを押しているを取得
		*
		* @param mouseButton 対応しているボタン
		*
		* @retval true	押している
		* @retval false	押していない
		*/
		static bool GetMouseButton(MouseButton mouseButton);

		/**
		* マウスのボタンが上がったかを取得
		*
		* @param mouseButton 対応しているボタン
		*
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		static bool GetMouseButtonUp(MouseButton mouseButton);

		/**
		* マウスのボタンが下がったかを取得
		*
		* @param mouseButton 対応しているボタン
		*
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		static bool GetMouseButtonDown(MouseButton mouseButton);

		/**
		* マウスがクリックしたかを取得
		*
		* @param mouseButton 対応しているボタン
		*
		* @retval true クリックした
		* @retval false クリックしていない
		*/
		static bool GetMouseButtonClick(MouseButton mouseButton);

	private:

		// ウィンドウオブジェクト
		GLFWwindow* window = nullptr;

		// キーボードデバイス
		static std::shared_ptr<InputKey> inputKey;

		// マウスデバイス
		static std::shared_ptr<InputMouse> inputMouse;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
