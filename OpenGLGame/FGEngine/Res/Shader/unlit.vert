/**
* @file unlit.vert
*/
# version 450

// シェーダの入力
layout(location=0) in vec3 inPosition;	// 頂点座標
layout(location=1) in vec2 inTexcoord;	// テクスチャ座標

// シェーダの出力
layout(location=0) out vec3 outPosition;	// ワールド座標
layout(location=1) out vec2 outTexcoord;	// テクスチャ座標

// プログラムからの入力
layout(location=0) uniform mat4 transformMatrix;
layout(location=3) uniform vec2 aspectRatioAndScaleFov;	// アスペクト比
layout(location=4) uniform vec3 cameraPosition;	// カメラの位置
//layout(location=5) uniform vec3 cameraSin;
//layout(location=6) uniform vec3 cameraCos;
layout(location=7) uniform mat3 cameraRotationMatrix;


void main()
{
	outTexcoord = inTexcoord;

	// ローカル座標系からワールド座標に変換
	// ローカル座標系からワールド座標に変換
	gl_Position = transformMatrix * vec4(inPosition, 1);

	outPosition = gl_Position.xyz;

	// ワールド座標系からビュー座標系に変換
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// ビュー座標系からクリップ座標系に変換
	gl_Position.xy *= aspectRatioAndScaleFov;

	// 深度値の計算結果が-1～+1になるようなパラメータA、Bを計算
	const float near = 0.35f;
	const float far = 1000;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// 遠近法を有効にする
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // 深度値を補正
}