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

// ��s�錾
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine
{

	// ��s�錾
	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr <FrameBufferObject>;
	class ProgramObject;
	using ProgramObjectPtr = std::shared_ptr<ProgramObject>;

	struct GltfFile;
	using GltfFilePtr = std::shared_ptr<GltfFile>;
	class GltfFileBuffer;
	using GltfFileBufferPtr = std::shared_ptr<GltfFileBuffer>;

	// �V�F�[�_�Ŏg���郉�C�g�̐�
	constexpr size_t maxShaderLightCount = 16;

	// �V�F�[�_�̃��P�[�V�����ԍ�
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

	// �_����
	struct LightData
	{
		Vector3 color;			// �F
		float intensity;	// ���邳
		Vector3 position;		// �ʒu
		float radius;		// ���C�g���͂��ő唼�a

		// �X�|�b�g���C�g�p�̕ϐ�
		Vector3 direction;	// ���C�g�̌���
		float coneAngle;	// �X�|�b�g���C�g���Ƃ炷�p�x
		float falloffAngle;	// �X�|�b�g���C�g�̌����J�n�p�x
		bool used = false;	// �g�p�����ǂ���
	};

	// ���s����
	struct DirectionLight
	{
		Vector3 color = { 1.00f, 0.98f, 0.95f };	// �F
		float intensity = 5.0f;					// ���邳
		Vector3 direction = { 0.58f, -0.58f, 0.58f };	// ����
	};


	/**
	* �Q�[���G���W��
	*/
	class Engine : public Singleton<Engine>
	{
	private:

		friend Singleton<Engine>;

		// �R���X�g���N�^
		Engine() = default;

	public:

		~Engine() = default;

		// �Q�[���G���W�������s
		int Run();

		/**
		* �Q�[���I�u�W�F�N�g���쐬����
		*
		* @param name		�I�u�W�F�N�g�̖��O
		* @param position	�I�u�W�F�N�g�̈ʒu
		* @param rotation	�I�u�W�F�N�g�̉�]
		*
		* @return �쐬�����Q�[���I�u�W�F�N�g�|�C���^�[
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
		* �J�����I�u�W�F�N�g���쐬����
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

		// ���ׂẴQ�[���I�u�W�F�N�g���폜����
		void AllClearGameObject();

		// �J�������擾
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
		* ���C���J������ݒ肷��
		*
		* nullptr���ƃJ�������O����
		*/
		inline void SetMainCamera(GameObjectPtr newCamera) {
			camera = newCamera;
		}

		// ���C�g�z�������������
		void InitialzeLight();
		// �V�������C�g���擾����
		int AllocateLight();
		// ���C�g���J������
		void DeallocateLight(int index);
		// �C���f�b�N�X�ɑΉ����郉�C�g�f�[�^���擾����
		LightData* GetLight(int index);
		const LightData* GetLight(int index) const;

		// �t���[���o�b�t�@�̑傫�����擾����
		Vector2 GetFramebufferSize() const;

		// �t���[���o�b�t�@�̃A�X�y�N�g����擾����
		float GetAspectRatio() const;


		/**
		* �X�^�e�B�b�N���b�V���̎擾
		*
		* @param name ���b�V����
		*
		* @return ���O��name�ƈ�v����X�^�e�B�b�N���b�V��
		*/
		StaticMeshPtr GetStaticMesh(const char* name) {
			return meshBuffer->GetStaticMesh(name);
		}
		GltfFilePtr LoadGltf(const char* filename);

		StaticMeshPtr LoadObj(const char* filename)
		{
			return meshBuffer->LoadObj(filename);
		}

		// �e�N�X�`���̎擾
		TexturePtr GetTexture(const char* name, Texture::Usage usage = Texture::Usage::for3D);

		GltfFileBufferPtr GetGltfFileBuffer() const { return gltfFileBuffer; }

	private:

		// ���[���h���W�n�̃R���C�_�[
		struct WorldCollder
		{
			// ���W��ύX����
			void AddPosition(const Vector3& v) {
				origin->transform->position += v;
				world->AddPosition(v);
			}

			ColliderPtr origin;
			ColliderPtr world;
		};
		using WorldCollderList = std::vector<WorldCollder>;

		// �Q�[���G���W����������
		int Initialize();
		// �Q�[���G���W�����X�V
		void Update();
		// �G���W���̏I��
		void Fainalize();

		// �Q�[���G���W���̏�Ԃ�`�悷��
		void Render();
		// �Q�[���I�u�W�F�N�g��`�悷��
		void DrawGameObject(const ProgramObject& prog, GameObjectList::iterator begin, GameObjectList::iterator end);
		// �Q�[���I�u�W�F�N�g���X�V����
		void UpdateGameObject();
		// �Q�[���I�u�W�F�N�g�̏Փ˂���������
		void HandleGameObjectCollision();
		// �ђʃx�N�g�����Q�[���I�u�W�F�N�g�ɔ��f����
		void ApplyPenetration(WorldCollderList*, GameObject*, const Vector3&);
		// �R���C�_�[�P�ʂ̏Փ˔���
		void HandleWorldColliderCollision(WorldCollderList* a, WorldCollderList* b);
		// �j���\��̃Q�[���I�u�W�F�N�g���폜����
		void RemoveDestroyedGameObject();
		// �J�����ɋ߂����C�g��I���GPU�������ɃR�s�[����
		void UpdateShaderLight();
		// �X�J�C�X�t�B�A��`�悷��
		void DrawSkySphere();
		// �f�v�X�V���h�E�}�b�v���쐬
		void CreateShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end);

	private:

		// �E�B���h�E
		GLFWwindow* window = nullptr;	// �E�B���h�E�I�u�W�F�N�g
		const std::string title = "OpenGLGame";	// �E�B���h�E�^�C�g��

		// �A�v���P�[�V�����|�C���^�[
		ApplicationPtr application;

		// �V�[���}�l�[�W���[�|�C���^�[
		SceneSystem::SceneManagerPtr sceneManager;

		/// �V�F�[�_�[�Ǘ��p�����o�[�ϐ�
		ProgramObjectPtr prog3D;		// ���C�g�t���V�F�[�_�[
		ProgramObjectPtr progUnlit;		// ���C�g�����V�F�[�_�[
		ProgramObjectPtr progShadow;	// �e�t���e�N�X�`���쐬�V�F�[�_�[
		ProgramObjectPtr progSkeletal3D;
		ProgramObjectPtr progShadowSkeletal3D;

		// 3D���f���̉e�`��p�̕ϐ�
		FrameBufferObjectPtr fboShadow;	// �f�v�X�V���h�E�pFBO

		MeshBufferPtr meshBuffer;		// �}�`�f�[�^�Ǘ��I�u�W�F�N�g
		GltfFileBufferPtr gltfFileBuffer;
		GLsizei indexCount = 0;			// �C���f�b�N�X�̃T�C�Y

		// �R���X�g���N�^�A�f�X�g���N�^���Ăׂ�悤�ɂ��邽�߂̕⏕�N���X
		struct TexHelper : public Texture {
			TexHelper(const char* p, Usage usage = Usage::for3D) : Texture(p, usage) {}
			TexHelper(const char* p, int w, int h, GLenum f) :Texture(p, w, h, f) {}
		};
		std::unordered_map<std::string, TexturePtr> textureCache;

		// ����
		std::vector<LightData> lights; // ���C�g�f�[�^�̔z��
		std::vector<int> usedLights;		// �g�p���̃��C�g�̃C���f�b�N�X�z��
		std::vector<int> freeLights;		// ���g�p�̃��C�g�C���f�b�N�X�z��

		// ��x�ɑ��₷���C�g��
		static constexpr size_t lightResizeCount = 100;

		// ���s����
		DirectionLight directionLight;

		// ����
		Vector3 ambientLight = Vector3(0.05f, 0.15f, 0.25f);

		// �X�J�C�X�t�B�A�p���f��
		StaticMeshPtr skySphere;

		// �Q�[���I�u�W�F�N�g
		GameObjectList gameObjects; // �Q�[���I�u�W�F�N�g�z��
		GameObjectPtr camera = nullptr;			// �J�����I�u�W�F�N�g
	};
}
#endif // !ENGINE_H_INCLUDED
