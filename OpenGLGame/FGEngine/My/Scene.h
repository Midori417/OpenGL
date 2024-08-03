/**
* @file Scene.h
*/
#ifndef FGENGINE_SCENE_H_INCLUDED
#define FGENGINE_SCENE_H_INCLUDED
#include "SystemFrd.h"
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

		protected:

			/**
			* �V�[���̏�����
			*
			* @param engine �G���W��
			*
			* @retval true	����������
			* @retval false	���������s
			*/
			virtual bool Initialize()
			{
				return true;
			}

			/**
			* �V�[���̍X�V
			*
			* @param engine �G���W��
			*/
			virtual void Update() {}

			/**
			* �V�[���̏I��
			*
			* @param engine �G���W��
			*/
			virtual void Finalize() {}


		public:

			// �X�J�C�X�t�B�A�p�̃}�e���A��
			MaterialPtr skyMaterial;

		};
		using ScenePtr = std::shared_ptr<Scene>;
	}
}
#endif // !SCENEH_INCLUDED
