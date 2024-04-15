/**
* RenderingEngine.cpp
*/
#include "RenderingEngine.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "ResouceManager.h"
#include "ObjectManager.h"
#include "ShaderObject.h"
#include "MeshBuffer.h"
#include "ShaderLocationNum.h"
#include <algorithm>

namespace FGEngine::RenderingSystem
{
	/**
	* グラフィックエンジンを初期化
	*
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int RenderingEngine::Initialize()
	{
		
		// スカイスフィアを設定
		skySphere = ResouceSystem::ResouceManager::GetInstance()->GetStaticMesh("skySphere");

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
	* スカイスフィアを描画
	*/
	void RenderingEngine::DrawSkySphere()
	{
		// シーンマネージャーを取得
		auto sceneManger = SceneSystem::SceneManager::GetInstance();

		// リソースマネージャーを取得
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		const GLuint progUnlit = resouceManager->GetShader("Unlit")->GetProgId();

		// スカイスフィアが設定されていない場合は描画しない
		if (!skySphere || !sceneManger->CurrentScene()->skyMaterial)
		{
			return;
		}

		// アンリッドシェーダで描画
		glUseProgram(progUnlit);
		glDepthMask(GL_FALSE);	// 深度バッファへの書き込みを禁止
		glBindVertexArray(*skySphere->vao);

		// スカイスフィアの半径を0.5mと仮定し、描画範囲の95%の大きさに拡大
		static const float far = 1000;	// 描画範囲の最大値
		static const float scale = far * 0.95f / 0.5f;
		static const Matrix4x4 transformMatrix = Matrix4x4{
			Vector4(scale, 0,		0,		0),
			Vector4(0,		scale,	0,		0),
			Vector4(0,		0,		scale,	0),
			Vector4(0,		0,		0,		1),
		};
		glProgramUniformMatrix4fv(progUnlit, locTransformMatrix, 1, GL_FALSE, &transformMatrix[0].x);

		// 色はマテリアルカラーで調整するのでオブジェクトカラーは白に設定
		static const Color color = Color::white;
		glProgramUniform4fv(progUnlit, locColor, 1, &color.r);

		// スカイスフィアはカメラを原点として描画
		static const Vector3 skySphereCameraPosition = Vector3{ 0,0,0 };
		glProgramUniform3fv(progUnlit, 4, 1, &skySphereCameraPosition.x);

		// スカイスフィアを描画
		const MaterialList materials(1, sceneManger->CurrentScene()->skyMaterial);
		Draw(progUnlit, *skySphere, materials);

		auto objectManager = ObjectSystem::ObjectManager::GetInstance();

		glProgramUniform3fv(progUnlit, 4, 1, &objectManager->GetMainCamera()->GetTransform()->position.x);	// カメラ座標を元に戻す
		glDepthMask(GL_TRUE);	// 深度バッファへの書き込みを許可

		glBindVertexArray(0);
		glUseProgram(0);

	}

	/**
	* ゲームオブジェクトの描画
	* 
	* @param レンダーコンポーネント範囲の先端
	* @param レンダーコンポーネント範囲の終端
	*/
	void RenderingEngine::DrawGameObject(std::vector<RendererPtr> rendererList)
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


		// 描画先をデフォルトフレームバッファに戻す
		auto fbSize = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);

		glEnable(GL_DEPTH_TEST);	// 深度テストを有効化
		glEnable(GL_CULL_FACE);		// 裏面カリングを有効化

		// 半透明合成を有効化
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		// transparent以前のキューを描画
		Draw3DGameObject(rendererList.begin(), transparentBegin);

		// スカイスフィアを描画
		DrawSkySphere();

		// transparentからoverlayまでのキューを描画
		glDepthMask(GL_FALSE); // 深度バッファへの書き込みを禁止
		Draw3DGameObject(transparentBegin, overlayBegin);
		glDepthMask(GL_TRUE); // 深度バッファへの書き込みを許可

		// overlay以降のキューを描画
		glDisable(GL_DEPTH_TEST);	// 深度テストを無効化
		glDisable(GL_CULL_FACE);	// 裏面カリングを無効化

	}
}