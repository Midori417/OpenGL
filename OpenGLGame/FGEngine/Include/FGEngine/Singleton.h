/**
* @file Singleton.h
*/
#ifndef FGENGINE_SINGLETON_H_INCLUDED
#define FGENGINE_SINGLETON_H_INCLUDED
#include <memory>

namespace FGEngine
{
	/**
	* シングルトン基底クラス
	*/
	template <typename T>
	class Singleton
	{
	protected:

		/**
		* デフォルトコンストラクタ
		*/
		Singleton() = default;

	public:

		/**
		* デフォルトデストラクタ
		*/
		virtual ~Singleton() = default;

		// コピーと代入を禁止
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

	public:

		/**
		* 自身のインスタンスを取得する
		* なければ作成する
		* 
		* @return 自身のインスタンス
		*/
		static std::shared_ptr<T> GetInstance()
		{
			auto ptr = instance.lock();
			if (!ptr)
			{
				ptr = std::shared_ptr<T>(new T{});
				instance = std::weak_ptr<T>(ptr);
			}
			return instance.lock();
		}

	private:

		// 自身のインスタンス
		static std::weak_ptr<T> instance;
	};

	// スタティック変数を初期化
	template <typename T>
	inline std::weak_ptr<T> Singleton<T>::instance;
}

#endif // !SINGLETON_H_INCLUDED
