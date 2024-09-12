/**
* @file SceneManager.h
*/
#ifndef FGENGINE_SCENEMANAGER_H_INCLUDED
#define FGENGINE_SCENEMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "Scene.h"
#include <unordered_map>

namespace FGEngine
{
	/**
	* �V�[�����Ǘ�����N���X
	*/
	class SceneManager : public Singleton<SceneManager>
	{
		friend Singleton<SceneManager>;
		friend class EngineCore;
	private:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		SceneManager() = default;

	private:

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
			// ���O����������
			auto tmp = scenes.find(name);
			if (tmp != scenes.end())
			{
				// ���ɑ��݂��Ă���
				return;
			}

			// �V�[�����쐬
			ScenePtr p = std::make_shared<T>();
			p->name = name;

			// �ŏ��̃V�[�����ݒ肳��Ă��Ȃ���ΐݒ肷��
			if (!nextScene)
			{
				nextScene = p;
			}
			
			// �V�[���z��ɒǉ�
			scenes.emplace(name, p);
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

	private:

		// ���s���̃V�[��
		ScenePtr scene;

		// ���̃V�[��
		static ScenePtr nextScene;

		// �V�[���Ǘ��z��
		static std::unordered_map<std::string, ScenePtr> scenes;

	};
}

#endif // !SCENEMANAGER_H_INCLUDED