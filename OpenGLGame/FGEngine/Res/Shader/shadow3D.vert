/**
* @file shadow.vert
*/
# version 450

// シェーダへの入力
layout(location=0) in vec3 inPosition; // 頂点座標
layout(location=1) in vec2 inTexcoord; // テクスチャ座標
layout(location=4) in vec4 inJoints;
layout(location=5) in vec4 inWeights;

// シェーダからの出力
layout(location=1) out vec2 outTexcoord;	// テクスチャ座標

// プログラムからの入力
layout(location=0) uniform mat4 transformMatrix;	// 座標変換行列
layout(location=2) uniform mat4 viewProjectionMatrix;	// ビュープロジェクト行列

void main()
{
	// テクスチャ座標
	outTexcoord = inTexcoord;

	// ローカル座標系からワールド座標系に変換
	gl_Position = transformMatrix * vec4(inPosition, 1);
	gl_Position = viewProjectionMatrix * gl_Position;
}