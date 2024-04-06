/**
* @file GraphicsEngine.h
*/
#ifndef FGENGINE_GRAPHICSENGINE_H_INCLUDED
#define FGENGINE_GRAPHICSENGINE_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include "LightData.h"
#include "GameObject.h"
#include "VertexArrayObject.h"

namespace FGEngine
{

	namespace Rendering
	{
		class MeshBuffer;
		using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	}
	namespace GraphicsSystem
	{
		/**
		* 描画エンジン
		*/
		class GraphicsEngine : Singleton<GraphicsEngine>
		{
		private:

			friend MainSystem::EngineCore;
			friend Singleton<GraphicsEngine>;

			GraphicsEngine() = default;

			/**
			* グラフィックエンジンを初期化
			*
			* @retval 0		初期化成功
			* @retval 0以外	初期化失敗
			*/
			int Initialize();

			/**
			* グラフィックエンジンを更新
			*/
			void Update();

			/**
			* グラフィックエンジンを終了
			*/
			void Fainalize();

			/**
			* ゲームオブジェクトを描画する
			*
			* @param begin	オブジェクト描画開始位置
			* @param end	オブジェクト描画終了位置
			*/
			void DrawGameObject(GameObjectList::iterator begin, GameObjectList::iterator end);

			/**
			* ライト配列を初期化する
			*/
			void InitializeLight(GameObjectList::iterator begin, GameObjectList::iterator end);

			/**
			* スカイスフィアを描画する
			*/
			void DrawSkySphere();

			/**
			* デプスシャドウを描画する
			*
			* @param begin	オブジェクト描画開始位置
			* @param end	オブジェクト描画終了位置
			*/
			void ShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end);

		public:


			/**
			* 新しいライトを取得する
			*
			* @return 新しいライトの要素番号
			*/
			int AllocateLight();

			/**
			* ライトを開放する
			*
			* @param index 解放する要素番号
			*/
			void DeallocateLight(int index);

			/**
			* インデックスに対応するライトデータを取得する
			*
			* @param index 取得する要素番号
			*/
			LightData* GetLight(int index);
			const LightData* GetLight(int index) const;

		private:

			// メッシュバッファ
			Rendering::MeshBufferPtr meshBuffer;
		};
	}
}
#endif // !FGENGINE_GRAPHICSENGINE_H_INCLUDED
