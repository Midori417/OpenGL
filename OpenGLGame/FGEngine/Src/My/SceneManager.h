/**
* @file SceneManager.h
*/
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Scene.h"
#include <unordered_map>

namespace FGEngine
{
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace SceneSystem
	{
		/**
		* �V�[�����Ǘ�����N���X
		*/
		class SceneManager : public Singleton<SceneManager>
		{
		private:
			
			friend Singleton<SceneManager>;
			friend class EngineCore;

			// �R���X�g���N�^
			SceneManager() = default;

			/**
			* �V�[���}�l�[�W���[�̏�����
			*
			* @retval 0		����������
			* @retval 0�ȊO	���������s
			*/
			int Initialize();

			/**
			* �V�[���}�l�[�W���[�̍X�V
			*/
			void Update();

		public:

			/**
			* �V�[����o�^����
			*
			* @parma name �o�^����V�[���̖��O
			*/
			template<typename T>
			static void AddScene(const std::string& name)
			{
				auto scenePtr = std::make_shared<T>();
				scenes.emplace(name, scenePtr);
			}

			/**
			* �V�[�������[�h����
			*
			* @param name ���[�h����V�[���̖��O
			*/
			static void LoadScene(const std::string& name);

			/**
			* ���݂̃V�[�����擾
			*/
			ScenePtr CurrentScene() const
			{
				return scene;
			}


		public:

			// ���̃V�[����ݒ肷��
			template<typename T>
			static void SetNextScene()
			{
				nextScene = std::make_shared<T>();
			}

		private:

			ScenePtr scene;				// ���s���̃V�[��
			static ScenePtr nextScene;	// ���̃V�[��
			static std::unordered_map<std::string, ScenePtr> scenes;	// �V�[���Ǘ��z��

		};
	}
}

#endif // !SCENEMANAGER_H_INCLUDED