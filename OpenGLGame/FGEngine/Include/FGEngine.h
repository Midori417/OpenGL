/**
* @file MyEngine.h
*/
#pragma once

// ===================
//
// Mathf | ���w�֘A
//
// ===================

#include "FGEngine/Math/Math.h"

// ����
#include "FGEngine/Time.h"
#include <time.h>

// ����
#include "FGEngine/Math/Random.h"

// ===================
//
// Color | �F
//
// ===================

// RGBA
#include "FGEngine/Color.h"

// ===================
//
// Other | ���̑��֗��@�\
//
// ===================

// �V���O���g��
#include "FGEngine/Singleton.h"

// ===================
//
// DebugSystem | �f�o�b�O�V�X�e��
//
// ===================

// �f�o�b�O
#include "FGEngine/Debug.h"

// ===================
//
// Object | �I�u�W�F�N�g�֘A
//
// ===================

// �}�e���A��
#include "FGEngine/Asset/Material.h"

// ���b�V��
#include "FGEngine/Asset/StaticMesh.h"

#include "FGEngine/Asset/GltfFile.h"

// �Q�[���I�u�W�F�N�g
#include "FGEngine/GameObject.h"

// �R���|�[�l���g
#include "FGEngine/Component/Component.h"

// �R���|�[�l���g�̕⏕
#include "FGEngine/Component/ComponentHelper.h"

// �g�����X�t�H�[���R���|�[�l���g
#include "FGEngine/Component/Transform.h"

// �����_���[�R���|�[�l���g
#include "FGEngine/Component/Renderer.h"

// �X�^�e�B�b�N���b�V�������_���[�R���|�[�l���g
#include "FGEngine/Component/MeshRenderer.h"

#include "FGEngine/Component/GltfMeshRenderer.h"

// �R���C�_�[�R���|�[�l���g���
#include "FGEngine/Component/Collider.h"

// AABB�R���C�_�[�R���|�[�l���g
#include "FGEngine/Component/AabbCollider.h"

// Sphere�R���C�_�[�R���|�[�l���g
#include "FGEngine/Component/SphereCollider.h"

// Box�R���C�_�[�R���|�[�l���g
#include "FGEngine/Component/BoxCollider.h"

// ����(����)�R���|�[�l���g
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Camera.h"

// UI���C�A�E�g�̊��N���X
#include "FGEngine/Component/ImGuiLayout.h"

// �摜(UI)�`��R���|�[�l���g
#include "FGEngine/Component/Image.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Component/AudioListner.h"
#include "FGEngine/Component/AudioSource.h"

// ===================
//
// SceneSystem | �V�[���V�X�e��
//
// ===================

// �V�[���}�l�[�W���[
#include "FGEngine/Scene/SceneManager.h"

// �V�[��
#include "FGEngine/Scene/Scene.h"

// ===================
//
// ResouceSystem | ���\�[�X�V�X�e��
//
// ===================

// �A�Z�b�g�}�l�[�W���[
#include "FGEngine/Asset/AssetManager.h"

// �f�t�H���g�V�F�[�_�̎��
#include "FGEngine/Asset/DefalutShader.h"

// ===================
//
// WindowSystem | �E�B���h�E�V�X�e��
//
// ===================


#include "FGEngine/Window/WindowManager.h"

#include "FGEngine/Audio/SoundManager.h"

// ���͊Ǘ�
#include "FGEngine/Input/InputManager.h"

// �L�[�{�[�h�z��
#include "FGEngine/Input/KeyCode.h"

// �L�[�{�[�h�̓���
#include "FGEngine/Input/InputKey.h"

// �}�E�X�̃{�^��
#include "FGEngine/Input/MouseButton.h"

// �}�E�X�̓���
#include "FGEngine/Input/InputMouse.h"
