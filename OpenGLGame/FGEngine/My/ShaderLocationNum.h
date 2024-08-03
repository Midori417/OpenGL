/**
* @file ShaderLocationNum.h
*/
#ifndef FGENGINE_SHADERLOCATIONNUM_H_INCLUDED
#define FGENGINE_SHADERLOCATIONNUM_H_INCLUDED
#include <GLFW/glfw3.h>

namespace FGEngine::RenderingSystem
{	
	// シェーダで使えるライトの数
	constexpr size_t maxShaderLightCount = 16;

	// シェーダのロケーション番号
	constexpr GLint locTransformMatrix = 0;
	constexpr GLint locNormalMatrix = 1;
	constexpr GLint locViewProjectionMatrix = 2;
	constexpr GLint locAspectRatioAndScaleFov = 3;
	constexpr GLint locCameraPos = 4;
	constexpr GLint locCameraRotationMatrix = 5;
	constexpr GLint locShadowTextureMatrix = 10;
	constexpr GLint locShadowNormalOffset = 11;
	constexpr GLint locColor = 100;
	constexpr GLint locAlphaCutoff = 102;
	constexpr GLint locDirectionalLightColor = 108;
	constexpr GLint locAmbientLight = 107;
	constexpr GLint locDirectionalLightDericion = 109;
	constexpr GLint locLightCount = 110;
	constexpr GLint locLightColorAndFalloffAngle = 111;
	constexpr GLint locLightPositionAndRadius = locLightColorAndFalloffAngle + maxShaderLightCount;
	constexpr GLint locLightDirectionAndConeAngle = locLightColorAndFalloffAngle + maxShaderLightCount * 2;
}

#endif // !FGENGINE_SHADERLOCATIONNUM_H_INCLUDED
