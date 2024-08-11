/**
* @file SoundMnager.h
*/
#ifndef FGENGINE_SOUNDMANAGER_H_INCLUDED
#define FGENGINE_SOUNDMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/SystemFrd.h"

namespace FGEngine
{
	class AudioListner;
	using AudioListnerPtr = std::shared_ptr<AudioListner>;
	class AudioSource;
	namespace SoundSystem
	{
		/**
		* サウンド管理クラス
		*/
		class SoundManager : public Singleton<SoundManager>
		{
		public:

			friend Singleton<SoundManager>;
			friend MainSystem::EngineCore;
			friend AudioSource;

			// コンストラクタ・デストラクタ
			SoundManager() = default;
			virtual ~SoundManager() = default;

			/**
			* リスナーを設定
			*/
			void SetListner(const AudioListnerPtr audioListner);

			/**
			* リスナーを取得
			*/
			AudioListnerPtr GetListner() const;

			/**
			* マスターボリュームを設定
			*
			* @param volume 設定する音量
			*/
			void SetMasterVolume(float volume);

			/**
			* マスターボリュームを取得
			*
			* @return マスターボリューム
			*/
			float GetMasterVolume() const;

		private:

			/**
			* サウンドマネージャーを初期化
			*
			* @retval true	初期化成功
			* @retval false	初期化失敗
			*/
			int Inititalize();

			/**
			* サウンドマネージャーを更新
			*/
			void Update();

			/**
			* サウンドマネージャーを終了
			*/
			void Fainalize();

			int AudioIdAdd();

		private:

			// 現在のリスナー
			AudioListnerPtr audioListner;

			int audioIdList = -1;
		};
	}
}
#endif // !FGENGINE_SOUNDMANAGER_H_INCLUDED
