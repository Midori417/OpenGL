/**
* @file RenderingEngine.h
*/
#ifndef FGENGINE_RENDERINGENGINE_H_INCLUDED
#define FGENGINE_RENDERINGENGINE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "GameObject.h"
#include "LightData.h"
#include "Mesh.h"

namespace FGEngine::RenderingSystem
{
	/**
	* �`��G���W��
	*/
	class RenderingEngine : public Singleton<RenderingEngine>
	{
	private:

		friend Singleton<RenderingEngine>;
		friend MainSystem::EngineCore;

		RenderingEngine() = default;

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

		/**
		* 3D�I�u�W�F�N�g�̕`��
		*
		* @param �����_�[�R���|�[�l���g�͈͂̐�[
		* @param �����_�[�R���|�[�l���g�͈͂̏I�[
		*/
		void Draw3DGameObject(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end);

		/**
		* �X�J�C�X�t�B�A��`��
		*/
		void DrawSkySphere();

	public:

		/**
		* �Q�[���I�u�W�F�N�g�̕`��
		*
		* @param �����_�[�R���|�[�l���g�͈͂̐�[
		* @param �����_�[�R���|�[�l���g�͈͂̏I�[
		*/
		void DrawGameObject(std::vector<RendererPtr> rendererList);

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


	};
}

#endif // !FGENGINE_RENDERINGENGINE_H_INCLUDED