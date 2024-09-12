/**
* @file RenderingEngine.h
*/
#ifndef FGENGINE_RENDERINGENGINE_H_INCLUDED
#define FGENGINE_RENDERINGENGINE_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/Rendering/LightData.h"
#include "FGEngine/BufferAndVAO/FrameBufferObject.h"

namespace FGEngine
{
	class GltfFileBuffer;
	/**
	* �`��G���W��
	*/
	class RenderingEngine : public Singleton<RenderingEngine>
	{
		friend Singleton<RenderingEngine>;
		friend class EngineCore;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		RenderingEngine() = default;

	private:		// EngineCore�ŌĂяo��

		/**
		* �����_�����O�G���W����������
		*
		* @retval 0		����������
		* @retval 0�ȊO	���������s
		*/
		int Initialize();

		/**
		* �����_�����O�G���W�����X�V
		*/
		void Update();

	private:

		/**
		* 3D�I�u�W�F�N�g�̕`��
		*
		* @param �����_�[�R���|�[�l���g�͈͂̐�[
		* @param �����_�[�R���|�[�l���g�͈͂̏I�[
		*/
		void Draw3DGameObject(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end);

		/**
		* �J�����ɋ߂����C�g��I���GPU�������[�ɃR�s�[����
		*/
		void UpdateShaderLight(const CameraPtr& camera);

		/**
		* �f�v�X�V���h�E�}�b�v�̍쐬
		*/
		void CreateShadowMap(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end);

		/**
		* �X�J�C�X�t�B�A��`��
		*/
		void DrawSkySphere(const CameraPtr& camera);

	public:

		/**
		* �Q�[���I�u�W�F�N�g�̕`��
		*
		* @param �����_�[�R���|�[�l���g�͈͂̐�[
		* @param �����_�[�R���|�[�l���g�͈͂̏I�[
		*/
		void DrawGameObject(std::vector<RendererPtr> rendererList, const CameraPtr& camera);

	private:

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

		// �f�v�X�V���h�E�pFBO
		FrameBufferObjectPtr fboShadow;

		// glTF�t�@�C���o�b�t�@
		GltfFileBuffer* glTFfileBuffer;
	};
}

#endif // !FGENGINE_RENDERINGENGINE_H_INCLUDED
