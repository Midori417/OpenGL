/**
* @file GraphicsEngine.h
*/
#ifndef FGENGINE_GRAPHICSENGINE_H_INCLUDED
#define FGENGINE_GRAPHICSENGINE_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include "LightData.h"
#include "GameObject.h"
#include "VertexArrayObject.h"

namespace FGEngine
{

	namespace Rendering
	{
		class MeshBuffer;
		using MeshBufferPtr = std::shared_ptr<MeshBuffer>;
	}
	namespace GraphicsSystem
	{
		/**
		* �`��G���W��
		*/
		class GraphicsEngine : Singleton<GraphicsEngine>
		{
		private:

			friend MainSystem::EngineCore;
			friend Singleton<GraphicsEngine>;

			GraphicsEngine() = default;

			/**
			* �O���t�B�b�N�G���W����������
			*
			* @retval 0		����������
			* @retval 0�ȊO	���������s
			*/
			int Initialize();

			/**
			* �O���t�B�b�N�G���W�����X�V
			*/
			void Update();

			/**
			* �O���t�B�b�N�G���W�����I��
			*/
			void Fainalize();

			/**
			* �Q�[���I�u�W�F�N�g��`�悷��
			*
			* @param begin	�I�u�W�F�N�g�`��J�n�ʒu
			* @param end	�I�u�W�F�N�g�`��I���ʒu
			*/
			void DrawGameObject(GameObjectList::iterator begin, GameObjectList::iterator end);

			/**
			* ���C�g�z�������������
			*/
			void InitializeLight(GameObjectList::iterator begin, GameObjectList::iterator end);

			/**
			* �X�J�C�X�t�B�A��`�悷��
			*/
			void DrawSkySphere();

			/**
			* �f�v�X�V���h�E��`�悷��
			*
			* @param begin	�I�u�W�F�N�g�`��J�n�ʒu
			* @param end	�I�u�W�F�N�g�`��I���ʒu
			*/
			void ShadowMap(GameObjectList::iterator begin, GameObjectList::iterator end);

		public:


			/**
			* �V�������C�g���擾����
			*
			* @return �V�������C�g�̗v�f�ԍ�
			*/
			int AllocateLight();

			/**
			* ���C�g���J������
			*
			* @param index �������v�f�ԍ�
			*/
			void DeallocateLight(int index);

			/**
			* �C���f�b�N�X�ɑΉ����郉�C�g�f�[�^���擾����
			*
			* @param index �擾����v�f�ԍ�
			*/
			LightData* GetLight(int index);
			const LightData* GetLight(int index) const;

		private:

			// ���b�V���o�b�t�@
			Rendering::MeshBufferPtr meshBuffer;
		};
	}
}
#endif // !FGENGINE_GRAPHICSENGINE_H_INCLUDED
