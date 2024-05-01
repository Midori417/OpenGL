/**
* @file Engine.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include "Engine.h"
#include "GameObject.h"
#include "FrameBufferObject.h"
#include "Debug.h"
#include "EasyAudio.h"
#include "Time.h"
#include "GltfMesh.h"
#include "Input.h"
#include "GamePad.h"
#include "ProgramObject.h"
#include "SceneManager.h"
using namespace SceneManagment;


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "AabbCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include <vector>
#include <fstream>
#include <filesystem>

// 図形データ
#include "box_mesh.h"
#include "plane_xy_mesh.h"

/**
* OpenGLからのメッセージを処理するコールバック関数
*
* @param source		メッセージの発信者
* @param type		メッセージの種類
* @param id			メッセージを一位に選別する値
* @param severiry	メッセージの重要度(高、中、小、最低)
* @param length		メッセージの文字数、負数ならメッセージは0終端されている
* @param message	メッセージ本体
* @param userParam	コールバック設定時に指定したポインタ
*/
void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string s;
	if (length < 0)
	{
		s = message;
	}
	else
	{
		s.assign(message, message + length);
	}
	s += '\n';
	LOG(s.c_str());
}

/**
* ゲームエンジンを実行する
*
* @retval 0		正常に終了
* @retval 0以外 エラーが発生した
*/
int Engine::Run()
{
	const int result = Initialize();
	if (result) {
		return result;
	}

	// 音声ライブラリを初期化
	if (!EasyAudio::Initialize()) {
		return 1;
	}

	// ループ
	while (!glfwWindowShouldClose(window))
	{
		// -------------------------
		// ImGuiフレームの更新
		// -------------------------

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		Update();
		RemoveDestroyedGameObject();
		Render();

		// 時間ライブラリを更新
		Time::Update();
		// 入力ライブラリを更新
		Input::Update(window);
		GamePad::Update();
		// 音声ライブラリを更新
		EasyAudio::Update();

	}


	// 音声ライブラリを終了
	EasyAudio::Finalize();
	GamePad::DestoryGamePad();


	// -----------------
	// ImGuiの終了
	// -----------------

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();

	// ------------------------
	// コンテキストの削除
	// ------------------------

	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

/**
* すべてのゲームオブジェクトを削除する
*/
void Engine::AllClearGameObject()
{
	for (auto& e : gameObjects) {
		e->OnDestroy();
	}
	SetMainCamera(nullptr);
	gameObjects.clear();
}

/**
* ライト配列を初期化する
*/
void Engine::InitialzeLight()
{
	// 指定された数のライトを生成する
	lights.resize(lightResizeCount);
	usedLights.reserve(lightResizeCount);

	// すべてのライトを未使用ライト配列に「逆順」で追加
	freeLights.resize(lightResizeCount);
	for (int i = 0; i < lightResizeCount; ++i) {
		freeLights[i] = static_cast<int>(lightResizeCount - i - 1);
	}
}

/**
* 新しいライトを取得する
*
* @return ライトのインデックス
*/
int Engine::AllocateLight()
{
	// 未使用のライトがなければライト配列を拡張する
	if (freeLights.empty()) {
		const size_t oldSize = lights.size();
		lights.resize(oldSize + lightResizeCount);
		// 拡張子吾ライトを未使用ライト配列に「逆順」で追加
		for (size_t i = lights.size() - 1; i >= oldSize; --i) {
			freeLights.push_back(static_cast<int>(i));
		}
	}

	// 未使用ライト配列の末尾からインデックスを取り出す
	const int index = freeLights.back();
	freeLights.pop_back();

	// 取り出したインデックスを使用中ライト配列に追加
	usedLights.push_back(index);

	// ライトの状態を「使用中」にする
	lights[index].used = true;

	// 取り出したインデックスを返す
	return index;
}

/**
* ライトを開放する
*
* @param index 解放したいライトのインデックス
*/
void Engine::DeallocateLight(int index)
{
	if (index >= 0 && index < lights.size()) {
		// インデックスを未使用ライト配列に追加
		freeLights.push_back(index);

		// ライトの状態を「未使用」にする
		lights[index].used = false;
	}
}

/**
* 指定されたポイントライトを取得
*
* @param index ほしいライトのindex
*
* @return indexに対応するライト
*/
LightData* Engine::GetLight(int index)
{
	if (index >= 0 && index < lights.size() && lights[index].used) {
		return &lights[index];
	}
	return nullptr;
}

/**
* 指定されたポイントライトを取得
*
* @param index ほしいライトのindex
*
* @return indexに対応するライト
*/
const LightData* Engine::GetLight(int index) const
{
	return const_cast<Engine*>(this)->GetLight(index);
}


/**
* フレームバッファの大きさを取得する
*
* @return フレームバッファの縦の横のサイズ
*/
Vector2 Engine::GetFramebufferSize() const
{
	int w = 0;
	int h = 0;
	glfwGetFramebufferSize(window, &w, &h);
	return Vector2{ static_cast<float>(w), static_cast<float>(h) };
}

/**
* フレームバッファのアスペクト比を取得する
*
* @return フレームバッファのアスペクト比
*/
float Engine::GetAspectRatio() const
{
	const Vector2 size = GetFramebufferSize();
	return size.x / size.y;
}

/**
* glTFファイルを読み込む
*
* @param filename 読み込むglTFファイル名
*
* @retval nullptr以外	作成したglTFファイルオブジェクト
* @retval nullptr		読み込み失敗
*/
GltfFilePtr Engine::LoadGltf(const char* filename)
{
	return gltfFileBuffer->Load(filename);
}

/**
* テクスチャの取得
*
* @param name テクスチャのファイル名
*
* @return 名前がnameと一致するテクスチャ
*/
TexturePtr Engine::GetTexture(const char* name, Texture::Usage usage)
{
	// キャッシュがあれば、キャッシュされたテクスチャを返す
	auto itr = textureCache.find(name);
	if (itr != textureCache.end()) {
		return itr->second; // キャッシュされたテクスチャを返す
	}


	// キャッシュになければ、テクスチャを作成してキャッシュに登録
	auto tex = std::make_shared<TexHelper>(name, usage);
	textureCache.emplace(name, tex);
	return tex; // 作成したテクスチャを返す

}

/**
* ゲームエンジンを初期化する
*
* @retval 0		正常に終了
* @ratval 0以外	エラーが発生
*/
int Engine::Initialize()
{
	// GLFWの初期化
	if (glfwInit() != GLFW_TRUE)
	{
		return 1; // 初期化失敗
	}

	// 描画ウィンドウの作成
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_HOVERED, GLFW_FALSE);
	window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
	if (!window) 
	{
		glfwTerminate();
		return 1; // ウィンドウの作成失敗
	}


	// OpenGLコンテキストの作成
	glfwMakeContextCurrent(window);

	// OpenGL関数のアドレスを取得
	// OpenGLVersion 4.5
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		glfwTerminate();
		return 1;	// アドレスの取得失敗
	}

	// メッセージコールバック設定
	glDebugMessageCallback(DebugCallback, nullptr);

	// ライトを初期化
	InitialzeLight();

	prog3D = std::make_shared<ProgramObject>("standard3D","Src/Shader/standard3D.vert", "Src/Shader/standard3D.frag");
	progShadow = std::make_shared<ProgramObject>("shadow3D", "Src/Shader/shadow3D.vert", "Src/Shader/shadow3D.frag");
	progSkeletal3D = std::make_shared<ProgramObject>("skeletal3D","Src/Shader/skeletal3D.vert", "Src/Shader/standard3D.frag");
	progShadowSkeletal3D = std::make_shared<ProgramObject>("shadowSkeletal3D","Src/Shader/shadowSkeletal3D.vert", "Src/Shader/shadow3D.frag");
	progUnlit = std::make_shared<ProgramObject>("unlit", "Src/Shader/unlit.vert", "Src/Shader/unlit.frag");

	glProgramUniform1f(*progShadow, locAlphaCutoff, 0.5f);	// カットオフ値を設定しておく
	glProgramUniform1f(*progShadowSkeletal3D, locAlphaCutoff, 0.5f);	// カットオフ値を設定しておく

	// FBOの作成
	auto texShadow = std::make_shared<TexHelper>(
		"FBO(depth)", 2048, 2048, GL_DEPTH_COMPONENT32);
	fboShadow = std::make_shared<FrameBufferObject>(nullptr, texShadow);


	// 図形データの情報
	struct MeshData
	{
		const char* name;				// メッシュ名
		const char* textureFilename;	// テクスチャファイル名
		size_t vertexSize;		// 頂点データのバイト数
		size_t indexSize;		// インデックスデータのバイト数
		const void* vertexData;	// 頂点データのアドレス
		const void* indexData;	// インデックスデータのアドレス
	};
	const MeshData meshes[] = {
		{"box", nullptr, sizeof(box_vertices), sizeof(box_indices), box_vertices, box_indices},
		{"plane_xy", nullptr, sizeof(plane_xy_vertices), sizeof(plane_xy_indices), plane_xy_vertices, plane_xy_indices},
	};

	// 図形データから描画パラメータを作成し、データをGPUメモリにコピーする
	meshBuffer = MeshBuffer::Create(32000000);
	meshBuffer->SetTextureCallback([this](const char* filename) {return GetTexture(filename); });
	// glTFファイル用バッファを初期化
	const size_t maxAnimationModelCount = 64;	// アニメーションするモデル数
	const size_t maxAnimationMatrixCount = 256;	// 1モデルのボーン数
	gltfFileBuffer = GltfFileBuffer::Create(10'000'000, maxAnimationModelCount * maxAnimationMatrixCount);
	gltfFileBuffer->SetTextureCallback([this](const char* filename) {return GetTexture(filename); });

	for (const auto& e : meshes) {
		auto pVertex = static_cast<const Vertex*>(e.vertexData);
		auto pIndex = static_cast<const uint16_t*>(e.indexData);
		std::vector<Vertex> v(pVertex, pVertex + e.vertexSize / sizeof(Vertex));

		// コピーした図形データ法線を設定
		for (auto& e : v)
		{
			e.normal = { 0,0,0 };
		}
		FillMissingNormals(v.data(), v.size(), pIndex, e.indexSize / sizeof(uint16_t));

		// 法線を設定した図形データをGPUメモリにコピー
		meshBuffer->AddVertexData(v.data(), e.vertexSize, pIndex, e.indexSize);

		// 直前のAddVertexDataで作成した描画パラメータを取得
		const DrawParams& drawParams = meshBuffer->GetDrawParams(meshBuffer->GetDrawParamsCount() - 1);

		// テクスチャを作成
		TexturePtr texBaseColor;
		if (e.textureFilename) {
			texBaseColor = GetTexture(e.textureFilename);
		}

		// 描画パラメータとテクスチャをからスタティックメッシュを作成
		meshBuffer->CreateStaticMesh(e.name, drawParams, texBaseColor);
	}

	// OBJファイルを読み込む
	meshBuffer->LoadObj("Res/Gundam/Model/MagunamBullet.obj");
	meshBuffer->LoadObj("Res/Map/Load.obj");
	meshBuffer->LoadObj("Res/Map/Biru01.obj");
	meshBuffer->LoadObj("Res/Map/Biru02.obj");
	meshBuffer->LoadObj("Res/Map/Biru03.obj");


	// ---------------------------
	// コンテキスト作成
	// ---------------------------

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// ------------------------
	// ImGuiの初期化
	// ------------------------

	// GLFW
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	// GLSLのバージョンを指定
	ImGui_ImplOpenGL3_Init("#version 450");

	ImGuiIO io = ImGui::GetIO();
	ImFont* font01 = io.Fonts->AddFontFromFileTTF("Res/Font/arial.ttf", 100);
	ImFont* font02 = io.Fonts->AddFontFromFileTTF("Res/Font/arial.ttf", 160);

	// SkySphereの設定
	skySphere = meshBuffer->LoadObj("Res/sky_sphere/sky_sphere.obj");

	// ゲームオブジェクト配列を予約
	gameObjects.reserve(1000);

	// Axisの登録
	Input::AxisSet("Horizontal");
	Input::AxisSet("Vertical");

	return 0;
}

