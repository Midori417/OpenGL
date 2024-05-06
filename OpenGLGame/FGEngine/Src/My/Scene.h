/**
* @file Scene.h
*/
#ifndef FGENGINE_SCENE_H_INCLUDED
#define FGENGINE_SCENE_H_INCLUDED
#include "SystemFrd.h"
#include <memory>
#include <string>

namespace FGEngine
{
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace SceneSystem
	{
		/**
		* シーンの基底クラス
		*/
		class Scene
		{
		public:

			friend SceneManager;

			// コンストラクタ・デストラクタ
			Scene() = default;
			virtual ~Scene() = default;

		protected:

			/**
			* シーンの初期化
			*
			* @param engine エンジン
			*
			* @retval true	初期化成功
			* @retval false	初期化失敗
			*/
			virtual bool Initialize()
			{
				return true;
			}

			/**
			* シーンの更新
			*
			* @param engine エンジン
			*/
			virtual void Update() {}

			/**
			* シーンの終了
			*
			* @param engine エンジン
			*/
			virtual void Finalize() {}


		public:

			// スカイスフィア用のマテリアル
			MaterialPtr skyMaterial;

		};
		using ScenePtr = std::shared_ptr<Scene>;
	}
}
#endif // !SCENEH_INCLUDED
