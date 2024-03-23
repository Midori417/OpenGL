/**
* @file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "EngineSystemFrd.h"
#include <memory>
#include <string>

namespace FGEngine
{
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace SceneSystem
	{
		/**
		* �V�[���̊��N���X
		*/
		class Scene
		{
		public:

			friend SceneManager;

			// �R���X�g���N�^�E�f�X�g���N�^
			Scene() = default;
			virtual ~Scene() = default;

			/**
			* �X�J�C�X�t�B�A�}�e���A��ݒ�
			*
			* @param skyMaterial �ݒ肷��}�e���A��
			*/
			void SetSkyMaterial(MaterialPtr material)
			{
				skyMaterial = material;
			}

			/**
			* �X�J�C�X�t�B�A���擾����
			* 
			* @return �V�[���ɐݒ肳��Ă���}�e���A��
			*/
			MaterialPtr GetSkyMaterial() const
			{
				return skyMaterial;
			}


		protected:

			/**
			* �V�[���̏�����
			*
			* @param engine �G���W��
			*
			* @retval true	����������
			* @retval false	���������s
			*/
			virtual bool Initialize(Engine& engine)
			{
				return true;
			}

			/**
			* �V�[���̍X�V
			*
			* @param engine �G���W��
			*/
			virtual void Update(Engine& engine) {}

			/**
			* �V�[���̏I��
			*
			* @param engine �G���W��
			*/
			virtual void Finalize(Engine& engine) {}


		private:

			MaterialPtr skyMaterial;	// �X�J�C�X�t�B�A�p�̃}�e���A��

		};
		using ScenePtr = std::shared_ptr<Scene>;
	}
}
#endif // !SCENEH_INCLUDED
