/**
* @file UsingComponent.h
*/
#ifndef FGENGINE_USINGCOMPONENT_H_INCLUDED
#define FGENGINE_USINGCOMPONENT_H_INCLUDED
#include <memory>
#include <vector>

namespace FGEngine
{
	// コンポーネント
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;

	// トランスフォーム
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;

	// レンダラー
	class Renderer;
	using RendererPtr = std::shared_ptr<Renderer>;

	// メッシュレンダラー
	class MeshRenderer;
	using MeshRendererPtr = std::shared_ptr<MeshRenderer>;

	// Gltfメッシュレンダラー
	class GltfMeshRenderer;
	using GltfMeshRendererPtr = std::shared_ptr<GltfMeshRenderer>;

	//コライダー
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;
	using ColliderList = std::vector<ColliderPtr>;

	// AABBコライダー
	class AabbCollider;
	using AabbColliderPtr = std::shared_ptr<AabbCollider>;

	// スフィアコライダー
	class SphereCollider;
	using SphereColliderPtr = std::shared_ptr<SphereCollider>;

	// ボックスコライダー
	class BoxCollider;
	using BoxColliderPtr = std::shared_ptr<BoxCollider>;

	// リジッドボディ
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;

	// アニメータ
	class Animator;
	using AnimatorPtr = std::shared_ptr<Animator>;

	// カメラ
	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;

	// オウディオソース
	class AudioSource;
	using AudioSourcePtr = std::shared_ptr<AudioSource>;

	// イメージコンポーネント
	class Image;
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_USINGCOMPONENT_H_INCLUDED
