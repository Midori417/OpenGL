/**
* @file GroundCheck.cpp
*/
#include "GroundCheck.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AssetManager.h"

/**
* Update�̑O�Ɏ��s
*/
void GroundCheck::Start()
{
	// �A�Z�b�g�}�l�[�W���[���擾
	auto assetManager = AssetManager::GetInstance();

	if (isRender)
	{
		renderer = OwnerObject()->AddComponent<MeshRenderer>();
		renderer->mesh = assetManager->GetStaticMesh("Sphere");
		renderer->shader = assetManager->GetShader(DefalutShader::Unlit);
	}

	SphereColliderPtr col = OwnerObject()->AddComponent<SphereCollider>();
	col->isTrigger = true;
}

/**
* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
*/
void GroundCheck::OnCollisionEnter(const CollisionPtr& other)
{
	isGround = true;
}

/**
* ���̃R���W�������痣�ꂽ�Ƃ��Ɏ��s
*/
void GroundCheck::OnCollisionExit(const CollisionPtr& other)
{
	isGround = false;
}
