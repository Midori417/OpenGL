/**
* @file Input.h
*/
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "InputHelper.h"
#include "KeyCode.h"
#include <unordered_map>
#include "String.h"
#include <string>

// 先行宣言
class Engine;
struct Vector2;

/// <summary>
/// 入力クラス
/// </summary>
class Input
{
	friend Engine;
public:

private:
	// キーの状態
	static StKeyState keyState[(int)KeyCode::Max];
	static constexpr float keyPushSpeed = 0.3f;
	// マウスの状態
	static MouseButtonState mouseButtonsState[(int)MouseButton::Max];
	// マウスの位置
	static Vector2 mousePosition;
	// マウスのクリック受付時間
	static constexpr float mouseClickSpeed = 0.3f;
	static Vector2 mousePosAxis;

	static std::unordered_map<std::string, float> axis;

private:

	Input() = default;
	~Input() = default;

private:

	static void AxisSet(const std::string& axisName);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="window"></param>
	static void Update(GLFWwindow* window);

public:

	// == key == //

	/// <summary>
	/// keyCodeに指定されたキーが押されているか
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns>
	/// true　押されている
	/// falsae 押されていない
	/// </returns>
	static bool GetKey(KeyCode keyCode);

	/// <summary>
	/// KeyCodeに指定されたキーが下がったら
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	static bool GetKeyDown(KeyCode keyCode);

	/// <summary>
	/// KeyCodeに指定されたキーが上がったら
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	static bool GetKeyUp(KeyCode keyCode);

	static bool GetKetSpeedPush(KeyCode keyCode);
	// == Mouse == //

	/// <summary>
	/// マウスカーソルの座標を取得する
	/// </summary>
	/// <returns>カメラ座標系のカーソル座標</returns>
	static Vector2 GetMousePosition();

	static bool GetMouseButton(MouseButton mouseButton);
	static bool GetMouseButtonUp(MouseButton mouseButton);
	static bool GetMouseButtonDown(MouseButton mouseButton);
	static bool GetMouseButtonClick(MouseButton mouseButton);

	// ========= Axis ======= //
	static float GetAxis(const std::string& axisName);
};

#endif // !INPUT_H_INCLUDED
