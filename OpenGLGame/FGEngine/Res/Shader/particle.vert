/**
* @file particle.vert
*/
#version 450

// シェーダーへの入力
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;

// シェーダからの出力
layout(location=0) out vec4 outColor;
layout(location=1) out vec2 outTexcoord;

// プログラムからの入力
layout(location=3) uniform vec4 aspectRatioAndScaleFov;	// アスペクト比
layout(location=4) uniform vec3 cameraPosition;	// カメラの位置
layout(location=5) uniform mat3 cameraRotationMatrix;

// テクスチャ
layout(binding=0) uniform sampler2D texColor;

// テクスチャ座標構造体
struct Texcoord
{
	vec2 uv;
	vec2 size;
};

// パーティクルデータ構造体
struct ParticleData
{
	mat4 transformMatrix;
	vec4 color;		// 色と不透明度
	Texcoord texcoord;	// テクスチャ座標
};

// パーティクル用SSBO
layout(std430, binding=0)buffer praticleDataBuffer
{
	ParticleData particlList[];
};

void main()
{
	ParticleData particle = particlList[gl_InstanceID];

	// プリミティブの色を設定
	outColor = particle.color;
	outColor.a = clamp(outColor.a, 0, 1);

	// プリミティブのテクスチャ座標を計算
	outTexcoord = particle.texcoord.uv + (inTexcoord * particle.texcoord.size);

	// ローカル座標系からワールド座標に変換
	gl_Position = particle.transformMatrix * vec4(inPosition, 1);

	// ワールド座標系からビュー座標系に変換
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// ビュー座標系からクリップ座標系に変換
	gl_Position.xy *= aspectRatioAndScaleFov;

	// 深度値の計算結果が-1～+1になるようなパラメータA、Bを計算
	const float near = aspectRatioAndScaleFov.z;
	const float far = aspectRatioAndScaleFov.w;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// 遠近法を有効にする
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // 深度値を補正
}

//// エントリーポイント
//void main()
//{
//	ParticleData particle = particlList[gl_InstanceID];
//
//	// プリミティブの色を設定
//	outColor = particle.color;
//	outColor.a = clamp(outColor.a, 0, 1);
//
//	// プリミティブのテクスチャ座標を計算
//	outTexcoord = particle.texcoord.uv + (inTexcoord * particle.texcoord.size);
//
//	// プリミティブの大きさを画像の大きさと等しくする
//	vec2 v = inPosition * abs(particle.texcoord.size) * textureSize(texColor, 0);
//
//	// プリミティブの拡大縮小
//	v *= particle.scale;
//
//	// プリミティブを回転
//	gl_Position.x = v.x * particle.cosZ - v.y * particle.sinZ;
//	gl_Position.y = v.x + particle.sinZ + v.y * particle.cosZ;
//
//	// プリミティブをカメラの方向に向ける(ビルボード化する)
//	gl_Position.z = 0;
//	gl_Position.xyz = matBillboard * gl_Position.xyz;
//
//	// プリミティブをワールド座標に平行移動
//	gl_Position.xyz += particle.position.xyz;
//
//	//プリミティブをワールド座標系からクリップ座標系へ変換
//	gl_Position.w = 1;
//	gl_Position = matViewPorj * gl_Position;
//}