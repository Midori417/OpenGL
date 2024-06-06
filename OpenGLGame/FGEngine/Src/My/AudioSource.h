/**
* @file AudioSource.h
*/
#ifndef FGENGINE_AUDIOSOURCE_H_INCLUDED
#define FGENGINE_AUDIOSOURCE_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* サウンドを鳴らす
	*/
	class AudioSource : public Component
	{
	public:

		friend GameObject;
		friend ObjectSystem::ObjectManager;

		// コンストラクタ・デストラクタ
		AudioSource() = default;
		virtual ~AudioSource() = default;

		/**
		* オーディオIDを設定
		*/
		void SetAudioId(int id);

		/**
		* サウンドを再生
		*/
		void Play();

		/**
		* サウンドを停止
		*/
		void Stop();

		/**
		* サウンドを一時停止
		*/
		void Pause();
		
		/**
		* サウンドを再開(一時停止を解除)
		*/
		void Resume(); 

		/**
		* サウンドを単発再生
		* 
		* @param filename 再生するサウンドのファイル
		*/
		void PlayOneShot(const char* filename);

		/**
		* サウンドファイル名を設定
		*/
		void SetSoundFilename(const std::string& filename);
		void SetSoundFilename(const char* filename);

		// 音量の設定・取得
		void SetVolume(float volume);
		float GetVolume();

		// ピッチの設定・取得
		void SetPitch(float pitch);
		float GetPitch();

		// パンの設定・取得
		void SetPan(float pan);
		float GetPan();

	private:

		void Awake();

		/**
		* 立体音響用の更新
		*/
		void Set3DSoundPos();

	private:

		// サウンドのファイル名
		std::string filename = "NoFile";


		int id = -1;

		// 音量
		float volume = 1;
		
		// ピッチ
		float picth = 1;
		
		// パン
		float pan = 0;

	public:

		// 立体音響の影響を受けるか
		bool is3DSound = false;

		// ループ再生をするかtrue=ループ再生:false=ループ再生しない
		bool isLooop = true;
	};
}
#endif // !FGENGINE_AUDIOSOURCE_H_INCLUDED
