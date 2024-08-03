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
	std::vector<InputInterfacePtr> InputManager::inputDevices;

	/**
	* 入力デバイスの種類
	*/
	enum InputDeviceType
	{
		// キーボード
		Key,

		// マウス
		Mouse,
	};

	/**
	* インプットマネージャを初期化
	* 
	* @retval 0		正常に初期化
	* @retval 0以外	エラー発生
	*/
	int InputManager::Initialize()
	{
		// キーボードデバイスを追加
		if(AddDevice(std::make_shared<InputKey>()) != 0)
		{
			LOG_ERROR("キーボードデバイスの追加に失敗");
			return 1;
		}
		// マウスデバイスを追加
		if (AddDevice(std::make_shared<InputMouse>()) != 0)
		{
			LOG_ERROR("マウスデバイスの追加に失敗");
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
		// デバイスの状態を更新
		for (auto& x : inputDevices)
		{
			x->Update(window);
		}
	}

	/**
	* 入力デバイスを追加
	*
	* @param inputDeviec 追加するデバイス
	*
	* @retval 0		追加成功
	* @retval 0以外	エラー発生
	*/
	int InputManager::AddDevice(InputInterfacePtr inputDevice)
	{
		// デバイスを初期化
		int result = inputDevice->Initialize();

		if (result != 0)
		{
			// デバイスの初期化に失敗
			return result;
		}

		// デバイスを配列に追加
		inputDevices.push_back(inputDevice);

		return 0;
	}

	/**
	* キーボードデバイスを取得
	*/
	std::shared_ptr<InputKey> InputManager::GetKeyDevice()
	{
		auto inputKey = std::dynamic_pointer_cast<InputKey>(inputDevices[InputDeviceType::Key]);
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
	std::shared_ptr<InputMouse> InputManager::GetMouseDevice()
	{
		auto inputMouse = std::dynamic_pointer_cast<InputMouse>(inputDevices[InputDeviceType::Mouse]);
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
		return GetKeyDevice()->GetKey(keyCode);
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
		return GetKeyDevice()->GetKeyUp(keyCode);
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
		return GetKeyDevice()->GetKeyDown(keyCode);
	}

	/**
	* 何かしらのキーが押されているか取得
	*
	* @retval true 押されている
	* @retval false 押されていない
	*/
	bool InputManager::AnyKey()
	{
		return GetKeyDevice()->AnyKey();
	}

#pragma endregion

#pragma region Mouse

	/**
	* マウスの位置を取得
	*/
	Vector2 InputManager::GetMousePosition()
	{
		return GetMouseDevice()->GetMousePosition();
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
		return GetMouseDevice()->GetMouseButton(mouseButton);
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
		return GetMouseDevice()->GetMouseButtonUp(mouseButton);
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
		return GetMouseDevice()->GetMouseButtonDown(mouseButton);
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
		return GetMouseDevice()->GetMouseButtonClick(mouseButton);
	}

#pragma endregion
}