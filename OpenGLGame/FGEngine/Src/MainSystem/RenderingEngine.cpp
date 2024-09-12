/**
* RenderingEngine.cpp
*/
#include "FGEngine/MainSystem/RenderingEngine.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Math/Math.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Renderer.h"
#include "FGEngine/Component/Camera.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* グラフィックエンジンを初期化
	*
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int RenderingEngine::Initialize()
	{
		auto resManager = AssetManager::GetInstance();

		// スカイスフィアを設定
		skySphere = resManager->GetStaticMesh("skySphere");

		// glTFファイルバッファを取得
		glTFfileBuffer = resManager->GetGltfFileBuffer();

		// FBOを作成
		auto texShadow = Texture::Create("FBO(depth)", 4096, 4096, GL_DEPTH_COMPONENT32, GL_CLAMP_TO_EDGE);
		fboShadow = FrameBufferObject::Create(nullptr, texShadow);


		return 0;
	}

	/**
	* レンダリングエンジンを更新
	*/
	void RenderingEngine::Update()
	{
	}

	/**
	* 3Dオブジェクトの描画
	*
	* @param レンダーコンポーネント範囲の先端
	* @param レンダーコンポーネント範囲の終端
	*/
	void RenderingEngine::Draw3DGameObject(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end)
	{
		for (auto i = begin; i != end; ++i)
		{
			const auto& e = *i;
			// 描画コンポーネントが機能停止していたら何もしない
			if (!e->enabled)
			{
				continue;
			}
			// 描画
			e->Draw(DrawType::normal);
		}
	}

	/**
	* カメラに近いライトを選んでGPUメモリーにコピーする
	*/
	void RenderingEngine::UpdateShaderLight(const CameraPtr& camera)
	{
		// シェーダの仕分け
		auto resouceManager = AssetManager::GetInstance();
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));

		for (auto prog : programs)
		{
			// 環境光をGPUメモリにコピー
			prog->SetVector3("ambientLight", ambientLight);

			// 平行光源パラメータをGPUメモリにコピー
			const Vector3 color = directionLight.color * directionLight.intensity;
			prog->SetVector3("directionLight.color", color);
			prog->SetVector3("directionLight.direction", directionLight.direction);

		}

		// コピーするライトがなければライト数を0に設定
		if (usedLights.empty())
		{
			for (auto prog : programs)
			{
				prog->SetInt("lightCount", 0);
				return;
			}
		}
		// 使用中ライトの配列から、未使用になったライトを除外する
		const auto itrUnsed = std::remove_if(usedLights.begin(), usedLights.end(),
			[&](int i) {return !lights[i].used; });
		usedLights.erase(itrUnsed, usedLights.end());

		// 重複する番号を消去する
		std::sort(usedLights.begin(), usedLights.end());
		const auto itrUnique = std::unique(usedLights.begin(), usedLights.end());
		usedLights.erase(itrUnique, usedLights.end());


		// カメラの正面ベクトルを計算
		const Vector3 front = camera->GetTransform()->Forward();

		// カメラからライトまでの距離を計算
		struct Distance
		{
			float distance;		// カメラからライトの半径までの距離
			const LightData* p;	// ライトのアドレス
		};
		std::vector<Distance> distanceList;
		distanceList.reserve(lights.size());
		for (auto index : usedLights)
		{
			const auto& light = lights[index];
			const Vector3 v = light.position - camera->GetTransform()->position;
			// カメラの後ろにあるライトを除外
			if (Vector3::Dot(front, v) <= -light.radius)
			{
				continue;
			}
			const float d = Vector3::Magnitude(v) - light.radius; // カメラからのライトまでの半駅までの距離
			distanceList.push_back({ d,&light });
		}
		// 画面に影響するライトがなければライト数を0に設定
		if (distanceList.empty())
		{
			for (auto prog : programs)
			{
				prog->SetInt("lightCount", 0);
			}
			return;
		}

		// カメラに近いライトを優先する
		std::stable_sort(distanceList.begin(), distanceList.end(),
			[&](const auto& a, const auto& b) {return a.distance < b.distance; });

		// ライトデータをGPUメモリにコピーする
		constexpr size_t maxShaderLightCount = 16;
		const int lightCount = static_cast<int>(std::min(distanceList.size(), maxShaderLightCount)); // コピーするライト数
		std::vector<Vector4> colorAndFalloffAngle(lightCount);
		std::vector<Vector4> positionAndRadius(lightCount);
		std::vector<Vector4> directionAndConeAngle(lightCount);
		for (int i = 0; i < lightCount; ++i)
		{
			const LightData* p = distanceList[i].p;
			const Vector3 color = p->color * p->intesity;
			colorAndFalloffAngle[i] = Vector4{
				color.x,color.y,color.z, p->fallOffAngle
			};
			positionAndRadius[i] = Vector4{
				p->position.x, p->position.y, p->position.z, p->radius
			};
			directionAndConeAngle[i] = Vector4{
					p->direction.x,p->direction.y,p->direction.z,p->coneAngle
			};
		}

		for (auto prog : programs)
		{
			//glProgramUniform4fv(prog, locLightColorAndFalloffAngle, lightCount, &colorAndFalloffAngle[0].x);
			//glProgramUniform4fv(prog, locLightPositionAndRadius, lightCount, &positionAndRadius[0].x);
			//glProgramUniform4fv(prog, locLightDirectionAndConeAngle, lightCount, &directionAndConeAngle[0].x);
			prog->SetInt("lightCount", lightCount);
		}
	}

	/**
	* デプスシャドウマップの作成
	*/
	void RenderingEngine::CreateShadowMap(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end)
	{
		// 描画先フレームバッファを変更
		glBindFramebuffer(GL_FRAMEBUFFER, *fboShadow);

		// ビューポートをフレームバッファのサイズに合わせる
		const auto& texShadow = fboShadow->GetDepthTexture();
		glViewport(0, 0, texShadow->GetWidth(), texShadow->GetHeight());

		// 深度バッファをクリア
		glClear(GL_DEPTH_BUFFER_BIT);

		// 影の描画パラメータ
		const float shadowAreaSize = 450;	// 影の描画範囲(XY平面)
		const float shadowNearZ = 1;		// 影の描画範囲(近Z平面)
		const float shadowFarZ = 400;		// 影の描画範囲(遠Z平面)
		const float shadowCenterZ = (shadowNearZ + shadowFarZ) * 0.5f; // 描画範囲の中心
		const Vector3 target = Vector3{ 0, 0, -50 }; // カメラの注視点
		const Vector3 eye = target - directionLight.direction * shadowCenterZ; // カメラの位置

		// ビュープロジェクション行列を計算
		const Matrix4x4 matShadowView = Matrix4x4::LookAt(eye, target, Vector3::up);
		const Matrix4x4 matShadowProj = Matrix4x4::Orthogonal(
			-shadowAreaSize / 2, shadowAreaSize / 2,
			-shadowAreaSize / 2, shadowAreaSize / 2,
			shadowNearZ, shadowFarZ);
		const Matrix4x4 matShadow = matShadowProj * matShadowView;

		// シェーダの仕分け
		auto resouceManager = AssetManager::GetInstance();
		std::vector<ShaderPtr> shadowPrograms;

		shadowPrograms.push_back(resouceManager->GetShader(DefalutShader::Shadow3D));
		shadowPrograms.push_back(resouceManager->GetShader(DefalutShader::ShadowSkeletal3D));

		// 影を使用するシェーダを取得
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));

		// ビュープロジェクション行列をGPUメモリにコピー
		for (auto prog : shadowPrograms)
		{
			prog->SetMatrix4x4("viewProjectionMatrix", matShadow);
		}

		// メッシュを描画
		for (std::vector<RendererPtr>::iterator i = begin; i != end; ++i)
		{
			const auto& e = *i;
			e->Draw(DrawType::shadow);
		}

		// 深度テクスチャを割り当てる
		glBindTextureUnit(2, *texShadow);

		// 深度テクスチャ座標への変換行列を作成
		static const Matrix4x4 matTexture = Matrix4x4{
			Vector4{0.5f, 0.0f, 0.0f, 0.0f},
			Vector4{0.0f, 0.5f, 0.0f, 0.0f},
			Vector4{0.0f, 0.0f, 0.5f, 0.0f},
			Vector4{0.5f, 0.5f, 0.5f, 1.0f}
		};

		for (auto prog : programs)
		{
			// シャドウテクスチャ行列をGPUメモリにコピー
			const Matrix4x4 matShadowTexture = matTexture * matShadowProj * matShadowView;
			prog->SetMatrix4x4("shadowTextureMatrix", matShadowTexture);

			// 法線方向の設定
			const float texSize = shadowAreaSize / static_cast<float>(texShadow->GetWidth());
			prog->SetFloat("shadowNormalOffset", texSize);
		}
	}

	/**
	* スカイスフィアを描画
	*/
	void RenderingEngine::DrawSkySphere(const CameraPtr& camera)
	{
		// シーンマネージャーを取得
		auto sceneManger = SceneManager::GetInstance();

		// リソースマネージャーを取得
		auto resouceManager = AssetManager::GetInstance();
		const auto progUnlit = resouceManager->GetShader("Unlit");

		// スカイスフィアが設定されていない場合は描画しない
		if (!skySphere || !sceneManger->CurrentScene()->skyBoxMaterial)
		{
			return;
		}

		glDepthMask(GL_FALSE);	// 深度バッファへの書き込みを禁止

		// スカイスフィアの半径を0.5mと仮定し、描画範囲の95%の大きさに拡大
		static const float far = 1000;	// 描画範囲の最大値
		static const float scale = far * 0.95f / 0.5f;
		static const Matrix4x4 transformMatrix = Matrix4x4{
			Vector4(scale, 0,		0,		0),
			Vector4(0,		scale,	0,		0),
			Vector4(0,		0,		scale,	0),
			Vector4(0,		0,		0,		1),
		};
		progUnlit->SetMatrix4x4("transformMatrix", transformMatrix);

		// 色はマテリアルカラーで調整するのでオブジェクトカラーは白に設定
		progUnlit->SetColor("color", Color::white);

		// スカイスフィアはカメラを原点として描画
		progUnlit->SetVector3("cameraPosition", Vector3::zero);

		// スカイスフィアを描画
		const MaterialList materials(1, sceneManger->CurrentScene()->skyBoxMaterial);
		Draw(progUnlit, *skySphere, materials);

		// カメラ座標を元に戻す
		progUnlit->SetVector3("cameraPosition", camera->GetTransform()->position);
		glDepthMask(GL_TRUE);	// 深度バッファへの書き込みを許可
	}

	/**
	* ゲームオブジェクトの描画
	*
	* @param レンダーコンポーネント範囲の先端
	* @param レンダーコンポーネント範囲の終端
	*/
	void RenderingEngine::DrawGameObject(std::vector<RendererPtr> rendererList, const CameraPtr& camera)
	{
		// ゲームオブジェクトをレンダーキュー順に並べる
		std::stable_sort(rendererList.begin(), rendererList.end(),
			[](const RendererPtr& a, const RendererPtr& b) {
				return a->renderQueue < b->renderQueue; });

		// transparentキューの先頭を検索
		const auto transparentBegin = std::lower_bound(
			rendererList.begin(), rendererList.end(), RenderQueue_transparent,
			[](const RendererPtr& e, int value) { return e->renderQueue < value; });

		// overlayキューの先頭を検索
		const auto overlayBegin = std::lower_bound(
			transparentBegin, rendererList.end(), RenderQueue_overlay,
			[](const RendererPtr& e, int value) { return e->renderQueue < value; });

		glEnable(GL_DEPTH_TEST);	// 深度テストを有効化
		glEnable(GL_CULL_FACE);		// 裏面カリングを有効化

		// 半透明合成を有効化
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		// ライトの更新
		UpdateShaderLight(camera);

		// デプスシャドウマップを作成
		CreateShadowMap(rendererList.begin(), rendererList.end());

		// 描画先をデフォルトフレームバッファに戻す
		auto fbSize = WindowManager::GetInstance()->GetWindowSize();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);

		// アニメーションバッファをクリア
		glTFfileBuffer->ClearAnimationBuffer();

		// 描画の前処理
		for (auto& x : rendererList)
		{
			if (x->enabled)
			{
				x->PreDraw();
			}
		}

		// アニメーションバッファをGPUメモリにコピーする
		glTFfileBuffer->UploadAnimationBuffer();

		// transparent以前のキューを描画
		Draw3DGameObject(rendererList.begin(), transparentBegin);

		// スカイスフィアを描画
		DrawSkySphere(camera);

		// transparentからoverlayまでのキューを描画
		glDepthMask(GL_FALSE); // 深度バッファへの書き込みを禁止
		Draw3DGameObject(transparentBegin, overlayBegin);
		glDepthMask(GL_TRUE); // 深度バッファへの書き込みを許可

		// overlay以降のキューを描画
		glDisable(GL_DEPTH_TEST);	// 深度テストを無効化
		glDisable(GL_CULL_FACE);	// 裏面カリングを無効化

	}
}