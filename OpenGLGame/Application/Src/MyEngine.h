/**
* @file MyEngine.h
* ���̃w�b�_�[��ǂݍ��񂾂�G���W���̂��炩���̋@�\���g����
*/
#ifndef MYENGINE_H_INCLUDED
#define MYENGINE_H_INCLUDED

// ========================
//
// �G���W���n
//
// ========================

// ���C���G���W��
#include "Engine/Engine.h"

// ========================
//
// �f�o�b�O�n
//
// ========================

#include "Engine/Debug.h"

// ========================
//
// ���w�n
//
// ========================

// ����
#include "Engine/Time.h"

// �񎟌��x�N�g��
#include "Engine/Vector2.h"

// �O�����x�N�g��
#include "Engine/Vector3.h"

// �l�����x�N�g��
#include "Engine/Vector4.h"

// �x�N�g���܂Ƃ�
#include "Engine/VectorPoint.h"

// 4x4�s��
#include "Engine/Matrix4x4.h"

// 3x3�s��
#include "Engine/Matrix3x3.h"

// �N�H�[�^�j�I��
#include "Engine/Quaternion.h"

// ========================
//
// �I�u�W�F�N�g�n
//
// ========================

// �Q�[���I�u�W�F�N�g
#include "Engine/GameObject.h"

// ======== Component =========== //

// �I�u�W�F�N�g�ɋ@�\����������
#include "Engine/Component.h"

// �R���|�[�l���g�̃w���p�[
#include "Engine/ComponentHelper.h"

// ImGUI���g����UI�̊��N���X
#include "Engine/ImGuiUI.h"

// �摜UI
#include "Engine/Image.h"

#include "Engine/Text.h"

// �ړ��A��]�A�g��k��
#include "Engine/Transform.h"

// �d��
#include "Engine/ChracterMovement.h"

// AABB�̏Փ�
#include "Engine/AabbCollider.h"

// Sphere�̏Փ�
#include "Engine/SphereCollider.h"

// Box�̏Փ�
#include "Engine/BoxCollider.h"

#include "Engine/Renderer.h"

#include "Engine/MeshRenderer.h"

#include "Engine/GltfMeshRenderer.h"

#include "Engine/GltfAnimatednMeshRenderer.h"

// ========================
//
// ImGui
//
// ========================

#include "Engine/ImGui/imgui.h"

// ========================
//
// ���͌n
//
// ========================

// �L�[�{�[�h�E�}�E�X����
#include "Engine/Input.h"

// �Q�[���p�b�h(�R���g���[��)����
#include "Engine/GamePad.h"

// ========================
//
// �V�[���n
//
// ========================

// �V�[��
#include "Engine/Scene.h"

// �V�[���}�l�[�W���[
#include "Engine/SceneManager.h"

// ========================
//
// �O���t�B�b�N�n
//
// ========================

// �F
#include "Engine/Color.h"

// ���b�V��
#include "Engine/Mesh.h"

// �e�N�X�`��
#include "Engine/Texture.h"

// �}�e���A��
#include "Engine/Material.h"

// ========================
//
// �T�E���h�n
//
// ========================

// �T�E���h
#include "Engine/EasyAudio.h"

// �T�E���h���X�g
#include "Engine/AudioSettings.h"

#endif // !MYENGINE_H_INCLUDED
