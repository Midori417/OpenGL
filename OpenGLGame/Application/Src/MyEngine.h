/**
* @file MyEngine.h
* このヘッダーを読み込んだらエンジンのあらかたの機能が使える
*/
#ifndef MYENGINE_H_INCLUDED
#define MYENGINE_H_INCLUDED

// ========================
//
// エンジン系
//
// ========================

// メインエンジン
#include "Engine/Engine.h"

// ========================
//
// デバッグ系
//
// ========================

#include "Engine/Debug.h"

// ========================
//
// 数学系
//
// ========================

// 時間
#include "Engine/Time.h"

// 二次元ベクトル
#include "Engine/Vector2.h"

// 三次元ベクトル
#include "Engine/Vector3.h"

// 四次元ベクトル
#include "Engine/Vector4.h"

// ベクトルまとめ
#include "Engine/VectorPoint.h"

// 4x4行列
#include "Engine/Matrix4x4.h"

// 3x3行列
#include "Engine/Matrix3x3.h"

// クォータニオン
#include "Engine/Quaternion.h"

// ========================
//
// オブジェクト系
//
// ========================

// ゲームオブジェクト
#include "Engine/GameObject.h"

// ======== Component =========== //

// オブジェクトに機能を持たせる
#include "Engine/Component.h"

// コンポーネントのヘルパー
#include "Engine/ComponentHelper.h"

// ImGUIを使ったUIの基底クラス
#include "Engine/ImGuiUI.h"

// 画像UI
#include "Engine/Image.h"

#include "Engine/Text.h"

// 移動、回転、拡大縮小
#include "Engine/Transform.h"

// 重力
#include "Engine/ChracterMovement.h"

// AABBの衝突
#include "Engine/AabbCollider.h"

// Sphereの衝突
#include "Engine/SphereCollider.h"

// Boxの衝突
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
// 入力系
//
// ========================

// キーボード・マウス入力
#include "Engine/Input.h"

// ゲームパッド(コントローラ)入力
#include "Engine/GamePad.h"

// ========================
//
// シーン系
//
// ========================

// シーン
#include "Engine/Scene.h"

// シーンマネージャー
#include "Engine/SceneManager.h"

// ========================
//
// グラフィック系
//
// ========================

// 色
#include "Engine/Color.h"

// メッシュ
#include "Engine/Mesh.h"

// テクスチャ
#include "Engine/Texture.h"

// マテリアル
#include "Engine/Material.h"

// ========================
//
// サウンド系
//
// ========================

// サウンド
#include "Engine/EasyAudio.h"

// サウンドリスト
#include "Engine/AudioSettings.h"

#endif // !MYENGINE_H_INCLUDED
