/**
* @file BufferObject.h
*/
#ifndef FGENGINE_BUFFEROBJECT_H_INCLUDED
#define FGENGINE_BUFFEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include <memory>

namespace FGEngine::RenderingSystem
{
	// 先行宣言
	class BufferObject;
	using BufferObjectPtr = std::shared_ptr<BufferObject>;

	/**
	* バッファオブジェクト(BO)
	* 
	* GPUにアクセスするためのメモリ領域
	*/
	class BufferObject
	{
	public:

		// コンストラクタ・デストラクタ
		explicit BufferObject(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);
		~BufferObject();

		/**
		* バッファオブジェクトを作成する
		*
		* @param size	バッファオブジェクトのバイトサイズ
		* @param data	バッファにコピーするデータのアドレス
		*				nullptrを指定すると空のバッファが作成される
		* @param flags	用途を示すビットフラグの論理和(glBufferStorageを参照)
		*
		* @return 作成したバッファオブジェクトのポインター
		*/
		static BufferObjectPtr Create(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);

		// コピーと代入を禁止
		BufferObject(const BufferObject&) = delete;
		BufferObject& operator=(const BufferObject&) = delete;

		/**
		* バッファオブジェクトの管理番号の取得
		*/
		operator GLuint() const 
		{
			return id;
		}

		/**
		* バッファサイズを取得
		*/
		GLsizeiptr GetSize() const
		{ 
			return bufferSize;
		}

	private:

		// オブジェクト管理番号
		GLuint id = 0;				

		// バッファサイズ(バイト数)
		GLsizeiptr bufferSize = 0;

	};
}
#endif // !BUFFEROBJECT_H_INCLUDED
