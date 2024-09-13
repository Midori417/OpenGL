/**
* @file BaseControl.cpp
*/
#include "BaseControl.h"
#include "FGEngine/Component/Transform.h"

#include "LookOnCamera.h"
#include "BaseMs.h"

/**
* �J�n���}
*/
void BaseControl::StartOk()
{
	isStart = true;
}

/**
* �R���g���[���̏�����
*/
void BaseControl::Initialize()
{
	// �����^�[�Q�b�g��ݒ�
	targetControl = otherTeamControls[0];

	Transform* targetMs = targetControl->myMs->GetTransform().get();

	// �J�����Ɏ��g�̋@�̂ƃ^�[�Q�b�g��`����
	myCamera->SetMsTransform(myMs->GetTransform().get());
	myCamera->SelectTarget(targetMs);

	// �@�̂ɃJ�����ƃ^�[�Q�b�g��`����
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetControl->myMs.get());

	// �Q�[�����͂��쐬
	gameInput = std::make_shared<GameInput>();
}

/**
* �J�n����Ă��邩�擾
*/
bool BaseControl::IsStart() const
{
	return isStart;
}

/**
* �^�[�Q�b�g�Ƃ̋������v�Z
*/
bool BaseControl::GetDistance() const
{
	if (targetControl)
	{
		auto targetMs = targetControl->myMs;
		if (targetMs)
		{
			return Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
		}
	}

	return 0.0f;
}

/**
* �^�[�Q�b�g�̏�Ԃ��X�V
*/
void BaseControl::TargetUpdate()
{
	// �^�[�Q�b�g�؂�ւ�
	if (gameInput->targetChangeBtn && otherTeamControls.size() > 1)
	{
		if (targetControl == otherTeamControls[0])
		{
			targetControl = otherTeamControls[1];

			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
		else if (targetControl == otherTeamControls[1])
		{
			targetControl = otherTeamControls[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
	}
	// �^�[�Q�b�g�̋@�̂����񂾂�
	if (targetControl->myMs->IsDestroy() && otherTeamControls.size() > 1)
	{
		if (targetControl == otherTeamControls[0])
		{
			targetControl = otherTeamControls[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
		else if (targetControl == otherTeamControls[1])
		{
			targetControl = otherTeamControls[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
	}
}
