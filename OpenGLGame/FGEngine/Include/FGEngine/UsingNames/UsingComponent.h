/**
* @file UsingComponent.h
*/
#ifndef FGENGINE_USINGCOMPONENT_H_INCLUDED
#define FGENGINE_USINGCOMPONENT_H_INCLUDED
#include <memory>
#include <vector>

namespace FGEngine
{
	// �R���|�[�l���g
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;

	// �g�����X�t�H�[��
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;

	// �����_���[
	class Renderer;
	using RendererPtr = std::shared_ptr<Renderer>;

	// ���b�V�������_���[
	class MeshRenderer;
	using MeshRendererPtr = std::shared_ptr<MeshRenderer>;

	// Gltf���b�V�������_���[
	class GltfMeshRenderer;
	using GltfMeshRendererPtr = std::shared_ptr<GltfMeshRenderer>;

	//�R���C�_�[
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;
	using ColliderList = std::vector<ColliderPtr>;

	// AABB�R���C�_�[
	class AabbCollider;
	using AabbColliderPtr = std::shared_ptr<AabbCollider>;

	// �X�t�B�A�R���C�_�[
	class SphereCollider;
	using SphereColliderPtr = std::shared_ptr<SphereCollider>;

	// �{�b�N�X�R���C�_�[
	class BoxCollider;
	using BoxColliderPtr = std::shared_ptr<BoxCollider>;

	// ���W�b�h�{�f�B
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;

	// �A�j���[�^
	class Animator;
	using AnimatorPtr = std::shared_ptr<Animator>;

	// �J����
	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;

	// �I�E�f�B�I�\�[�X
	class AudioSource;
	using AudioSourcePtr = std::shared_ptr<AudioSource>;

	// �C���[�W�R���|�[�l���g
	class Image;
	using ImagePtr = std::shared_ptr<Image>;
}

#endif // !FGENGINE_USINGCOMPONENT_H_INCLUDED
