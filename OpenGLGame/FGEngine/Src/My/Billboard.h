/**
* @file Billboard.h
*/
#ifndef BILLBOARD_H_INCLUDED
#define BILLBOARD_H_INCLUDED

#include "Component.h"
#include "Engine.h"
#include "Transform.h"

/**
* ビルボード化コンポーネント
*/
class Billboard : public Component
{
public:

	Billboard() = default;
	virtual ~Billboard() = default;

	// ビルボードの更新
	virtual void Update() override 
	{
		// 常にカメラのほうを向くようにメッセージオブジェクトの向きを調整
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
