/**
* @file MapBufferObject.h
*/
#ifndef MAPBUFFEROBJECT_H_INCLUDED
#define MAPBUFFEROBJECT_H_INCLUDED
#include "glad/glad.h"
#include <memory>

class MappedBufferObject;
using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

/**
* バッファオブジェクト(マップあり)
*/
class MappedBufferObject
{
public:

	// コンストラクタ・デストラクタ
	MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access);
	~MappedBufferObject();

	static MappedBufferObjectPtr Create(GLsizeiptr size, GLenum type, GLenum access);

	// 管理番号を取得する
	operator GLuint() const { return id; }
	GLsizeiptr GetSize() const { return bufferSize; }

	void WaitSync();
	uint8_t* GetMappedAddress()const;
	void Bind(GLuint index, size_t offset, size_t size);
	void SwapBuffers();

private:

	GLuint id = 0;
	GLsizeiptr bufferSize = 0;

	uint8_t* p = nullptr;			// データコピー先アドレス
	size_t bufferIndex = 0;			// コピー先バッファのインデックス
	GLsync syncList[2] = { 0,0 };	// 同期オブジェクト
	GLenum type = GL_ARRAY_BUFFER;	// バッファの種類

};

#endif // !MAPBUFFEROBJECT_H_INCLUDED
