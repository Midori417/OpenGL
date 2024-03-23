/**
* @file Input.cpp
*/
#include "Input.h"
#include <GLFW/glfw3.h>
#include "VecMath.h"
#include "Time.h"

namespace FGEngine
{
	StKeyState Input::keyState[] = { StKeyState() };
	MouseButtonState Input::mouseButtonsState[] = { MouseButtonState() };
	Vector2 Input::mousePosition = Vector2(0, 0);
	Vector2 Input::mousePosAxis = Vector2(0, 0);
	std::unordered_map<std::string, float> Input::axis;


	void Input::AxisSet(const std::string& axisName)
	{
		axis.emplace(axisName, 0.0f);
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="window"></param>
	void Input::Update(GLFWwindow* window)
	{
		// === Key === //
		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;

			keyState[i].on = now;
			keyState[i].down = now && !keyState[i].old;
			keyState[i].up = !now && keyState[i].old;

			keyState[i].old = now;
		}

		// == MousePos == //
		{
			// スクリーン座標系のカーソル座標を取得する
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			// 戻り型に合わせるためにfloatにキャスト
			const Vector2 pos{ static_cast<float>(x),static_cast<float>(y) };

			// UILayoutの座標系に合わせるために、スクリーン座標系からカメラ座標系(Z=-1)に変換する
			int w, h;
			glfwGetFramebufferSize(window, &w, &h); // 画面のサイズを取得
			const Vector2 framebufferSize{ static_cast<float>(w),static_cast<float>(h) }; // 変換
			const float aspectRatio = framebufferSize.x / framebufferSize.y;	// アスペクト比

			// カメラ座標系のマウス座標.x = ((スクリーン座標系のマウス座標.x / 画面サイズ.x) * 2 - 1) * アスペクト比
			// カメラ座標系のマウス座標.y = ((スクリーン座標系のマウス座標.y / 画面サイズ.y) * 2 - 1) * -1
			// -1 をかけてるのはY軸の方向が逆だから
			mousePosition = Vector2((pos.x / framebufferSize.x * 2 - 1) * aspectRatio, (pos.y / framebufferSize.y * 2 - 1) * -1);
		}

		// == MouseButton == //
		for (int i = 0; i < (int)MouseButton::Max; ++i)
		{
			mouseButtonsState[i].previous = mouseButtonsState[i].current;

			const bool now = glfwGetMouseButton(window, MOUSEBUTTON_ASSIGN[i]) == GLFW_PRESS;
			mouseButtonsState[i].current = now;
			// 押されている時間を更新
			if (mouseButtonsState[i].previous) {
				mouseButtonsState[i].timer += Time::deltaTime();
			}
			else {
				mouseButtonsState[i].timer = 0;
			}
			// 以下の条件をすべて満たす場合はクリックと判定
			// - 前フレームで押されている
			// - 現在のフレームで押されていない
			// - 押されている時間が0.3秒以下
			if (mouseButtonsState[i].previous && !mouseButtonsState[i].current && mouseButtonsState[i].timer <= mouseClickSpeed)
			{
				mouseButtonsState[i].click = true;
			}
			else
			{
				mouseButtonsState[i].click = false;
			}

			mouseButtonsState[i].on = now;
			mouseButtonsState[i].down = now && !mouseButtonsState[i].old;
			mouseButtonsState[i].up = !now && mouseButtonsState[i].old;

			mouseButtonsState[i].old = now;

		}
		// Axis (修正したい)
		{
			auto horizontal = axis.find("Horizontal");
			if (GetKey(KeyCode::D) || GetKey(KeyCode::RightArrow)) {
				horizontal->second = 1.0f;
			}
			else if (GetKey(KeyCode::A) || GetKey(KeyCode::LeftArrow)) {
				horizontal->second = -1.0f;
			}
			else if (!GetKey(KeyCode::D) && !GetKey(KeyCode::RightArrow) && !GetKey(KeyCode::A) && !GetKey(KeyCode::LeftArrow)) {
				horizontal->second = 0;
			}


			auto vertical = axis.find("Vertical");
			if (GetKey(KeyCode::W) || GetKey(KeyCode::UpArrow)) {
				vertical->second = 1.0f;
			}
			else if (GetKey(KeyCode::S) || GetKey(KeyCode::DownArrow)) {
				vertical->second = -1.0f;
			}
			else if (!GetKey(KeyCode::W) && !GetKey(KeyCode::UpArrow) && !GetKey(KeyCode::S) && !GetKey(KeyCode::DownArrow)) {
				vertical->second = 0;
			}

		}
	}

	/// <summary>
	/// keyCodeに指定されたキーが押されているか
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns>
	/// true　押されている
	/// falsae 押されていない
	/// </returns>
	bool Input::GetKey(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].on;
	}

	/// <summary>
	/// KeyCodeに指定されたキーが下がったら
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	bool Input::GetKeyDown(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].down;
	}

	/// <summary>
	/// KeyCodeに指定されたキーが上がったら
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	bool Input::GetKeyUp(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].up;
	}

	bool Input::GetKetSpeedPush(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].push;
	}

	/// <summary>
	/// マウスカーソルの座標を取得する
	/// </summary>
	/// <returns>カメラ座標系のカーソル座標</returns>
	Vector2 Input::GetMousePosition()
	{
		return mousePosition;
	}


	bool Input::GetMouseButton(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].on;
	}

	bool Input::GetMouseButtonUp(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].up;
	}

	bool Input::GetMouseButtonDown(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].down;
	}

	bool Input::GetMouseButtonClick(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].click;
	}

	/**
	*
	*/
	float Input::GetAxis(const std::string& axisName)
	{
		auto itr = axis.find(axisName);
		if (itr != axis.end()) {
			return itr->second;
		}
		return 0.0f;
	}
}