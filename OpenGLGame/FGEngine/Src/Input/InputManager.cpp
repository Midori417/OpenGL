/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include "FGEngine/Debug/Debug.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// 静的変数の初期化
	std::shared_ptr<InputKey> InputManager::inputKey = nullptr;
	std::shared_ptr<InputMouse> InputManager::inputMouse = nullptr;

	/**
	* インプットマネージャを初期化
	* 
	* @retval 0		正常に初期化
	* @retval 0以外	エラー発生
	*/
	int InputManager::Initialize()
	{
		// キーボードデバイス生成
		inputKey = std::shared_ptr<InputKey>(new InputKey{});
		if (inputKey->Initialize() != 0)
		{
			LOG_ERROR("キーボードデバイスの初期化に失敗");
			return 1;
		}

		// マウスデバイス生成
		inputMouse = std::shared_ptr<InputMouse>(new InputMouse{});
		if (inputMouse->Initialize() != 0)
		{
			LOG_ERROR("マウスデバイスの初期化に失敗");
			return 1;
		}

		// 初期化成功
		return 0;
	}

	/**
	* インプットマネージャを更新
	*/
	void InputManager::Update()
	{
		if (!window)
		{
			LOG_WARNINGS("(InputManger)ウィンドウオブジェクトが存在しません");
			return;
		}

		// 入力デバイスの状態を更新

		if (inputKey)
		{
			inputKey->Update(window);
		}

		if (inputMouse)
		{
			inputMouse->Update(window);
		}
	}

	/**
	* キーボードデバイスを取得
	*/
	std::shared_ptr<InputKey> InputManager::GetInputKey()
	{
		if (!inputKey)
		{
			LOG_ERROR("キーボードデバイスが存在しません");
			return nullptr;
		}
		return inputKey;
	}

	/**
	* マウスデバイスを取得
	*/
	std::shared_ptr<InputMouse> InputManager::GetInputMouse()
	{
		if (!inputMouse)
		{
			LOG_ERROR("マウスデバイスが存在しません");
			return nullptr;
		}
		return inputMouse;
	}

#pragma region Key

	/**
	* キーが押されているかを取得
	*
	* @param keyCode 対応しているキー
	*
	* @retval true	押している
	* @retval false	押していない
	*/
	bool InputManager::GetKey(KeyCode keyCode)
	{
		return GetInputKey()->GetKey(keyCode);
	}

	/**
	* キーが上がったかを取得
	*
	* @param keyCode 対応しているキー
	*
	* @retval true	押しあがっている
	* @retval false	押し上げっていない
	*/
	bool InputManager::GetKeyUp(KeyCode keyCode)
	{
		return GetInputKey()->GetKeyUp(keyCode);
	}

	/**
	* キーが下がったかを取得
	*
	* @param keyCode 対応しているキー
	*
	* @retval true	押し下がった
	* @retval false	押し下がっていない
	*/
	bool InputManager::GetKeyDown(KeyCode keyCode)
	{
		return GetInputKey()->GetKeyDown(keyCode);
	}

	/**
	* 何かしらのキーが押されているか取得
	*
	* @retval true 押されている
	* @retval false 押されていない
	*/
	bool InputManager::AnyKey()
	{
		return GetInputKey()->AnyKey();
	}

#pragma endregion

#pragma region Mouse

	/**
	* マウスの位置を取得
	*/
	Vector2 InputManager::GetMousePosition()
	{
		return GetInputMouse()->GetMousePosition();
	}

	/**
	* マウスのボタンを押しているを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押している
	* @retval false	押していない
	*/
	bool InputManager::GetMouseButton(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButton(mouseButton);
	}

	/**
	* マウスのボタンが上がったかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押しあがっている
	* @retval false	押し上げっていない
	*/
	bool InputManager::GetMouseButtonUp(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonUp(mouseButton);
	}

	/**
	* マウスのボタンが下がったかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押し下がった
	* @retval false	押し下がっていない
	*/
	bool InputManager::GetMouseButtonDown(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonDown(mouseButton);
	}

	/**
	* マウスがクリックしたかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true クリックした
	* @retval false クリックしていない
	*/
	bool InputManager::GetMouseButtonClick(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonClick(mouseButton);
	}

#pragma endregion
}