/**
* ゲームエンジンの状態を更新する
*/
void Engine::Update()
{
	SceneManager::Update(*this);

	// アニメーションバッファをクリア
	gltfFileBuffer->ClearAnimationBuffer();

	// 描画の前処理を実行
	for (auto& e : gameObjects)
	{
		if (e->renderer)
		{
			e->renderer->PreDraw();
		}
	}

	// アニメーションバッファをGPUメモリにコピーする
	gltfFileBuffer->UploadAnimationBuffer();
	// ゲームオブジェクトの衝突を調べる
	HandleGameObjectCollision();
	// ゲームオブジェクトを更新する
	UpdateGameObject();

}

/**
* ゲームエンジンの状態を描画する
*/
void Engine::Render()
{
	// バックバッファをクリア
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// フレームバッファの大きさを取得
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

	const GLuint programs[] = { *prog3D, *progUnlit, *progSkeletal3D };
	for (auto prog : programs) {

		if (GetMainCamera() != nullptr) {
			auto fovScale = camera->GetComponent<Camera>()->GetFovScale();
			// アスペクト比と視野角を設定
			const float aspectRatio =
				static_cast<float>(fbWidth) / static_cast<float>(fbHeight);
			glProgramUniform2f(prog, 3, fovScale / aspectRatio, fovScale);

			// カメラパラメータを設定
			Vector3 pos;
			Vector3 scale;
			Matrix3x3 rm;
			Decompose(camera->transform->GetTransformMatrix(), pos, scale, rm);
			Quaternion q = Quaternion::RotationMatrixToQuaternio(rm);
			rm = Quaternion::Matrix3x3Cast(Quaternion(q.x, q.y, q.z, -q.w));
			glProgramUniform3fv(prog, 4, 1, &pos.x);
			glProgramUniformMatrix3fv(prog, 7, 1, GL_FALSE, &rm.data[0].x);
		}
	}

	glEnable(GL_DEPTH_TEST);	// 深度テストを有効化
	glEnable(GL_CULL_FACE);		// 裏面カリングを有効化

	// 半透明合成を有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	// ライトの更新
	UpdateShaderLight();


	// ゲームオブジェクトをレンダーキュー順に並べる
	std::stable_sort(gameObjects.begin(), gameObjects.end(),
		[](const GameObjectPtr& a, const GameObjectPtr& b) {
			return a->renderQueue < b->renderQueue; });

	// transparentキューの先頭を検索
	const auto transparentBegin = std::lower_bound(
		gameObjects.begin(), gameObjects.end(), RenderQueue_transparent,
		[](const GameObjectPtr& e, int value) { return e->renderQueue < value; });

	// overlayキューの先頭を検索
	const auto overlayBegin = std::lower_bound(
		transparentBegin, gameObjects.end(), RenderQueue_overlay,
		[](const GameObjectPtr& e, int value) { return e->renderQueue < value; });


	// === ゲームオブジェクトを描画 === //

	// デプスシャドウマップを作成
	CreateShadowMap(gameObjects.begin(), transparentBegin);

	// 描画先をデフォルトフレームバッファに戻す
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, fbWidth, fbHeight);
	glUseProgram(*prog3D);

	// transparent以前のキューを描画
	glProgramUniform1f(*prog3D, locAlphaCutoff, 0.5f);
	DrawGameObject(*prog3D, gameObjects.begin(), transparentBegin);
	glProgramUniform1f(*prog3D, locAlphaCutoff, 0);

	// スカイスフィアを描画
	DrawSkySphere();

	// transparentからoverlayまでのキューを描画
	glDepthMask(GL_FALSE); // 深度バッファへの書き込みを禁止
	DrawGameObject(*prog3D, transparentBegin, overlayBegin);
	glDepthMask(GL_TRUE); // 深度バッファへの書き込みを許可

	// overlay以降のキューを描画
	glDisable(GL_DEPTH_TEST);	// 深度テストを無効化
	glDisable(GL_CULL_FACE);	// 裏面カリングを無効化
	glUseProgram(*progUnlit);
	DrawGameObject(*progUnlit, overlayBegin, gameObjects.end());

	// エディタ画面を描画
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

