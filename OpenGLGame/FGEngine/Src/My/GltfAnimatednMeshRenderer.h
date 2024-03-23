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
	* �A�j���[�V������glTF���b�V���`��p�R���|�[�l���g
	*/
	class GltfAnimatedMeshRenderer : public Renderer
	{
	public:

		// �A�j���[�V�����̍Đ����
		enum class State
		{
			stop,
			play,
			pause,
		};

		// �R���X�g���N�^�E�f�X�g���N�^
		GltfAnimatedMeshRenderer() = default;
		virtual ~GltfAnimatedMeshRenderer() = default;

		// �V�F�[�_�̎��
		virtual ModelFormat GetModelFormat() const override
		{
			return ModelFormat::gltfAnimated;
		}

		virtual void Update() override;
		virtual void PreDraw() override;
		virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const;

		// �A�j���[�V�����̐���
		void Play();
		void Stop();
		void Pause();
		State GetState() const { return state; }

		// �A�j���[�V�����̎w��Ǝ擾
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

		std::vector<GltfMaterialPtr> materials;		// �ŗL�}�e���A��
		GltfFileBufferPtr fileBuffer;
		GltfFilePtr file;							// �`��Ɏg��glTF�t�@�C��
		float time = 0;								// ���݂̍Đ�����
		float animationSpeed = 1;
		bool isLoop = true;

	private:

		std::vector<GltfFileBuffer::Range> ssboRanges;
		State state = State::stop;	// �Đ����
		GltfAnimationPtr animation;	// �Đ�����A�j���[�V����
	};
	using GltfAnimatedMeshRendererPtr = std::shared_ptr<GltfAnimatedMeshRenderer>;
}
#endif // !COMPONENT_GLTFANIMATIONMESHRENDERER_H_INCLUDED
