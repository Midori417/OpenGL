/**
* @file BufferAndVAOFrd.h
*/
#ifndef FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
#define FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
#include <memory>

// gladの先行宣言
typedef unsigned int GLuint;
typedef int GLint;
typedef unsigned int GLenum;

/**
* BufferAndVAOの先行宣言
*/
namespace FGEngine
{
	// バッファオブジェクト
	class BufferObject;
	// バッファオブジェクトポインター
	using BufferObjectPtr = std::shared_ptr<BufferObject>;

	// フレームバッファオブジェクト
	class FrameBufferObject;
	// フレームバッファオブジェクトポインター
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;

	// マップバッファオブジェクト
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

	// 頂点配列オブジェクト
	class VertexArrayObject;
	// 頂点配列オブジェクトポインター
	using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;
}

#endif // !FGENGINE_BUFFERANDVAOFRD_H_INCLUDED
