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
layout(location=2) uniform mat4 viewProjectionMatrix;	 // ビュープロジェクト行列

// スケルタルアニメーション用SSBO
layout(std430, binding=0) buffer AnimationDataBlock
{
	mat4 matBones[];	// 姿勢行列の配列
};


void main()
{
	// テクスチャ座標
	outTexcoord = inTexcoord;

	// 姿勢行列にウェイトをかけて加算合成し、モデル行列を作成
	mat4 matModel = 
		matBones[int(inJoints.x)] * inWeights.x + 
		matBones[int(inJoints.y)] * inWeights.y + 
		matBones[int(inJoints.z)] * inWeights.z + 
		matBones[int(inJoints.w)] * inWeights.w;

	// ウェイトが正規化されていない場合の対策([3][3]が1.0になるとは限らない)
	matModel[3][3] = dot(inWeights, vec4(1));

	// ローカル座標系からワールド座標系に変換
	gl_Position = matModel * (vec4(inPosition, 1));

	// ワールド座標系からクリップ座標系に変換
	gl_Position = viewProjectionMatrix * gl_Position;

}