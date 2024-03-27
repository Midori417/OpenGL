/**
* @file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
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

			friend class SceneManager;

			// コンストラクタ・デストラクタ
			Scene() = default;
			virtual ~Scene() = default;

			/**
			* スカイスフィアマテリアを設定
			*
			* @param skyMaterial 設定するマテリアル
			*/
			void SetSkyMaterial(MaterialPtr material)
			{
				skyMaterial = material;
			}

			/**
			* スカイスフィアを取得する
			* 
			* @return シーンに設定されているマテリアル
			*/
			MaterialPtr GetSkyMaterial() const
			{
				return skyMaterial;
			}


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


		private:

			MaterialPtr skyMaterial;	// スカイスフィア用のマテリアル

		};
		using ScenePtr = std::shared_ptr<Scene>;
	}
}
#endif // !SCENEH_INCLUDED
