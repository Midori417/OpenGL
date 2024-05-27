/**
* @file standard.vert
*/
# version 450

// シェーダの入力
layout(location=0) in vec3 inPosition;	// 頂点座標
layout(location=1) in vec2 inTexcoord;	// テクスチャ座標
layout(location=2) in vec3 inNormal;	// 法線ベクトル

// シェーダの出力
layout(location=0) out vec3 outPosition;	// ワールド座標
layout(location=1) out vec2 outTexcoord;	// テクスチャ座標
layout(location=2) out vec3 outNormal;		// 法線ベクトル
layout(location=3) out vec3 outShadowTexcoord;	// シャドウテクスチャ座標

// プログラムからの入力
layout(location=0) uniform mat4 transformMatrix;
layout(location=1) uniform mat3 normalMatrix;
layout(location=2) uniform mat4 viewProjectionMatrix;	// ビュープロジェクト行列
layout(location=3) uniform vec4 aspectRatioAndScaleFov;	// アスペクト比
layout(location=4) uniform vec3 cameraPosition;	// カメラの位置
layout(location=5) uniform mat3 cameraRotationMatrix;
layout(location=10) uniform mat4 shadowTextureMatrix;	// シャドウテクスチャ行列
layout(location=11) uniform float shadowNormalOffset;	// 座標を法線方向にずらす量

void main()
{
	outTexcoord = inTexcoord;

	// ローカル座標系からワールド座標に変換
	gl_Position = transformMatrix * vec4(inPosition, 1);

	outPosition = gl_Position.xyz;
	
	// ワールド法線を計算
	outNormal = normalMatrix *inNormal;

	// シャドウテクスチャ座標を計算
	outShadowTexcoord = outPosition + outNormal * shadowNormalOffset;
	outShadowTexcoord = vec3(shadowTextureMatrix* vec4(outShadowTexcoord, 1));

	// ワールド座標系からビュー座標系に変換
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// ビュー座標系からクリップ座標系に変換
	gl_Position.xy *= aspectRatioAndScaleFov.xy;

	// 深度値の計算結果が-1～+1になるようなパラメータA、Bを計算
	const float near = aspectRatioAndScaleFov.z;
	const float far = aspectRatioAndScaleFov.w;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// 遠近法を有効にする
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // 深度値を補正
}