/**
* @file RenderingEngine.h
*/
#ifndef FGENGINE_RENDERINGENGINE_H_INCLUDED
#define FGENGINE_RENDERINGENGINE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "GameObject.h"
#include "LightData.h"
#include "StaticMesh.h"
#include "FrameBufferObject.h"

namespace FGEngine::RenderingSystem
{
	class GltfFileBuffer;

	/**
	* 描画エンジン
	*/
	class RenderingEngine : public Singleton<RenderingEngine>
	{
	private:

		friend Singleton<RenderingEngine>;
		friend MainSystem::EngineCore;

		// コンストラクタ
		RenderingEngine() = default;

		/**
		* レンダリングエンジンを初期化
		* 
		* @retval 0		初期化成功
		* @retval 0以外	初期化失敗
		*/
		int Initialize();

		/**
		* レンダリングエンジンを更新
		*/
		void Update();

		/**
		* 3Dオブジェクトの描画
		*
		* @param レンダーコンポーネント範囲の先端
		* @param レンダーコンポーネント範囲の終端
		*/
		void Draw3DGameObject(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end);

		/**
		* カメラに近いライトを選んでGPUメモリーにコピーする
		*/
		void UpdateShaderLight();

		/**
		* デプスシャドウマップの作成
		*/
		void CreateShadowMap(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end);

		/**
		* スカイスフィアを描画
		*/
		void DrawSkySphere();

	public:

		/**
		* ゲームオブジェクトの描画
		*
		* @param レンダーコンポーネント範囲の先端
		* @param レンダーコンポーネント範囲の終端
		*/
		void DrawGameObject(std::vector<RendererPtr> rendererList);

	private:

		// 光源
		std::vector<LightData> lights; // ライトデータの配列
		std::vector<int> usedLights;		// 使用中のライトのインデックス配列
		std::vector<int> freeLights;		// 未使用のライトインデックス配列

		// 一度に増やすライト数
		static constexpr size_t lightResizeCount = 100;

		// 平行光源
		DirectionLight directionLight;

		// 環境光
		Vector3 ambientLight = Vector3(0.05f, 0.15f, 0.25f);

		// スカイスフィア用モデル
		StaticMeshPtr skySphere;
		
		// デプスシャドウ用FBO
		FrameBufferObjectPtr fboShadow;

		// glTFファイルバッファ
		GltfFileBuffer* glTFfileBuffer;

	};
}

#endif // !FGENGINE_RENDERINGENGINE_H_INCLUDED
