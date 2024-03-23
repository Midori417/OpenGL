/**
* @file FGEngine.h
*/
#pragma once

// シングルトン
#include "My/Singleton.h"

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

// 行列ポイント
#include "My/MatrixPoint.h"

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
#include "My/Collider.h"


// ===================
//
// Debug | デバッグ
//
// ===================

// デバッグ
#include "My/Debug.h"

// ===================
//
// EngineCore | エンジンのコア 
//
// ===================

// エンジンコア
#include "My/Engine.h"

// ===================
//
// Input | 入力
//
// ===================

// キーボード、マウス入力
#include "My/Input.h"
#include "My/InputHelper.h"

// キー一覧
#include "My/KeyCode.h"


// コントローラー入力
#include "My/GamePad.h"

// ===================
//
// Object | オブジェクト
//
// ===================

// オブジェクト
#include "My/Object.h"

// ゲームオブジェクト
#include "My/GameObject.h"

// コンポーネント
#include "My/Component.h"
#include "My/ComponentHelper.h"

// 位置回転拡大縮小コンポーネント
#include "My/Transform.h"

// 描画基底コンポーネント
#include "My/Renderer.h"

// ライトコンポーネント
#include "My/Light.h"

// カメラコンポーネント
#include "My/Camera.h"

// コライダー基底コンポーネント
#include "My/Collider.h"

// AABBコライダー
#include "My/AabbCollider.h"

// Boxコライダー
#include "My/BoxCollider.h"

// 球体コライダー
#include "My/SphereCollider.h"

// ImGuiを使ったUI基底コンポーネント
#include "My/ImGuiUI.h"

// 画像コンポーネント
#include "My/Image.h"

// テキストコンポーネント
#include "My/Text.h"

// Obj描画コンポーネント
#include "My/MeshRenderer.h"

// GLTF描画コンポーネント
#include "My/GltfMeshRenderer.h"

// スケルタル描画コンポーネント
#include "My/GltfAnimatednMeshRenderer.h"

#include "My/ChracterMovement.h"

// マテリアル
#include "My/Material.h"

// テクスチャ
#include "My/Texture.h"

// ===================
//
// SoundSystem | サウンドシステム
//
// ===================

// サウンド
#include "My/EasyAudio.h"

// ===================
//
// SceneSystem | シーンシステム
//
// ===================

// シーンマネージャー
#include "My/SceneManager.h"

// シーン
#include "My/Scene.h"

// Mesh
#include "My/Mesh.h"
#include "My/GltfMesh.h"


