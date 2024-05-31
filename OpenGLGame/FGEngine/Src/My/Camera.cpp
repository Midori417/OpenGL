/**
* @file Camera.cpp
*/
#include "Camera.h"
#include "Transform.h"
#include "Mathf.h"

namespace FGEngine
{
	Vector2 Camera::WorldPointToScreenPoint(const Vector3& targetPos, const CameraPtr& targetCamera, float screenWidth, float screenHeight)
	{
        auto cameraTrs = targetCamera->GetTransform();
        auto viewMat = Matrix4x4::LookAt(cameraTrs->position, cameraTrs->position + (cameraTrs->Forward()), cameraTrs->Up());

        auto projMat = Matrix4x4::Perspective(targetCamera->radFovY, screenWidth / screenHeight, targetCamera->near, targetCamera->far);

        auto mvp = projMat * viewMat ;

        // ���[���h���W���N���b�v��Ԃɕϊ�
        Vector4 clipSpacePos = mvp * Vector4(targetPos, 1.0f);

        // �N���b�v��Ԃ�NDC�ɕϊ�
        Vector3 ndcSpacePos = Vector3(-clipSpacePos.x, clipSpacePos.y, clipSpacePos.z) / clipSpacePos.w;

        // NDC���E�B���h�E���W�ɕϊ�
        Vector2 screenSpacePos;
        screenSpacePos.x = Mathf::Clamp(((ndcSpacePos.x + 1.0f) * 0.5f * screenWidth) + screenWidth * -0.5f,
            screenWidth * -0.5f, screenWidth * 0.5f);
        screenSpacePos.y = Mathf::Clamp(((1.0f - ndcSpacePos.y) * 0.5f * screenHeight) + screenHeight * -0.5f,
            screenWidth * -0.5f, screenHeight * 0.5f);

        return screenSpacePos;
    }
}