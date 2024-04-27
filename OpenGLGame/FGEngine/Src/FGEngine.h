/**
* @file FGEngine.h
*/
#pragma once

// ===================
//
// Mathf | 数学関連
//
// ===================

// 数学関数
#include "My/Mathf.h"

// ベクトルの前方宣言
#include "My/VectorFrd.h"

// 二次元ベクトル
#include "My/Vector2.h"

// 三次元ベクトル
#include "My/Vector3.h"

// 四次元ベクトル
#include "My/Vector4.h"

// ベクトルポイント
#include "My/VectorPoint.h"

// 行列の前方宣言
#include "My/MatrixFrd.h"

// 3x3の行列
#include "My/Matrix3x3.h"

// 4x4の行列
#include "My/Matrix4x4.h"

// 時間
#include "My/Time.h"

// 乱数
#include "My/Random.h"

// ===================
//
// Color | 色
//
// ===================

// RGBA
#include "My/Color.h"

// ===================
//
// Other | その他便利機能
//
// ===================

// シングルトン
#include "My/Singleton.h"

// ===================
//
// DebugSystem | デバッグシステム
//
// ===================

// デバッグ
#include "My/Debug.h"

// ===================
//
// InputSystem | 入力システム
//
// ===================

#include "My/InputManager.h"

// キーボードの入力
#include "My/InputKey.h"

// マウスの入力
#include "My/MouseButton.h"


// ===================
//
// ObjectSystem | オブジェクトシステム
//
// ===================

// オブジェクト管理クラス
#include "My/ObjectManager.h"

// ===================
//
// Object | オブジェクト関連
//
// ===================

// オブジェクト
#include "My/Object.h"

// マテリアル
#include "My/Material.h"

// メッシュ
#include "My/Mesh.h"

// ゲームオブジェクト
#include "My/GameObject.h"

// コンポーネント
#include "My/Component.h"

// コンポーネントの補助
#include "My/ComponentHelper.h"

// トランスフォームコンポーネント
#include "My/Transform.h"

// レンダラーコンポーネント
#include "My/Renderer.h"

// スタティックメッシュレンダラーコンポーネント
#include "My/MeshRenderer.h"

// コライダーコンポーネント基底
#include "My/Collider.h"

// AABBコライダーコンポーネント
#include "My/AabbCollider.h"

// Sphereコライダーコンポーネント
#include "My/SphereCollider.h"

// Boxコライダーコンポーネント
#include "My/BoxCollider.h"

// 物理(剛体)コンポーネント
#include "My/Rigidbody.h"

// UIレイアウトの基底クラス
#include "My/ImGuiLayout.h"

// 画像(UI)描画コンポーネント
#include "My/Image.h"

// ===================
//
// SceneSystem | シーンシステム
//
// ===================

// シーンマネージャー
#include "My/SceneManager.h"

// シーン
#include "My/Scene.h"

// ===================
//
// ResouceSystem | リソースシステム
//
// ===================

// リソースマネージャー
#include "My/ResouceManager.h"

// 図形の種類
#include "My/ShapeType.h"

// デフォルトシェーダの種類
#include "My/DefalutShader.h"