/**
* ゲームオブジェクト配列を描画する
*
* @param prog	描画に使うプログラムパイプラインオブジェクト
* @param begin	描画するゲームオブジェクト範囲の先端
* @param end	描画するゲームオブジェクト範囲の終端
*/
void Engine::DrawGameObject(const ProgramObject& prog, GameObjectList::iterator begin, GameObjectList::iterator end)
{

	for (GameObjectList::iterator i = begin; i != end; ++i) {
		const auto& e = *i;
		if (e->renderer)
		{
			if (e->renderer->GetModelFormat() == ModelFormat::obj || e->renderer->GetModelFormat() == ModelFormat::gltfStatic)
			{
				glBindVertexArray(*meshBuffer->GetVAO());
				glUseProgram(prog);
				e->renderer->Draw(prog);
				glUseProgram(0);

			}
			else if (e->renderer->GetModelFormat() == ModelFormat::gltfAnimated)
			{
				glUseProgram(*progSkeletal3D);
				glProgramUniform1f(*progSkeletal3D, locAlphaCutoff, 0.5f);
				e->renderer->Draw(*progSkeletal3D);
				glUseProgram(0);
			}
		}
	}

}

/**
* ゲームオブジェクトを更新する
*
* @param deltaTime	前回の更新からの経過時間
*/
void Engine::UpdateGameObject()
{
	// スタートイベント処理
	for (int i = 0; i < gameObjects.size(); ++i) {

		// ゲームオブジェクトを取得
		GameObject* e = gameObjects[i].get();
		// ゲームオブジェクトが破棄予定されていないか
		if (!e->IsDestroyed()) {
			e->Start();
		}
	}

	// 要素の追加に対応するために添え字を使う
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		// ゲームオブジェクトを取得
		GameObject* e = gameObjects[i].get();
		// ゲームオブジェクトが破棄予定されていないか
		if (!e->IsDestroyed()) {
			e->Update();
		}
	}
	for (int i = 0; i < gameObjects.size(); ++i) 
	{
		// ゲームオブジェクトを取得
		GameObject* e = gameObjects[i].get();
		// ゲームオブジェクトが破棄予定されていないか
		if (!e->IsDestroyed()) {
			e->LateUpdate();
		}
	}

	// ローカル座標変換行列を計算
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		GameObject* e = gameObjects[i].get();
		if (e->transform != nullptr)
		{	
			e->transform->SetTransformMatrix(GetTransformMatrix(e->transform->scale, e->transform->rotation, e->transform->position));
			e->transform->SetNormalMatrix(Quaternion::Matrix3x3Cast(Quaternion(e->transform->rotation)));
		}
	}

	// ワールド座標変換行列を計算
	std::vector<Matrix4x4> worldTransforms(gameObjects.size());
	std::vector<Matrix3x3> worldNormals(gameObjects.size());
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		GameObject* e = gameObjects[i].get();
		if (e->transform != nullptr)
		{
			Matrix4x4 m = e->transform->GetTransformMatrix();
			Matrix3x3 n = e->transform->GetNormalMatrix();
			for (e = e->parent; e; e = e->parent)
			{
				m = e->transform->GetTransformMatrix() * m;
				n = e->transform->GetNormalMatrix() * n;
			}
			worldTransforms[i] = m;
			worldNormals[i] = n;
		}
	}

	// ワールド座標変換行列をゲームオブジェクトに設定
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i]->transform->SetTransformMatrix(worldTransforms[i]);
		gameObjects[i]->transform->SetNormalMatrix(worldNormals[i]);
	}
}

