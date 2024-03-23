/**
* @file GltfAnimationMeshRenderer.h 
*/
#ifndef COMPONENT_GLTFANIMATIONMESHRENDERER_H_INCLUDED
#define COMPONENT_GLTFANIMATIONMESHRENDERER_H_INCLUDED
#include "Renderer.h"
#include "GltfMesh.h"
#include "ProgramObject.h"

namespace FGEngine
{

	/**
	* アニメーションつきglTFメッシュ描画用コンポーネント
	*/
	class GltfAnimatedMeshRenderer : public Renderer
	{
	public:

		// アニメーションの再生状態
		enum class State
		{
			stop,
			play,
			pause,
		};

		// コンストラクタ・デストラクタ
		GltfAnimatedMeshRenderer() = default;
		virtual ~GltfAnimatedMeshRenderer() = default;

		// シェーダの種類
		virtual ModelFormat GetModelFormat() const override
		{
			return ModelFormat::gltfAnimated;
		}

		virtual void Update() override;
		virtual void PreDraw() override;
		virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const;

		// アニメーションの制御
		void Play();
		void Stop();
		void Pause();
		State GetState() const { return state; }

		// アニメーションの指定と取得
		bool SetAnimation(const GltfAnimationPtr& animation, bool isLoop = true);
		bool SetAnimation(const std::string& name, bool isLoop = true);
		bool SetAnimation(size_t index, bool isLoop = true);

		float GetTime() const
		{
			return time;
		}
		const GltfAnimationPtr& GetAnimation() const
		{
			return animation;
		}

	public:

		std::vector<GltfMaterialPtr> materials;		// 固有マテリアル
		GltfFileBufferPtr fileBuffer;
		GltfFilePtr file;							// 描画に使うglTFファイル
		float time = 0;								// 現在の再生時刻
		float animationSpeed = 1;
		bool isLoop = true;

	private:

		std::vector<GltfFileBuffer::Range> ssboRanges;
		State state = State::stop;	// 再生状態
		GltfAnimationPtr animation;	// 再生するアニメーション
	};
	using GltfAnimatedMeshRendererPtr = std::shared_ptr<GltfAnimatedMeshRenderer>;
}
#endif // !COMPONENT_GLTFANIMATIONMESHRENDERER_H_INCLUDED
