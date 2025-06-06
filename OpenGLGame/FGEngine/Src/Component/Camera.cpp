/**
* @file Camera.cpp
*/
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	Vector2 Camera::WorldPointToScreenPoint(const Vector3& targetPos, const CameraPtr& targetCamera, float screenWidth, float screenHeight)
	{
        auto cameraTrs = targetCamera->GetTransform();
        auto viewMat = Matrix4x4::LookAt(cameraTrs->position, cameraTrs->position + (cameraTrs->Forward()), cameraTrs->Up());

        auto projMat = Matrix4x4::Perspective(targetCamera->radFovY, screenWidth / screenHeight, targetCamera->near, targetCamera->far);

        auto mvp = projMat * viewMat ;

        // ワールド座標をクリップ空間に変換
        Vector4 clipSpacePos = mvp * Vector4(targetPos, 1.0f);

        // クリップ空間をNDCに変換
        Vector3 ndcSpacePos = Vector3(-clipSpacePos.x, clipSpacePos.y, clipSpacePos.z) / clipSpacePos.w;

        // NDCをウィンドウ座標に変換
        Vector2 screenSpacePos;
        screenSpacePos.x = Mathf::Clamp(((ndcSpacePos.x + 1.0f) * 0.5f * screenWidth) + screenWidth * -0.5f,
            screenWidth * -0.5f, screenWidth * 0.5f);
        screenSpacePos.y = Mathf::Clamp(((1.0f - ndcSpacePos.y) * 0.5f * screenHeight) + screenHeight * -0.5f,
            screenWidth * -0.5f, screenHeight * 0.5f);

        return screenSpacePos;
    }

    ComponentPtr Camera::Clone() const
    {
        CameraPtr p = std::make_shared<Camera>();

        p->far = this->far;
        p->near = this->near;
        p->aspect = this->aspect;

        p->degFovY = this->degFovY;
        p->radFovY = this->radFovY;
        p->fovScale = this->fovScale;

        return p;
    }
}