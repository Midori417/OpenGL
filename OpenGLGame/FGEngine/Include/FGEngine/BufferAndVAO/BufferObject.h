/**
* @file BufferObject.h
*/
#ifndef FGENGINE_BUFFEROBJECT_H_INCLUDED
#define FGENGINE_BUFFEROBJECT_H_INCLUDED
#include "BufferAndVAOFrd.h"
#include "FGEngine/Package/Glad.h"

namespace FGEngine
{
	/**
	* バッファオブジェクト(BO)
	* 
	* GPUにアクセスするためのメモリ領域
	*/
	class BufferObject
	{
	public:	// コンストラクタ・デストラクタ

		/**
		* コンストラクタ
		*
		* @param size	バッファオブジェクトのバイトサイズ
		* @param data	バッファにコピーするデータのアドレス
		*				nullptrを指定すると空のバッファが作成される
		* @param flags	用途を示すビットフラグの論理和(glBufferStorageを参照)
		*/
		explicit BufferObject(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);

		/**
		* デストラクタ
		*/
		~BufferObject();

	public:	// 禁止事項

		// コピーを禁止
		BufferObject(const BufferObject&) = delete;

		// 代入を禁止
		BufferObject& operator=(const BufferObject&) = delete;

	public:

		/**
		* バッファオブジェクトを作成する
		*
		* @param size	バッファオブジェクトのバイトサイズ
		* @param data	バッファにコピーするデータのアドレス
		*				nullptrを指定すると空のバッファが作成される
		* @param flags	用途を示すビットフラグの論理和(glBufferStorageを参照)
		*
		* @return 作成したバッファオブジェクトポインター
		*/
		static BufferObjectPtr Create(GLsizeiptr size, const void* data = nullptr, GLbitfield flags = 0);

	public:

		/**
		* 管理番号の取得
		*/
		operator GLuint() const;

		/**
		* バッファサイズを取得
		*/
		GLsizeiptr GetSize() const;

	private:

		// オブジェクト管理番号
		GLuint id = 0;				

		// バッファサイズ(バイト数)
		GLsizeiptr bufferSize = 0;

	};
}
#endif // !BUFFEROBJECT_H_INCLUDED
