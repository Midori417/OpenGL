/**
* @file Light.cpp
*/
#include "Light.h"
#include "Engine.h"

namespace FGEngine
{

	/**
	* �f�X�g���N�^
	*/
	Light::~Light()
	{
		// ���C�g���J������
		GetGameObject()->GetEngine()->DeallocateLight(lightIndex);
	}

	/**
	* �R���|�[�l���g�̏�����
	*/
	void Light::Awake()
	{
		// ���C�g���擾���Ă��Ȃ���΁A���C�g���擾����
		if (lightIndex < 0)
		{
			lightIndex = GetGameObject()->GetEngine()->AllocateLight();
		}
	}

	/**
	* �R���|�[�l���g�̍X�V
	*/
	void Light::Update()
	{
		auto light = GetGameObject()->GetEngine()->GetLight(lightIndex);
		if (light)
		{
			light->position = transform->position;
			light->intensity = intensity;
			light->color = color;
			light->radius = radius;
			light->coneAngle = 0;	// �Ǝˊp�x��0�ȉ��Ȃ�|�C���g���C�g����

			// �X�|�b�g���C�g�̏ꍇ�A�X�|�b�g���C�g�̃p�����[�^�𔽉f
			if (type == Type::spotLight)
			{
				// ���C�g�̌������v�Z
				Vector3 direction = { 0,0,-1 }; // ��]�A�����̌����x�N�g��

				// X����]
				const float sinX = sin(transform->eulerAngles().x);
				const float cosX = cos(transform->eulerAngles().x);
				direction = {
					direction.x,
					direction.y * cosX - direction.z * sinX,
					direction.y * sinX + direction.z * cosX
				};

				// Y����]
				const float sinY = sin(transform->eulerAngles().y);
				const float cosY = cos(transform->eulerAngles().y);
				direction = {
					direction.x * cosY + direction.z * sinY,
					direction.y,
					direction.x * sinY + direction.z * cosY
				};

				// �p�����[�^�[�𔽉f
				light->direction = direction;
				light->coneAngle = coneAngle;
				light->falloffAngle = falloffAngle;
			}
		}
	}
}