/**
* ゲームオブジェクトの衝突を処理する
*/
void Engine::HandleGameObjectCollision()
{
	// ワールド座標系の衝突判定を作成
	std::vector<WorldCollderList> colliders;
	colliders.reserve(gameObjects.size());
	for (const auto& e : gameObjects) {
		if (e->colliders.empty()) {
			continue; // コライダーを持っていなかったら何もしない
		}

		// 「接地していない」状態にする
		e->isGrounded = false;

		// 衝突判定を作成
		WorldCollderList list(e->colliders.size());
		for (int i = 0; i < e->colliders.size(); ++i) {
			// オリジナルのコライダーをコピー
			list[i].origin = e->colliders[i];

			//コライダーの座標をワールド座標に変換
			list[i].world = e->colliders[i]->GetTransformedCollider(e->transform->GetTransformMatrix());
		}
		colliders.push_back(list);
	}

	if (colliders.size() >= 2) {
		// ゲームオブジェクト単位の衝突判定
		for (auto a = colliders.begin(); a != colliders.end() - 1; ++a) {
			const GameObject* goA = a->at(0).origin->GetGameObject();
			if (goA->IsDestroyed()) {
				continue;	// 削除済みなので飛ばす
			}
			for (auto b = a + 1; b != colliders.end(); ++b) {
				const GameObject* goB = b->at(0).origin->GetGameObject();
				if (goB->IsDestroyed()) {
					continue;	// 削除済みなので飛ばす
				}
				HandleWorldColliderCollision(&*a, &*b); // コライダー単位の衝突判定
			}
		}
	}
}

