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

// ��s�錾
class Engine;
struct Vector2;

/// <summary>
/// ���̓N���X
/// </summary>
class Input
{
	friend Engine;
public:

private:
	// �L�[�̏��
	static StKeyState keyState[(int)KeyCode::Max];
	static constexpr float keyPushSpeed = 0.3f;
	// �}�E�X�̏��
	static MouseButtonState mouseButtonsState[(int)MouseButton::Max];
	// �}�E�X�̈ʒu
	static Vector2 mousePosition;
	// �}�E�X�̃N���b�N��t����
	static constexpr float mouseClickSpeed = 0.3f;
	static Vector2 mousePosAxis;

	static std::unordered_map<std::string, float> axis;

private:

	Input() = default;
	~Input() = default;

private:

	static void AxisSet(const std::string& axisName);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="window"></param>
	static void Update(GLFWwindow* window);

public:

	// == key == //

	/// <summary>
	/// keyCode�Ɏw�肳�ꂽ�L�[��������Ă��邩
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns>
	/// true�@������Ă���
	/// falsae ������Ă��Ȃ�
	/// </returns>
	static bool GetKey(KeyCode keyCode);

	/// <summary>
	/// KeyCode�Ɏw�肳�ꂽ�L�[������������
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	static bool GetKeyDown(KeyCode keyCode);

	/// <summary>
	/// KeyCode�Ɏw�肳�ꂽ�L�[���オ������
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	static bool GetKeyUp(KeyCode keyCode);

	static bool GetKetSpeedPush(KeyCode keyCode);
	// == Mouse == //

	/// <summary>
	/// �}�E�X�J�[�\���̍��W���擾����
	/// </summary>
	/// <returns>�J�������W�n�̃J�[�\�����W</returns>
	static Vector2 GetMousePosition();

	static bool GetMouseButton(MouseButton mouseButton);
	static bool GetMouseButtonUp(MouseButton mouseButton);
	static bool GetMouseButtonDown(MouseButton mouseButton);
	static bool GetMouseButtonClick(MouseButton mouseButton);

	// ========= Axis ======= //
	static float GetAxis(const std::string& axisName);
};

#endif // !INPUT_H_INCLUDED
