/**
* @file BufferObject.cpp
*/
#include "BufferObject.h"
#include "Debug.h"

namespace FGEngine::Rendering::Rall
{

	/**
	* コンストラクタ
	*
	* @param size	バッファオブジェクトのバイトサイズ
	* @param data	バッファにコピーするデータのアドレス
	*				nullptrを指定すると空のバッファが作成される
	* @param flags	用途を示すビットフラグの論理和(glBufferStorageを参照)
	*
	*/
	BufferObject::BufferObject(GLsizeiptr size, const void* data, GLbitfield flags)
		:bufferSize(size)
	{
		glCreateBuffers(1, &id);
		glNamedBufferStorage(id, bufferSize, data, flags);
	}

	/**
	* デストラクタ
	*/
	BufferObject::~BufferObject()
	{
		glDeleteBuffers(1, &id);
	}

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
	BufferObjectPtr BufferObject::Create(GLsizeiptr size, const void* data, GLbitfield flags)
	{
		return std::make_shared<BufferObject>(size, data, flags);
	}
}