/**
* 型によって交差判定関数を呼び分けるための関数テンプレート
*/
template<class T, class U>
bool CallIntersect(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
{
	return Intersect(static_cast<T&>(*a).GetShape(), static_cast<U&>(*b).GetShape(), p);
}

/**
* 型によって交差判定関数を呼び分けるための関数テンプレート
*
* 交差判定関数に渡す引数を逆にするバージョン
*/
template<class T, class U>
bool CallIntersectRevers(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
{
	if (Intersect(static_cast<U&>(*b).GetShape(), static_cast<T&>(*a).GetShape(), p)) {
		p *= -1;	// 貫通ベクトルを逆向きにする
		return true;
	}
	return false;
}

/**
* 常にfalseを返す関数テンプレート
*
* 未実装または実装予定のない組み合わせ用
*/
template<class T, class U>
bool NotImplemented(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
{
	return false;
}

/**
* 貫通ベクトルをゲームオブジェクトに反映する
*/
void Engine::ApplyPenetration(WorldCollderList* worldColliders, GameObject* gameObject, const Vector3& penetration)
{
	// 設置判定
	// 衝突ベクトルが垂直に近い場合、床と触れたとみなす
	static const float cosGround = cosf(90 * Mathf::Deg2Rad); //　床とみなす角度
	if (penetration.y > 0)
	{
		// 対象が単位垂直ベクトルであることを利用して、内積による角度の比較を単純化
		const float d = penetration.magnitude();
		if (penetration.y >= d * cosGround) {
			gameObject->isGrounded = true; // 設置した
		}
	}

	// すべてのワールドコライダーを移動
	for (auto& e : *worldColliders) 
	{
		e.AddPosition(penetration);
	}
}


/**
* コライダー単位の衝突判定
*
* @param a 判定対象のワールドコライダー配列その１
* @param b 判定対象のワールドコライダー配列その２
*/
void Engine::HandleWorldColliderCollision(WorldCollderList* a, WorldCollderList* b)
{
	// 関数ポインタ型を定義
	using FuncType = bool(*)(const ColliderPtr&, const ColliderPtr&, Vector3&);

	// 組み合わせに対応する交差判定関数を選ぶための配列
	static const FuncType funcList[3][3] = {
		{
			CallIntersect<AabbCollider, AabbCollider>,
			CallIntersect<AabbCollider, SphereCollider>,
			NotImplemented<AabbCollider, BoxColliderPtr>,
		},
		{
			CallIntersectRevers<SphereCollider, AabbCollider>,
			CallIntersect<SphereCollider, SphereCollider>,
			CallIntersectRevers<SphereCollider, BoxCollider>,
		},
		{
			NotImplemented<BoxCollider, AabbCollider>,
			CallIntersect<BoxCollider, SphereCollider>,
			NotImplemented<BoxCollider, BoxCollider>,
		},
	};

	// コライダー単位の衝突判定
	for (auto& colA : *a) {
		for (auto& colB : *b) {
			// スタティックコライダー同氏は衝突しない
			if (colA.origin->isStatic && colB.origin->isStatic) {
				continue;
			}
			// 衝突判定を行う
			Vector3 penetration;
			const int typeA = static_cast<int>(colA.origin->GetType());
			const int typeB = static_cast<int>(colB.origin->GetType());
			if (funcList[typeA][typeB](colA.world, colB.world, penetration)) {
				GameObject* goA = colA.origin->GetGameObject();
				GameObject* goB = colB.origin->GetGameObject();

				// コライダーが重ならないように座標を調整
				if (!colA.origin->isTrigger && !colB.origin->isTrigger)
				{
					if (colA.origin->isStatic)
					{
						// Aは動かないのでBを移動させる
						ApplyPenetration(b, goB, penetration);
					}
					else if (colB.origin->isStatic)
					{
						// Bは動かないのでAを移動させる
						ApplyPenetration(a, goA, -penetration);
					}
					else 
					{
						// AとBを均等に移動させる
						ApplyPenetration(b, goB, penetration * 0.5f);
						ApplyPenetration(a, goA, penetration * -0.5f);
					}
				}

				// イベントの呼び出し
				goA->OnCollision(colA.origin, colB.origin);
				goB->OnCollision(colB.origin, colA.origin);

				// イベントの結果、どちらかのゲームオブジェクトが破壊されたらループ終了
				if (goA->IsDestroyed() || goB->IsDestroyed()) {
					return;	// 関数終了
				}
			}
		}
	}

}


/**
* 破棄予定のゲームオブジェクトを削除
*/
void Engine::RemoveDestroyedGameObject()
{
	// ゲームオブジェクトを持っていなければ何もしない
	if (gameObjects.empty()) {
		return;
	}

	// 破棄予定の有無でゲームオブジェクトを分ける
	const auto iter = std::stable_partition(
		gameObjects.begin(), gameObjects.end(),
		[](const GameObjectPtr p) {return !p->IsDestroyed(); });

	// 破棄予定のゲームオブジェクトを別の配列に移動
	GameObjectList destroyList(
		std::move_iterator(iter),
		std::move_iterator(gameObjects.end()));

	// 配列から移動済みゲームオブジェクトを削除
	gameObjects.erase(iter, gameObjects.end());

	// 破棄予定のゲームオブジェクトのOnDestroyを実行
	for (auto& e : destroyList) {
		e->OnDestroy();
	}
}// ここでdestoryListの寿命がおわり削除される

/**
* カメラに近いライトを選んでGPUメモリーにコピーする
*/
void Engine::UpdateShaderLight()
{
	const GLuint programs[] = { *prog3D, *progSkeletal3D };

	for (auto prog : programs) {
		// 環境光をGPUメモリにコピー
		glProgramUniform3fv(prog, locAmbientLight, 1, &ambientLight.x);

		// 平行光源のパラメターをGPUメモリにコピー
		const Vector3 color = directionLight.color * directionLight.intensity;
		glProgramUniform3fv(prog, locDirectionalLightColor, 1, &color.x);
		glProgramUniform3fv(prog, locDirectionalLightDericion, 1, &directionLight.direction.x);
	}

	// コピーするライトがなければライト数を0に設定
	if (usedLights.empty()) {
		for (auto prog : programs) {
			if (usedLights.empty()) {
				glProgramUniform1i(prog, locLightCount, 0);
				return;
			}
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
	const Vector3 front = camera->transform->forward();

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
		const Vector3 v = light.position - camera->transform->position;
		// カメラの後ろにあるライトを除外
		if (Vector3::Dot(front, v) <= -light.radius) {
			continue;
		}
		const float d = v.magnitude() - light.radius; // カメラからのライトまでの半駅までの距離
		distanceList.push_back({ d,&light });
	}
	// 画面に影響するライトがなければライト数を0に設定
	if (distanceList.empty()) {
		for (auto prog : programs) {
			glProgramUniform1i(prog, locLightCount, 0);
		}
		return;
	}

	// カメラに近いライトを優先する
	std::stable_sort(distanceList.begin(), distanceList.end(),
		[&](const auto& a, const auto& b) {return a.distance < b.distance; });

	// ライトデータをGPUメモリにコピーする
	const int lightCount = static_cast<int>(std::min(distanceList.size(), maxShaderLightCount)); // コピーするライト数
	std::vector<Vector4> colorAndFalloffAngle(lightCount);
	std::vector<Vector4> positionAndRadius(lightCount);
	std::vector<Vector4> directionAndConeAngle(lightCount);
	for (int i = 0; i < lightCount; ++i)
	{
		const LightData* p = distanceList[i].p;
		const Vector3 color = p->color * p->intensity;
		colorAndFalloffAngle[i] = Vector4{
			color.x,color.y,color.z, p->falloffAngle
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
		glProgramUniform4fv(prog, locLightColorAndFalloffAngle, lightCount, &colorAndFalloffAngle[0].x);
		glProgramUniform4fv(prog, locLightPositionAndRadius, lightCount, &positionAndRadius[0].x);
		glProgramUniform4fv(prog, locLightDirectionAndConeAngle, lightCount, &directionAndConeAngle[0].x);
		glProgramUniform1i(prog, locLightCount, lightCount);
	}
}

/**
* スカイスフィアを描画する
*/
void Engine::DrawSkySphere()
{
	// シーンにスカイスフィアが設定されていない場合は描画しない
	if (!skySphere || !SceneManager::CurrentSceneSkyMaterial())
	{
		return;
	}

	// アンリッドシェーダで描画
	glUseProgram(*progUnlit);
	glBindVertexArray(*meshBuffer->GetVAO());
	glDepthMask(GL_FALSE);	// 深度バッファへの書き込みを禁止

	// スカイスフィアの半径を0.5mと仮定し、描画範囲の95%の大きさに拡大
	static const float far = 1000;	// 描画範囲の最大値
	static const float scale = far * 0.95f / 0.5f;
	static const Matrix4x4 transformMatrix = {
		Vector4(scale, 0,		0,		0),
		Vector4(0,		scale,	0,		0),
		Vector4(0,		0,		scale,	0),
		Vector4(0,		0,		0,		1),
	};
	glProgramUniformMatrix4fv(*progUnlit, 0, 1, GL_FALSE, &transformMatrix[0].x);

	// 色はマテリアルカラーで調整するのでオブジェクトカラーは白に設定
	static const Vector4 color = Vector4{ 1,1,1,1 };
	glProgramUniform4fv(*progUnlit, locColor, 1, &color.x);

	// スカイスフィアはカメラを原点として描画
	static const Vector3 skySphereCameraPosition = { 0,0,0 };
	glProgramUniform3fv(*progUnlit, 4, 1, &skySphereCameraPosition.x);

	// スカイスフィアを描画
	const MaterialList materials(1, SceneManager::CurrentSceneSkyMaterial());
	Draw(*skySphere, *progUnlit, materials);

	glProgramUniform3fv(*progUnlit, 4, 1, &camera->transform->position.x);	// カメラ座標を元に戻す
	glDepthMask(GL_TRUE);	// 深度バッファへの書き込みを許可
	glUseProgram(*prog3D);
}

/**
* デプスシャドウマップの作成
*/
void Engine::CreateShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end)
{
	// 描画先フレームバッファを変更
	glBindFramebuffer(GL_FRAMEBUFFER, *fboShadow);

	// ビューポートをフレームバッファのサイズに合わせる
	const auto& texShadow = fboShadow->GetDepthTexture();
	glViewport(0, 0, texShadow->GetWidth(), texShadow->GetHeight());

	// 深度バッファをクリア
	glClear(GL_DEPTH_BUFFER_BIT);

	const GLuint programs[] = { *progShadow, *progShadowSkeletal3D };

	// 影の描画パラメータ
	const float shadowAreaSize = 200;	// 影の描画範囲(XY平面)
	const float shadowNearZ = 1;		// 影の描画範囲(近Z平面)
	const float shadowFarZ = 100;		// 影の描画範囲(遠Z平面)
	const float shadowCenterZ = (shadowNearZ + shadowFarZ) * 0.5f; // 描画範囲の中心
	const Vector3 target = { 0, 0, -50 }; // カメラの注視点
	const Vector3 eye = target - directionLight.direction * shadowCenterZ; // カメラの位置

	// ビュープロジェクション行列を計算
	const Matrix4x4 matShadowView = LookAt(eye, target, Vector3::up);
	const Matrix4x4 matShadowProj = Orthogonal(
		-shadowAreaSize / 2, shadowAreaSize / 2,
		-shadowAreaSize / 2, shadowAreaSize / 2,
		shadowNearZ, shadowFarZ);
	const Matrix4x4 matShadow = matShadowProj * matShadowView;

	for (auto prog : programs)
	{
		// ビュープロジェクション行列をGPUメモリにコピー
		glProgramUniformMatrix4fv(prog, locViewProjectionMatrix, 1, GL_FALSE, &matShadow[0].x);
	}

	// メッシュを描画
	for (GameObjectList::iterator i = begin; i != end; ++i)
	{
		const auto& e = *i;
		if (e->renderer)
		{
			if (e->renderer->GetModelFormat() == ModelFormat::obj || e->renderer->GetModelFormat() == ModelFormat::gltfStatic)
			{
				glUseProgram(*progShadow);
				glBindVertexArray(*meshBuffer->GetVAO());
				e->renderer->Draw(*progShadow, Renderer::Type::Shadow);
				glBindVertexArray(0);
			}
			else if (e->renderer->GetModelFormat() == ModelFormat::gltfAnimated)
			{
				glUseProgram(*progShadowSkeletal3D);
				e->renderer->Draw(*progShadowSkeletal3D, Renderer::Type::Shadow);
				glBindVertexArray(0);
			}
		}
	}

	// 深度テクスチャを割り当てる
	glBindTextureUnit(2, *texShadow);

	// 深度テクスチャ座標への変換行列を作成
	static const Matrix4x4 matTexture = {
		Vector4{0.5f, 0.0f, 0.0f, 0.0f},
		Vector4{0.0f, 0.5f, 0.0f, 0.0f},
		Vector4{0.0f, 0.0f, 0.5f, 0.0f},
		Vector4{0.5f, 0.5f, 0.5f, 1.0f}
	};

	// シャドウテクスチャ行列をGPUメモリにコピー
	const Matrix4x4 matShadowTexture = matTexture * matShadowProj * matShadowView;
	glProgramUniformMatrix4fv(*prog3D, locShadowTextureMatrix, 1, GL_FALSE, &matShadowTexture[0].x);
	glProgramUniformMatrix4fv(*progSkeletal3D, locShadowTextureMatrix, 1, GL_FALSE, &matShadowTexture[0].x);

	// 法線方向の設定
	const float texSize = shadowAreaSize / static_cast<float>(texShadow->GetWidth());
	glProgramUniform1f(*prog3D, locShadowNormalOffset, texSize);
	glProgramUniform1f(*progSkeletal3D, locShadowNormalOffset, texSize);

}