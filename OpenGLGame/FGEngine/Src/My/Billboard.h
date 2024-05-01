/**
* @file Billboard.h
*/
#ifndef BILLBOARD_H_INCLUDED
#define BILLBOARD_H_INCLUDED

#include "Component.h"
#include "Engine.h"
#include "Transform.h"

/**
* �r���{�[�h���R���|�[�l���g
*/
class Billboard : public Component
{
public:

	Billboard() = default;
	virtual ~Billboard() = default;

	// �r���{�[�h�̍X�V
	virtual void Update() override 
	{
		// ��ɃJ�����̂ق��������悤�Ƀ��b�Z�[�W�I�u�W�F�N�g�̌����𒲐�
		const Engine* engine = GetGameObject()->GetEngine();
		if (engine->GetMainCamera() == nullptr) 
		{
			return;
		}
		const GameObject* camera = engine->GetMainCamera().get();
		transform->SetEulerAngles(transform->eulerAngles().x, camera->transform->eulerAngles().y, transform->eulerAngles().z);
	}
};

#endif // !BILLBOARD_H_INCLUDED
