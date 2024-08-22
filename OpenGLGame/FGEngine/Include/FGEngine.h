/**
* @file MyEngine.h
*/
#pragma once

// ===================
//
// Mathf | 数学関連
//
// ===================

#include "FGEngine/Math/Math.h"

// 時間
#include "FGEngine/Time.h"
#include <time.h>

// 乱数
#include "FGEngine/Math/Random.h"

// ===================
//
// Color | 色
//
// ===================

// RGBA
#include "FGEngine/Color.h"

// ===================
//
// Other | その他便利機能
//
// ===================

// シングルトン
#include "FGEngine/Singleton.h"

// ===================
//
// DebugSystem | デバッグシステム
//
// ===================

// デバッグ
#include "FGEngine/Debug.h"

// ===================
//
// Object | オブジェクト関連
//
// ===================

// マテリアル
#include "FGEngine/Asset/Material.h"

// メッシュ
#include "FGEngine/Asset/StaticMesh.h"

#include "FGEngine/Asset/GltfFile.h"

// ゲームオブジェクト
#include "FGEngine/GameObject.h"

// コンポーネント
#include "FGEngine/Component/Component.h"

// コンポーネントの補助
#include "FGEngine/Component/ComponentHelper.h"

// トランスフォームコンポーネント
#include "FGEngine/Component/Transform.h"

// レンダラーコンポーネント
#include "FGEngine/Component/Renderer.h"

// スタティックメッシュレンダラーコンポーネント
#include "FGEngine/Component/MeshRenderer.h"

#include "FGEngine/Component/GltfMeshRenderer.h"

// コライダーコンポーネント基底
#include "FGEngine/Component/Collider.h"

// AABBコライダーコンポーネント
#include "FGEngine/Component/AabbCollider.h"

// Sphereコライダーコンポーネント
#include "FGEngine/Component/SphereCollider.h"

// Boxコライダーコンポーネント
#include "FGEngine/Component/BoxCollider.h"

// 物理(剛体)コンポーネント
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Camera.h"

// UIレイアウトの基底クラス
#include "FGEngine/Component/ImGuiLayout.h"

// 画像(UI)描画コンポーネント
#include "FGEngine/Component/Image.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Component/AudioListner.h"
#include "FGEngine/Component/AudioSource.h"

// ===================
//
// SceneSystem | シーンシステム
//
// ===================

// シーンマネージャー
#include "FGEngine/Scene/SceneManager.h"

// シーン
#include "FGEngine/Scene/Scene.h"

// ===================
//
// ResouceSystem | リソースシステム
//
// ===================

// アセットマネージャー
#include "FGEngine/Asset/AssetManager.h"

// デフォルトシェーダの種類
#include "FGEngine/Asset/DefalutShader.h"

// ===================
//
// WindowSystem | ウィンドウシステム
//
// ===================


#include "FGEngine/Window/WindowManager.h"

#include "FGEngine/Audio/SoundManager.h"

// 入力管理
#include "FGEngine/Input/InputManager.h"

// キーボード配列
#include "FGEngine/Input/KeyCode.h"

// キーボードの入力
#include "FGEngine/Input/InputKey.h"

// マウスのボタン
#include "FGEngine/Input/MouseButton.h"

// マウスの入力
#include "FGEngine/Input/InputMouse.h"
