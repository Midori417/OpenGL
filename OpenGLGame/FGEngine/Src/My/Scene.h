/**
* @file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <memory>
#include <string>

// 先行宣言
class Engine;
struct Material;
using MaterialPtr = std::shared_ptr<Material>;

namespace SceneManagment
{
	/**
	* シーンの基底クラス
	*/
	class Scene
	{
		friend class SceneManager;
	public:

		// コンストラクタ・デストラクタ
		Scene() = default;
		virtual ~Scene() = default;

		/**
		* スカイスフィアマテリアを設定
		* 
		* @param skyMaterial 設定するマテリアル
		*/
		void SetSkeyMaterial(MaterialPtr skyMaterial)
		{
			this->skyMaterial = skyMaterial;
		}

	private:

		/**
		* シーンの初期化
		* 
		* @param engine エンジン
		* 
		* @retval true	初期化成功
		* @retval false	初期化失敗
		*/
		virtual bool Initialize(Engine& engine) 
		{
			return true;
		}

		/**
		* シーンの更新
		* 
		* @param engine エンジン
		*/
		virtual void Update(Engine& engine) {}

		/**
		* シーンの終了
		* 
		* @param engine エンジン
		*/
		virtual void Finalize(Engine& engine) {}


	public:

		std::string name = "sampleScene";
		MaterialPtr skyMaterial;	// スカイスフィア用のマテリアル

	};
	using ScenePtr = std::shared_ptr<Scene>;
}
#endif // !SCENEH_INCLUDED
