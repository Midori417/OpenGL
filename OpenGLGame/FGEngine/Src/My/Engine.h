/**
* @file Engine.h
*/
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include "EngineSystemFrd.h"
#include "Singleton.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "Package/Glad.h"

#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

// 先行宣言
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine
{

	// 先行宣言
	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr <FrameBufferObject>;
	class ProgramObject;
	using ProgramObjectPtr = std::shared_ptr<ProgramObject>;

	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	// シェーダで使えるライトの数
	constexpr size_t maxShaderLightCount = 16;

	// シェーダのロケーション番号
	constexpr GLint locViewProjectionMatrix = 2;
	constexpr GLint locShadowTextureMatrix = 10;
	constexpr GLint locShadowNormalOffset = 11;
	constexpr GLint locColor = 100;
	constexpr GLint locAlphaCutoff = 102;
	constexpr GLint locDirectionalLightColor = 108;
	constexpr GLint locAmbientLight = 107;
	constexpr GLint locDirectionalLightDericion = 109;
	constexpr GLint locLightCount = 110;
	constexpr GLint locLightColorAndFalloffAngle = 111;
	constexpr GLint locLightPositionAndRadius = locLightColorAndFalloffAngle + maxShaderLightCount;
	constexpr GLint locLightDirectionAndConeAngle = locLightColorAndFalloffAngle + maxShaderLightCount * 2;

	// 点光源
	struct LightData
	{
		Vector3 color;			// 色
		float intensity;	// 明るさ
		Vector3 position;		// 位置
		float radius;		// ライトが届く最大半径

		// スポットライト用の変数
		Vector3 direction;	// ライトの向き
		float coneAngle;	// スポットライトが照らす角度
		float falloffAngle;	// スポットライトの減衰開始角度
		bool used = false;	// 使用中かどうか
	};

	// 平行光源
	struct DirectionLight
	{
		Vector3 color = { 1.00f, 0.98f, 0.95f };	// 色
		float intensity = 5.0f;					// 明るさ
		Vector3 direction = { 0.58f, -0.58f, 0.58f };	// 向き
	};


	/**
	* ゲームエンジン
	*/
	class Engine : public Singleton<Engine>
	{
	private:

		friend Singleton<Engine>;

		// コンストラクタ
		Engine() = default;

	public:

		~Engine() = default;

		// ゲームエンジンを実行
		int Run();

		/**
		* ゲームオブジェクトを作成する
		*
		* @param name		オブジェクトの名前
		* @param position	オブジェクトの位置
		* @param rotation	オブジェクトの回転
		*
		* @return 作成したゲームオブジェクトポインター
		*/
		template<class T>
		inline std::shared_ptr<T> Create(const std::string& name,
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion::identity)
		{
			auto p = std::make_shared<T>();
			p->engine = this;
			p->AddComponent<Transform>();
			p->SetName(name);
			p->transform->position = position;
			p->transform->rotation = (rotation);
			gameObjects.push_back(p);
			return p;
		}


		/**
		* カメラオブジェクトを作成する
		*/
		GameObjectPtr CreateCameraObject(const std::string& name, const Vector3& position = Vector3::zero, const Quaternion& rotation = Quaternion::identity)
		{
			auto Object = Create<GameObject>(name, position, rotation);
			Object->AddComponent<Camera>();
			if (camera == nullptr) {
				camera = Object;
			}
			return Object;
		}

		// すべてのゲームオブジェクトを削除する
		void AllClearGameObject();

		// カメラを取得
		inline GameObjectPtr GetMainCamera() {
			if (camera == nullptr) {
				return nullptr;
			}
			return camera;
		}
		inline const GameObjectPtr GetMainCamera() const {
			if (camera == nullptr) {
				return nullptr;
			}
			return camera;
		}

		/**
		* メインカメラを設定する
		*
		* nullptrだとカメラを外せる
		*/
		inline void SetMainCamera(GameObjectPtr newCamera) {
			camera = newCamera;
		}

		// ライト配列を初期化する
		void InitialzeLight();
		// 新しいライトを取得する
		int AllocateLight();
		// ライトを開放する
		void DeallocateLight(int index);
		// インデックスに対応するライトデータを取得する
		LightData* GetLight(int index);
		const LightData* GetLight(int index) const;

		// フレームバッファの大きさを取得する
		Vector2 GetFramebufferSize() const;

		// フレームバッファのアスペクト比を取得する
		float GetAspectRatio() const;


		/**
		* スタティックメッシュの取得
		*
		* @param name メッシュ名
		*
		* @return 名前がnameと一致するスタティックメッシュ
		*/
		StaticMeshPtr GetStaticMesh(const char* name) {
			return meshBuffer->GetStaticMesh(name);
		}
		GltfFilePtr LoadGltf(const char* filename);

		StaticMeshPtr LoadObj(const char* filename)
		{
			return meshBuffer->LoadObj(filename);
		}

		// テクスチャの取得
		TexturePtr GetTexture(const char* name, Texture::Usage usage = Texture::Usage::for3D);

		GltfFileBufferPtr GetGltfFileBuffer() const { return gltfFileBuffer; }

	private:

		// ワールド座標系のコライダー
		struct WorldCollder
		{
			// 座標を変更する
			void AddPosition(const Vector3& v) {
				origin->transform->position += v;
				world->AddPosition(v);
			}

			ColliderPtr origin;
			ColliderPtr world;
		};
		using WorldCollderList = std::vector<WorldCollder>;

		// ゲームエンジンを初期化
		int Initialize();
		// ゲームエンジンを更新
		void Update();
		// エンジンの終了
		void Fainalize();

		// ゲームエンジンの状態を描画する
		void Render();
		// ゲームオブジェクトを描画する
		void DrawGameObject(const ProgramObject& prog, GameObjectList::iterator begin, GameObjectList::iterator end);
		// ゲームオブジェクトを更新する
		void UpdateGameObject();
		// ゲームオブジェクトの衝突を処理する
		void HandleGameObjectCollision();
		// 貫通ベクトルをゲームオブジェクトに反映する
		void ApplyPenetration(WorldCollderList*, GameObject*, const Vector3&);
		// コライダー単位の衝突判定
		void HandleWorldColliderCollision(WorldCollderList* a, WorldCollderList* b);
		// 破棄予定のゲームオブジェクトを削除する
		void RemoveDestroyedGameObject();
		// カメラに近いライトを選んでGPUメモリにコピーする
		void UpdateShaderLight();
		// スカイスフィアを描画する
		void DrawSkySphere();
		// デプスシャドウマップを作成
		void CreateShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end);

	private:

		// ウィンドウ
		GLFWwindow* window = nullptr;	// ウィンドウオブジェクト
		const std::string title = "OpenGLGame";	// ウィンドウタイトル

		// アプリケーションポインター
		ApplicationPtr application;

		// シーンマネージャーポインター
		SceneSystem::SceneManagerPtr sceneManager;

		/// シェーダー管理用メンバー変数
		ProgramObjectPtr prog3D;		// ライト付きシェーダー
		ProgramObjectPtr progUnlit;		// ライト無しシェーダー
		ProgramObjectPtr progShadow;	// 影付きテクスチャ作成シェーダー
		ProgramObjectPtr progSkeletal3D;
		ProgramObjectPtr progShadowSkeletal3D;

		// 3Dモデルの影描画用の変数
		FrameBufferObjectPtr fboShadow;	// デプスシャドウ用FBO

		MeshBufferPtr meshBuffer;		// 図形データ管理オブジェクト
		GltfFileBufferPtr gltfFileBuffer;
		GLsizei indexCount = 0;			// インデックスのサイズ

		// コンストラクタ、デストラクタを呼べるようにするための補助クラス
		struct TexHelper : public Texture {
			TexHelper(const char* p, Usage usage = Usage::for3D) : Texture(p, usage) {}
			TexHelper(const char* p, int w, int h, GLenum f) :Texture(p, w, h, f) {}
		};
		std::unordered_map<std::string, TexturePtr> textureCache;

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

		// ゲームオブジェクト
		GameObjectList gameObjects; // ゲームオブジェクト配列
		GameObjectPtr camera = nullptr;			// カメラオブジェクト
	};
}
#endif // !ENGINE_H_INCLUDED
