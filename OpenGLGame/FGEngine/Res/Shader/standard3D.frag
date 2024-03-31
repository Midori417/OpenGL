/**
* @file standard.frag
*/
# version 450

// シェーダの入力
layout(location=0) in vec3 inPosition;	// ワールド座標
layout(location=1) in vec2 inTexcoord;	// テクスチャ座標
layout(location=2) in vec3 inNormal;	// 法線ベクトル
layout(location=3) in vec3 inShadowTexcoord;	// シャドウテクスチャ座標

// 出力する色データ
out vec4 outColor;

// テクスチャサンプラ
layout(binding=0) uniform sampler2D texColor;
layout(binding=1) uniform sampler2D texEmission;
layout(binding=2) uniform sampler2DShadow texShadow;	// 影長深度テクスチャ

// プログラムからの入力
layout(location=100) uniform vec4 color;	// 物体の色
layout(location=101) uniform vec4 emissionColor; // 物体の発光色
layout(location=102) uniform float alphaCutoff;	// フラグメントを破棄する境界線

// 環境光
layout(location=107) uniform vec3 ambientLight;

// 平行光源
struct DirectionalLight
{
	vec3 color;		// 色と明るさ
	vec3 direction;	// 光の向き
};
layout(location=108) uniform DirectionalLight directionLight;

// ライトパラメータ
struct Light
{
	vec4 colorAndFalloffAngle[16];		// 色と明るさ、減衰開始角度
	vec4 positionAndRadius[16];			// 座標と半径
	vec4 directionAndConeAngle[16];		// 向き、最大照射角度
};
layout(location=110) uniform int lightCount;
layout(location=111) uniform Light light;

void main()
{
	vec4 c = texture(texColor, inTexcoord);

	// カットオフ値が指定されている場合、アルファがその値未満の場合は描画をキャンセル
	if(alphaCutoff > 0){
		if(c.a < alphaCutoff){
			discard;	// フラグメントを破棄
		}
		c.a = 1;	// 破棄されなかったら不透明にする
	}

	// テクスチャのガンマ補正を解除
	const float crtGamma = 2.2;	// CRTモニターのガンマ値
	c.rgb = pow(c.rgb, vec3(2.2));

	outColor = c * color;

	// 線形補間によって長さが一ではなくなっているので正規化して長さを一に復元する
	vec3 normal = normalize(inNormal);


	vec3 diffuse = vec3(0);		// 拡散光の明るさの合計
	for(int i = 0; i < lightCount; ++i)
	{
		// 光源の方向
		vec3 direction = light.positionAndRadius[i].xyz - inPosition;

		// 光源までの距離
		float sqrDistance = dot(direction, direction);
		float distance = sqrt(sqrDistance);

		// 方向を正規化して長さを１にする
		direction = normalize(direction);


		// ランベルトの余弦則を使って明るさを計算
		float theta = max(dot(direction, normal), 0);

		// ランパート反射による反射光のエネルギー量を入射光と等しくするためにπで割る
		float illuminance = theta / 3.14159265;

		// 照射角度が0より大きければスポットライトとみなす
		const float coneAngle = light.directionAndConeAngle[i].w;
		if(coneAngle > 0){
			// 「ライトからフラグ面へ向かうベクトル」と「スポットライトのベクトル」のなす角を計算
			// 角度がconeAngle以上なら範囲外
			float angle = acos(dot(-direction, light.directionAndConeAngle[i].xyz));
			if(angle >= coneAngle){
				continue; // 照射範囲外
			}

			// 最大照射角度の時0、減衰開始角度のとき1になるように補間
			const float falloffAngle = light.colorAndFalloffAngle[i].w;
			const float a = min((coneAngle - angle) / (coneAngle - falloffAngle), 1);
			illuminance *= a;
		}

		// ライトの最大距離の制限
		const float radius = light.positionAndRadius[i].w;
		const float smoothFactor = clamp(1 - pow(distance / radius, 4), 0, 1);
		illuminance *= smoothFactor * smoothFactor;

		// 逆二乗の法則によって明るさを減衰させる
		// 0除算が起きないように１を足している
		illuminance /= sqrDistance + 1;

		// 拡散光の明るさを計算
		diffuse += light.colorAndFalloffAngle[i].xyz * illuminance;
	}

	// 影を計算
	float shadow = texture(texShadow, inShadowTexcoord).r;

	// 平行光源の明るさを計算
	float theta = max(dot(-directionLight.direction, normal),0);
	float illuminance = theta / 3.14159265;
	diffuse += directionLight.color * illuminance * shadow;

	// アンビエントライトの明るさを計算
	diffuse += ambientLight;

	// 拡散光の影響を反映
	outColor.rgb *= diffuse;

	// 発光色を反映
	if(emissionColor.w > 0)
	{
		outColor.rgb += texture(texEmission, inTexcoord).rgb * emissionColor.rgb;
	}
	else 
	{
	 outColor.rgb += emissionColor.rgb;
	}

	// ガンマ補正を行う
	outColor.rgb = pow(outColor.rgb, vec3(1 / 2.2));
}