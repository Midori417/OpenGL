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
	/// �X�V����
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
			// �X�N���[�����W�n�̃J�[�\�����W���擾����
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			// �߂�^�ɍ��킹�邽�߂�float�ɃL���X�g
			const Vector2 pos{ static_cast<float>(x),static_cast<float>(y) };

			// UILayout�̍��W�n�ɍ��킹�邽�߂ɁA�X�N���[�����W�n����J�������W�n(Z=-1)�ɕϊ�����
			int w, h;
			glfwGetFramebufferSize(window, &w, &h); // ��ʂ̃T�C�Y���擾
			const Vector2 framebufferSize{ static_cast<float>(w),static_cast<float>(h) }; // �ϊ�
			const float aspectRatio = framebufferSize.x / framebufferSize.y;	// �A�X�y�N�g��

			// �J�������W�n�̃}�E�X���W.x = ((�X�N���[�����W�n�̃}�E�X���W.x / ��ʃT�C�Y.x) * 2 - 1) * �A�X�y�N�g��
			// �J�������W�n�̃}�E�X���W.y = ((�X�N���[�����W�n�̃}�E�X���W.y / ��ʃT�C�Y.y) * 2 - 1) * -1
			// -1 �������Ă�̂�Y���̕������t������
			mousePosition = Vector2((pos.x / framebufferSize.x * 2 - 1) * aspectRatio, (pos.y / framebufferSize.y * 2 - 1) * -1);
		}

		// == MouseButton == //
		for (int i = 0; i < (int)MouseButton::Max; ++i)
		{
			mouseButtonsState[i].previous = mouseButtonsState[i].current;

			const bool now = glfwGetMouseButton(window, MOUSEBUTTON_ASSIGN[i]) == GLFW_PRESS;
			mouseButtonsState[i].current = now;
			// ������Ă��鎞�Ԃ��X�V
			if (mouseButtonsState[i].previous) {
				mouseButtonsState[i].timer += Time::deltaTime();
			}
			else {
				mouseButtonsState[i].timer = 0;
			}
			// �ȉ��̏��������ׂĖ������ꍇ�̓N���b�N�Ɣ���
			// - �O�t���[���ŉ�����Ă���
			// - ���݂̃t���[���ŉ�����Ă��Ȃ�
			// - ������Ă��鎞�Ԃ�0.3�b�ȉ�
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
		// Axis (�C��������)
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
	/// keyCode�Ɏw�肳�ꂽ�L�[��������Ă��邩
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns>
	/// true�@������Ă���
	/// falsae ������Ă��Ȃ�
	/// </returns>
	bool Input::GetKey(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].on;
	}

	/// <summary>
	/// KeyCode�Ɏw�肳�ꂽ�L�[������������
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
	/// KeyCode�Ɏw�肳�ꂽ�L�[���オ������
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
	/// �}�E�X�J�[�\���̍��W���擾����
	/// </summary>
	/// <returns>�J�������W�n�̃J�[�\�����W</returns>
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