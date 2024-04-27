/**
* @file FGEngine.h
*/
#pragma once

// ===================
//
// Mathf | ���w�֘A
//
// ===================

// ���w�֐�
#include "My/Mathf.h"

// �x�N�g���̑O���錾
#include "My/VectorFrd.h"

// �񎟌��x�N�g��
#include "My/Vector2.h"

// �O�����x�N�g��
#include "My/Vector3.h"

// �l�����x�N�g��
#include "My/Vector4.h"

// �x�N�g���|�C���g
#include "My/VectorPoint.h"

// �s��̑O���錾
#include "My/MatrixFrd.h"

// 3x3�̍s��
#include "My/Matrix3x3.h"

// 4x4�̍s��
#include "My/Matrix4x4.h"

// ����
#include "My/Time.h"

// ����
#include "My/Random.h"

// ===================
//
// Color | �F
//
// ===================

// RGBA
#include "My/Color.h"

// ===================
//
// Other | ���̑��֗��@�\
//
// ===================

// �V���O���g��
#include "My/Singleton.h"

// ===================
//
// DebugSystem | �f�o�b�O�V�X�e��
//
// ===================

// �f�o�b�O
#include "My/Debug.h"

// ===================
//
// InputSystem | ���̓V�X�e��
//
// ===================

#include "My/InputManager.h"

// �L�[�{�[�h�̓���
#include "My/InputKey.h"

// �}�E�X�̓���
#include "My/MouseButton.h"


// ===================
//
// ObjectSystem | �I�u�W�F�N�g�V�X�e��
//
// ===================

// �I�u�W�F�N�g�Ǘ��N���X
#include "My/ObjectManager.h"

// ===================
//
// Object | �I�u�W�F�N�g�֘A
//
// ===================

// �I�u�W�F�N�g
#include "My/Object.h"

// �}�e���A��
#include "My/Material.h"

// ���b�V��
#include "My/Mesh.h"

// �Q�[���I�u�W�F�N�g
#include "My/GameObject.h"

// �R���|�[�l���g
#include "My/Component.h"

// �R���|�[�l���g�̕⏕
#include "My/ComponentHelper.h"

// �g�����X�t�H�[���R���|�[�l���g
#include "My/Transform.h"

// �����_���[�R���|�[�l���g
#include "My/Renderer.h"

// �X�^�e�B�b�N���b�V�������_���[�R���|�[�l���g
#include "My/MeshRenderer.h"

// �R���C�_�[�R���|�[�l���g���
#include "My/Collider.h"

// AABB�R���C�_�[�R���|�[�l���g
#include "My/AabbCollider.h"

// Sphere�R���C�_�[�R���|�[�l���g
#include "My/SphereCollider.h"

// Box�R���C�_�[�R���|�[�l���g
#include "My/BoxCollider.h"

// ����(����)�R���|�[�l���g
#include "My/Rigidbody.h"

// UI���C�A�E�g�̊��N���X
#include "My/ImGuiLayout.h"

// �摜(UI)�`��R���|�[�l���g
#include "My/Image.h"

// ===================
//
// SceneSystem | �V�[���V�X�e��
//
// ===================

// �V�[���}�l�[�W���[
#include "My/SceneManager.h"

// �V�[��
#include "My/Scene.h"

// ===================
//
// ResouceSystem | ���\�[�X�V�X�e��
//
// ===================

// ���\�[�X�}�l�[�W���[
#include "My/ResouceManager.h"

// �}�`�̎��
#include "My/ShapeType.h"

// �f�t�H���g�V�F�[�_�̎��
#include "My/DefalutShader.h"
