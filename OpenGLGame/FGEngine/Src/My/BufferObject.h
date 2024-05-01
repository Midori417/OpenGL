/**
* @file BufferObject.h
*/
#ifndef BUFFEROBJECT_H_INCLUDED
#define BUFFEROBJECT_H_INCLUDED
#include "glad/glad.h"
#include <memory>

// 先行宣言
class BufferObject;
using BufferObjectPtr = std::shared_ptr<BufferObject>;

/**
* バッファオブジェクト(BO)
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

	// 管理番号の取得
	operator GLuint() const { return id; }

	// バッファサイズを取得
	GLsizeiptr GetSize() const { return bufferSize; }

private:

	GLuint id = 0;				// オブジェクト管理番号
	GLsizeiptr bufferSize = 0;	// バッファサイズ(バイト数)

};

#endif // !BUFFEROBJECT_H_INCLUDED
