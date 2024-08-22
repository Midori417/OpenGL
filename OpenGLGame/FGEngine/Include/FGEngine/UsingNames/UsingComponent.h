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

	//コライダー
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;
	using ColliderList = std::vector<ColliderPtr>;

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

}

#endif // !FGENGINE_USINGCOMPONENT_H_INCLUDED
